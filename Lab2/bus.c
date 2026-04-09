#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PASSENGERS 15
#define BUS_CAPACITY 5

pthread_t passengers[NUM_PASSENGERS];

struct Bus {
    int passengers_on_board;
    pthread_mutex_t mutex;
    pthread_cond_t cond_passenger;  // Condizione per i passeggeri
    pthread_cond_t cond_bus;        // Condizione per il bus
    bool bus_full;
    bool in_trip;                   // Indica se il bus è in viaggio
    int waiting_passengers;         // Contatore passeggeri in attesa
};

struct Bus autobus;

void* passenger_func(void* arg) {
    int id = *(int*)arg;
    
    while(true) {
        pthread_mutex_lock(&autobus.mutex);
        
        // Se il bus è in viaggio o è pieno, il passeggero aspetta
        while(autobus.in_trip || autobus.passengers_on_board >= BUS_CAPACITY) {
            autobus.waiting_passengers++;
            printf("Passeggero %d è in attesa che il bus torni al capolinea...\n", id);
            pthread_cond_wait(&autobus.cond_passenger, &autobus.mutex);
            autobus.waiting_passengers--;
        }
        
        // Il bus è al capolinea e c'è posto, il passeggero sale
        autobus.passengers_on_board++;
        printf("Passeggero %d sale sul bus. Posti occupati: %d/%d\n", 
               id, autobus.passengers_on_board, BUS_CAPACITY);
        
        // Se il bus è pieno, segnala al bus di partire
        if(autobus.passengers_on_board == BUS_CAPACITY) {
            printf("Bus pieno! Segnalo la partenza...\n");
            pthread_cond_signal(&autobus.cond_bus);
        }
        
        pthread_mutex_unlock(&autobus.mutex);
        
        // Simula il tempo di arrivo al bus
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* bus_func(void* arg) {
    while(1) {
        pthread_mutex_lock(&autobus.mutex);
        
        // Attende finché il bus non è pieno
        while(autobus.passengers_on_board < BUS_CAPACITY) {
            printf("Bus in attesa di %d passeggeri...\n", 
                   BUS_CAPACITY - autobus.passengers_on_board);
            pthread_cond_wait(&autobus.cond_bus, &autobus.mutex);
        }
        
        // Bus pieno, parte per il viaggio
        printf("\n================================================================\n");
        printf("BUS PARTE CON %d PASSEGGERI!\n", autobus.passengers_on_board);
        printf("================================================================\n");
        
        autobus.in_trip = true;
        pthread_mutex_unlock(&autobus.mutex);
        
        // Simula il viaggio
        sleep(3);
        
        // Arrivo al capolinea
        pthread_mutex_lock(&autobus.mutex);
        printf("\n----------------------------------------------------------------\n");
        printf("BUS ARRIVATO AL CAPOLINEA\n");
        printf("----------------------------------------------------------------\n");
        
        // Svuota il bus
        autobus.passengers_on_board = 0;
        autobus.in_trip = false;
        
        // Sveglia tutti i passeggeri in attesa
        if(autobus.waiting_passengers > 0) {
            printf("Ci sono %d passeggeri in attesa, sveglio tutti!\n", 
                   autobus.waiting_passengers);
            pthread_cond_broadcast(&autobus.cond_passenger);
        }
        
        printf("Bus pronto per nuova partenza al capolinea\n");
        printf("----------------------------------------------------------------\n\n");
        
        pthread_mutex_unlock(&autobus.mutex);
        
        sleep(1);  // Pausa prima del prossimo ciclo
    }
    return NULL;
}

int main(void) {
    int ids[NUM_PASSENGERS];
    pthread_t bus_thread;
    
    // Inizializzazione
    pthread_mutex_init(&autobus.mutex, NULL);
    pthread_cond_init(&autobus.cond_passenger, NULL);
    pthread_cond_init(&autobus.cond_bus, NULL);
    
    autobus.passengers_on_board = 0;
    autobus.bus_full = false;
    autobus.in_trip = false;
    autobus.waiting_passengers = 0;
    
    // Creazione thread passeggeri
    for(int i = 0; i < NUM_PASSENGERS; i++) {
        ids[i] = i + 1;
        pthread_create(&passengers[i], NULL, passenger_func, &ids[i]);
    }
    
    // Creazione thread bus
    pthread_create(&bus_thread, NULL, bus_func, NULL);
    
    // Attesa terminazione (non terminerà mai in questo esempio)
    for(int i = 0; i < NUM_PASSENGERS; i++) {
        pthread_join(passengers[i], NULL);
    }
    
    // Pulizia (non raggiunto in questo esempio)
    pthread_mutex_destroy(&autobus.mutex);
    pthread_cond_destroy(&autobus.cond_passenger);
    pthread_cond_destroy(&autobus.cond_bus);
    
    return 0;
}