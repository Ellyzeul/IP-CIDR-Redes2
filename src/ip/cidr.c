#include "../../include/cidr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* maskForNHosts(const int hosts) {
    int i = 0, value = hosts, netBits, count = 0;
    char* mask = calloc(36, sizeof(char));

    while((value*=2) < 256) i++;

    netBits = 32 - (8 - i);
    mask[35] = '\0';

    i = 0;
    while (i < 35)
    {
        if(count == 8) {
            mask[i++] = '.';
            count = 0;
            continue;
        }

        mask[i++] = (netBits-- > 0 ? '1' : '0');
        count++;
    }
    
    return mask;
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

int getBitsForNet(const IPv4* ip) {
    int bits = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            if(ip->mask[i][j] == '0') return bits;

            bits++;
        }
    }

    return bits;
}

int totalHostsOfNet(const IPv4* ip) {
    int hostsBits = 32 - getBitsForNet(ip), hosts = 1;

    while (hostsBits-- > 0) hosts *= 2;
    hosts -= 2;

    return hosts;
}

char* getNetID(const IPv4* ip) {
    int hostBits = 32 - getBitsForNet(ip), bytes[4], chars = 3, aux, index = 0;
    char byte[8], *netId, *byteStr;

    for(int i = 3; i >= 0; i--) {
        strcpy(byte, ip->block[i]);

        for(int j = 7; j >= 0 && hostBits > 0; j--) {
            byte[j] = '0';
            hostBits--;
        }

        bytes[i] = binToDecimal(byte);
    }

    for(int i = 0; i < 4; i++) {
        aux = bytes[i];
        do {
            chars++;
            aux /= 10;
        } while(aux != 0);
    }

    netId = calloc(chars+1, sizeof(char));
    netId[chars] = '\0';

    for(int i = 0; i < 4; i++) {
        itoa(bytes[i], byteStr, 10);

        for(int j = 0; byteStr[j] != '\0'; j++) netId[index++] = byteStr[j];

        if(i < 3) netId[index++] = '.';
    }

    return netId;
}

IPv4* netFirstHost(const char* netIp) {
    IPv4* first = allocIPv4(netIp);

    first->block[3][7] = '1';

    return first;
}

IPv4* netLastHost(const char* netIp, int hostBits) {
    IPv4* last = allocIPv4(netIp);

    for(int i = hostBits; i < 31; i++) {
        last->block[i/8][i%8] = '1';
    }

    return last;
}

IPv4* netBroadcast(const char* netIp, int hostBits) {
    IPv4* broadcast = netLastHost(netIp, hostBits);

    broadcast->block[3][7] = '1';

    return broadcast;
}

IPv4* allocIPv4(const char* netIp) {
    int i = 0, j = 0, mask, *bytes = calloc(5, sizeof(int));
    char ch;
    IPv4* ip = calloc(1, sizeof(IPv4));
    ip->block = calloc(4, sizeof(char*));
    ip->mask = calloc(4, sizeof(char*));

    while ((ch = *(netIp+(i++))) != '\0')
    {
        if(ch == 46 || ch == 47) {
            j++;
            continue;
        }

        bytes[j] *= 10;
        bytes[j] += ch-48;
    }

    for(i = 0; i < 4; i++) ip->block[i] = decimalToBin(bytes[i]);

    mask = bytes[4];
    for(i = 0; i < 4; i++) {
        ip->mask[i] = calloc(9, sizeof(char));
        ip->mask[i][8] = '\0';

        for(j = 0; j < 8; j++) ip->mask[i][j] = (mask-- > 0 ? '1' : '0');
    }

    return ip;
}

void changeMask(IPv4* ip, char* newMask) {
    int index = 0, j = 0;

    for(int i = 0; i < 35; i++) {
        if(newMask[i] == '.') {
            index++;
            j = 0;
            continue;
        }

        ip->mask[index][j++] = newMask[i];
    }
}