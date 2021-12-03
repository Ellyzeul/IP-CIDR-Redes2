#include "include/cidr.h"
#include "include/ui.h"
#include "include/tests.h"
#include <stdio.h>


int main(void) {
    int debug = 0;
    IPv4* ip;
    char* netIp;


    ip = allocIPv4(index());

    listNetInfo(ip);

    if(debug) tests();
    return 0;
}