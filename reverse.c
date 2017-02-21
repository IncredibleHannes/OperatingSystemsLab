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

void getparams(int argc, char **argv, char **inname);

void getfilehandles(char *inname, char *outname, int *infd, int *outfd);

void reverse(int infd, int outfd);

int askUsr(char const *question);

int main(int argc, char **argv)
{
  time_t starttime = time(NULL);
  char *inname;
  char *outname;
  char const *ending = ".rev";
  int infd;
  int outfd;

  getparams(argc, argv, &inname);
  outname = (char*)malloc(strlen(inname)+strlen(ending)+1);//+1 for the zero-terminator
      //in real code you would check for errors in malloc here
  strcpy(outname, inname);
  strcat(outname, ending);

  getfilehandles(inname, outname, &infd, &outfd);
  reverse(infd, outfd);
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

void getparams(int argc, char **argv, char **inname)
{
  int opterrflag = 0;

  if (optind < argc) {
    *inname = argv[optind++];
  } else {
    opterrflag = 1;
  }

  if (opterrflag) {
    fprintf(stderr,
            "Benutzung:\n"
            "\n"
            "  %s [-b n] <Eingabedatei> <Ausgabedatei>\n"
            , argv[0]);
    exit(EXIT_FAILURE);
  }
}

void getfilehandles(char *inname, char *outname, int *infd, int *outfd)
{
  printf(" inname: %s\n outname : %s\n", inname, outname);
  if (strcmp(inname, outname) == 0) {
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
    *outfd = open(outname, O_CREAT | O_WRONLY, permissions.st_mode);
  }
  if (*outfd == -1) {
    perror("Fehler beim Öffnen der Ausgabedatei");
    close(*infd);
    exit(EXIT_FAILURE);
  }
}


void reverse(int infd, int outfd)
{
  int ctr = 0; // counter for iterating offset

  //move to end of file
  int off_t = lseek(infd, ctr, SEEK_END);
  if (off_t <0) {
    perror("Error seeking end of Inputfile");
  }


  int buflen = 1;
  char buffer[buflen];
  while (off_t >= 0) {
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

    ctr = ctr-1;
    off_t = lseek(infd, ctr, SEEK_END);
  }
}

int askUsr(char const *question)
{
  char choice;
    printf("%s",question);
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
