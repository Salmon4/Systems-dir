#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

int main(){
  DIR * stream = opendir(".");

  if (stream == NULL){
    printf("%s\n", strerror(errno));
  }

  int size = 0;
  char *allDir = malloc(0);
  char *allFiles = malloc(0);
  struct dirent *entry = readdir(stream);
  while (entry != NULL){
    char *curr = malloc(0);
    strcat(curr,entry->d_name);

    if (entry->d_type == DT_DIR){
      strcat(allDir,"\t");
      strcat(allDir,curr);
      strcat(allDir,"\n");
    }
    else{
      strcat(allFiles,"\t");
      strcat(allFiles,curr);
      strcat(allFiles,"\n");
      //size goes here
    }
    entry = readdir(stream);
  }
  printf("All Directories:\n%s", allDir);
  printf("\n");
  printf("All Regular Files:\n%s", allFiles);

  closedir(stream);

  return 1;
}
