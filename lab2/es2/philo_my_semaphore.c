#include <stdio.h>
#include <stdlib.h>
// # include <pthread.h>
#include "my_semaphore.h"

#define N_FILOSOFI 5 

my_semaphore ticket;
my_semaphore bacchette[N_FILOSOFI];
pthread_t filosofo[N_FILOSOFI];

void* func(void* arg){
    int id = *(int*)arg;
    free(arg);
    for(int i = 0; i<3; i++){   //mangio 3 volte
        my_sem_wait(&ticket);
        my_sem_wait(&bacchette[id]);
        my_sem_wait(&bacchette[(id+1)%N_FILOSOFI]);
        printf("Filosofo %d mangia\n", id);
        sleep(1);
        printf("Filosofo %d finisce di mangiare [%d/3]\n", id, i+1);
        my_sem_signal(&bacchette[id]);
        my_sem_signal(&bacchette[(id+1)%N_FILOSOFI]);
        my_sem_signal(&ticket);
        sleep(1);
    }
}

int main(){
    my_sem_init(&ticket, N_FILOSOFI-1);
    for(int i = 0; i < N_FILOSOFI; i++) {
        my_sem_init(&bacchette[i], 1);
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&filosofo[i], NULL, func, id);
    }

    for(int i = 0; i<N_FILOSOFI; i++){
        pthread_join(filosofo[i], NULL);
    }

    return 0;
}