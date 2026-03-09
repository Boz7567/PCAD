#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>


void *foo(void *ptr);

pthread_barrier_t bar;

int main(){
  pthread_t th1, th2, th3, th4, th5, th6;
  char *id1="id1";
  char *id2="id2";
  char *id3="id3";
  char *id4="id4";
  char *id5="id5";
  char *id6="id6";
  pthread_barrier_init(&bar,NULL,6);
  pthread_create(&th1,NULL,foo,id1);
  pthread_create(&th2,NULL,foo,id2);
  pthread_create(&th3,NULL,foo,id3);
  pthread_create(&th4,NULL,foo,id4);
  pthread_create(&th5,NULL,foo,id5);
  pthread_create(&th6,NULL,foo,id6);

  pthread_join(th1,NULL);
  pthread_join(th2,NULL);
  pthread_join(th3,NULL);
  pthread_join(th4,NULL);
  pthread_join(th5,NULL);
  pthread_join(th6,NULL);
  printf("END\n");
  
  return 0;
}

void *foo(void  *ptr){
  char *id=(char *)ptr;
  printf("--> BEGIN %s\n",id);
  pthread_barrier_wait(&bar);
  printf("--> END %s\n",id);
  return NULL;
}



