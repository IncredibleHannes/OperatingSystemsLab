#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *perform_work(void *argument)
{
    printf("new thread running\n");
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t threads;
    pthread_create(&threads, NULL, perform_work, NULL);

    // wait for thread to complete
    pthread_join(threads, NULL);

    printf("Thread completed successfully\n");
    exit(EXIT_SUCCESS);
}
