CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) threadProgram.c -o threadProgram
clean:
	rm -vfr *~ threadProgram
