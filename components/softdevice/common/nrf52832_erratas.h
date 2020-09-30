#include <stdbool.h>
#include "compiler_abstraction.h"

static bool errata_1(void);
static bool errata_2(void);
static bool errata_3(void);
static bool errata_4(void);
static bool errata_7(void);
static bool errata_8(void);
static bool errata_9(void);
static bool errata_10(void);
static bool errata_11(void);
static bool errata_12(void);
static bool errata_15(void);
static bool errata_16(void);
static bool errata_17(void);
static bool errata_20(void);
static bool errata_23(void);
static bool errata_24(void);
static bool errata_25(void);
static bool errata_26(void);
static bool errata_27(void);
static bool errata_28(void);
static bool errata_29(void);
static bool errata_30(void);
static bool errata_31(void);
static bool errata_32(void);
static bool errata_33(void);
static bool errata_34(void);
static bool errata_35(void);
static bool errata_36(void);
static bool errata_37(void);
static bool errata_38(void);
static bool errata_39(void);
static bool errata_40(void);
static bool errata_41(void);
static bool errata_42(void);
static bool errata_43(void);
static bool errata_44(void);
static bool errata_46(void);
static bool errata_47(void);
static bool errata_48(void);
static bool errata_49(void);
static bool errata_51(void);
static bool errata_54(void);
static bool errata_55(void);
static bool errata_57(void);
static bool errata_58(void);
static bool errata_62(void);
static bool errata_63(void);
static bool errata_64(void);
static bool errata_65(void);
static bool errata_66(void);
static bool errata_67(void);
static bool errata_68(void);
static bool errata_70(void);
static bool errata_71(void);
static bool errata_72(void);
static bool errata_73(void);
static bool errata_74(void);
static bool errata_75(void);
static bool errata_76(void);
static bool errata_77(void);
static bool errata_78(void);
static bool errata_79(void);
static bool errata_81(void);
static bool errata_83(void);
static bool errata_84(void);
static bool errata_86(void);
static bool errata_87(void);
static bool errata_88(void);
static bool errata_89(void);
static bool errata_91(void);
static bool errata_94(void);
static bool errata_96(void);
static bool errata_97(void);
static bool errata_98(void);
static bool errata_101(void);
static bool errata_102(void);
static bool errata_103(void);
static bool errata_104(void);
static bool errata_106(void);
static bool errata_107(void);
static bool errata_108(void);
static bool errata_109(void);
static bool errata_110(void);
static bool errata_111(void);
static bool errata_112(void);
static bool errata_113(void);
static bool errata_115(void);
static bool errata_116(void);
static bool errata_117(void);
static bool errata_118(void);
static bool errata_119(void);
static bool errata_120(void);
static bool errata_121(void);
static bool errata_122(void);
static bool errata_127(void);
static bool errata_128(void);
static bool errata_131(void);
static bool errata_132(void);
static bool errata_133(void);
static bool errata_134(void);
static bool errata_135(void);
static bool errata_136(void);
static bool errata_138(void);
static bool errata_140(void);
static bool errata_141(void);
static bool errata_142(void);
static bool errata_143(void);
static bool errata_144(void);
static bool errata_145(void);
static bool errata_146(void);
static bool errata_147(void);
static bool errata_149(void);
static bool errata_150(void);
static bool errata_151(void);
static bool errata_153(void);
static bool errata_154(void);
static bool errata_155(void);
static bool errata_156(void);
static bool errata_158(void);
static bool errata_160(void);
static bool errata_162(void);
static bool errata_163(void);
static bool errata_164(void);
static bool errata_166(void);
static bool errata_170(void);
static bool errata_171(void);
static bool errata_172(void);
static bool errata_173(void);
static bool errata_174(void);
static bool errata_176(void);
static bool errata_178(void);
static bool errata_179(void);
static bool errata_180(void);
static bool errata_181(void);
static bool errata_182(void);
static bool errata_183(void);
static bool errata_184(void);
static bool errata_186(void);
static bool errata_187(void);
static bool errata_189(void);
static bool errata_190(void);
static bool errata_191(void);
static bool errata_192(void);
static bool errata_193(void);
static bool errata_194(void);
static bool errata_195(void);
static bool errata_196(void);
static bool errata_197(void);
static bool errata_198(void);
static bool errata_199(void);
static bool errata_200(void);
static bool errata_201(void);
static bool errata_202(void);
static bool errata_204(void);
static bool errata_208(void);
static bool errata_209(void);
static bool errata_210(void);
static bool errata_212(void);
static bool errata_213(void);
static bool errata_214(void);
static bool errata_215(void);
static bool errata_217(void);
static bool errata_218(void);
static bool errata_219(void);
static bool errata_225(void);


static bool errata_1(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
		}

	}

	return false;
}

