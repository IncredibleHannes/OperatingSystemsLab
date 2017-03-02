#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sendChar(char input, pid_t parentid);
void sendBit(int bit, pid_t parentid);
void reciverSignalHandler(int sigNumber);
void senderSignalHandler(int sigNumber);
void error(char const *errorMassage);


// Elternvariablen
volatile int signalcount = 0;
volatile int finished = 0;
volatile char resultString[100];
volatile char received;
volatile pid_t pid;

// Kindvariablen
volatile int receiverReady = 0;

int main(int argc, char **argv)
{
    if ((pid = fork()) < 0) {
        error("should not happen");
    } else if (pid == 0) {
        /* Kindprozess */
        if (signal(SIGUSR1, senderSignalHandler) == SIG_ERR)
            error("Fehler beim setzen der Signalhandler");
        pid_t parentid = getppid();

        char *input = (char *) malloc(sizeof(char) * 101);
        while (receiverReady == 0);
        printf("Bitte geben Sie eine Zeichenkette < 100 Zeichen ein:\n");
        if (fgets(input, 100, stdin) == NULL)
            error("Fehler beim lesen des Inputs");
        for (int i = 0; i < 100; i++) {
            sendChar(input[i], parentid);
            if (input[i] == '\0') {
                break;
            }
        }
    } else {
        /* Elternprozess */
        if (signal(SIGUSR1, reciverSignalHandler) == SIG_ERR)
            error("Fehler beim setzen der Signalhandler");
        if (signal(SIGUSR2, reciverSignalHandler) == SIG_ERR)
            error("Fehler beim setzen der Signalhandler");
        // give the child process some time to make signalhandler ;) 
        sleep(0.1);
        if (kill(pid, SIGUSR1) < 0)
            error("Fehler beim senden von der bereitschaft");
        while (finished == 0);
        printf("Received result %s", resultString);

    }
}

void sendChar(char input, pid_t parentid)
{
    for (int i = 0; i < 8; i++) {
        // wait for ack
        while (receiverReady == 0);

        if (input & 1) {
            sendBit(1, parentid);
        } else {
            sendBit(0, parentid);
        }
        input = input >> 1;
    }
}

void senderSignalHandler(int sigNumber)
{
    if (sigNumber == SIGUSR1) {
        receiverReady = 1;
    } else
        error("Fehler beim empfangen der Signale");
    if (signal(SIGUSR1, senderSignalHandler) == SIG_ERR)
        error("Fehler beim setzen der Signalhandler");
}

void reciverSignalHandler(int sigNumber)
{
    if (sigNumber == SIGUSR1) {
        signalcount ++;
        if (signal(SIGUSR1, reciverSignalHandler) == SIG_ERR)
            error("Fehler beim setzen der Signalhandler");
    } else if (sigNumber == SIGUSR2) {
        received = received | 1 << (signalcount % 8);
        signalcount ++;
        if (signal(SIGUSR2, reciverSignalHandler) == SIG_ERR)
            error("Fehler beim setzen der Signalhandler");
    } else
        error("Fehler beim empfangen der Signale");


    if ((signalcount % 8) == 0) {
        if (received == '\0') {
            finished = 1;
        }
        resultString[div(signalcount, 8).quot - 1] = received;
        received = '\0';
    }
    if (kill(pid, SIGUSR1) < 0)
        error("Fehler beim senden von der bereitschaft");
}

void sendBit(int bit, pid_t parentid)
{
    if (bit == 0) {
        if (kill(parentid, SIGUSR1) < 0)
            error("Fehler beim senden von einem Bit");
    } else {
        if (kill(parentid, SIGUSR2) < 0)
            error("Fehler beim senden von einem Bit");
    }
    receiverReady = 0;
}

void error(char const *errorMassage) {
    perror(errorMassage);
    exit(EXIT_FAILURE);
}
