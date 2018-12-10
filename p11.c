#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


main()
   {
     int i;
     int old_mask;

     old_mask = umask(0);
     i = open("f1", O_WRONLY | O_CREAT | O_TRUNC, 0666);
     close(i);
     printf("created f1: 0666\n");
     i = open("f2", O_WRONLY | O_CREAT | O_TRUNC, 0200);
     close(i);
     printf("created f2: 0200\n");

     umask(022);
     i = open("f3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
     close(i);
     printf("created f3: %o\n", 0666 & ~022 & 0777);
     i = open("f4", O_WRONLY | O_CREAT | O_TRUNC, 0777);
     close(i);
     printf("created f4: %o\n", 0777 & ~022 & 0777);
     i = open("f5", O_WRONLY | O_CREAT | O_TRUNC, 0200);
     close(i);
     printf("created f5: %o\n", 0200 & ~022 & 0777);
   }
