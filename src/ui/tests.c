#include "../../include/cidr.h"
#include "../../include/tests.h"
#include <stdio.h>


void tests(void) {
    IPv4* ip = allocIPv4(110, 40, 240, 16, 22);

    printf("%s.%s.%s.%s\n",
        ip->block[0],
        ip->block[1],
        ip->block[2],
        ip->block[3]
    );

    printf("%d\n", bitsForNHosts(65));
    printf("%d\n", bitsForNHosts(100));
    printf("%d\n", bitsForNHosts(33));
    printf("%d\n", bitsForNHosts(13));

    printf("%s\n", decimalToBin(1));
    printf("%s\n", decimalToBin(2));
    printf("%s\n", decimalToBin(3));
    printf("%s\n", decimalToBin(4));
    printf("%s\n", decimalToBin(5));
    printf("%s\n", decimalToBin(16));

    printf("%d\n", binToDecimal("00000001"));
    printf("%d\n", binToDecimal("00000010"));
    printf("%d\n", binToDecimal("00000011"));
    printf("%d\n", binToDecimal("00000100"));
    printf("%d\n", binToDecimal("00000101"));
    printf("%d\n", binToDecimal("00010000"));
}