#include <stdio.h>
#include "printer.h"

int _start()
{
    char *pChr = "StringInArg";
    char chr = 'c';
    unsigned int	testHex0 = 0x102345,
                	testHex1 = 0x6789AB,
                	testHex2 = 0xCDEF,
                	testOct = 012345670,
                	testBin = 0b00111011000101001111010100001111;
	int				testInt1 = -50698,
					testInt2 = 2147483647,
					zero;
    int a = self_printf("%s\nnormalString\nCharInArg: %c\nPercentSign: %%\nNot supporting: %e%e%r%a%%%y\nHexZeroCheck: %x    %X\nHex0: %x    %X\nHex1: %x    %X\nHex2: %x    %X\nOctZeroCheck: %o\nOct: %o\nBinZeroCheck: %b\nBin: %b\nIntZeroCheck: %d\nInt: %d, %d\n", pChr, chr, zero, zero, testHex0, testHex0, testHex1, testHex1, testHex2, testHex2, zero, testOct, zero, testBin, zero, testInt1, testInt2);

    return 0;
}
