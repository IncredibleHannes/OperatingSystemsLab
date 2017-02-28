CC = gcc
CFLAGS = -Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
LINKING=-pthread
DEPS = mutex.h my_mutex.h test_my_mutex.h test_mutex.h
OBJ = mutex.o my_mutex.o test_my_mutex.o test_mutex.o test.o

%.o: %.c $(DEPS)
	  $(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -vfr *~ *.o
