#include "../../include/cidr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* maskForNHosts(const int hosts) {                      // Funcao para obter a mascara a partir do numero de hosts desejados
    int i = 0, value = hosts, netBits, count = 0;
    char* mask = calloc(36, sizeof(char));

    while((value*=2) < 256) i++;                            // Total de bits nao utlizados no ultimo octeto para o numero de hosts

    netBits = 32 - (8 - i);                                 // Total de bits 1 na mascara
    mask[35] = '\0';

    i = 0;
    while (i < 35)
    {
        if(count == 8) {
            mask[i++] = '.';                                // Colocando '.' a cada octeto na string
            count = 0;
            continue;
        }

        mask[i++] = (netBits-- > 0 ? '1' : '0');            // Colocando netBits de 1 na mascara e preenchendo restante com 0
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
        *(bin+i) = (actual % 2) + 48;                       // Pegando resto da divisão por 2 como e o algoritmo de conversao decimal -> binario
        actual /= 2;
    }

    return bin;
}

int binToDecimal(const char* binary) {
    int dec = 0, mul = 1;

    for(int i = 7; i >= 0; i--) {
        dec += (*(binary+i) - 48) * mul;                    // Pegando multiplicacao por 2^n como e o algoritmo de conversao binario -> decimal
        mul *= 2;
    }

    return dec;
}

int getBitsForNet(const IPv4* ip) {                         // Funcao para retornar o total de bits da porcao de rede do IP
    int bits = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            if(ip->mask[i][j] == '0') return bits;          // Contando bits 1 da mascara

            bits++;
        }
    }

    return bits;
}

int totalHostsOfNet(const IPv4* ip) {                       // Funcao para retornar total de hosts utilizaveis da rede
    int hostsBits = 32 - getBitsForNet(ip), hosts = 1;

    while (hostsBits-- > 0) hosts *= 2;                     // Realizando o calculo 2^n para o total de hosts
    hosts -= 2;                                             // 2^n - 2 para total de hosts utilizaveis

    return hosts;
}

char* getNetID(const IPv4* ip) {                            // Funcao para retornar o IP base da rede
    int hostBits = 32 - getBitsForNet(ip), bytes[4], chars = 3, aux, index = 0;
    char byte[8], *netId, *byteStr;

    for(int i = 3; i >= 0; i--) {                           // Passeia pelos 4 octetos do bloco de endereco de tras pra frente
        strcpy(byte, ip->block[i]);

        for(int j = 7; j >= 0 && hostBits > 0; j--) {       // Passeia pelos 8 bits do octeto de tras pra frente
            byte[j] = '0';                                  // Atribui bits 0 de tras pra frente para obter o endereco base da rede
            hostBits--;
        }

        bytes[i] = binToDecimal(byte);                      // Convertendo byte para decimal
    }

    for(int i = 0; i < 4; i++) {                            // Verifica o total de caracteres que a string resultante deve alocar para comportar o novo endereco
        aux = bytes[i];
        do {
            chars++;
            aux /= 10;
        } while(aux != 0);
    }

    netId = calloc(chars+1, sizeof(char));                  // Alocando string resultante
    netId[chars] = '\0';

    sprintf(netId, "%d.%d.%d.%d",                           // Escrevendo bytes decimais na string resultante
        bytes[0],
        bytes[1],
        bytes[2],
        bytes[3]
    );

    return netId;
}

IPv4* netFirstHost(const char* netIp) {                     // Funcao para retornar o primeiro IP utlizavel da rede
    IPv4* first = allocIPv4(netIp);

    first->block[3][7] = '1';                               // Atribuindo 1 ao bit mais a direita

    return first;
}

IPv4* netLastHost(const char* netIp, int hostBits) {        // Funcao para retornar o ultimo IP utilizavel da rede
    IPv4* last = allocIPv4(netIp);

    for(int i = hostBits; i < 31; i++) {
        last->block[i/8][i%8] = '1';                        // Atribuindo 1 a todos os bits da porcao de host, exceto o ultimo
    }

    return last;
}

IPv4* netBroadcast(const char* netIp, int hostBits) {       // Funcao para retornar o IP de broadcast
    IPv4* broadcast = netLastHost(netIp, hostBits);         // Pegando o ultimo endereco utilizavel da rede

    broadcast->block[3][7] = '1';                           // Atribuindo 1 ao ultimo bit do endereco

    return broadcast;
}

IPv4* allocIPv4(const char* netIp) {                        // Funcao para alocar um IP a partir da string de entrada do usuario
    int i = 0, j = 0, mask, *bytes = calloc(5, sizeof(int));
    char ch;
    IPv4* ip = calloc(1, sizeof(IPv4));
    ip->block = calloc(4, sizeof(char*));
    ip->mask = calloc(4, sizeof(char*));

    while ((ch = *(netIp+(i++))) != '\0')
    {
        if(ch == 46 || ch == 47) {                          // Se encontrar '.' ou '/' pula para o proximo indice da string
            j++;
            continue;
        }

        bytes[j] *= 10;
        bytes[j] += ch-48;                                  // Convertendo caractere em ASCII em int
    }

    for(i = 0; i < 4; i++) ip->block[i] = decimalToBin(bytes[i]);   // Convertendo numeros da string de entrada em binario

    mask = bytes[4];
    for(i = 0; i < 4; i++) {
        ip->mask[i] = calloc(9, sizeof(char));
        ip->mask[i][8] = '\0';

        for(j = 0; j < 8; j++) ip->mask[i][j] = (mask-- > 0 ? '1' : '0');   // Criando mascara a partir da notacao CIDR
    }

    return ip;
}

void changeMask(IPv4* ip, char* newMask) {                      // Funcao para trocar a mascara do IP
    int index = 0, j = 0;

    for(int i = 0; i < 35; i++) {
        if(newMask[i] == '.') {                                 // Se encontrar '.' pula para o proximo indice da mascara
            index++;
            j = 0;
            continue;
        }

        ip->mask[index][j++] = newMask[i];                      // Copiando bit da mascara para o IP
    }
}