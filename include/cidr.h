#ifndef __ELLYZ__CIDR_HEADER__
#define __ELLYZ__CIDR_HEADER__

struct ip {
    char** block;
    char** mask;
};
typedef struct ip IPv4;

int bitsForNHosts(const int hosts);
char* decimalToBin(const int decimal);
int binToDecimal(const char* binary);
int netBitsOfMask(const IPv4* ipv4);
IPv4* allocIPv4(const int byte1, const int byte2, const int byte3, const int byte4, const int netType);

#endif