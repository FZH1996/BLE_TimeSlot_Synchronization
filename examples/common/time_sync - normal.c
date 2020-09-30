/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "time_sync.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "boards.h"

#include "app_error.h"
#include "app_util_platform.h"
#include "nrf.h"
#include "nrf_atomic.h"
#include "nrf_balloc.h"
#include "nrf_error.h"
#include "nrf_soc.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdm.h"

#define NRF_LOG_MODULE_NAME time_sync
#define NRF_LOG_LEVEL 4
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#if   defined ( __CC_ARM )
#define TX_CHAIN_DELAY_PRESCALER_0 (699 - 235)
#elif defined ( __ICCARM__ )
#define TX_CHAIN_DELAY_PRESCALER_0 (703 - 235)
#elif defined ( __GNUC__ )
#define TX_CHAIN_DELAY_PRESCALER_0 (704 - 235)
#endif

#define SYNC_TIMER_PRESCALER 0
#define SYNC_RTC_PRESCALER 0

#if SYNC_TIMER_PRESCALER == 0
#define TX_CHAIN_DELAY TX_CHAIN_DELAY_PRESCALER_0
#else
#error Invalid prescaler value
#endif

static void ts_on_sys_evt(uint32_t sys_evt, void * p_context);

NRF_SDH_SOC_OBSERVER(timesync_soc_obs,     \
                     TS_SOC_OBSERVER_PRIO, \
                     ts_on_sys_evt, 0);

#define TS_LEN_US                            (3000UL)   /**< The timeslot duration, the occupied time in radio of one packet is 540us. > */
#define TX_LEN_EXTENSION_US                  (1000UL)
#define TS_SAFETY_MARGIN_US                  (500UL)   /**< The timeslot activity should be finished with this much to spare. */
#define TS_EXTEND_MARGIN_US                  (700UL)   /**< The timeslot activity should request an extension this long before end of timeslot. */


#define MAIN_DEBUG                           0x12345678UL

static void ppi_sync_timer_adjust_configure(void);
static void ppi_sync_timer_adjust_enable(void);
static void ppi_sync_timer_adjust_disable(void);
static void ppi_radio_rx_disable(void);
static void ppi_radio_rx_configure(void);
static void ppi_radio_tx_configure(void);

typedef PACKED_STRUCT
{
    uint32_t  sequence;
    uint32_t  device_name;
    //int32_t  rtc_val;
    //uint32_t counter_val;
    int32_t  timer_val;
    bool pkt_received;
} sync_pkt_t;

NRF_BALLOC_DEF(m_sync_pkt_pool, sizeof(sync_pkt_t), 10);

static volatile bool     m_timeslot_session_open;
static volatile uint32_t m_blocked_cancelled_count;
static uint32_t          m_total_timeslot_length = 0;
static uint32_t          m_timeslot_distance = 0;
static ts_params_t       m_params;

static volatile bool m_send_sync_pkt = false;
static volatile bool m_timer_update_in_progress = false;
static volatile bool m_radio_received = false;
static volatile bool peer_radio_received = true;

static volatile uint32_t m_master_counter = 0;
static volatile uint32_t m_rcv_count      = 0;
static volatile uint32_t m_slot_sequence  = 0;
static volatile uint32_t m_device_num     = 3;
static volatile uint8_t m_period          = 0;
static volatile sync_pkt_t * mp_curr_adj_pkt;
static prng_t m_adv_prng;

#define SEND_TIMESLOT         (2)  
uint8_t send_timeslot = SEND_TIMESLOT;
#define COMPENSATE_TIMESLOT   (1)
#define END_TIMESLOT          (8)

#define STORAGE               (4)
static volatile int32_t timer_offset[STORAGE] = {0};
static volatile uint8_t cur_point = 0;
static volatile float skew = 1.0;                 //estimated skew of clock
static volatile float relative_skew = 1.0;        //global consensus skew
static volatile uint32_t send_time_estimate = 0;  //compensate the skew
static volatile uint32_t pri_send_estimate = 0;
static volatile uint32_t receive_time_estimate = 0;  //compensate the skew
static volatile uint32_t received_time_update = 0;//compensated time in current timeslot
static volatile uint32_t pri_time_update = 0;      //compensated time in last timeslot
static volatile uint32_t cur_time_send = 0;       //real time of sending in current timeslot
static volatile uint32_t cur_time_receive = 0;    //real time of receiving in current timeslot
static volatile uint32_t pri_time_send = 0;       //real time of sending in last period
static volatile uint32_t pri_time_receive = 0;    //real time of receiving in last timeslot

static volatile enum
{
    RADIO_STATE_IDLE, /* Default state */
    RADIO_STATE_RX,   /* Waiting for packets */
    RADIO_STATE_TX    /* Trying to transmit packet */
} m_radio_state = RADIO_STATE_IDLE;

//static void sync_timer_consensus_compensate();
static bool sync_timer_record(sync_pkt_t * p_pkt);
static void timeslot_begin_handler(void);
static void timeslot_end_handler(void);

/**< This will be used when requesting the first timeslot or any time a timeslot is blocked or cancelled. */
static nrf_radio_request_t m_timeslot_req_earliest = {
        NRF_RADIO_REQ_TYPE_EARLIEST,
        .params.earliest = {
            NRF_RADIO_HFCLK_CFG_XTAL_GUARANTEED,  //自动开启外部晶振，因为射频发送需要开启外部高频时钟
            NRF_RADIO_PRIORITY_HIGH,
            TS_LEN_US,                            //length_us
            NRF_RADIO_EARLIEST_TIMEOUT_MAX_US     //timeout_us
        }};

/**< This will be used at the end of each timeslot to request the next timeslot. */
static nrf_radio_request_t m_timeslot_req_normal = {
        NRF_RADIO_REQ_TYPE_NORMAL,
        .params.normal = {
            NRF_RADIO_HFCLK_CFG_XTAL_GUARANTEED,
            NRF_RADIO_PRIORITY_HIGH,
            TS_LEN_US*2,                        //distance_us
            TS_LEN_US                           //length_us
        }};

/**< This will be used at the end of each timeslot to request the next timeslot. */
static nrf_radio_signal_callback_return_param_t m_rsc_return_sched_next_normal = {
        NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END,
        .params.request = {
                (nrf_radio_request_t*) &m_timeslot_req_normal
        }};

/**< This will be used at the end of each timeslot to request the next timeslot. */
static nrf_radio_signal_callback_return_param_t m_rsc_return_sched_next_earliest = {
        NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END,
        .params.request = {
                (nrf_radio_request_t*) &m_timeslot_req_earliest
        }};

