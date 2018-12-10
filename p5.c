#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int get_size(char *fn)
{
  DIR *d;
  struct dirent *de;
  struct stat buf;
  int exists;
  int total_size;
  char *s;

  d = opendir(fn);
  if (d == NULL) {
    perror("prsize");
    exit(1);
  }
 
  s = (char *) malloc(sizeof(char)*(strlen(fn)+258));
  total_size = 0;

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    sprintf(s, "%s/%s", fn, de->d_name);
    exists = stat(s, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", de->d_name);
    } else {
      total_size += buf.st_size;
    }

    if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && 
        strcmp(de->d_name, "..") != 0 ){
	  //      printf("Making recursive call on directory %s\n", de->d_name);
      total_size += get_size(s);
    }
  }
  closedir(d);
  free(s);
  return total_size;
}


main()
{
  printf("Size = %d\n", get_size("."));
}
