#include "../include/cidr.h"
#include <string.h>
#include <stdlib.h>


int bitsForNHosts(const int hosts) {
    int i = 0, value = hosts;

    while((value*=2) < 256) i++;

    return 8 - i;
}

char* decimalToBin(const int decimal) {
    char* bin;
    int actual = decimal;

    bin = calloc(9, sizeof(char));
    *(bin+8) = '\0';
    for(int i = 7; i >= 0; i--) {
        *(bin+i) = (actual % 2) + 48;
        actual /= 2;
    }

    return bin;
}

int binToDecimal(const char* binary) {
    int dec = 0, mul = 1;

    for(int i = 7; i >= 0; i--) {
        dec += (*(binary+i) - 48) * mul;
        mul *= 2;
    }

    return dec;
}

int netBitsOfMask(const IPv4* ipv4) {
    int bits = 0, stop = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            if(ipv4->mask[i][j] != '1') {
                stop = 1;
                break;
            }
            bits++;
        }
    }

    return bits;
}

IPv4* allocIPv4(const int byte1, const int byte2, const int byte3, const int byte4, const int netType) {
    IPv4* ip = calloc(1, sizeof(IPv4));
    ip->block = calloc(4, sizeof(char*));
    ip->mask = calloc(4, sizeof(char*));

    ip->block[0] = decimalToBin(byte1);
    ip->block[1] = decimalToBin(byte2);
    ip->block[2] = decimalToBin(byte3);
    ip->block[3] = decimalToBin(byte4);

    // ...

    return ip;
}