/**< This will be used at the end of each timeslot to request an extension of the timeslot. */
static nrf_radio_signal_callback_return_param_t m_rsc_extend = {
        NRF_RADIO_SIGNAL_CALLBACK_ACTION_EXTEND,
        .params.extend = {TX_LEN_EXTENSION_US}
        };

/**< This will be used at the end of each timeslot to request the next timeslot. */
static nrf_radio_signal_callback_return_param_t m_rsc_return_no_action = {
        NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE,
        .params.request = {NULL}
        };
static volatile uint32_t time=0;
void RADIO_IRQHandler(void)
{
    if (NRF_RADIO->EVENTS_END != 0)
    {
        NRF_RADIO->EVENTS_END = 0;
        (void)NRF_RADIO->EVENTS_END;
        NRF_LOG_INFO("m_radio_state=0x%x\n",m_radio_state);
//        m_params.high_freq_timer[0]->TASKS_CAPTURE[5]=1;
//        time=m_params.high_freq_timer[0]->CC[5];
//        NRF_LOG_INFO("radio_events_end=%d\n",time);
        //NRF_LOG_INFO("m_radio_state=0x%x,CRCSTATUS=%x,CRCSTATUS_Msk=%x,choose=%x\n",m_radio_state,NRF_RADIO->CRCSTATUS,RADIO_CRCSTATUS_CRCSTATUS_Msk,RADIO_CRCSTATUS_CRCSTATUS_CRCOk << RADIO_CRCSTATUS_CRCSTATUS_Pos);
        if (m_radio_state == RADIO_STATE_RX && 
           (NRF_RADIO->CRCSTATUS & RADIO_CRCSTATUS_CRCSTATUS_Msk) == (RADIO_CRCSTATUS_CRCSTATUS_CRCOk << RADIO_CRCSTATUS_CRCSTATUS_Pos))
        {
            sync_pkt_t * p_pkt;
            bool         adjustment_procedure_started;

            p_pkt = (sync_pkt_t *) NRF_RADIO->PACKETPTR;
            NRF_LOG_INFO("p_pkt->device_name=0x%x,p_pkt->sequence=0x%x\n",p_pkt->device_name,p_pkt->sequence);

            //if(p_pkt->device_name <= 3)    //&& m_period != COMPENSATE_TIMESLOT
            adjustment_procedure_started = sync_timer_record(p_pkt);

            if (adjustment_procedure_started)
            {
                p_pkt = nrf_balloc_alloc(&m_sync_pkt_pool);
                APP_ERROR_CHECK_BOOL(p_pkt != 0);

                NRF_RADIO->PACKETPTR = (uint32_t) p_pkt;
                m_radio_received=true;
            }
            ++m_rcv_count;
            NRF_LOG_INFO("m_rcv_count=0x%x,m_radio_received=0x%x\n",m_rcv_count,m_radio_received);
        }

        NRF_RADIO->TASKS_START = 1;
    }
}

/**@brief   Function for handling timeslot events.
 */
