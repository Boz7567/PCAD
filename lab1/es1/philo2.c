#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_FILOSOFI 5
#define NUM_PASTI 5

pthread_t filosofi[N_FILOSOFI];
pthread_mutex_t bacchette[N_FILOSOFI];

int id[N_FILOSOFI];

void* filosofo(void* arg){
    int i = *(int*)arg;

    for(int pasto=0; pasto<NUM_PASTI; pasto++){

        printf("Filosofo %d: sta pensando\n", i);
        // tempo uguale per tutti, per mostrare il caso di deadlock        
        sleep(1);

        if(i == N_FILOSOFI - 1){
            pthread_mutex_lock(&bacchette[0]);   //bacchette[0] perchè non ha senso calcolare bacchette[(i+1)%N_FILOSOFI]
            printf("Filosofo %d: ha la bacchetta destra (ultimo filosofo prende prima la destra) \n", i);
            sleep(1);
            
            pthread_mutex_lock(&bacchette[i]);   //bacchette[0] perchè non ha senso calcolare bacchette[(i+1)%N_FILOSOFI]
            printf("Filosofo %d: ha la bacchetta sinistra (ultimo filosofo prende prima la destra) \n", i);
        }
        else{
            pthread_mutex_lock(&bacchette[i]);
            printf("Filosofo %d: ha la bacchetta sinistra\n", i);
            sleep(1);

            pthread_mutex_lock(&bacchette[(i+1)%N_FILOSOFI]);
            printf("Filosofo %d: ha la bacchetta destra\n", i);
        }
        sleep(1);
        printf("Filosofo %d: sta mangiando\n", i);
        sleep(2);

        pthread_mutex_unlock(&bacchette[i]);
        pthread_mutex_unlock(&bacchette[(i+1)%N_FILOSOFI]);
        printf("Filosofo %d: ha rilasciato le sue due bacchette\n", i);
        sleep(1);
    }

    return NULL;
}

int main(){
    printf("\nIn questo caso, facciamo in modo che l'ultimo filosofo prenda la bacchetta destra prima della bacchetta sinistra, e facendo ciò evitiamo deadlock\n\n");

    for(int i = 0; i<N_FILOSOFI; i++){
        id[i] = i;
    }
    // srand(time(NULL));
    for(int i=0; i<N_FILOSOFI; i++){
        pthread_mutex_init(&bacchette[i], NULL);
    }

    for(int i=0; i<N_FILOSOFI; i++){
        pthread_create(&filosofi[i], NULL, filosofo, &id[i]);
    }

    for(int i=0; i<N_FILOSOFI; i++){
        pthread_join(filosofi[i], NULL);
    }

    for(int i=0; i<N_FILOSOFI; i++){
        pthread_mutex_destroy(&bacchette[i]);
    }

    return 0;
}