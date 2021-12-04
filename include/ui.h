#ifndef __ELLYZ__UI__IP_CIDR_REDES2__
#define __ELLYZ__UI__IP_CIDR_REDES2__

#ifdef __linux__
    #define CLEAR "clear"
#elif _WIN32
    #define CLEAR "cls"
#endif

#include "cidr.h"

char* getIp(void);
void listNetInfo(const IPv4* ip, const char* msg);

#endif