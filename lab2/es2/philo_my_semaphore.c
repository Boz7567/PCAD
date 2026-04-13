#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "my_semaphore.h"

#define N 5 

my_semaphore bacchette[N];
my_semaphore sala_attesa;

void* filosofo(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < 3; i++) { 
        printf("Filosofo %d sta pensando...\n", id);
        sleep(rand() % 2);

       
        my_sem_wait(&sala_attesa);
        
        // Prendo la bacchetta sinistra e poi la destra
        my_sem_wait(&bacchette[id]);
        my_sem_wait(&bacchette[(id + 1) % N]);


        printf("Filosofo %d sta MANGIANDO (pasto %d/3)\n", id, i + 1);
        sleep(1);

    
        my_sem_signal(&bacchette[id]);
        my_sem_signal(&bacchette[(id + 1) % N]);
        

        my_sem_signal(&sala_attesa);
    }

    printf("Filosofo %d ha finito i suoi pasti \n", id);
    return NULL;
}

int main() {
    pthread_t thread_id[N];

    
    my_sem_init(&sala_attesa, N - 1);
    for (int i = 0; i < N; i++) {
        my_sem_init(&bacchette[i], 1);
    }

    for (int i = 0; i < N; i++) {
        int *id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&thread_id[i], NULL, filosofo, id);
    }


    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    my_sem_destroy(&sala_attesa);
    for (int i = 0; i < N; i++) {
        my_sem_destroy(&bacchette[i]);
    }

    printf("Simulazione terminata con successo.\n");
    return 0;
}
