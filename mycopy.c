#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void getparams(int argc, char **argv, size_t *buflen, char **inname,
               char **outname);

void getfilehandles(char *inname, char *outname, int *infd, int *outfd);

void copy(int infd, int outfd, size_t buflen);

int askUsr(char* question);

int main(int argc, char **argv)
{
  time_t starttime = time(NULL);
  char *inname;
  char *outname;
  size_t buflen;
  int infd;
  int outfd;

  getparams(argc, argv, &buflen, &inname, &outname);
  getfilehandles(inname, outname, &infd, &outfd);
  copy(infd, outfd, buflen);
  if (close(outfd) == -1) {
    perror("Fehler beim Schließen der Ausgabedatei");
    exit(EXIT_FAILURE);
  }

  if (close(infd) == -1) {
    perror("Fehler beim Schließen der Eingabedatei");
    exit(EXIT_FAILURE);
  }
    
 printf("Time needed: %.2f\n", (double)(time(NULL) - starttime));

  return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, size_t *buflen, char **inname,
               char **outname)
{
  int opterrflag = 0;
  int opt;

  /* Standard-Wert */
  *buflen = 1;

  /* Kommandozeilenoptionen verarbeiten */
  while ((opt = getopt(argc, argv, "b:")) != -1) {
    switch (opt) {
    case 'b':
      opterrflag = sscanf(optarg, "%zu", buflen) != 1 || *buflen <= 0
        || *buflen >= 1024 * 1024;
      break;
    case '?':
      opterrflag = 1;
      break;
    }
  }

  if (optind < argc) {
    *inname = argv[optind++];
  } else {
    opterrflag = 1;
  }

  if (optind < argc) {
    *outname = argv[optind];
  } else {
    opterrflag = 1;
  }

  if (opterrflag) {
    fprintf(stderr,
            "Benutzung:\n"
            "\n"
            "  %s [-b n] <Eingabedatei> <Ausgabedatei>\n"
            "\n" "b[=1]: Puffergröße mit 0 < n <= 1024^2\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

void getfilehandles(char *inname, char *outname, int *infd, int *outfd)
{
  if(strcmp(inname, outname)==0){
     perror("Ein- und Ausgabepfad sind gleich");
      exit(EXIT_SUCCESS);
  }
  // open the input file
  if (access(inname, F_OK) != -1) {
    *infd = open(inname, O_RDONLY);
    if (*infd == -1) {
      perror("Fehler beim Öffnen der Eingabedatei");
      exit(EXIT_FAILURE);
    }
  } else {
    perror("Eingabedatei nicht gefunden");
    exit(EXIT_FAILURE);
  }
  
  // reading permissions of the input file descriptor
  struct stat permissions;
  if (stat(inname, &permissions) == -1) {
    perror("Error reading permissions");
    close(*infd);
    exit(EXIT_FAILURE);
  }
 
  // open the output file
  if (access(outname, F_OK) != -1) {
    int a = askUsr("Möchten Sie die bestehende Datei ersetzen?\n");
    if (a == 1) {
      remove(outname);
      *outfd = open(outname, O_CREAT | O_WRONLY, permissions.st_mode);
    } else {
      perror("Thank you for using this incredible application. We look \
      forward to serve you again.");
      close(*infd);
      exit(EXIT_SUCCESS);
    }
  } else {
//     fseek(infd, 0L, SEEK_END);
//     int size = ftell(infd);
//     rewind(infd); 
    *outfd = open(outname, O_CREAT | O_WRONLY, permissions.st_mode);
  }
  if (*outfd == -1) {
    perror("Fehler beim Öffnen der Ausgabedatei");
    close(*infd);
    exit(EXIT_FAILURE);
  }
}


void copy(int infd, int outfd, size_t buflen)
{
  char buffer[buflen];
  while (infd != EOF) {
    int readSize = read(infd, buffer, buflen);
    if (readSize == -1) {
      perror("Error reading inputfile.");
      close(infd);
      close(outfd);
      exit(EXIT_FAILURE);
    }    
    int  writeSize = write(outfd, buffer, readSize);
    if (writeSize == -1) {
      perror("Error writing outpfile");
      close(infd);
      close(outfd);
      exit(EXIT_FAILURE);
    }
    if (readSize != writeSize) {
      perror("Programm made mess");
      close(infd);
      close(outfd);
      exit(EXIT_FAILURE);
    }
    if (readSize < buflen) {
      break;
    }
  }
}

int askUsr(char* question)
{
  char choice;
    printf(question);
    printf("Please enter [y]es or [n]o: ");
  while (1) {
    choice = getchar();
    fflush(stdin);
    // validate input
    if (choice == 'y' || choice == 'n' || choice == 'j') {
        break;
    } else {
      printf("Please enter only \'y\' or \'n\'!\n");
    }
  }
  switch (choice) {
    case 'j': return 1;
    case 'y': return 1;
    case 'n': return 0;
    default : return -1;
  }
}
