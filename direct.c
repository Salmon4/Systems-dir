#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int findDirSize(char *path){
  DIR * stream = opendir(path);
  int size = 0;
  struct dirent *entry = readdir(stream);
  while (entry != NULL){
    char *curr = malloc(0);
    strcat(curr,entry->d_name);
    if (entry->d_type == DT_DIR){
      strcat(path,"/");
      strcat(path,entry->d_name);
      size += findDirSize(path);
    }
    else{
      struct stat buffer;
      char *file = entry->d_name;
      stat(file,&buffer);
      size += buffer.st_size;
    }
    entry = readdir(stream);
  }
  return size;
}

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
      //char *path = malloc(0);
      //strcat(path,"/");
      //strcat(path,entry->d_name);
      //if (strcmp(entry->d_name,"/.") != 0){
      //  printf("%s\n",path);
      //  size += findDirSize(path);
      //}
    }
    else{
      strcat(allFiles,"\t");
      strcat(allFiles,curr);
      strcat(allFiles,"\n");

      struct stat buffer;
      char *file = entry->d_name;
      stat(file,&buffer);
      size += buffer.st_size;
    }
    entry = readdir(stream);
  }

  char format[] = " ";
  if (size > 1073741823){
    size = size / 1073741824;
    strcat(format,"GB");
    //char format[] = "GB";
  }
  else if (size > 1048575){
    size = size / 1048576;
    strcat(format,"MB");
    //char format[] = "MB";
  }
  else if (size > 1023){
    size = size / 1024;
    strcat(format,"KB");
    //char format[] = "KB";
  }
  else{
    strcat(format,"B");
    //char format[] = "B";
  }


  printf("The size is %d%s\n\n", size,format);
  printf("All Directories:\n%s", allDir);
  printf("\n");
  printf("All Regular Files:\n%s", allFiles);

  closedir(stream);

  return 1;
}
