#include "include/cidr.h"
#include "include/ui.h"
#include "include/tests.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int debug = 0;
    IPv4* ip;

    if(debug) {
        tests();
        return 0;
    }
    
    ip = allocIPv4(getIp());

    listNetInfo(ip, "Informacoes do IP inserido");

    changeMask(ip, maskForNHosts(128));
    listNetInfo(ip, "Rede com 128 IPs utilizaveis");

    changeMask(ip, maskForNHosts(57));
    listNetInfo(ip, "Rede com 57 IPs utilizaveis");

    changeMask(ip, maskForNHosts(32));
    listNetInfo(ip, "Rede com 32 IPs utilizaveis");

    changeMask(ip, maskForNHosts(180));
    listNetInfo(ip, "Rede com 180 IPs utilizaveis");

    changeMask(ip, maskForNHosts(10));
    listNetInfo(ip, "Rede com 10 IPs utilizaveis");


    system("pause");

    return 0;
}