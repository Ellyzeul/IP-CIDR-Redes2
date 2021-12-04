#include "../../include/ui.h"
#include "../../include/cidr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


_Bool validateIp(const char* netIp) {
    char actChar;
    int count = 0, byte = 0, illegalSymbol = 0, dotCounter = 0;

    for(int i = 0; i < 18; i++) {
        actChar = *(netIp+i);

        if(*(netIp+i-3) == '/') break;                  // Verificacao ao final da string se ja ultrapassou o '/' no caso de a string de entrada ser menor do que 18 caracteres
        if(actChar == 46 || actChar == 47) {            // Verificacao se foram encontrados os caracteres '.' ou '/' e se o número nesse intervalo e valido
            if(byte > 255) return 0;
            if(illegalSymbol) return 0;

            if(actChar == 46) dotCounter++;
            byte = 0;
            count = 0;
            illegalSymbol = 1;
            continue;
        }
        else if(actChar < 48 || actChar > 57) return 0; // Verificacao se o caracter atual e um digito ou se e invalido
        if(count == 3) return 0;                        // Verificacao se o numero na string, antes do ponto de separacao é maior do que quatro algarismos

        byte *= 10;
        byte += actChar-48;                             // Conversao de string para decimal

        illegalSymbol = 0;
        count++;                                        // Incrementando contador de digitos antes do proximo ponto
    }
    if(byte > 32) return 0;                             // Verificacao se a notacao CIDR está num intervalo valida
    if(dotCounter != 3) return 0;

    return 1;                                           // Caso a execucao nao seja barrada em nenhuma restricao, entao um valor verdadeiro sera retornado
}

void displayIP(const IPv4* ip) {
    printf("%d.%d.%d.%d", 
        binToDecimal(ip->block[0]),
        binToDecimal(ip->block[1]),
        binToDecimal(ip->block[2]),
        binToDecimal(ip->block[3])
    );
}

void displayMask(const IPv4* ip) {
    printf("%d.%d.%d.%d", 
        binToDecimal(ip->mask[0]),
        binToDecimal(ip->mask[1]),
        binToDecimal(ip->mask[2]),
        binToDecimal(ip->mask[3])
    );
}

char* getIp(void) {                                        // Funcao para ler um endereco IPv4, valida-lo e retornar a string com esse endereco
    char* netIp = calloc(19, sizeof(char));
    int error = 0;

    do {
        system(CLEAR);
        if(error) printf("Endereco IPv4 incorreto...\n");
        printf("Digite o endereco IPv4 (xxx.xxx.xxx.xxx/xx)\n\n");

        fflush(stdin);
        scanf("%s", netIp);
    } while((error = !validateIp(netIp)));                // Validando endereço inserindo

    return netIp;
}

void listNetInfo(const IPv4* ip, const char* msg) {
    IPv4* display_ip;
    printf("\n\n%s", msg);
    int hostBits = getBitsForNet(ip);
    char* netIp = getNetID(ip);


    printf("\n\nIntervalo de hosts:\t");

    display_ip = netFirstHost(netIp);                       // Pegando primeiro host da rede
    displayIP(display_ip);                                  // Exibindo primeiro host
    printf(" ~ ");

    display_ip = netLastHost(netIp, hostBits);              // Pegando ultimo host da rede
    displayIP(display_ip);                                  // Exibindo ultimo host


    printf("\nEndereco de broadcast:  ");
    display_ip = netBroadcast(netIp, hostBits);             // Pegando endereco de broadcast
    displayIP(display_ip);                                  // Exibindo broadcast


    printf("\nMascara da sub-rede:\t");
    displayMask(ip);                                        // Exibindo a mascara da sub-rede


    printf("\nNotacao CIDR:\t\t");
    printf("/%d", hostBits);                                // Exibindo notacao CIDR


    printf("\nID da rede:\t\t");
    display_ip = allocIPv4(netIp);                          // Pegando IP da rede
    displayIP(display_ip);                                  // Exibindo IP da rede


    printf("\nNumero de hosts:\t");
    printf("%d", totalHostsOfNet(ip));                      // Exibindo total de hosts utilizaveis da rede
}