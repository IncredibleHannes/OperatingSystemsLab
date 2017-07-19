#include "mutex.h"
//Johannes Hartmann, Jonas Einig

void mutex_lock(unsigned char *adr)
{
    while (tsl(adr) == 1);
}

void mutex_unlock(unsigned char *adr)
{
    *adr = 0;
}
