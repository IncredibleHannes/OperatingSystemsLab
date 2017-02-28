CC = gcc
CFLAGS = -Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
LINKING=-lpthread

#OBJ = my_mutex.o test_my_mutex test_mutex mutex.o my_tsl.o
OBJ = my_mutex.o test_my_mutex test_mutex mutex.o my_tsl.o


all:

	$(CC) $(CFLAGS) $(DEBUG) -c mutex.c
	$(CC) $(CFLAGS) $(DEBUG) test_mutex.c -o test_mutex $(LINKING) mutex.o tsl.o

	as my_tsl.s -o my_tsl.o
	$(CC) $(CFLAGS) $(DEBUG) -c my_mutex.c
	$(CC) $(CFLAGS) $(DEBUG) test_my_mutex.c -o test_my_mutex $(LINKING) my_mutex.o my_tsl.o

	$(CC) -O2 -S test.c -o test.s

tsl:
	$(CC) $(CFLAGS) $(DEBUG) -c mutex.c
	$(CC) $(CFLAGS) $(DEBUG) test_mutex.c -o test_mutex $(LINKING) mutex.o tsl.o

mytsl:
ifeq ($(OS), Ubuntu)
	as my_tsl.s -o my_tsl.o
endif
	$(CC) $(CFLAGS) $(DEBUG) -c my_mutex.c
	$(CC) $(CFLAGS) $(DEBUG) test_my_mutex.c -o test_my_mutex $(LINKING) my_mutex.o my_tsl.o

examle:
		$(CC) -O2 -S test.c -o test.s

clean:
	rm -vfr *~ $(OBJ) test.s