static nrf_radio_signal_callback_return_param_t * radio_callback (uint8_t signal_type)  //sd_radio_session_open
{
    // NOTE: This callback runs at lower-stack priority (the highest priority possible).
    switch (signal_type) {
    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_START:
        m_params.high_freq_timer[0]->TASKS_CAPTURE[5]=1;
        time=m_params.high_freq_timer[0]->CC[5];
        NRF_LOG_INFO("start_time=%d\n",time);
        // TIMER0 is pre-configured for 1Mhz.
        NRF_TIMER0->TASKS_STOP          = 1;
        NRF_TIMER0->TASKS_CLEAR         = 1;
        NRF_TIMER0->MODE                = (TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos);
        NRF_TIMER0->EVENTS_COMPARE[0]   = 0;
        NRF_TIMER0->EVENTS_COMPARE[1]   = 0;

//        if (m_send_sync_pkt)
//        {
            NRF_TIMER0->INTENSET  = (TIMER_INTENSET_COMPARE0_Set << TIMER_INTENSET_COMPARE0_Pos);
//        }
//        else
//        {
//            NRF_TIMER0->INTENSET = (TIMER_INTENSET_COMPARE0_Set << TIMER_INTENSET_COMPARE0_Pos) |
//                                   (TIMER_INTENSET_COMPARE1_Set << TIMER_INTENSET_COMPARE1_Pos);
//        }
        
        //if (!m_send_sync_pkt)
        NRF_TIMER0->CC[0]               = (TS_LEN_US - TS_SAFETY_MARGIN_US);
        NRF_TIMER0->CC[1]               = (TS_LEN_US - TS_SAFETY_MARGIN_US)/2;
        //else
        //NRF_TIMER0->CC[0]               = (m_timeslot_distance - TS_SAFETY_MARGIN_US);
//        NRF_TIMER0->CC[1]               = (TS_LEN_US - TS_EXTEND_MARGIN_US);
        NRF_TIMER0->BITMODE             = (TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos);
        NRF_TIMER0->TASKS_START         = 1;
//        if(m_radio_state == RADIO_STATE_TX){
//            NRF_LOG_INFO("TX TASKS_START\n");
//        }
//        else if(m_radio_state == RADIO_STATE_RX){
//            NRF_LOG_INFO("RX TASKS_START\n");
//        }
//        NRF_LOG_INFO("RADIO start,%d\n",m_params.high_freq_timer[0]->CC[1]);

        NRF_RADIO->POWER                = (RADIO_POWER_POWER_Enabled << RADIO_POWER_POWER_Pos);

        NVIC_EnableIRQ(TIMER0_IRQn);

        m_total_timeslot_length = 0;
        ++m_period;
//        NRF_LOG_INFO("m_period_start=%d\n",m_period);

        timeslot_begin_handler();

        break;

    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_TIMER0:
        if (NRF_TIMER0->EVENTS_COMPARE[0] &&
           (NRF_TIMER0->INTENSET & (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENCLR_COMPARE0_Pos)))
        {
            NRF_TIMER0->TASKS_STOP  = 1;
            NRF_TIMER0->EVENTS_COMPARE[0] = 0;
            (void)NRF_TIMER0->EVENTS_COMPARE[0];
            NRF_TIMER0->EVENTS_COMPARE[1] = 0;
            (void)NRF_TIMER0->EVENTS_COMPARE[1];

            // This is the "timeslot is about to end" timeout
            //NRF_LOG_INFO("RADIO end,%d\n",m_params.high_freq_timer[0]->CC[1]);
            timeslot_end_handler();
          
            m_params.high_freq_timer[0]->TASKS_CAPTURE[5]=1;
            time=m_params.high_freq_timer[0]->CC[5];
            NRF_LOG_INFO("end_time=%d,CC[2]=%d\n",time,m_params.high_freq_timer[0]->CC[2]);
            
            // Schedule next timeslot
            if (m_send_sync_pkt)
            {
////                rand_prng_seed(&m_adv_prng);
////                uint32_t rand_offset=rand_prng_get(&m_adv_prng);
////                uint32_t m_distance = (m_timeslot_distance + rand_offset) % NRF_RADIO_DISTANCE_MAX_US;
//                uint32_t m_distance = m_total_timeslot_length + m_timeslot_distance;
//                m_timeslot_req_normal.params.normal.distance_us = m_timeslot_distance; //Distance from the start of the previous radio timeslot
//                m_timeslot_req_normal.params.normal.length_us = m_distance - TS_SAFETY_MARGIN_US;
////                NRF_LOG_INFO("rand_offset=%d,m_distance=%d\n",rand_offset,m_timeslot_distance);
////                NRF_LOG_INFO("distance_us=%d,length_us=%d\n",m_timeslot_req_normal.params.normal.distance_us,m_timeslot_req_normal.params.normal.length_us);
                //NRF_LOG_INFO("m_rsc_return_sched_next_normal\n");
                return (nrf_radio_signal_callback_return_param_t*) &m_rsc_return_sched_next_normal;
            }
            else
            {
                return (nrf_radio_signal_callback_return_param_t*) &m_rsc_return_sched_next_normal;
            }
        }
        

//        if (NRF_TIMER0->EVENTS_COMPARE[1] &&
//           (NRF_TIMER0->INTENSET & (TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENCLR_COMPARE1_Pos)))
//        {
//            NRF_TIMER0->EVENTS_COMPARE[1] = 0;
//            (void)NRF_TIMER0->EVENTS_COMPARE[1];
//
//            // This is the "try to extend timeslot" timeout
//
//            if (m_total_timeslot_length < (128000000UL - 5000UL - TX_LEN_EXTENSION_US) && !m_send_sync_pkt)
//            {
//                // Request timeslot extension if total length does not exceed 128 seconds 扩展时隙长度
//                return (nrf_radio_signal_callback_return_param_t*) &m_rsc_extend;
//            }
//            else if (!m_send_sync_pkt)
//              {
//                  // Don't do anything. Timeslot will end and new one requested upon the next timer0 compare.
//              }
//        }

    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_RADIO:
        RADIO_IRQHandler();
        //NRF_LOG_INFO("NRF_RADIO_CALLBACK_SIGNAL_TYPE_RADIO\n");
        break;

    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_FAILED:
        // Don't do anything. Our timer will expire before timeslot ends
        return (nrf_radio_signal_callback_return_param_t*) &m_rsc_return_no_action;

    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_SUCCEEDED:
        // Extension succeeded: update timer
        NRF_TIMER0->TASKS_STOP          = 1;
        NRF_TIMER0->EVENTS_COMPARE[0]   = 0;
        NRF_TIMER0->EVENTS_COMPARE[1]   = 0;
        NRF_TIMER0->CC[0]               += (TX_LEN_EXTENSION_US - 25);
        NRF_TIMER0->CC[1]               += (TX_LEN_EXTENSION_US - 25);
        NRF_TIMER0->TASKS_START         = 1;

        // Keep track of total length
        m_total_timeslot_length += TX_LEN_EXTENSION_US;
        //NRF_LOG_INFO("EXTEND_SUCCEEDED,\n");
        break;

    default:
        app_error_handler(MAIN_DEBUG, __LINE__, (const uint8_t*)__FILE__);
        NRF_LOG_INFO("app_error_handler\n");
        break;
    };

    // Fall-through return: return with no action request
    return (nrf_radio_signal_callback_return_param_t*) &m_rsc_return_no_action;
}

static void update_radio_parameters(sync_pkt_t * p_pkt)
{
    // TX power
    NRF_RADIO->TXPOWER  = RADIO_TXPOWER_TXPOWER_0dBm   << RADIO_TXPOWER_TXPOWER_Pos;

    // RF bitrate
    NRF_RADIO->MODE     = RADIO_MODE_MODE_Nrf_2Mbit       << RADIO_MODE_MODE_Pos;

    // Fast startup mode
    NRF_RADIO->MODECNF0 = RADIO_MODECNF0_RU_Fast << RADIO_MODECNF0_RU_Pos;

    // CRC configuration
    NRF_RADIO->CRCCNF  = RADIO_CRCCNF_LEN_Three << RADIO_CRCCNF_LEN_Pos;
    NRF_RADIO->CRCINIT = 0xFFFFFFUL;      // Initial value
    NRF_RADIO->CRCPOLY = 0x11021UL;     // CRC poly: x^16+x^12^x^5+1

    // Packet format
    NRF_RADIO->PCNF0 = (0 << RADIO_PCNF0_S0LEN_Pos) | (0 << RADIO_PCNF0_LFLEN_Pos) | (0 << RADIO_PCNF0_S1LEN_Pos);
    NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled     << RADIO_PCNF1_WHITEEN_Pos) |
                       (RADIO_PCNF1_ENDIAN_Big           << RADIO_PCNF1_ENDIAN_Pos)  |
                       (4                                << RADIO_PCNF1_BALEN_Pos)   |
                       (sizeof(sync_pkt_t)               << RADIO_PCNF1_STATLEN_Pos) |
                       (sizeof(sync_pkt_t)               << RADIO_PCNF1_MAXLEN_Pos);
    NRF_RADIO->PACKETPTR = (uint32_t) p_pkt;
    //Packet address to be used for the next transmission or reception. 
    //When transmitting, the packet pointed to by this address will be transmitted
    //and when receiving, the received packet will be written to this address.

    // Radio address config
    NRF_RADIO->PREFIX0 = m_params.rf_addr[0];
    NRF_RADIO->BASE0   = (m_params.rf_addr[1] << 24 | m_params.rf_addr[2] << 16 | m_params.rf_addr[3] << 8 | m_params.rf_addr[4]);

    NRF_RADIO->TXADDRESS   = 0; //use channal 0 to transmit.
    NRF_RADIO->RXADDRESSES = (1 << 0);  //use channel 1 to receive.

    NRF_RADIO->FREQUENCY = m_params.rf_chn; //Frequency = 2400 + FREQUENCY (MHz). ->125
    //channel -> 37:2402MHz, 38:2426MHz, 39:2480MHz
    NRF_RADIO->TXPOWER   = RADIO_TXPOWER_TXPOWER_Pos4dBm << RADIO_TXPOWER_TXPOWER_Pos;

    NRF_RADIO->EVENTS_END = 0;

    NRF_RADIO->INTENCLR = 0xFFFFFFFF;
    NRF_RADIO->INTENSET = RADIO_INTENSET_END_Msk;

    NVIC_EnableIRQ(RADIO_IRQn);
}

