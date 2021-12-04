#ifndef __ELLYZ__CIDR_HEADER__
#define __ELLYZ__CIDR_HEADER__

struct ip {
    char** block;
    char** mask;
};
typedef struct ip IPv4;

char* maskForNHosts(const int hosts);
char* decimalToBin(const int decimal);
int binToDecimal(const char* binary);
IPv4* allocIPv4(const char* netIp);
int getBitsForNet(const IPv4* ip);
char* getNetID(const IPv4* ip);
IPv4* netFirstHost(const char* netIp);
IPv4* netLastHost(const char* netIp, int hostBits);
int totalHostsOfNet(const IPv4* ip);
IPv4* netBroadcast(const char* netIp, int hostBits);
void changeMask(IPv4* ip, char* newMask);

#endif