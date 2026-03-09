#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *stampa(void *ptr);

int main(){
  pthread_t th1, th2;
  char *s1="Sono il thread 1\n";
  char *s2="Sono il thread 2\n";
  pthread_create(&th1,NULL,stampa,s1);
  pthread_create(&th2,NULL,stampa,s2);

  //pthread_join(th1,NULL);
  //pthread_join(th2,NULL);
  return 0;
}

void *stampa(void *ptr){
  char *s=(char *)ptr;
  printf("Il mio messagio e: %s",s); 
  return NULL;
}
