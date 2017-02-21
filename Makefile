CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) mydir.c -o mydir
clean:
	rm -vfr *~ reverse mycopy
