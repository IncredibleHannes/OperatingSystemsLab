#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "mutex.h"

int main(int argc, char **argv);

void *perform_work(void *argument);
typedef struct threadArguments ThreadArguments;

struct threadArguments {
    unsigned char *mutex;
    int criticalResorce;
};

int main(int argc, char **argv)
{
    ThreadArguments *threadArguments = (ThreadArguments *)malloc(sizeof(ThreadArguments));
    threadArguments->mutex = (unsigned char *)malloc(sizeof(char));
    (threadArguments->criticalResorce) = 0;

    pthread_t thread1;
    pthread_create(&thread1, NULL, perform_work, threadArguments);
    pthread_t thread2;
    pthread_create(&thread2, NULL, perform_work, threadArguments);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread completed successfully with critical resorce: %d\n", threadArguments->criticalResorce);
    free(threadArguments->mutex);
    exit(EXIT_SUCCESS);
}

void *perform_work(void *argument)
{
    ThreadArguments *threadArguments = (ThreadArguments *) argument;
    mutex_lock(threadArguments->mutex);
    if(threadArguments->criticalResorce == 0){
      sleep(1);
      threadArguments->criticalResorce = threadArguments->criticalResorce + 1 ;
      printf("addet +1\n");
    } else {
      printf("done noting!\n");
    }
    mutex_unlock(threadArguments->mutex);
    return NULL;
}
