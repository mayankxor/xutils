#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int nargs = (argc == 1) ? 1 : argc - 1;
  for (int i = 0; i < nargs; ++i) {
    const char *path = (argc == 1) ? "." : argv[i + 1];
    char *absolutepath;
    if (!(absolutepath = realpath(path, NULL))) {
      perror("realpath");
      return 1;
    }
    DIR *stream;
    if (!(stream = opendir(path))) {
      perror("opendir");
      return 1;
    }

    if (nargs > 1) {
      if (!strcmp(path, ".")) {
        printf(".:\n");

      } else {
        printf("%s:\n", absolutepath);
      }
    }
    struct dirent *direntry;
    errno = 0;
    while ((direntry = readdir(stream))) {
      char *name = direntry->d_name;
      printf("%s\n", name);
    }
    if (errno) {
      perror("readdir");
      return 1;
    }
    if (i < nargs - 1) {
      printf("\n");
    }

    if ((closedir(stream)) == -1) {
      perror("closedir");
      return 1;
    }
    free(absolutepath);
  }

  return 0;
}
