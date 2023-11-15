CC = gcc 

CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -I../include $(CWARNINGS) $(COPTIMISING)

CWARNINGS=-Wall -Wextra -Wpedantic -Wformat=2 -Wswitch-default -Wpointer-arith -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls -Wold-style-definition 

COPTIMISING=-O0 -ggdb3 -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing -g

DIR := $(shell pwd)

# need to set LD_LIBRARY_PATH

ANSI_RED=\033[0;31m
ANSI_BLUE=\033[0;34m
ANSI_RESET=\033[0m 

libtEngine.so: tEngine.o
	@echo "--------------------------------------------------"
	@echo -e "$(ANSI_RED)LINKING$(ANSI_RESET): Producing shared library libtEngine.so"

	@$(CC) $(CFLAGS) -shared -o libtEngine.so tEngine.o

	@echo "--------------------------------------------------"

tEngine.o: tEngine.c
	@echo "--------------------------------------------------"
	@echo -e "$(ANSI_RED)COMPILING$(ANSI_RESET): producing tEngine.o"

	@$(CC) $(CFLAGS)  -c -fPIC tEngine.c

test.o: test.c
	@echo "--------------------------------------------------"
	@echo -e "$(ANSI_RED)COMPILING$(ANSI_RESET): producing test.o"
	@$(CC) $(CFLAGS) -c test.c

clean: 
	rm -f *.o *.out

test: test.o libtEngine.so
	@$(CC) test.c $(CFLAGS) -L$(DIR) -ltEngine -Wl,-rpath=$(DIR) -o test.out
