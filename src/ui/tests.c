#include "../../include/cidr.h"
#include "../../include/tests.h"
#include <stdio.h>


void _displayMask(const IPv4* ip) {
    printf("%s.%s.%s.%s\n", 
        ip->mask[0],
        ip->mask[1],
        ip->mask[2],
        ip->mask[3]
    );
}

void tests(void) {
    IPv4* ip = allocIPv4("110.40.240.16/22");

    _displayMask(ip);

    changeMask(ip, maskForNHosts(128));
    _displayMask(ip);

    changeMask(ip, maskForNHosts(57));
    _displayMask(ip);

    changeMask(ip, maskForNHosts(32));
    _displayMask(ip);

    changeMask(ip, maskForNHosts(180));
    _displayMask(ip);

    changeMask(ip, maskForNHosts(10));
    _displayMask(ip);
}