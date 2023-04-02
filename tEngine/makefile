CC = gcc
CFLAGS = -std=gnu17 -pedantic -Wall -Wextra -I/home/hhyh/psu/lib/c
DIR := $(shell pwd)

headerTest: headerTest.o libtEngine.so
	$(CC) $(CFLAGS)  headerTest.c -L$(DIR) -ltEngine 
	. ./LDPath.sh

libtEngine.so: tEngine.o
	$(CC) $(CFLAGS) -shared -o libtEngine.so tEngine.o

tEngine.o: tEngine.c
	$(CC) $(CFLAGS)  -c -fPIC tEngine.c

headerTest.o: headerTest.c
	$(CC) $(CFLAGS) -c headerTest.c

clean: 
	rm *.o *.so *.out
