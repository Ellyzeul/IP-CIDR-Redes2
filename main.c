#include "include/cidr.h"
#include "include/ui.h"
#include "include/tests.h"
#include <stdio.h>


int main(void) {
    int debug = 0;
    IPv4* ipv4;
    char* netIp;

    if(debug) tests();

    netIp = index();

    printf("%s", netIp);

    return 0;
}