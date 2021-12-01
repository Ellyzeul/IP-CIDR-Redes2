main:
	gcc -c src/cidr.c -o obj/cidr.o
	gcc obj/cidr.o main.c -o main.exe