#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv) {
  const char *path = (argc > 1) ? argv[1] : ".";

  DIR *stream;
  if (!(stream = opendir(path))) {
    perror("opendir");
    return 1;
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

  if ((closedir(stream)) == -1) {
    perror("closedir");
    return 1;
  }

  return 0;
}
