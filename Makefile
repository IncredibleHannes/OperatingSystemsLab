CC = gcc
CFLAGS = -Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
LINKING=-lpthread

DEPS = my_mutex.h test_my_mutex.h test_mutex.h
OBJ = my_mutex.o test_my_mutex.o test_mutex.o

%.o: %.c $(DEPS)
	  $(CC) $(CFLAGS) -c -o $@ $<

all:# $(OBJ)
	gcc -std=c99 -O0 -g -c mutex.c
	gcc -std=c99 -O0 -g test_mutex.c -o test_mutex.o -lpthread mutex.o tsl.o

	as my_tsl.s -o my_tsl.o
	gcc -c my_mutex.c
	gcc -std=c99 -O0 -g test_my_mutex.c -o test_my_mutex.o -lpthread my_mutex.o my_tsl.o
#	$(CC) -O2 -S test.c -o test.s
#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) -c mutex.c tsl.o
#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) test_mutex.c -o test_mutex mutex.o

#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) -o $@ $^

clean:
	rm -vfr *~ $(OBJ) test.s mutex.o
