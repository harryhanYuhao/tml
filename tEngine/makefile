CC = gcc
CFLAGS = -std=gnu17 -pedantic -Wall -Wextra -I$(HOME)/psu/lib/c
DIR := $(shell pwd)

test: test.o libtEngine.so
	$(CC) test.c $(CFLAGS) -L$(DIR) -ltEngine 
	. ./LDPath.sh

libtEngine.so: tEngine.o
	$(CC) $(CFLAGS) -shared -o libtEngine.so tEngine.o

tEngine.o: tEngine.c
	$(CC) $(CFLAGS)  -c -fPIC tEngine.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean: 
	rm *.o *.out
