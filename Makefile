CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_sequential.c -o calc_pi_sequential -lm
clean:
	rm -vfr *~ calc_pi_sequential
