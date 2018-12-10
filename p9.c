#include <stdio.h>
#include <stdlib.h>

#define LOG_FILE "fill_log_file"

write_to_fill_log()
{
  char *username;
  long t;
  FILE *f;

  username = getenv("USER");
  t = time(0);

  f = fopen(LOG_FILE, "a");
  if (f == NULL) {
    fprintf(stderr, "Can't write log file %s\n", LOG_FILE);
    return;
  }

  fprintf(f, "%s %ld\n", username, t); 
  fclose(f);
}
  
main()
{
  write_to_fill_log();
}
