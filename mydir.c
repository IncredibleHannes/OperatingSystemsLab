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

#include <sys/types.h>
#include <dirent.h>

void getparams(int argc, char **argv, int *mode, char **path);
void getdirhandler(char *path, DIR **dir);
void printdir(DIR **dir, int mode, char *parentpath);

int main(int argc, char **argv)
{
  // 0: -1aF 1: -1aFR
  int mode;
  char *path;
  DIR *dir;
  getparams(argc, argv, &mode, &path);
  getdirhandler(path, &dir);
  printdir(&dir, mode, path);
  closedir(dir);
  return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, int *mode, char **path)
{
  // Default arguemnts
  *mode = 0;
  *path = ".";
  // 2 arguments given
  if (argc == 3) {
    if (strcmp("-r", argv[1]) == 0) {
      *mode = 1;
      *path = argv[2];
      return;
    }
  }
  // 1 argument given
  if (argc == 2) {
    if (strcmp("-r", argv[1]) == 0) {
      *mode = 1;
      return;
    } else {
      *path = argv[1];
      return;
    }
  }
  // no arguments given
  if (argc == 1) {
    return;
  }
  fprintf(stderr,
    "Benutzung:\n"
    "\n"
    "  %s [-r] [name]\n", argv[0]);
  exit(EXIT_FAILURE);
}

void getdirhandler(char *path, DIR **dir)
{
  if ((*dir = opendir(path)) == NULL) {
        fprintf(stderr, "Cannot open directory %s \n", path);
        exit(EXIT_FAILURE);
  }
}

void printdir(DIR **dir, int mode, char *parentpath)
{
  struct dirent *currentEntry = readdir(*dir);
  while (currentEntry != NULL){
    if(currentEntry->d_type == 4){
      // print the diractory in fancy colouring
      printf("%s%s%s/\n", "\x1B[34m", currentEntry->d_name, "\x1B[0m");
    } else {
      printf("%s%s\n", "\x1B[0m", currentEntry->d_name);
    }
    currentEntry = readdir(*dir);
  }
  // recursive direcory printing
  if(mode == 1){

    rewinddir(*dir);
    currentEntry = readdir(*dir);

    while (currentEntry != NULL){
      // if currententy is directory and not one of "." or ".."
      if (currentEntry->d_type == 4 && (strcmp(currentEntry->d_name, ".") != 0)
          && (strcmp(currentEntry->d_name, "..") != 0)) {
        // build new path string and open subdirectory
        char *path = (char*) malloc(strlen(parentpath) +
            strlen(currentEntry->d_name) + 2);
        strcat(path, parentpath);
        strcat(path, "/");
        strcat(path, currentEntry->d_name);
        DIR *newdir;
        getdirhandler(path, &newdir);
        // print headline
        printf("\n%s:\n", path);
        // recursive call of printdir
        printdir(&newdir, mode, path);
      }
      currentEntry = readdir(*dir);
    }
  }
}
