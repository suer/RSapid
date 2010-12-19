#include <stdio.h>
#include <stdlib.h>
#define MAX_COMMAND_SIZE 256

void sdb4_wrapper(char** args, int* status) {
  char* sapid_dest;
  char command_line[MAX_COMMAND_SIZE];

  printf("command: %s\n", *args);
  sapid_dest = getenv("SAPID_DEST");
  sprintf(command_line, "SAPID_DEST=%s sdb4 %s", sapid_dest, *args);  
  printf("%s\n", command_line);
  *status = system(command_line);
}
