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
    pthread_cond_t bus_full;     // bisogna svegliare l'autobus!
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

        //  Fa il giro 
        pthread_cond_wait(&b->can_offboard, &b->mutex);

        // Scende dal bus
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

        // Il bus arriva alla fermata 
        printf("\n Arrivato alla fermata. Apre le porte. \n");
        b->bus_ready = true;
        pthread_cond_broadcast(&b->can_board);

        while (b->count < BUS_CAPACITY) {
            pthread_cond_wait(&b->bus_full, &b->mutex);
        }

        
        b->bus_ready = false;
        printf("Il bus e' pieno e parte per il giro\n\n");
        pthread_mutex_unlock(&b->mutex);

        // Giro
        sleep(3); //per simulare il "giro della città". Mentre il bus dorme, il tempo passa per i turisti a bordo.

        //  Ritorna e fa scendere tutti i passengeri
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
int main() {
    Bus myBus;

    myBus.count = 0;
    myBus.bus_ready = false;
    
    pthread_mutex_init(&myBus.mutex, NULL);
    pthread_cond_init(&myBus.can_board, NULL);
    pthread_cond_init(&myBus.bus_full, NULL);
    pthread_cond_init(&myBus.can_offboard, NULL);
    pthread_cond_init(&myBus.bus_empty, NULL);

    pthread_t bus_tid;
    pthread_t passenger_tids[PASSENGERS];

    if (pthread_create(&bus_tid, NULL, bus_thread, &myBus) != 0) {
        perror("Errore creazione thread bus");
        return 1;
    }

    for (int i = 0; i < PASSENGERS; i++) {
        Passenger *p = (Passenger*)malloc(sizeof(Passenger));
        p->id = i + 1;
        p->bus = &myBus;
        
        if (pthread_create(&passenger_tids[i], NULL, passenger_thread, p) != 0) {
            perror("Errore creazione thread passeggero");
            return 1;
        }
    }

    pthread_join(bus_tid, NULL);
    for (int i = 0; i < PASSENGERS; i++) {
        pthread_join(passenger_tids[i], NULL);
    }
    pthread_mutex_destroy(&myBus.mutex);
    pthread_cond_destroy(&myBus.can_board);
    pthread_cond_destroy(&myBus.bus_full);
    pthread_cond_destroy(&myBus.can_offboard);
    pthread_cond_destroy(&myBus.bus_empty);

    return 0;
}
