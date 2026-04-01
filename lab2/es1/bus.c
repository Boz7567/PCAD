#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define N_PASSEGGERI 3
#define CAPIENZA_BUS 2

typedef struct {

    int passeggeri;
    bool capolinea;

    pthread_mutex_t lock;

    pthread_cond_t bus_pieno;
    pthread_cond_t bus_disponibile;
    pthread_cond_t giro_finito;

} bus_t;

bus_t Bus;

pthread_t passeggeri[N_PASSEGGERI];
pthread_t bus_thread;

int id[N_PASSEGGERI];

void* passenger_func(void* arg){

    int id = *(int*)arg;

    while(true){

        pthread_mutex_lock(&Bus.lock);

        // Aspetta se:
        // - bus non al capolinea
        // - bus pieno
        while(!Bus.capolinea || Bus.passeggeri == CAPIENZA_BUS){
            pthread_cond_wait(
                &Bus.bus_disponibile,
                &Bus.lock
            );
        }

        // Sale sul bus
        Bus.passeggeri++;

        printf("Passeggero %d sale (%d/%d)\n",
               id,
               Bus.passeggeri,
               CAPIENZA_BUS);

        // Se è l'ultimo passeggero
        if(Bus.passeggeri == CAPIENZA_BUS){

            printf("Bus pieno, ultimo passeggero sveglia il bus\n");

            pthread_cond_signal(
                &Bus.bus_pieno
            );
        }

        // Aspetta fine giro
        pthread_cond_wait(
            &Bus.giro_finito,
            &Bus.lock
        );

        printf("Passeggero %d scende\n", id);

        pthread_mutex_unlock(&Bus.lock);

        sleep(1);
    }

    return NULL;
}


// ================= BUS =================

void* bus_func(void* arg){

    while(true){

        pthread_mutex_lock(&Bus.lock);

        // Aspetta che il bus sia pieno
        while(Bus.passeggeri < CAPIENZA_BUS){

            printf("Bus dorme\n");

            pthread_cond_wait(
                &Bus.bus_pieno,
                &Bus.lock
            );
        }

        // Parte
        Bus.capolinea = false;

        pthread_mutex_unlock(&Bus.lock);

        printf("\nBus fa il giro della citta\n\n");

        sleep(3);

        pthread_mutex_lock(&Bus.lock);

        printf("Bus torna al capolinea\n");

        // Tutti scendono
        Bus.passeggeri = 0;
        Bus.capolinea = true;

        // Sveglia tutti i passeggeri
        pthread_cond_broadcast(
            &Bus.giro_finito
        );

        // Permette nuovi ingressi
        pthread_cond_broadcast(
            &Bus.bus_disponibile
        );

        pthread_mutex_unlock(&Bus.lock);

        sleep(1);
    }

    return NULL;
}


// ================= MAIN =================

int main(){

    Bus.passeggeri = 0;
    Bus.capolinea = true;

    pthread_mutex_init(&Bus.lock, NULL);

    pthread_cond_init(&Bus.bus_pieno, NULL);
    pthread_cond_init(&Bus.bus_disponibile, NULL);
    pthread_cond_init(&Bus.giro_finito, NULL);

    // Crea thread bus
    pthread_create(&bus_thread, NULL, bus_func, NULL);

    // Crea thread passeggeri
    for(int i = 0; i < N_PASSEGGERI; i++){

        id[i] = i;

        pthread_create(
            &passeggeri[i],
            NULL,
            passenger_func,
            &id[i]
        );
    }

    // Join bus
    pthread_join(bus_thread, NULL);

    return 0;
}