#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MATRIX_SIZE 5


void *memcpy(void *dest, const void *src, size_t n);
void printMatrix(double (*matrix)[MATRIX_SIZE][MATRIX_SIZE]);

typedef struct task task;

struct task {
    double (*matrix)[MATRIX_SIZE][MATRIX_SIZE];
    double *result;
    int i;
    int j;
};

void *perform_work(void *argument)
{
    struct task *argValue = (struct task *) argument;
printf("idx : %d , %d  ",   (*argValue).i , (*argValue).j );
    (*argValue->result) = 0;

    for (int k = 0; k < MATRIX_SIZE; k++) {
        (*argValue->result) = (*argValue->result) + (*argValue->matrix)[argValue->i][k] *
                              (*argValue->matrix)[k][argValue->j];
    }

    printf("%f\n",(*argValue->result));
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

    double resultMatrix [MATRIX_SIZE][MATRIX_SIZE] =  {   {1, 2, 3, 4, 5},
          {6, 7, 8, 9, 10},
          {1, 2, 3, 4, 5},
          {6, 7, 8, 9, 10},
          {1, 2, 3, 4, 5}
      };

    printMatrix(&resultMatrix);
    pthread_t threads[ MATRIX_SIZE * MATRIX_SIZE ];


    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            struct task threadTask ;//= malloc();

            //task tmp = {.matrix = matrix,  .i = i, .j = j};
            //memcpy(tasklist[(i * MATRIX_SIZE) + j].matrix, matrix, MATRIX_SIZE);
            threadTask.matrix = &matrix;
            threadTask.i = i;
            threadTask.j = j;
            threadTask.result = &(resultMatrix[i][j]);

            pthread_create(&(threads[((i * MATRIX_SIZE) + j)]), NULL, perform_work, &threadTask);

        }
    }

    // wait for thread to complete
    // block until thread 'index' completes
    for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
        pthread_join(threads[ i ], NULL);
    }


    printMatrix(&resultMatrix);

    printf("In main: All threads completed successfully\n");
    exit(EXIT_SUCCESS);
}



void printMatrix(double (*matrix)[MATRIX_SIZE][MATRIX_SIZE]) {

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f, ", (*matrix)[i][j] );
        }
        printf("\n");
    }
}
