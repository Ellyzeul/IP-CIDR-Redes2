main:
	gcc -c src/ip/cidr.c -o obj/cidr.o
	gcc -c src/ui/tests.c -o obj/tests.o
	gcc obj/cidr.o obj/tests.o main.c -o main.exe