/**@brief IRQHandler used for execution context management.
  *        Any available handler can be used as we're not using the associated hardware.
  *        This handler is used to stop and disable UESB
  */
void timeslot_end_handler(void)
{
    NRF_RADIO->TASKS_DISABLE = 1;
    NRF_RADIO->INTENCLR      = 0xFFFFFFFF;

    ppi_radio_rx_disable();

    nrf_balloc_free(&m_sync_pkt_pool, (void*) NRF_RADIO->PACKETPTR);

    m_total_timeslot_length = 0;
    m_radio_state           = RADIO_STATE_IDLE;
    m_rcv_count = 0;    //only counting packets received in one timeslot.
    m_slot_sequence = 0;
    if (m_period==END_TIMESLOT)
    {
        m_period=0;
        send_timeslot=SEND_TIMESLOT;
        //timer_offset=0;
        //if(m_radio_received) m_radio_received=false;
    }
    
//    int32_t timer = 0;
//    if(m_radio_received)    //m_period==COMPENSATE_TIMESLOT && 
//    {
//        //sync_timer_consensus_compensate(); //compensate the offset
//        //m_radio_received=false;
////        timer_offset=0;
//        pri_time_update = received_time_update;
//        pri_time_receive = cur_time_receive;
//        timer = timer_offset[cur_point];
//    }
////    if (m_period==SEND_TIMESLOT && m_send_sync_pkt)
//        
//        pri_time_send = (cur_time_send-timer+TIME_SYNC_TIMER_MAX_VAL)%TIME_SYNC_TIMER_MAX_VAL;
//        pri_send_estimate = (send_time_estimate-timer+TIME_SYNC_TIMER_MAX_VAL)%TIME_SYNC_TIMER_MAX_VAL;
//
//    NRF_LOG_INFO("timeslot_end\n");
}

void send_configure(void)
{
uint32_t ppi_chn  = m_params.ppi_chns[0];
uint32_t ppi_chn1 = m_params.ppi_chns[1];
 
// Use PPI to create fixed offset between timer capture and packet transmission
// Compare event #0: Capture timer value for free running timer
// Compare event #1: Trigger radio transmission
 
NRF_PPI->CH[ppi_chn].EEP = (uint32_t) &m_params.high_freq_timer[1]->EVENTS_COMPARE[0];
NRF_PPI->CH[ppi_chn].TEP = (uint32_t) &m_params.high_freq_timer[0]->TASKS_CAPTURE[1];
NRF_PPI->CHENSET         = (1 << ppi_chn);
 
NRF_PPI->CH[ppi_chn1].EEP = (uint32_t) &m_params.high_freq_timer[1]->EVENTS_COMPARE[1];
NRF_PPI->CH[ppi_chn1].TEP = (uint32_t) &NRF_RADIO->TASKS_START;
NRF_PPI->CHENSET          = (1 << ppi_chn1);
 
m_params.high_freq_timer[1]->PRESCALER   = 4; // 1 us resolution
m_params.high_freq_timer[1]->MODE        = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
m_params.high_freq_timer[1]->SHORTS      = TIMER_SHORTS_COMPARE1_STOP_Msk | TIMER_SHORTS_COMPARE1_CLEAR_Msk;
m_params.high_freq_timer[1]->TASKS_STOP  = 1;
m_params.high_freq_timer[1]->TASKS_CLEAR = 1;
m_params.high_freq_timer[1]->CC[0]       = 40; // Matches 40 us radio rampup time
m_params.high_freq_timer[1]->CC[1]       = 50; // Margin for timer readout
 
m_params.high_freq_timer[1]->EVENTS_COMPARE[0] = 0;
m_params.high_freq_timer[1]->EVENTS_COMPARE[1] = 0;
 
//NRF_RADIO->SHORTS                        = RADIO_SHORTS_END_DISABLE_Msk;
//NRF_RADIO->TASKS_TXEN                    = 1;
m_params.high_freq_timer[1]->TASKS_START = 1;
 
while (m_params.high_freq_timer[1]->EVENTS_COMPARE[0] == 0)
{
    // Wait for timer to trigger
    __NOP();
}
 
//m_radio_state                                 = RADIO_STATE_TX;
//m_sync_pkt.timer_val                          = m_params.high_freq_timer[0]->CC[1];

}

void change_to_RX_state(void)
{
    while (NRF_RADIO->EVENTS_END == 0)
    {
        __NOP();  //wait RADIO to transmit packet
    }
    
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_DISABLE = 1;
    while(NRF_RADIO->EVENTS_DISABLED == 0){ __NOP(); }
    uint32_t time=0;
    m_params.high_freq_timer[0]->TASKS_CAPTURE[5]=1;
    time=m_params.high_freq_timer[0]->CC[5];
    NRF_LOG_INFO("TX to RX =%d\n",time);
    nrf_balloc_free(&m_sync_pkt_pool, (void*) NRF_RADIO->PACKETPTR);

    sync_pkt_t * p_pkt = nrf_balloc_alloc(&m_sync_pkt_pool);
    APP_ERROR_CHECK_BOOL(p_pkt != 0);
    update_radio_parameters(p_pkt);
    NRF_RADIO->SHORTS = RADIO_SHORTS_READY_START_Msk;
    NRF_RADIO->TASKS_RXEN = 1;
    ppi_radio_rx_configure();

    //while (NRF_RADIO->EVENTS_READY == 0)
    //{
    //    __NOP();
    //}

//    NRF_RADIO->TASKS_START = 1;
    m_radio_state = RADIO_STATE_RX;
}


/**@brief IRQHandler used for execution context management.
  *        Any available handler can be used as we're not using the associated hardware.
  *        This handler is used to initiate UESB RX/TX
  */
