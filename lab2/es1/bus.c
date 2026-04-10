#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define N 7
#define C 5

pthread_t pass[N];

typedef struct bus{
    unsigned int seats;
    pthread_t bus_t;

    bool boarding; // si può salire
    bool unboarding; // si sta scendendo

    pthread_mutex_t lock;
    pthread_cond_t start; // bus pieno
    pthread_cond_t end; // posti disponibili
    pthread_cond_t down; // fine tour
} Bus;

Bus bus;

void *up(void *ptr);
void *tour(void *ptr);

int main(){

    int n[N];

    pthread_mutex_init(&bus.lock,NULL);
    pthread_cond_init(&bus.start,NULL);
    pthread_cond_init(&bus.end,NULL);
    pthread_cond_init(&bus.down,NULL);

    bus.seats = 0;
    bus.boarding = true;
    bus.unboarding = false;

    pthread_create(&bus.bus_t,NULL,tour,NULL);
    
    for(int i=0; i<N; i++){
        n[i]=i+1;
        pthread_create(&pass[i],NULL,up,&n[i]);
    }

    pthread_join(bus.bus_t,NULL);

    for(int i=0; i<N; i++){
        pthread_join(pass[i],NULL);
    }

    return 0;
}

void *tour(void *ptr){

    while(1){

        pthread_mutex_lock(&bus.lock);

        printf("-----------------\nPOSTI RIMANENTI: %d\n", C - bus.seats);

        bus.boarding = true;
        bus.unboarding = false;

        while(bus.seats < C)
            pthread_cond_wait(&bus.start,&bus.lock);

        printf("Tour START\n");

        bus.boarding = false;

        pthread_mutex_unlock(&bus.lock);

        sleep(2);

        pthread_mutex_lock(&bus.lock);

        printf("Tour END\n");

        bus.unboarding = true;
        pthread_cond_broadcast(&bus.down);

        while(bus.seats > 0)
            pthread_cond_wait(&bus.end,&bus.lock);

        printf("Bus EMPTY!\n");

        bus.unboarding = false;
        bus.boarding = true;

        pthread_cond_broadcast(&bus.end);

        pthread_mutex_unlock(&bus.lock);
    }
}

void *up(void *ptr){

    int id = *(int *)ptr;

    while(1){

        pthread_mutex_lock(&bus.lock);

        while(bus.seats == C || bus.unboarding || !bus.boarding)
            pthread_cond_wait(&bus.end,&bus.lock);

        bus.seats++;
        printf("P%d salito. POSTI RIMANENTI: %d\n", id, C - bus.seats);

        if(bus.seats == C){
            pthread_cond_broadcast(&bus.start);
            printf("P%d avvisa: Possiamo partire!\n", id);
        }

        while(!bus.unboarding)
            pthread_cond_wait(&bus.down,&bus.lock);

        bus.seats--;
        printf("P%d sceso. POSTI RIMANENTI: %d\n", id, C - bus.seats);

        if(bus.seats == 0){
            pthread_cond_broadcast(&bus.end);
            printf("P%d avvisa: Bus vuoto!\n", id);
        }

        pthread_mutex_unlock(&bus.lock);

        sleep(1);
    }
}