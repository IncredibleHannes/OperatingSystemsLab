#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 5

void printMatrix(double (*matrix)[MATRIX_SIZE][MATRIX_SIZE]);

typedef struct task task;

struct task {
    double (*matrix)[MATRIX_SIZE][MATRIX_SIZE];
    double (*result)[MATRIX_SIZE];
    //line idx
    int i;
};

void *perform_work(void *argument)
{
    struct task *argValue = (struct task *) argument;
    (*argValue->result)[argValue->i] = 0;

    for (int j = 0; j < MATRIX_SIZE; j++) {
        (*argValue->result)[argValue->i] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            (*argValue->result)[argValue->i] =(*argValue->result)[argValue->i] + (*argValue->matrix)[argValue->i][k] *
                                  (*argValue->matrix)[k][j];
        }
    }

    free(argument);
    return NULL;
}

int main(int argc, char **argv)
{

    double matrix[MATRIX_SIZE][MATRIX_SIZE] =
    {   {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5}
    };

    double resultMatrix [MATRIX_SIZE][MATRIX_SIZE] =  {{0}};

    pthread_t threads[ MATRIX_SIZE ];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            struct task *threadTask = (struct task *) malloc(sizeof(struct task));
            threadTask->matrix = &matrix;
            threadTask->i = i;
            threadTask->result = &(resultMatrix[i]);

            pthread_create(&(threads[i]), NULL, perform_work, threadTask);
        }
    }

    // wait for thread to complete
    // block until thread 'index' completes
    for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }
    printMatrix(&resultMatrix);
    exit(EXIT_SUCCESS);
}



void printMatrix(double (*matrix)[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f, ", (*matrix)[i][j]);
        }
        printf("\n");
    }
}
