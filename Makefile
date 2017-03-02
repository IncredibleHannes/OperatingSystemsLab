CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) ipcsignal.c -o ipcsignal
clean:
	rm -vfr *~ ipcsignal 
