#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main(){
  int x=0;
  x=3;
  int pid = fork();
  if ( pid == 0 ) { 
    x=25;
    printf("Valore di x per il figlio:%d\n",x);
    printf("Fin del processo figlio\n"); 
  }
  else { 
    while(x!=25){
      sleep(2);
      printf("Valore di x per il  padre %d\n",x);
    }
      printf("Fine del processo padre\n"); 
  }
  return 0;
}
