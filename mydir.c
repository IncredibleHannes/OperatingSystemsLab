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

int main(int argc, char **argv)
{
  int mode;
  char *path;
  DIR *dir;
  getparams(argc, argv, &mode, &path);
  getdirhandler(path, &dir);
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
