#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>



#define LOG_FILE "fill_log_file"

write_to_fill_log()
{
  char *username;
  long t;
  int fd;
  char s[100];

  username = getenv("USER");
  t = time(0);

  fd = open(LOG_FILE, O_APPEND | O_SYNC | O_CREAT | O_WRONLY, 0666);

  if (fd < 0) {
    fprintf(stderr, "Can't write log file %s\n", LOG_FILE);
    return;
  }

  sprintf(s, "%s %ld\n", username, t); 
  write(fd, s, strlen(s));
  close(fd);
} 
  
main()
{
  write_to_fill_log();
}
