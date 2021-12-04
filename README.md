# IP-CIDR-Redes2
Trabalho de universidade para estudo de IPv4 CIDR
<hr>

### Compilação

#### Windows

com Make

```
make windows
```

sem Make

```
gcc -c src/ip/cidr.c -o obj/cidr.o
gcc -c src/ui/tests.c -o obj/tests.o
gcc -c src/ui/ui.c -o obj/ui.o
gcc obj/cidr.o obj/tests.o obj/ui.o main.c -o IPv4Calc.exe -pedantic -O3 -Wall
```


#### Linux

com Make

```
make linux
```

sem Make

```
gcc -c src/ip/cidr.c -o obj/cidr.o
gcc -c src/ui/tests.c -o obj/tests.o
gcc -c src/ui/ui.c -o obj/ui.o
gcc obj/cidr.o obj/tests.o obj/ui.o main.c -o IPv4Calc -pedantic -O3 -Wall
```

<hr>

### Uso

Esse projeto gera um programa bem simples. Ao inicializá-lo o programa irá esperar pelo usuário inserir um IPv4 válido.

![Tela de inserção do IP](https://raw.githubusercontent.com/Ellyzeul/IP-CIDR-Redes2/main/.github/images/ipv4_1.jpg)

Assim que o IP for inserido o programa listará as informações daquele IP com a máscara fornecida. Também listará as informações testando outras máscaras, no caso, máscaras que permitam 128 hosts, 57 hosts, 32 hosts, 180 hosts e 10 hosts respectivamente.

![Informações do IP inserido](https://raw.githubusercontent.com/Ellyzeul/IP-CIDR-Redes2/main/.github/images/ipv4_2.jpg)