void timeslot_begin_handler(void)
{
    NRF_LOG_INFO("m_period=%d\n",m_period);
    sync_pkt_t * p_pkt;

    if (m_period==send_timeslot && m_send_sync_pkt)   //else if (m_period==SEND_TIMESLOT && m_send_sync_pkt)
    {
        if (m_radio_state == RADIO_STATE_RX)
        {
            NRF_RADIO->EVENTS_DISABLED = 0;
            NRF_RADIO->TASKS_DISABLE = 1;
            while (NRF_RADIO->EVENTS_DISABLED == 0)
            {
                __NOP();
            }
        }

        p_pkt = nrf_balloc_alloc(&m_sync_pkt_pool);
        APP_ERROR_CHECK_BOOL(p_pkt != 0);

        ppi_radio_tx_configure();
        update_radio_parameters(p_pkt);

//        uint8_t count=0;
//        while (count < 100)
//        {
//            __NOP();
//            count++;
//        }

        NRF_RADIO->SHORTS     = RADIO_SHORTS_END_DISABLE_Msk | RADIO_SHORTS_READY_START_Msk;
        NRF_RADIO->TASKS_TXEN = 1;

//        NRF_LOG_INFO("pri_time_send=%d,pri_send_estimate=%d,relative_skew=%d\n",pri_time_send,pri_send_estimate,relative_skew);

        while (NRF_RADIO->EVENTS_READY == 0)
        {
            // PPI is used to trigger sync timer capture when radio is ready
            // Radio will automatically start transmitting once ready, so the captured timer value must be copied into radio packet buffer ASAP
            __NOP();
        }
        NRF_RADIO->EVENTS_END = 0;

        cur_time_send = m_params.high_freq_timer[0]->CC[1];
        if (relative_skew == 1) send_time_estimate = cur_time_send;
        else send_time_estimate = ((int)((cur_time_send - pri_time_send + TIME_SYNC_TIMER_MAX_VAL*2)*1) + pri_send_estimate) % TIME_SYNC_TIMER_MAX_VAL;
        //send_time_estimate = cur_time_send;

        p_pkt->sequence    = ++m_slot_sequence;
        p_pkt->device_name = m_device_num;
        //p_pkt->rtc_val     = m_params.rtc->COUNTER;
        //p_pkt->counter_val = m_params.high_freq_timer[1]->CC[1]; 
        p_pkt->timer_val   = send_time_estimate;
        p_pkt->pkt_received = m_radio_received;

        m_radio_state = RADIO_STATE_TX; //Trying to transmit packet!!!!!
        
        NRF_LOG_INFO("clock_time=%d,estimate=%d\n",cur_time_send,send_time_estimate);
        
        if (m_radio_received)
        {
            m_radio_received=false;
        }
        
        if(peer_radio_received==false && send_timeslot<END_TIMESLOT)
        {
//            send_timeslot=(send_timeslot)%END_TIMESLOT+1;
            //send_timeslot = send_timeslot + 1;
        }
        //change_to_RX_state();
    }
    else
    {
        if (m_radio_state    != RADIO_STATE_RX ||
            NRF_RADIO->STATE != (RADIO_STATE_STATE_Rx << RADIO_STATE_STATE_Pos))
        {
            p_pkt = nrf_balloc_alloc(&m_sync_pkt_pool);
            APP_ERROR_CHECK_BOOL(p_pkt != 0);

            update_radio_parameters(p_pkt); //确保定时主机在实际传输数据包时以一致的时间增量捕获自由运行的定时器值

            NRF_RADIO->SHORTS     = RADIO_SHORTS_READY_START_Msk;
            NRF_RADIO->TASKS_RXEN = 1;

            ppi_radio_rx_configure();

            m_radio_state = RADIO_STATE_RX;
        }
    }

}


/**@brief Function for handling the Application's system events.
 *
 * @param[in]   sys_evt   system event.
 */
void ts_on_sys_evt(uint32_t sys_evt, void * p_context)
{
    switch(sys_evt)
    {
        case NRF_EVT_FLASH_OPERATION_SUCCESS:
        case NRF_EVT_FLASH_OPERATION_ERROR:
            break;
        case NRF_EVT_RADIO_BLOCKED:
        case NRF_EVT_RADIO_CANCELED:
        {
            // Blocked events are rescheduled with normal priority. They could also
            // be rescheduled with high priority if necessary.
            uint32_t err_code = sd_radio_request((nrf_radio_request_t*) &m_timeslot_req_earliest);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_INFO("NRF_EVT_RADIO_CANCELED\n");
            m_blocked_cancelled_count++;

            break;
        }
        case NRF_EVT_RADIO_SIGNAL_CALLBACK_INVALID_RETURN:
            NRF_LOG_ERROR("NRF_EVT_RADIO_SIGNAL_CALLBACK_INVALID_RETURN\r\n");
            app_error_handler(MAIN_DEBUG, __LINE__, (const uint8_t*)__FILE__);
            break;
        case NRF_EVT_RADIO_SESSION_CLOSED:
            {
                m_timeslot_session_open = false;

                NRF_LOG_INFO("NRF_EVT_RADIO_SESSION_CLOSED\r\n");
            }

            break;
        case NRF_EVT_RADIO_SESSION_IDLE:
        {
            NRF_LOG_INFO("NRF_EVT_RADIO_SESSION_IDLE\r\n");

            uint32_t err_code = sd_radio_session_close();
            APP_ERROR_CHECK(err_code);
            break;
        }
        default:
            // No implementation needed.
            NRF_LOG_INFO("Event: 0x%08x\r\n", sys_evt);
            break;
    }
}

static void timestamp_counter_start(void)
{
    // m_params.high_freq_timer[1] (NRF_TIMER) is used in counter mode to count the number of sync timer overflows/resets (m_params.high_freq_timer[0])
    // When timestamp API is used, the number of overflows/resets + current value of sync timer must be added up to give accurate timestamp information
    m_params.high_freq_timer[1]->TASKS_STOP  = 1;
    m_params.high_freq_timer[1]->TASKS_CLEAR = 1;
    m_params.high_freq_timer[1]->PRESCALER   = 0;
    m_params.high_freq_timer[1]->MODE        = TIMER_MODE_MODE_Counter << TIMER_MODE_MODE_Pos;;
    m_params.high_freq_timer[1]->BITMODE     = TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;
    m_params.high_freq_timer[1]->CC[2]       = 255;
    m_params.high_freq_timer[1]->SHORTS      = TIMER_SHORTS_COMPARE2_CLEAR_Msk;
    m_params.high_freq_timer[1]->TASKS_START = 1;
}

