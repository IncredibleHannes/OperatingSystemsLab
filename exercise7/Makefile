CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
LINKING=-lm -fopenmp
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_sequential.c -o calc_pi_sequential $(LINKING)
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_critical.c -o calc_pi_critical $(LINKING)
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_atomic.c -o calc_pi_atomic $(LINKING)
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_reduction.c -o calc_pi_reduction $(LINKING)
clean:
	rm -vfr *~ calc_pi_sequential calc_pi_reduction calc_pi_atomic calc_pi_critical
