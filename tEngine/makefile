CC = gcc 

CFLAGS = -std=c99 -pedantic -Wall -Wextra -I../include $(CWARNINGS) $(COPTIMISING)

CWARNINGS=-Wall -Wextra -Wpedantic -Wformat=2 -Wswitch-default -Wpointer-arith -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls -Wold-style-definition 

COPTIMISING=-O0 -ggdb3 -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing -g

# CFLAGS=-std=c11 $(CWARNINGS) $(COPTIMISING) -lm

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
