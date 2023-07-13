# This directory depends on the tEngine directory. 
# Run make in the tEngine directory first.

CC=gcc
CFLAGS = -std=gnu17 -pedantic -Wall -Wextra -lm -I../tEngine
# CFLAGS = -std=gnu17 -pedantic -Wall -Wextra -lm -I../tEngine -L../tEngine -ltEngine -Wl,-rpath=../tEngine

all: main.o
	$(CC) $(CFLAGS) main.o ../tEngine/tEngine.o -o a.out

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 


