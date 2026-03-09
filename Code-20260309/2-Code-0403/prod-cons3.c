#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct shared_buf{
  volatile int val;
  volatile bool full;
  pthread_mutex_t lock;
  pthread_cond_t varcond_full;
  pthread_cond_t varcond_notfull;
} shared_buf;

shared_buf B;

void *consume(void *ptr);
void *produce(void *ptr);

int main(){
  B.val=0;
  B.full=false;
  pthread_mutex_init(&(B.lock),NULL);
  pthread_cond_init(&(B.varcond_full),NULL);
  pthread_cond_init(&(B.varcond_notfull),NULL);
  pthread_t th1, th2, th3;
  char *prod1="Prod1";
  char *cons1="Cons1";
  char *cons2="Cons2";
  pthread_create(&th1,NULL,consume,cons1);
  pthread_create(&th2,NULL,produce,prod1);
  pthread_create(&th3,NULL,consume,cons2);
  pthread_join(th1,NULL);
  pthread_join(th2,NULL);
  pthread_join(th3,NULL);
  printf("END\n");
  pthread_mutex_destroy(&(B.lock));
  return 0;
}

void *produce(void  *ptr){
  char *id=(char *)ptr;
  for(unsigned i=1;i<=10;++i){
    pthread_mutex_lock(&(B.lock));
    while(B.full){
      printf("----> %s waiting....\n",id);
      pthread_cond_wait(&(B.varcond_notfull),&(B.lock));
    }
    B.val=i;
    printf("--> Production of %d by %s\n",i,id);
    B.full=true;
    pthread_cond_signal(&(B.varcond_full));
    pthread_mutex_unlock(&(B.lock));
  }
  return NULL;
}

void *consume(void  *ptr){
  char *id=(char *)ptr;
  for(unsigned i=1;i<=5;++i){
    pthread_mutex_lock(&(B.lock));
    
    while(!B.full){
      printf("----> %s waiting....\n",id);
      pthread_cond_wait(&(B.varcond_full),&(B.lock));
    }
    int x=B.val;
    printf("--> Consumption of %d by %s\n",x,id);
    B.full=false;
    pthread_cond_signal(&(B.varcond_notfull));
    pthread_mutex_unlock(&(B.lock));
  }
  return NULL;
}

