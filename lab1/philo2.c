#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define TIMES_TO_EAT 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t print_lock;

void print_state(int philosopher, const char *state) {
    pthread_mutex_lock(&print_lock);
    printf("Filosofo %d: %s\n", philosopher, state);
    fflush(stdout);
    pthread_mutex_unlock(&print_lock);
}

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    
    for (int i = 0; i < TIMES_TO_EAT; i++) {
        print_state(id, "sta pensando");
        sleep(1); 
        int first_fork = (left_fork < right_fork) ? left_fork : right_fork;
        int second_fork = (left_fork < right_fork) ? right_fork : left_fork;
        
        pthread_mutex_lock(&forks[first_fork]);
        print_state(id, "ha la sua bacchetta");
        
        pthread_mutex_lock(&forks[second_fork]);
        print_state(id, "ha la sua bacchetta");
        
        // Mangio
        print_state(id, "sta mangiando");
        sleep(1);  // Sleep per simulare il mangiare
        
        // Rilascio le bacchette
        pthread_mutex_unlock(&forks[second_fork]);
        pthread_mutex_unlock(&forks[first_fork]);
        print_state(id, "ha rilasciato le sue due bacchette");
    }
    
    print_state(id, "ha finito");
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    // Inizializzo i lock delle bacchette e il lock di stampa
    pthread_mutex_init(&print_lock, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    
    // Creo i thread per i filosofi
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
    // Attendo che tutti i filosofi finiscano
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Distruggo i lock
    pthread_mutex_destroy(&print_lock);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    
    printf("\nTutti i filosofi hanno finito senza deadlock!\n");
    
    return 0;
}
