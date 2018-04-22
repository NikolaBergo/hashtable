main.o: main.c
	gcc -c -o main.o main.c
hash.o: hash.c
	gcc -c -o hash.o hash.c
hash: main.o hash.o
	gcc -o hash main.o hash.o
