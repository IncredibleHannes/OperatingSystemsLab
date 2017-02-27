#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MATRIX_SIZE 5
#define SYS_CORES sysconf(_SC_NPROCESSORS_ONLN)

void printMatrix(double (*matrix)[MATRIX_SIZE][MATRIX_SIZE]);

typedef struct task Task;

typedef struct taskQueue TaskQueue;

struct task {
    double (*matrix)[MATRIX_SIZE][MATRIX_SIZE];
    double *result;
    int i;
    int j;
};

struct taskQueue{
    Task **taskQueue;
    int queueLength;
};





void *perform_work(void *argument)
{
    TaskQueue *argValue = (TaskQueue *) argument;

    for(int l = 0; l < argValue->queueLength; l++) {
      Task *tmpTask = argValue->taskQueue[l];
      (*tmpTask->result) = 0;

      for (int k = 0; k < MATRIX_SIZE; k++) {
          (*tmpTask->result) = (*tmpTask->result) + (*tmpTask->matrix)[tmpTask->i][k] *
                                (*tmpTask->matrix)[k][tmpTask->j];
      }
    }
//TODO
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
    TaskQueue workQueues[SYS_CORES];

    for(int i = 0; i < SYS_CORES; i++) {
      workQueues[i].taskQueue = (Task**)malloc(sizeof(Task) * (int)((( MATRIX_SIZE * MATRIX_SIZE ) / SYS_CORES ) +1 ));
      workQueues[i].queueLength = 0;
  }

    pthread_t threads[ SYS_CORES ];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            Task *threadTask = (Task *) malloc(sizeof(Task));
            threadTask->matrix = &matrix;
            threadTask->i = i;
            threadTask->j = j;
            threadTask->result = &(resultMatrix[i][j]);

            TaskQueue* currentQueue = &workQueues[((i*MATRIX_SIZE) + j) % SYS_CORES];
            currentQueue->taskQueue[currentQueue->queueLength] = threadTask;
            currentQueue->queueLength++;

        }
    }

    for (int i = 0; i < SYS_CORES ; i++) {
        pthread_create(&(threads[i]), NULL, perform_work, &workQueues[i]);
    }
    //

    // wait for thread to complete
    // block until thread 'index' completes
    for (int i = 0; i < SYS_CORES ; i++) {
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
