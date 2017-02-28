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
	gcc -c mutex.c
	gcc -std=c99 test_mutex.c -o test_mutex.o -lpthread mutex.o tsl.o
#	$(CC) -O2 -S test.c -o test.s
#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) -c mutex.c tsl.o
#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) test_mutex.c -o test_mutex mutex.o

#	$(CC) $(CFLAGS) $(DEBUG) $(LINKING) -o $@ $^

clean:
	rm -vfr *~ $(OBJ) test.s mutex.o
