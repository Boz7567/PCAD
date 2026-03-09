#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *foo(void *ptr);
void *goo(void *ptr);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
volatile int a=0;

int main(){
  pthread_t th1, th2;
  pthread_create(&th1,NULL,foo,NULL);
  pthread_create(&th2,NULL,goo,NULL);
  pthread_join(th1,NULL);
  pthread_join(th2,NULL);
  printf("a vale %d\n",a);
  return 0;
}

void *foo(void  *ptr){
  pthread_mutex_lock(&lock);
  printf("foo prende lock1\n");
  pthread_mutex_lock(&lock2);
  printf("foo prende lock2\n");
  a=10;
  pthread_mutex_unlock(&lock2);
  printf("foo rende lock2\n");
  pthread_mutex_unlock(&lock);
  printf("foo rende lock1\n");
  return NULL;
}

void *goo(void  *ptr){
  pthread_mutex_lock(&lock2);
  printf("goo prende lock2\n");
  pthread_mutex_lock(&lock);
  printf("goo prende lock1\n");
  a=20;
  pthread_mutex_unlock(&lock);
  printf("goo rende lock1\n");
  pthread_mutex_unlock(&lock2);
  printf("goo rende lock2\n");
  return NULL;
}
