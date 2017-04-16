CC=gcc
STD=-std=c11
FLAGS = -Wall -std=c11 -I/usr/local/include 
LINKFLAGS =$(STD) -g -o
COMPFLAGS =$(STD) -Wall -g -c 

all: lager

lager: lager.o tree.o utils.o list.o item.o
	$(CC) $(LINKFLAGS) lager $^

lager.o: lager.c utils.h list.h tree.h item.h
	$(CC) $(COMPFLAGS) lager.c

tree.o: tree.c tree.h list.h item.h
	$(CC) $(COMPFLAGS) tree.c

utils.o: utils.c utils.h
	$(CC) $(COMPFLAGS) utils.c

list.o: list.c list.h
	$(CC) $(COMPFLAGS) list.c

item.o: item.c item.h utils.h list.h tree.h
	$(CC) $(COMPFLAGS) item.c

clean:
	rm -f lager *.o

unittest: unit_test.c list.c tree.c
	$(CC) $(FLAGS) -o test unit_test.c list.c tree.c item.c utils.c -L/usr/local/lib -lcunit
	@./test
	
run: lager
	./lager