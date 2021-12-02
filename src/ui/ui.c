#include "../../include/ui.h"
#include "../../include/cidr.h"
#include <stdlib.h>
#include <stdio.h>


_Bool validateIp(const char* netIp) {
    char actChar;
    int count = 0, byte = 0;

    for(int i = 0; i < 18; i++) {
        actChar = *(netIp+i);

        if(*(netIp+i-3) == '/') break;                  // Verificacao ao final da string se ja ultrapassou o '/' no caso de a string de entrada ser menor do que 18 caracteres
        if(actChar == 46 || actChar == 47) {            // Verificacao se foram encontrados os caracteres '.' ou '/' e se o número nesse intervalo e valido
            if(byte > 255) return 0;

            byte = 0;
            count = 0;
            continue;
        }
        else if(actChar < 48 || actChar > 57) return 0; // Verificacao se o caracter atual e um digito ou se e invalido
        if(count == 3) return 0;                        // Verificacao se o numero na string, antes do ponto de separacao é maior do que quatro algarismos

        byte *= 10;
        byte += actChar-48;                             // Conversao de string para decimal

        count++;                                        // Incrementando contador de digitos antes do proximo ponto
    }
    if(byte > 32) return 0;                             // Verificacao se a notacao CIDR está num intervalo valida

    return 1;                                           // Caso a execucao nao seja barrada em nenhuma restricao, entao um valor verdadeiro sera retornado
}

char* index() {
    // Funcao para ler um endereco IPv4, valida-lo e retornar a string com esse endereco

    char* netIp = calloc(19, sizeof(char));
    int error = 0;

    do {
        system("cls");
        if(error) printf("Endereco IPv4 incorreto...\n");
        printf("Digite o endereco IPv4 (xxx.xxx.xxx.xxx/xx)\n\n");

        fflush(stdin);
        scanf("%s", netIp);
    } while((error = !validateIp(netIp)));

    return netIp;
}