#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int show_all = 0;
int long_format = 0;

int main(int argc, char **argv) {
  int opt;
  char options[] = "al";
  while ((opt = getopt(argc, argv, options)) != -1) {
    switch (opt) {
    case 'a':
      show_all = 1;
      break;
    case 'l':
      long_format = 1;
      break;
    default:
      fprintf(stderr, "Usage: %s -[%s] [path]\n", argv[0], options);
      return 1;
    }
  }

  const char *path = (argc > optind) ? argv[optind] : ".";

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