static void sync_timer_start(void)
{
    // m_params.high_freq_timer[0] (NRF_TIMER) is the always-running sync timer
    // The timing master never adjusts this timer
    // The timing slave(s) adjusts this timer whenever a sync packet is received and the logic determines that there is
    m_params.high_freq_timer[0]->TASKS_STOP  = 1;
    m_params.high_freq_timer[0]->TASKS_CLEAR = 1;
    m_params.high_freq_timer[0]->PRESCALER   = SYNC_TIMER_PRESCALER;
    m_params.high_freq_timer[0]->BITMODE     = TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;
    m_params.high_freq_timer[0]->CC[0]       = TIME_SYNC_TIMER_MAX_VAL;
    m_params.high_freq_timer[0]->CC[1]       = 0xFFFFFFFF;
    m_params.high_freq_timer[0]->CC[2]       = TIME_SYNC_TIMER_MAX_VAL;
    m_params.high_freq_timer[0]->CC[3]       = 0xFFFFFFFF;
    if (m_params.high_freq_timer[0] == NRF_TIMER3 || m_params.high_freq_timer[0] == NRF_TIMER4)
    {
        // TIMERS 0,1, and 2 only have 4 compare registers
        m_params.high_freq_timer[0]->CC[4]   = TIME_SYNC_TIMER_MAX_VAL / 2; // Only used for debugging purposes such as pin toggling
        m_params.high_freq_timer[0]->CC[5]   = 0xFFFFFFFF;
    }
    m_params.high_freq_timer[0]->SHORTS      = TIMER_SHORTS_COMPARE0_CLEAR_Msk; // | TIMER_SHORTS_COMPARE2_CLEAR_Msk
    //clear timer when compare0 or compare2 are triggered.
    m_params.high_freq_timer[0]->TASKS_START = 1;
}

void SWI3_EGU3_IRQHandler(void)
{
    if (NRF_EGU3->EVENTS_TRIGGERED[0] != 0)
    {
        NRF_EGU3->EVENTS_TRIGGERED[0] = 0;

        ppi_sync_timer_adjust_disable();

        //m_master_counter = mp_curr_adj_pkt->counter_val;
        NRF_LOG_INFO("counter=%d,CC[2]=%d\n",m_master_counter,m_params.high_freq_timer[0]->CC[2]);

        m_timer_update_in_progress = false;

        nrf_balloc_free(&m_sync_pkt_pool, (void*)mp_curr_adj_pkt);

//        pri_time_update = received_time_update;
//        pri_time_receive = cur_time_receive;
    }
}

void sync_timer_consensus_compensate()
{
    uint32_t offset = 0;
    uint8_t index = cur_point;
    int8_t skew_offset = 0;

        relative_skew = (received_time_update-pri_time_update + TIME_SYNC_TIMER_MAX_VAL_ori*2) / (cur_time_receive-pri_time_receive+TIME_SYNC_TIMER_MAX_VAL_ori*2);
        if (relative_skew>1) skew_offset=1;
        else if (relative_skew<1)  skew_offset=-1;
        TIME_SYNC_TIMER_MAX_VAL_ori = TIME_SYNC_TIMER_MAX_VAL - skew_offset;
        m_params.high_freq_timer[0]->TASKS_STOP = 1;
        m_params.high_freq_timer[0]->CC[0] = TIME_SYNC_TIMER_MAX_VAL - skew_offset;
        //m_params.high_freq_timer[0]->CC[4] = m_params.high_freq_timer[0]->CC[0] / 2;
        m_params.high_freq_timer[0]->TASKS_START = 1;
      
      offset = (timer_offset[index] + TIME_SYNC_TIMER_MAX_VAL) % TIME_SYNC_TIMER_MAX_VAL;

    // Write offset to timer compare register
    if (offset > TIME_SYNC_TIMER_MAX_VAL)
    {
        m_params.high_freq_timer[0]->CC[2] = (offset - TIME_SYNC_TIMER_MAX_VAL);
    }
    else
    {
        m_params.high_freq_timer[0]->CC[2] = (TIME_SYNC_TIMER_MAX_VAL - offset);
    }
    NRF_LOG_INFO("offset=%d,timer[0]->CC[2]=%d\n",offset,m_params.high_freq_timer[0]->CC[2]);
    ppi_sync_timer_adjust_enable();
    
}

//接收器在收到同步信标数据包时如何更新其本地自由运行定时器
static inline bool sync_timer_record(sync_pkt_t * p_pkt)
{
    uint32_t peer_time;
    uint32_t local_time;
    uint32_t global_time_estimate;

//    if (m_timer_update_in_progress)
//    {
//NRF_LOG_INFO("m_timer_update_in_progress\n");
//        return false;
//    }
    
    ++cur_point;
    if (cur_point==STORAGE) cur_point=0;
 
    peer_radio_received = p_pkt->pkt_received;
    peer_time = p_pkt->timer_val + TX_CHAIN_DELAY - 10;
    //peer_time += TX_CHAIN_DELAY;     //传播延时固定
    cur_time_receive = m_params.high_freq_timer[0]->CC[1];
    local_time = cur_time_receive;
//    if (pri_time_receive == 0) local_time = cur_time_receive;
//    else local_time = ((int)((cur_time_receive - pri_time_receive + TIME_SYNC_TIMER_MAX_VAL*2)*1) + pri_time_update) % TIME_SYNC_TIMER_MAX_VAL;
    global_time_estimate = (local_time + peer_time) >> 1;
    NRF_LOG_INFO("sync_timer_record\n");
//global_time_estimate=peer_time;

        timer_offset[cur_point] = (global_time_estimate - local_time);
        receive_time_estimate = local_time;
        received_time_update = global_time_estimate;

    // m_params.high_freq_timer[0]->CC[2] represent the deviation of sender timer
    if (timer_offset[cur_point] == 0 ||
        timer_offset[cur_point] == TIME_SYNC_TIMER_MAX_VAL)
    {
        // Already in sync
        NRF_LOG_INFO("Already in sync\n");
        return false;
    }
    // Write offset to timer compare register
//    else if (timer_offset > TIME_SYNC_TIMER_MAX_VAL)
//    {
//        m_params.high_freq_timer[0]->CC[2] = (timer_offset - TIME_SYNC_TIMER_MAX_VAL);
//    }
//    else
//    {
//        m_params.high_freq_timer[0]->CC[2] = (TIME_SYNC_TIMER_MAX_VAL - timer_offset);
//    }
    
    NRF_LOG_INFO("peer_timer=%d,local_timer=%d,global_time_estimate=%d\n",peer_time,local_time,global_time_estimate);
    NRF_LOG_INFO("timer_offset=%d,timer[0]->CC[2]=%d\n",timer_offset[cur_point],m_params.high_freq_timer[0]->CC[2]);

#ifdef DEBUG
    if (m_params.high_freq_timer[0]->CC[2] > TIME_SYNC_TIMER_MAX_VAL)
    {
        NRF_LOG_ERROR("%d - %d - %d", peer_timer, local_timer, timer_offset);
        APP_ERROR_CHECK_BOOL(false);
    }
#endif

    m_timer_update_in_progress = true;
    mp_curr_adj_pkt            = p_pkt; //save current packet for recording timestampts

    //ppi_sync_timer_adjust_enable();
    sync_timer_consensus_compensate();

    return true;
}

