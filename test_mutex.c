#include "test_mutex.h"
//Johannes Hartmann, Jonas Einig

int main(int argc, char **argv)
{
    unsigned char *mutex = (unsigned char*)malloc(sizeof(char));
    mutex_lock(mutex);
}