static bool errata_2(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_3(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_4(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_7(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_8(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_9(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_10(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_11(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_12(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_15(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_16(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_17(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_20(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_23(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_24(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_25(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_26(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_27(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_28(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_29(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_30(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_31(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_32(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_33(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_34(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_35(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_36(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_37(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_38(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_39(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_40(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_41(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_42(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_43(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_44(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_46(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_47(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_48(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_49(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_51(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_54(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_55(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_57(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_58(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_62(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_63(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_64(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_65(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_66(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_67(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_68(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_70(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_71(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_72(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_73(void)
{
	uint32_t var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
	uint32_t var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return false;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_74(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_75(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_76(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_77(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_78(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_79(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_81(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_83(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_84(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_86(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_87(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_88(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_89(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_91(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_94(void)
{
	return false;
}

static bool errata_96(void)
{
	return false;
}

static bool errata_97(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_98(void)
{
	return false;
}

static bool errata_101(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_102(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_103(void)
{
	return false;
}

static bool errata_104(void)
{
	return false;
}

static bool errata_106(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_107(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_108(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_109(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_110(void)
{
	return false;
}

static bool errata_111(void)
{
	return false;
}

static bool errata_112(void)
{
	return false;
}

static bool errata_113(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_115(void)
{
	return false;
}

static bool errata_116(void)
{
	return false;
}

static bool errata_117(void)
{
	return false;
}

static bool errata_118(void)
{
	return false;
}

static bool errata_119(void)
{
	return false;
}

static bool errata_120(void)
{
	return false;
}

static bool errata_121(void)
{
	return false;
}

static bool errata_122(void)
{
	return false;
}

static bool errata_127(void)
{
	return false;
}

static bool errata_128(void)
{
	return false;
}

static bool errata_131(void)
{
	return false;
}

static bool errata_132(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_133(void)
{
	return false;
}

static bool errata_134(void)
{
	return false;
}

static bool errata_135(void)
{
	return false;
}

static bool errata_136(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_138(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_140(void)
{
	return false;
}

static bool errata_141(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_142(void)
{
	return false;
}

static bool errata_143(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_144(void)
{
	return false;
}

static bool errata_145(void)
{
	return false;
}

static bool errata_146(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_147(void)
{
	return false;
}

static bool errata_149(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_150(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_151(void)
{
	return false;
}

static bool errata_153(void)
{
	return false;
}

static bool errata_154(void)
{
	return false;
}

static bool errata_155(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_156(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_158(void)
{
	return false;
}

static bool errata_160(void)
{
	return false;
}

static bool errata_162(void)
{
	return false;
}

static bool errata_163(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_164(void)
{
	return false;
}

static bool errata_166(void)
{
	return false;
}

static bool errata_170(void)
{
	return false;
}

static bool errata_171(void)
{
	return false;
}

static bool errata_172(void)
{
	return false;
}

static bool errata_173(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_174(void)
{
	return false;
}

static bool errata_176(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_178(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_179(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_180(void)
{
	return false;
}

static bool errata_181(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return false;
		default:
			return false;
			
		}
		

	}

	return false;
}

static bool errata_182(void)
{
	uint32_t var1 = *(uint32_t *)0x10000130ul;
	uint32_t var2 = *(uint32_t *)0x10000134ul;

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return false;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_183(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_184(void)
{
	return false;
}

static bool errata_186(void)
{
	return false;
}

static bool errata_187(void)
{
	return false;
}

static bool errata_189(void)
{
	return false;
}

static bool errata_190(void)
{
	return false;
}

static bool errata_191(void)
{
	return false;
}

static bool errata_192(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_193(void)
{
	return false;
}

static bool errata_194(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_195(void)
{
	return false;
}

static bool errata_196(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_197(void)
{
	return false;
}

static bool errata_198(void)
{
	return false;
}

static bool errata_199(void)
{
	return false;
}

static bool errata_200(void)
{
	return false;
}

static bool errata_201(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_202(void)
{
	return false;
}

static bool errata_204(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_208(void)
{
	return false;
}

static bool errata_209(void)
{
	return false;
}

static bool errata_210(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_212(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_213(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return true;
		case 0x04ul:
			return true;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_214(void)
{
	return false;
}

static bool errata_215(void)
{
	return false;
}

static bool errata_217(void)
{
	return false;
}

static bool errata_218(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_219(void)
{
	uint32_t var1;
	uint32_t var2;

	if (*(uint32_t *)0x10000130ul == 0xFFFFFFFF)
	{
		var1 = ((*(uint32_t *)0xF0000FE0ul) & 0x000000FFul);
		var2 = ((*(uint32_t *)0xF0000FE8ul) & 0x000000F0ul) >> 4;
	}
	else
	{
		var1 = *(uint32_t *)0x10000130ul;
		var2 = *(uint32_t *)0x10000134ul;
	}

	switch (var1)
	{
	case 0x06:
		switch (var2)
		{
		case 0x03ul:
			return false;
		case 0x04ul:
			return false;
		case 0x05ul:
			return true;
		case 0x06ul:
			return true;
		default:
			return true;
			
		}
		

	}

	return false;
}

static bool errata_225(void)
{
	return false;
}