static void ppi_sync_timer_adjust_configure(void)
{
    uint32_t chn0, chn1, chg;

    chn0 = m_params.ppi_chns[0];
    chn1 = m_params.ppi_chns[1];
    chg  = m_params.ppi_chg;
    // Use a timer compare register to reset the timer according to the offset value

    // PPI channel 0: clear timer when compare[2] value is reached
    NRF_PPI->CHENCLR        = (1 << chn0);    //enable chn0???
    NRF_PPI->CH[chn0].EEP   = (uint32_t) &m_params.high_freq_timer[0]->EVENTS_COMPARE[2];
    NRF_PPI->CH[chn0].TEP   = (uint32_t) &m_params.high_freq_timer[0]->TASKS_CLEAR;
    NRF_PPI->FORK[chn0].TEP = 0;
    //NRF_PPI->FORK[chn0].TEP = (uint32_t) &m_params.high_freq_timer[1]->TASKS_CLEAR;

    // PPI channel 1: disable PPI channel 0 such that the timer is only reset once, and trigger software interrupt
    NRF_PPI->CHENCLR        = (1 << chn1);
    NRF_PPI->CH[chn1].EEP   = (uint32_t) &m_params.high_freq_timer[0]->EVENTS_COMPARE[2];
    NRF_PPI->CH[chn1].TEP   = (uint32_t) &NRF_PPI->TASKS_CHG[chg].DIS;
    NRF_PPI->FORK[chn1].TEP = (uint32_t) &m_params.egu->TASKS_TRIGGER[0];

    NRF_PPI->TASKS_CHG[chg].DIS = 1;  //disable channel group 0
    NRF_PPI->CHG[chg]           = (1 << chn0) | (1 << chn1);

    //m_params.high_freq_timer[0]->CC[2]       = TIME_SYNC_TIMER_MAX_VAL;
}

/* Set up timestamp capture */
static void ppi_radio_rx_configure(void)
{
    uint32_t chn2;

    chn2 = m_params.ppi_chns[2];

    NRF_PPI->CH[chn2].EEP   = (uint32_t) &NRF_RADIO->EVENTS_ADDRESS;
    NRF_PPI->CH[chn2].TEP   = (uint32_t) &m_params.high_freq_timer[0]->TASKS_CAPTURE[1];
    NRF_PPI->FORK[chn2].TEP = (uint32_t) &m_params.high_freq_timer[1]->TASKS_CAPTURE[1];
    NRF_PPI->CHENSET       = (1 << chn2);
}

static void ppi_radio_tx_configure(void)
{
    uint32_t chn4;
	  //uint32_t chn5;

    chn4 = m_params.ppi_chns[4];
//    chn5 = m_params.ppi_chns[5];

    NRF_PPI->CH[chn4].EEP   = (uint32_t) &NRF_RADIO->EVENTS_READY;
    NRF_PPI->CH[chn4].TEP   = (uint32_t) &m_params.high_freq_timer[0]->TASKS_CAPTURE[1];
    NRF_PPI->FORK[chn4].TEP = (uint32_t) &m_params.high_freq_timer[1]->TASKS_CAPTURE[1];
    NRF_PPI->CHENSET       = (1 << chn4);

//    NRF_PPI->CH[chn5].EEP = (uint32_t) &NRF_TIMER0->EVENTS_COMPARE[1];
//    //NRF_PPI->CH[chn5].TEP = (uint32_t) &NRF_RADIO->TASKS_START;
//    NRF_PPI->CH[chn5].TEP = (uint32_t) &NRF_RADIO->TASKS_TXEN;
//    NRF_PPI->CHENSET          = (1 << chn5);
}

static void ppi_timestamp_timer_configure(void)
{
    uint32_t chn3;
	  //uint32_t chn5;
    //uint32_t log[]={'C','O','U','N','T','\n'};

    chn3 = m_params.ppi_chns[3];
    //chn5 = m_params.ppi_chns[5];

    NRF_PPI->CH[chn3].EEP   = (uint32_t) &m_params.high_freq_timer[0]->EVENTS_COMPARE[2];
    NRF_PPI->CH[chn3].TEP   = (uint32_t) &m_params.high_freq_timer[1]->TASKS_COUNT;    //Increment Timer (Counter mode only)
    NRF_PPI->FORK[chn3].TEP = 0;
    NRF_PPI->CHENSET       = (1 << chn3);

//    NRF_PPI->CH[chn5].EEP   = (uint32_t) &m_params.high_freq_timer[0]->EVENTS_COMPARE[4];
//    NRF_PPI->CH[chn5].TEP   = (uint32_t) &NRF_GPIOTE->TASKS_OUT[3];
//    NRF_PPI->CHENSET       = (1 << chn5);
}

static void ppi_counter_timer_capture_configure(uint32_t chn)
{
    NRF_PPI->CH[chn].EEP    = (uint32_t) &m_params.egu->EVENTS_TRIGGERED[1];
    NRF_PPI->CH[chn].TEP    = (uint32_t) &m_params.high_freq_timer[0]->TASKS_CAPTURE[3];
    NRF_PPI->FORK[chn].TEP  = (uint32_t) &m_params.high_freq_timer[1]->TASKS_CAPTURE[0];
    NRF_PPI->CHENSET        = (1 << chn);
}

static void ppi_counter_timer_capture_disable(uint32_t chn)
{
    NRF_PPI->CHENCLR = (1 << chn);

    NRF_PPI->CH[chn].EEP    = 0;
    NRF_PPI->CH[chn].TEP    = 0;
    NRF_PPI->FORK[chn].TEP  = 0;
}

static void ppi_radio_rx_disable(void)
{
    uint32_t chn2;

    chn2 = m_params.ppi_chns[2];

    NRF_PPI->CHENCLR = (1 << chn2);
}

