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

#ifndef __TIME_SYNC_H__
#define __TIME_SYNC_H__

#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_soc.h"

#define TS_SOC_OBSERVER_PRIO 0

#define TIME_SYNC_TIMER_MAX_VAL (48000)
static volatile uint32_t TIME_SYNC_TIMER_MAX_VAL_ori=48000;
#define TIME_SYNC_RTC_MAX_VAL   (0xFFFFFF)

/**@brief Data handler type. */
typedef void (*ts_evt_handler_t)(uint32_t time);

typedef struct
{
    uint8_t          rf_chn;          /** RF Channel [0-80] */
    uint8_t          rf_addr[5];      /** 5-byte RF address */
    uint8_t          ppi_chns[5];     /** PPI channels */
    uint8_t          ppi_chg;        /** PPI Channel Group */
    NRF_TIMER_Type * high_freq_timer[2]; /** 16 MHz timer (e.g. NRF_TIMER2). NOTE: debug toggling only available if TIMER3 or TIMER4 is used for high_freq_timer[0]*/
    NRF_RTC_Type   * rtc;
    NRF_EGU_Type   * egu;
    IRQn_Type        egu_irq_type;
} ts_params_t;

/**@brief Initialize time sync library
 * 
 * @param[in] p_params Parameters
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_init(const ts_params_t * p_params);

/**@brief Enable time sync library. This will enable reception of sync packets.
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_enable(void);

/**@brief Disable time sync library. 
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_disable(void);

/**@brief Start sync packet transmission (become timing master).
 *
 * @note @ref ts_enable() must be called prior to calling this function
 * @note Expect some jitter depending on BLE activity.
 *
 * @param[in] sync_freq_hz Frequency of transmitted sync packets. 
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_tx_start(uint32_t sync_freq_hz);

/**@brief Stop sync packet transmission (become timing slave again).
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_tx_stop(void);

/**@brief Get timestamp value in 16 MHz ticks
 *
 * @note 32-bit variable overflows after ~268 seconds
 * 
 * @param[in] ppi_chn PPI channel to use for timer capture. Channel is not used after function exits.
 * 
 * @retval timestamp value [1 second/16 MHz]
 */
uint32_t ts_timestamp_get_ticks_u32(uint8_t ppi_chn);

/**@brief Get timestamp value in 16 MHz ticks
 *
 * @note Internal 32-bit counter overflows after (2^32 * @ref TIME_SYNC_TIMER_MAX_VAL) / 16 000 000 seconds. 
 * 
 * @param[in] ppi_chn PPI channel to use for timer capture. Channel is not used after function exits.
 * 
 * @retval timestamp value [1 second/16 MHz]
 */
uint64_t ts_timestamp_get_ticks_u64(uint8_t ppi_chn);

/**@brief Start sybil attack behevier
 * 
 * @param[in] p_params Parameters
 *
 * @retval NRF_SUCCESS if successful 
 */
uint32_t ts_attack_start(void);



/*
 * @defgroup RAND Random number generator
 * @ingroup MESH_CORE
 * This module abstracts the hardware RNG, as well as providing a simple PRNG for non-cryptographic
 * random numbers.
 * @{
 * PRNG instance structure. */
typedef struct
{
    uint32_t a; /**< PRNG state variable A */
    uint32_t b; /**< PRNG state variable B */
    uint32_t c; /**< PRNG state variable C */
    uint32_t d; /**< PRNG state variable D */
} prng_t;

#define SMALL_PRNG_BASE_SEED    (0xf1ea5eed)
#define ROT(x,k) (((x)<<(k))|((x)>>(32-(k)))) /** PRNG cyclic leftshift */

uint32_t rand_prng_get(prng_t* p_prng)
{
    /* Bob Jenkins' small PRNG
        http://burtleburtle.net/bob/rand/smallprng.html */
    uint32_t e = p_prng->a - ROT(p_prng->b, 27);
    p_prng->a = p_prng->b ^ ROT(p_prng->c, 17);
    p_prng->b = p_prng->c + p_prng->d;
    p_prng->c = p_prng->d + e;
    p_prng->d = e + p_prng->a;
    return p_prng->d;
}

void rand_hw_rng_get(uint8_t* p_result, uint16_t len)
{
    uint8_t bytes_available;
    uint32_t count = 0;
    while (count < len)
    {
        do
        {
            (void) sd_rand_application_bytes_available_get(&bytes_available);
        } while (bytes_available == 0);

        if (bytes_available > len - count)
        {
            bytes_available = len - count;
        }

        (void) sd_rand_application_vector_get(&p_result[count],
            bytes_available);

        count += bytes_available;
    }
}

void rand_prng_seed(prng_t* p_prng)
{
    uint32_t seed = 0;
    /* Get true random seed from HW. */
    rand_hw_rng_get((uint8_t*) &seed, sizeof(seed));

    /* establish base magic numbers */
    p_prng->a = SMALL_PRNG_BASE_SEED;
    p_prng->b = seed;
    p_prng->c = seed;
    p_prng->d = seed;

    /* run the prng a couple of times to flush out the seeds */
    for (uint32_t i = 0; i < 20; ++i)
    {
        (void) rand_prng_get(p_prng);
    }
}

#endif /* __TIME_SYNC_H__ */
