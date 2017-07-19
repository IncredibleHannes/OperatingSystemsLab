#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <math.h>

void getparams(int argc, char **argv, int *iterations);
int isNumber(char *number);
void calculatePi(int iterations);

int main(int argc, char **argv)
{
    int iterations;
    getparams(argc, argv, &iterations);
    calculatePi(iterations);
    return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, int *iterations)
{
    if (argc == 2 && isNumber(argv[1])) {
        *iterations = atoi(argv[1]);
        if (*iterations > 1) {
            return;
        }
    }
    fprintf(stderr,  "Insert a number greater 1!\n");
    exit(EXIT_FAILURE);
}

int isNumber(char *number)
{
    int length = strlen(number);
    for (int i = 0; i < length; i++) {
        if (!isdigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

void calculatePi(int iterations)
{
    double oneStep = 1.0 / iterations;
    double lowbound = 0;
    double higherbound = 0;
    for (int i = 1; i <= iterations; i++) {
        if (i < iterations) {
            lowbound += (sqrt(1 - pow(i * oneStep, 2)) * oneStep);
        }
        higherbound += (sqrt(1 - pow((i - 1) * oneStep, 2)) * oneStep);
    }

    lowbound = lowbound * 4;
    higherbound = higherbound * 4;
    printf("Lower Bound: %.12f\n", lowbound);
    printf("Upper Bound: %.12f\n", higherbound);
}
