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
    
    ip = allocIPv4(getIp());                            // Pegar endereco IP do usuario

    listNetInfo(ip, "Informacoes do IP inserido");      // LIstando informacoes do IP

    changeMask(ip, maskForNHosts(128));                 // Rede com 128 IPs utilizaveis
    listNetInfo(ip, "Rede com 128 IPs utilizaveis");

    changeMask(ip, maskForNHosts(57));                  // Rede com 57 IPs utilizaveis
    listNetInfo(ip, "Rede com 57 IPs utilizaveis");

    changeMask(ip, maskForNHosts(32));                  // Rede com 32 IPs utilizaveis
    listNetInfo(ip, "Rede com 32 IPs utilizaveis");

    changeMask(ip, maskForNHosts(180));                 // Rede com 180 IPs utilizaveis
    listNetInfo(ip, "Rede com 180 IPs utilizaveis");

    changeMask(ip, maskForNHosts(10));                  // Rede com 10 IPs utilizaveis
    listNetInfo(ip, "Rede com 10 IPs utilizaveis");

    printf("\n\n");

    return 0;
}