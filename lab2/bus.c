#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define PASSENGERS 10
#define BUS_CAPACITY 4


typedef struct {
    int count;              // Numero di passeggeri attualmente a bordo
    bool bus_ready;         // true se il bus è alla fermata, false se è in giro
    
    pthread_mutex_t mutex;
    pthread_cond_t can_board;    // "Sveglio" i passeggeri alla fermata
    pthread_cond_t bus_full;     // wake up bus!
    pthread_cond_t can_offboard; // i passeggeri scendono
    pthread_cond_t bus_empty;    // tutti sono scesi
} Bus;


typedef struct {
    int id;                 
    Bus *bus;               
} Passenger;

void* passenger_thread(void* arg) {
    Passenger *data = (Passenger*)arg;
    int my_id = data->id;
    Bus *b = data->bus;

    while (true) {
        pthread_mutex_lock(&b->mutex);

        // Wait till bus is ready and there's place to drop in
        while (b->count == BUS_CAPACITY || !b->bus_ready) {
            pthread_cond_wait(&b->can_board, &b->mutex);
        }

        // Sale a bordo
        b->count++;
        printf("Passeggero %d Salito sul bus. (Posti occupati: %d/%d)\n", my_id, b->count, BUS_CAPACITY);

        // Se è l'ultimo a salire, sveglia il bus
        if (b->count == BUS_CAPACITY) {
            printf("Passeggero %d Il bus è pieno! Avviso il conducente.\n", my_id);
            pthread_cond_signal(&b->bus_full);
        }

        // (b') Fa il giro 
        pthread_cond_wait(&b->can_offboard, &b->mutex);

        // (c') Scende dal bus
        b->count--;
        printf("Passeggero %d Sceso dal bus. (Rimasti a bordo: %d)\n", my_id, b->count);

        // Se è l'ultimo a scendere, avvisa il bus
        if (b->count == 0) {
            pthread_cond_signal(&b->bus_empty);
        }

        pthread_mutex_unlock(&b->mutex);
        sleep(2 + (rand() % 5));
    }
    return NULL;
}

void* bus_thread(void* arg) {
    Bus *b = (Bus*)arg;

    while (true) {
        pthread_mutex_lock(&b->mutex);

        // Il bus arriva alla fermata e apre le porte
        printf("\n Arrivato alla fermata. Apre le porte. \n");
        b->bus_ready = true;
        pthread_cond_broadcast(&b->can_board);

        // Aspetto che il bus sia pieno
        while (b->count < BUS_CAPACITY) {
            pthread_cond_wait(&b->bus_full, &b->mutex);
        }

        // Chiude le porte e parte
        b->bus_ready = false;
        printf("Il bus e' pieno e parte per il giro\n\n");
        pthread_mutex_unlock(&b->mutex);

        // (b) Giro della città
        sleep(3); //per simulare il "giro della città". Mentre il bus dorme, il tempo passa per i turisti a bordo.

        // (c) Ritorno e sbarco
        pthread_mutex_lock(&b->mutex);
        printf("\n Il bus ha finito il giro. Arrivo al punto di partenza. Scendono tutti\n");
        pthread_cond_broadcast(&b->can_offboard);

        // Aspetta che tutti siano scesi prima di ricominciare
        while (b->count > 0) {
            pthread_cond_wait(&b->bus_empty, &b->mutex);
        }

        printf("Il bus ha fatto scendere tutti ed e' pronto per il prossimo giro\n");
        pthread_mutex_unlock(&b->mutex);
        
        sleep(1); 
    }
    return NULL;
}