static void ppi_sync_timer_adjust_enable(void)
{
    NRF_PPI->TASKS_CHG[m_params.ppi_chg].EN = 1;
}

static void ppi_sync_timer_adjust_disable(void)
{
    NRF_PPI->TASKS_CHG[m_params.ppi_chg].DIS = 1;
}

static void timers_capture(uint32_t * p_sync_timer_val, uint32_t * p_count_timer_val, uint32_t * p_peer_counter, uint8_t ppi_chn)
{
    static nrf_atomic_flag_t m_timestamp_capture_flag = 0;

    uint32_t peer_counter;
    bool     timeslot_active;

    if (nrf_atomic_flag_set_fetch(&m_timestamp_capture_flag) != 0)
    {
        // Not thread-safe
        APP_ERROR_CHECK_BOOL(false);
    }

    ppi_counter_timer_capture_configure(ppi_chn);

    // Use loop in case radio state changes from inactive to active during value copy
    // Value copy needs to be atomic to get accurate timestamp
    do
    {
        if (m_radio_state == RADIO_STATE_IDLE)
        {
            timeslot_active = false;
        }
        else
        {
            timeslot_active =  true;
        }

        if (timeslot_active)
        {
            // Do critical section during timeslot
            NVIC_DisableIRQ(RADIO_IRQn);
            m_params.egu->TASKS_TRIGGER[1] = 1;
            (void) m_params.egu->EVENTS_TRIGGERED[1];
            peer_counter = m_master_counter;
            NVIC_EnableIRQ(RADIO_IRQn);
        }
        else
        {
            // Critical section not needed outside of timeslot
            m_params.egu->TASKS_TRIGGER[1] = 1;
            (void) m_params.egu->EVENTS_TRIGGERED[1];
            peer_counter = m_master_counter;
        }

    } while (!timeslot_active && (m_radio_state != RADIO_STATE_IDLE));

    ppi_counter_timer_capture_disable(ppi_chn);

    *p_sync_timer_val  = m_params.high_freq_timer[0]->CC[3];
    *p_count_timer_val = (m_params.high_freq_timer[1]->CC[0]);
    *p_peer_counter    = peer_counter;

    nrf_atomic_flag_clear(&m_timestamp_capture_flag);
}

uint32_t ts_init(const ts_params_t * p_params)
{
    memcpy(&m_params, p_params, sizeof(ts_params_t));

    if (m_params.high_freq_timer[0] == 0 ||
        m_params.rtc                == 0 ||
        m_params.egu                == 0)
    {
        // TODO: Check all params
        return NRF_ERROR_INVALID_PARAM;
    }

    if (m_params.egu != NRF_EGU3)
    {
        // TODO: Remove hardcoded use of SWI3_EGU3_IRQHandler()
        return NRF_ERROR_INVALID_PARAM;
    }

    // TODO: Implement use of RTC as a low-power (and lower accuracy)
    // alternative to 16 MHz TIMER
    // if (SYNC_RTC_PRESCALER != m_params.rtc->PRESCALER)
    // {
    //     // TODO: Handle this
    //     return NRF_ERROR_INVALID_STATE;
    // }

    APP_ERROR_CHECK(nrf_balloc_init(&m_sync_pkt_pool));

    return NRF_SUCCESS;
}

uint32_t ts_enable(void)
{
    uint32_t err_code;

    if (m_timeslot_session_open)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    err_code = sd_clock_hfclk_request();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code |= sd_power_mode_set(NRF_POWER_MODE_CONSTLAT);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_radio_session_open(radio_callback); //start session
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_radio_request(&m_timeslot_req_earliest);  //obtain the timeslot
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    NRF_LOG_INFO("sd_radio_request\n");
    ppi_timestamp_timer_configure();
    ppi_sync_timer_adjust_configure();

    NVIC_ClearPendingIRQ(m_params.egu_irq_type);
    NVIC_SetPriority(m_params.egu_irq_type, 7);
    NVIC_EnableIRQ(m_params.egu_irq_type);

    m_params.egu->INTENCLR = 0xFFFFFFFF;
    m_params.egu->INTENSET = EGU_INTENSET_TRIGGERED0_Msk;

    m_blocked_cancelled_count  = 0;
    m_send_sync_pkt            = false;
    m_radio_state              = RADIO_STATE_IDLE;

    timestamp_counter_start();
    sync_timer_start();

    m_timeslot_session_open    = true;

    return NRF_SUCCESS;
}

uint32_t ts_disable(void)
{
    // TODO:
    //       - Close SoftDevice radio session (sd_radio_session_close())
    //       - Stop radio activity
    //       - Stop timers
    //       - Disable used PPI channels
    //       - Disable used interrupts
    //       - Release HFCLK (sd_clock_hfclk_release()),
    //       - Go back to low-power (mode sd_power_mode_set(NRF_POWER_MODE_LOWPWR))
    // Care must be taken to ensure clean stop. Order of tasks above should be reconsidered.
    return NRF_ERROR_NOT_SUPPORTED;
}

uint32_t ts_tx_start(uint32_t sync_freq_hz)
{
    uint32_t distance;

    distance = (1000000 / sync_freq_hz);

    if (distance >= NRF_RADIO_DISTANCE_MAX_US)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_timeslot_distance = distance;

    ////while(NRF_TIMER0->EVENTS_COMPARE[0]==0){}

    m_send_sync_pkt = true;
    m_timer_update_in_progress = false;

    return NRF_SUCCESS;
}

uint32_t ts_tx_stop()
{
    m_send_sync_pkt = false;

    return NRF_SUCCESS;
}

uint32_t ts_timestamp_get_ticks_u32(uint8_t ppi_chn)
{
    uint32_t sync_timer_val;
    uint32_t count_timer_val;
    uint32_t peer_count;

    timers_capture(&sync_timer_val, &count_timer_val, &peer_count, ppi_chn);

    return (((count_timer_val + peer_count) * TIME_SYNC_TIMER_MAX_VAL) + sync_timer_val);
}

uint64_t ts_timestamp_get_ticks_u64(uint8_t ppi_chn)
{
    uint32_t sync_timer_val;
    uint32_t count_timer_val;
    uint64_t timestamp;
    uint32_t  peer_count;

    timers_capture(&sync_timer_val, &count_timer_val, &peer_count, ppi_chn);

    timestamp  = (uint64_t) count_timer_val;
    timestamp += (uint64_t) peer_count;
    timestamp *= TIME_SYNC_TIMER_MAX_VAL;
    timestamp += (uint64_t) sync_timer_val;

    return timestamp;
}

