#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define N_PASSEGGERI 10
#define CAPIENZA_BUS 3

struct bus {
    pthread_t thread;
    unsigned int passeggeri;
    pthread_mutex_t lock;
    pthread_cond_t full;
    pthread_cond_t disponibile;
    pthread_cond_t lap;
    pthread_cond_t empty;
    bool giro_finito;
};

pthread_t passeggeri[N_PASSEGGERI];
struct bus Bus;
int id[N_PASSEGGERI];

void* passenger_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&Bus.lock);

        while (Bus.giro_finito || Bus.passeggeri >= CAPIENZA_BUS)
            pthread_cond_wait(&Bus.disponibile, &Bus.lock);

        Bus.passeggeri++;
        printf("Passeggero %d salito sul bus. (Posti occupati: %d/%d)\n",
               id, Bus.passeggeri, CAPIENZA_BUS);

        if (Bus.passeggeri == CAPIENZA_BUS) {
            pthread_cond_signal(&Bus.full);
            printf("Bus pieno!\n");
        }

        while (!Bus.giro_finito)
            pthread_cond_wait(&Bus.lap, &Bus.lock);

        Bus.passeggeri--;
        printf("Passeggero %d sceso dal bus. (Posti occupati: %d/%d)\n",
               id, Bus.passeggeri, CAPIENZA_BUS);

        if (Bus.passeggeri == 0)
            pthread_cond_signal(&Bus.empty);

        pthread_mutex_unlock(&Bus.lock);
        usleep(100000);
    }
    return NULL;
}

void* bus_func(void* arg) {
    pthread_mutex_lock(&Bus.lock);

    while (1) {
        Bus.giro_finito = false;
        pthread_cond_broadcast(&Bus.disponibile);

        while (Bus.passeggeri < CAPIENZA_BUS)
            pthread_cond_wait(&Bus.full, &Bus.lock);

        printf("\n--- FACCIO IL GIRO ---\n");
        pthread_mutex_unlock(&Bus.lock);
        sleep(3);
        pthread_mutex_lock(&Bus.lock);
        printf("--- GIRO FATTO ---\n\n");

        Bus.giro_finito = true;
        pthread_cond_broadcast(&Bus.lap);

        while (Bus.passeggeri > 0)
            pthread_cond_wait(&Bus.empty, &Bus.lock);
    }
    return NULL;
}

int main() {
    Bus.passeggeri = 0;
    Bus.giro_finito = false;
    pthread_mutex_init(&Bus.lock, NULL);
    pthread_cond_init(&Bus.full, NULL);
    pthread_cond_init(&Bus.disponibile, NULL);
    pthread_cond_init(&Bus.lap, NULL);
    pthread_cond_init(&Bus.empty, NULL);

    pthread_create(&Bus.thread, NULL, bus_func, NULL);

    for (int i = 0; i < N_PASSEGGERI; i++) {
        id[i] = i;
        pthread_create(&passeggeri[i], NULL, passenger_func, &id[i]);
    }

    for (int i = 0; i < N_PASSEGGERI; i++)
        pthread_join(passeggeri[i], NULL);

    return 0;
}