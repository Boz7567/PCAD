#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int idfork=fork();
  if(idfork==0){
    for(int i=0;i<25;++i){
      sleep(1);
      printf("SON\n");
    }
    exit(0);
  } else {
    printf("PADRE\n");
    exit(0);
  }
}
