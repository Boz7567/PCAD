#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *inc(void *ptr);
void *dec(void *ptr);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

volatile int a=0;

int main(){
  pthread_t th1, th2,th3;
  pthread_create(&th1,NULL,inc,NULL);
  pthread_create(&th2,NULL,dec,NULL);
  pthread_create(&th3,NULL,dec,NULL);
  pthread_join(th1,NULL);
  pthread_join(th2,NULL);
  pthread_join(th3,NULL);
  printf("a vale %d\n",a);
  return 0;
}

void *inc(void *ptr){
  int r=pthread_mutex_lock(&lock);
  if(r!=0){
    printf("Problem with lock\n");
    return NULL;
  } 
  a=a+1;
  r=pthread_mutex_unlock(&lock);
  if(r!=0){
    printf("Problem with unlock\n");
    return NULL;
  } 
  return NULL;
}

void *dec(void *ptr){
  int r=pthread_mutex_lock(&lock);
  if(r!=0){
    printf("Problem with lock\n");
    return NULL;
  } 
  if(a>0){
    /*r=pthread_mutex_unlock(&lock);
    sleep(1);
    r=pthread_mutex_lock(&lock);*/
    a=a-1;
  }
  r=pthread_mutex_unlock(&lock);
  if(r!=0){
    printf("Problem with unlock\n");
    return NULL;
  } 
  return NULL;
}
