#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

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
    }
}

int isNumber(char *number) {
    int length = strlen(number);
    for (int i = 0; i < length; i++) {
        if (!isdigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

void calculatePi(int iterations) {
    while(1);
}
