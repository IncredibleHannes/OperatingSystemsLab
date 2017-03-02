#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sendChar(char input, pid_t parentid);


int main(int argc, char **argv)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Fehler... \n");
    } else if (pid == 0) {
        /* Kindprozess */
        pid_t parentid = getppid();

        char *input = (char *) malloc(sizeof(char) * 101);
        printf("Bitte geben Sie eine Zeichenkette < 100 Zeichen ein:\n");
        if (fgets(input, 101, stdin) == NULL) {
            perror("Fehler beim lesen des Inputs");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 100; i++) {
            sendChar(input[i], parentid);
            if (input[i] == '\0') {
                break;
            }
        }
    } else {
        while (1);
    }
}

void sendChar(char input, pid_t parentid) {
    for (int i = 0; i < 8; i++) {
        // wait for ack
        if (input & 1) {
            sendsiglgnal1;
        } else {
            sendsignal0;
        }
        input = input >> 1;
    }

}
