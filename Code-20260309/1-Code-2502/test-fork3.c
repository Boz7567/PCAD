#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int id=getpid();
  printf("Sono il processore %d\n",id);
  printf("Faccio un fork\n");
  int idfork=fork();
  if(idfork==0){
    int idfiglio=getpid();
    int idpadre=getppid();
    printf("Sono %d figlio di  %d\n",idfiglio,idpadre);
    char *args[]={"ls","-l",NULL};
    execvp(args[0],args);
    printf("Fine exec\n");
  } else {
    printf("Il mio figlio e %d\n",idfork);
    int stato;
    waitpid(idfork, &stato, 0);
    printf("Fine del figlio\n");
  }
  printf("BYE\n");
  return 0;
}
