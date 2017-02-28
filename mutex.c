#include "mutex"
//Johannes Hartmann, Jonas Einig

void mutex_lock()
{
    while(tsl(*adr) == 1);
}

void mutex_unlock()
{

}
