#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LOG_FILE "/home/misafir/log_file"

write_to_fill_log()
{
  char *username;
  time_t t;
  int fd;
  char s[1000];
  char *time_string;

  username = getenv("USER");
  t = time(0);

  fd = open(LOG_FILE, O_APPEND | O_SYNC | O_CREAT | O_WRONLY, 0666);

  if (fd < 0) {
    fprintf(stderr, "Can't write log file %s\n", LOG_FILE);
    return;
  }

  time_string = asctime(localtime(&t));
  
  sprintf(s, "%-10s %s", username, time_string); 
  write(fd, s, strlen(s));
  close(fd);
}
  
main()
{
  write_to_fill_log();
}
