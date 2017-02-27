CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
LINKING=-pthread
all:
	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) threadProgram.c -o threadProgram
	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) matrixManyThread.c -o matrixManyThread
clean:
	rm -vfr *~ threadProgram
