#include "my_barrier.h"
#include <unistd.h>
#include <stdio.h>


my_barrier b;

unsigned int pthread_my_barrier_init(my_barrier *mb , unsigned int v){
    if(v == 0)
        return -1;
    mb->vinit = v;
    mb->val = 0;
    pthread_mutex_init(&mb->lock, NULL);
    pthread_cond_init(&mb->varcond, NULL);
    return 0;
}

unsigned int pthread_my_barrier_wait(my_barrier *mb){
    pthread_mutex_lock(&mb->lock);
    mb->val++;
    if(mb->val < mb->vinit){
        pthread_cond_wait(&mb->varcond, &mb->lock);
    }
    else{
        mb->val = 0;
        pthread_cond_broadcast(&mb->varcond);
    }
    pthread_mutex_unlock(&mb->lock);
    return 0;
}

void* func(void* arg){
    int n = *(int*)arg;
    sleep(1);
    pthread_my_barrier_wait(&b);
}


int main(){
    printf("\nBarrier test\n\n");
    pthread_t threads[5];

    if(pthread_my_barrier_init(&b, 5) == -1){
        printf("\nErrore nell'inizializzazione della barriera\n");
        return -1;
    }

    for(int i = 0; i<5; i++){
        pthread_create(&threads[i], NULL, func, &i);
    }

    for(int i = 0; i<5; i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("Tutti i thread hanno finito\n");
    return 0;
}