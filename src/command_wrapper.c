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

int main(int argc, char** argv) {
  int status;
  //command_wrapper("SAPID_DEST=/usr/local/Sapid/Profiled-6.92.11 /usr/local/Sapid/Profiled-6.92.11/bin/sdb4 /Users/sue/work/raisin/sapid-profile/hello.c -sdbd hello -sdbd SDB", &status);
  //command_wrapper("/usr/local/Sapid/Profiled-6.92.11/bin/sdb4 /Users/sue/work/raisin/sapid-profile/hello.c -o hello -sdbd SDB", &status);
  //command_wrapper("sdb4 /Users/sue/work/raisin/sapid-profile/hello.c -o hello -sdbd SDB", &status);
}
