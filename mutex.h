#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include "tsl.o"

int tsl(unsigned char *adr);
void mutex_lock(unsigned char *adr);
void mutex_unlock(unsigned char *adr);
