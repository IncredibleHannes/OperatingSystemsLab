#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void getparams(int argc, char **argv, char **path);
void getdirhandler(char *path, DIR **dir);
void calcstat(DIR **dir, char *parentpath, int stats[]);
void printstat(int stats[]);

int main(int argc, char **argv)
{
  char *path;
  DIR *dir;
  int stats[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  getparams(argc, argv, &path);
  getdirhandler(path, &dir);
  calcstat(&dir, path, stats);
  closedir(dir);
  printstat(stats);
  return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, char **path)
{
  // Default arguemnts
  *path = ".";
  // 1 argument given
  if (argc == 2) {
      *path = argv[1];
      return;
  }
  // no arguments given
  if (argc == 1) {
    return;
  }
  fprintf(stderr,
    "Benutzung:\n"
    "\n"
    "  %s [name]\n", argv[0]);
  exit(EXIT_FAILURE);
}

void getdirhandler(char *path, DIR **dir)
{
  if ((*dir = opendir(path)) == NULL) {
        fprintf(stderr, "Cannot open directory %s \n", path);
        exit(EXIT_FAILURE);
  }
}

void calcstat(DIR **dir, char *parentpath, int *stats)
{
  struct dirent *currentEntry = readdir(*dir);
  while (currentEntry != NULL) {

    char *path = (char*) malloc(strlen(parentpath) +
        strlen(currentEntry->d_name) + 2);
    strcat(path, parentpath);
    strcat(path, "/");
    strcat(path, currentEntry->d_name);

    // check if it is file
    if (currentEntry->d_type == 8) {
      struct stat size;
      if (stat(path, &size) == -1) {
        fprintf(stderr , "Error while reading stats of %s", path);
      }
      currentEntry = readdir(*dir);
      if(size.st_size <= 1<<9){
        stats[0] ++;
        continue;
      }
      if(size.st_size <= 1<<10){
        stats[1] ++;
        continue;
      }
      if(size.st_size <= 1<<11){
        stats[2] ++;
        continue;
      }
      if(size.st_size <= 1<<12){
        stats[3] ++;
        continue;
      }
      if(size.st_size <= 1<<13){
        stats[4] ++;
        continue;
      }
      if(size.st_size <= 1<<16){
        stats[5] ++;
        continue;
      }
      if(size.st_size <= 1<<20){
        stats[6] ++;
        continue;
      }
      stats[7] ++;
      continue;
    } else if(currentEntry->d_type == 4 && (strcmp(currentEntry->d_name, ".") != 0)
        && (strcmp(currentEntry->d_name, "..") != 0)) {
          DIR *newdir;
          getdirhandler(path, &newdir);
          // recursive call of calcstat
          calcstat(&newdir, path, stats);
    }
    currentEntry = readdir(*dir);
  }
}

void printstat(int stats[])
{
  printf("Files are only includen in the highes possible category:\n");
  char const * label[8] = {
    "< 512  B",
    "< 1  KiB",
    "< 2  KiB",
    "< 4  KiB",
    "< 8  KiB",
    "< 64 KiB",
    "< 1  MiB",
    "> 1  MiB"
  };
  for (int i = 0; i < 8; i++) {
    printf("Files %s:\t%d Files!\n", label[i], stats[i]);
  }
}
