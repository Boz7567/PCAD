#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int fds[2];
  pipe(fds);
  int idfork=fork();
  if(idfork==0){
    close(fds[1]);
    char buffer[100];
    read(fds[0],buffer,sizeof(buffer));
    printf("Sono il figlio e ho ricevuto %s dal mio padre\n",buffer);
    close(fds[0]);
  } else {
    close(fds[0]);
    write(fds[1],"Luke, I am your father",22);
    int stato;
    waitpid(idfork, &stato, 0);
    close(fds[1]);
    return 0;
  }
}
