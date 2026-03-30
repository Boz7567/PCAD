#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// numeri arbitrari
#define N_PASSEGGERI 10
#define CAPIENZA_BUS 4


struct bus{
    pthread_t thread;
    unsigned int passeggeri;
    bool capolinea; // true se si trova al capolinea, false altrimenti
    pthread_mutex_t lock_passeggeri;
};

pthread_t passeggeri[N_PASSEGGERI];
struct bus Bus;

int id[N_PASSEGGERI];

void* passenger_func(void* arg){
    int id = *(int*)arg;
    // printf("%d\n", id);
    while(true){
        pthread_mutex_lock(&Bus.lock_passeggeri);
        if(Bus.capolinea && Bus.passeggeri<CAPIENZA_BUS){
            Bus.passeggeri++;
            printf("Passeggero %d sale sul bus\n", id);
        }
        else{
            printf("Il passeggero %d dorme\n\n", id);
        }
        pthread_mutex_unlock(&Bus.lock_passeggeri);
        sleep(1);
    }
}

void* bus_func(void* arg){
    while (true){
        // if(Bus.capolinea){//not sure if i need
            while(Bus.passeggeri <= CAPIENZA_BUS){
                printf("Il bus dorme\n\n");
                sleep(1);
            }
            Bus.capolinea = false;
            printf("Bus fa il giro della città\n");
            sleep(3); // giro della città
            printf("Bus torna al capolinea\n");
            Bus.passeggeri = 0;
            Bus.capolinea = true;
        // }
    }
}

int main(){
    Bus.capolinea = true;
    Bus.passeggeri = 0;
    pthread_mutex_init(&Bus.lock_passeggeri, NULL);
    pthread_create(&Bus.thread, NULL, bus_func, NULL);
    for(int i = 0; i<N_PASSEGGERI; i++){
        id[i] = i;
    }
    printf("start\n");
    for(int i = 0; i<N_PASSEGGERI; i++){
        pthread_create(&passeggeri[i], NULL, passenger_func, &id[i]);
    }

    // for(int i = 0; i<N_PASSEGGERI; i++){
    //     pthread_join(passeggeri[i], NULL);
    // }
}