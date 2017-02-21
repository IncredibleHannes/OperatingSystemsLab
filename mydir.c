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

void getparams(int argc, char **argv, int *mode, char **path);


int main(int argc, char **argv)
{
  int mode;
  char *path;
  getparams(argc, argv, &mode, &path);
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
