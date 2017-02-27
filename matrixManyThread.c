#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *memcpy(void *dest, const void *src, size_t n);

#define MATRIX_SIZE 5
typedef struct task task;

struct task {
    double (*matrix)[MATRIX_SIZE][MATRIX_SIZE];
    double result;
    int i;
    int j;
};

void *perform_work(void *argument)
{
    struct task  *argValue = (struct task *) argument;

    argValue->result = 0;
    for (int k = 0; k < MATRIX_SIZE; k++) {

        argValue->result = argValue->result + (*argValue->matrix)[argValue->i][k] *
                           (*argValue->matrix)[k][argValue->j];

    }

    printf("new thread running\n");
    return NULL;
}

int main(int argc, char **argv)
{

    double matrix[MATRIX_SIZE][MATRIX_SIZE] =
    {   1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        1, 2, 3, 4, 5
    };

    pthread_t threads[ MATRIX_SIZE * MATRIX_SIZE ];

    struct task tasklist[ MATRIX_SIZE * MATRIX_SIZE];


    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            //task tmp = {.matrix = matrix,  .i = i, .j = j};
            //memcpy(tasklist[(i * MATRIX_SIZE) + j].matrix, matrix, MATRIX_SIZE);
            tasklist[(i * MATRIX_SIZE) + j].matrix = &matrix;
        }
    }


    //TODO: how many tasks and threads

    pthread_create(&threads[1], NULL, perform_work, NULL);

    // wait for thread to complete
    // block until thread 'index' completes
    pthread_join(threads[ 1 ], NULL);

    printf("In main: All threads completed successfully\n");
    exit(EXIT_SUCCESS);
}
