#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "jrb.h"

int get_size(char *fn, JRB inodes)
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
    exists = lstat(s, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", de->d_name);
    } else {
      if (jrb_find_int(inodes, buf.st_ino) == NULL) {
	total_size += buf.st_size;
	jrb_insert_int(inodes, buf.st_ino, JNULL);
      }
    }

    if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && 
        strcmp(de->d_name, "..") != 0 ){
      total_size += get_size(s, inodes);
    }
  }
  closedir(d);
  free(s);
  return total_size;
}


main()
{
  JRB inodes;
  inodes = make_jrb();
  printf("Size = %d\n", get_size(".", inodes));
}
