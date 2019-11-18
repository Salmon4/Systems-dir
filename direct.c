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

  char allDir[] = "";
  char allFiles[] = "";
  struct dirent *entry = readdir(stream);
  while (entry != NULL){
    char curr[] = "";
    strcat(curr,entry->d_name);

    if (entry->d_type == DT_DIR){
      //strcat(allDir,curr);
      //strcat(allDir,"\n");
    }
    else{
      //strcat(allFiles,curr);
      //strcat(allFiles,"\n");
      //size goes here
    }
    entry = readdir(stream);
  }
  printf("%s", allDir);
  //printf("%s", allFiles);

  closedir(stream);

  return 1;
}
