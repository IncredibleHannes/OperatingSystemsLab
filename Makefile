CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
all:
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_sequential.c -o calc_pi_sequential -lm
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_critical.c -o calc_pi_critical -lm
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_atomic.c -o calc_pi_atomic -lm
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_reduction.c -o calc_pi_reduction -lm
clean:
	rm -vfr *~ calc_pi_sequential calc_pi_reduction calc_pi_atomic calc_pi_critical
