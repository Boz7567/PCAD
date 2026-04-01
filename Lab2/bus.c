#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PASSENGERS 15
#define BUS_CAPACITY 5

pthread_t passengers [NUM_PASSENGERS];
pthread_mutex_t passengers_lock = PTHREAD_MUTEX_INITIALIZER;


struct Bus {
    int passengers_on_board;
    pthread_mutex_t mutex;
    bool bus_full;
    bool capolinea_reached;
};

struct Bus autobus;

void* passenger_func(void* arg){
    int id = *(int*)arg;
    while(true){
        pthread_mutex_lock(&autobus.mutex);
        if(autobus.passengers_on_board < BUS_CAPACITY && !autobus.bus_full){
            autobus.passengers_on_board++;
            printf("Passeggero %d sale sul bus. posti occupati: %d\n", id, autobus.passengers_on_board);
        } else {
            printf("Passeggero %d è in attesa che il bus parta...\n", id);
        }
        pthread_mutex_unlock(&autobus.mutex);
        sleep(rand() % 3 + 1); 
    }
}

void* bus_func(void*arg){
    while(1){
        pthread_mutex_lock(&autobus.mutex);
        if(autobus.passengers_on_board == BUS_CAPACITY){
            autobus.bus_full = true;
            printf("-------------------------------------------------------------------------------------------------------------------------------\n");
            printf("In attesa che il bus parta\n");
            
            sleep(3);
            autobus.passengers_on_board = false;
            autobus.bus_full = false;
            printf("Bus al capolinea, in attesa di una nuova partenza...\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        }
        pthread_mutex_unlock(&autobus.mutex);
        sleep(1); 
    }
}

int main(void) {
    int ids[NUM_PASSENGERS];
    pthread_t bus_thread;
    pthread_mutex_init(&autobus.mutex, NULL);
    autobus.passengers_on_board = false;
    autobus.bus_full = false;
    for(int i = 0; i < NUM_PASSENGERS; i++){
        ids[i] = i + 1;
        pthread_create(&passengers[i], NULL, passenger_func, &ids[i]);
    }
    pthread_create(&bus_thread, NULL, bus_func, NULL);
    for(int i = 0; i < NUM_PASSENGERS; i++){
        pthread_join(passengers[i], NULL);
    }
    return 0;
}