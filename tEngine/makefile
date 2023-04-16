CC = gcc 
CFLAGS = -std=gnu17 -pedantic -Wall -Wextra -I../include
DIR := $(shell pwd)

libtEngine.so: tEngine.o
	$(CC) $(CFLAGS) -shared -o libtEngine.so tEngine.o

tEngine.o: tEngine.c
	$(CC) $(CFLAGS)  -c -fPIC tEngine.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean: 
	rm *.o *.out

test: test.o libtEngine.so
	$(CC) test.c $(CFLAGS) -L$(DIR) -ltEngine -Wl,-rpath=$(DIR) -o test.out
	# . ./LDPath.sh 
