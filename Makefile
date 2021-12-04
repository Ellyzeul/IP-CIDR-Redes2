main:
	gcc -c src/ip/cidr.c -o obj/cidr.o
	gcc -c src/ui/tests.c -o obj/tests.o
	gcc -c src/ui/ui.c -o obj/ui.o
	gcc obj/cidr.o obj/tests.o obj/ui.o main.c -o IPv4Calc.exe -pedantic -O3 -Wall