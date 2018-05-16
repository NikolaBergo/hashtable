#Makefile

OBJS=main.o hash.o list.o
HEADERS=hash.h list.h

all:hash

hash:$(OBJS)
        gcc -fprofile-arcs -ftest-coverage $^ -o $@

%.o:%.c $(HEADERS)
        gcc -c -fprofile-arcs -ftest-coverage $<

clean:
        rm -f *.o
        rm -f hash
