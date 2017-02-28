CC = gcc
CFLAGS = -Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
LINKING=-pthread
DEPS =  my_mutex.h test_my_mutex.h test_mutex.h
OBJ =   my_mutex.o test_my_mutex.o test_mutex.o

%.o: %.c $(DEPS)
	  $(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) mutex.h mutex.c -o mutex.o
	$(CC) -O2 -S test.c -o test.s
	$(CC) $(CFLAGS) $(LINKING) -o $@ $^
	gcc tsl.o mutex.o -o executable


clean:
	rm -vfr *~ $(OBJ) test.s
