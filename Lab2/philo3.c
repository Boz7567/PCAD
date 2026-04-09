#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "my_semaphore.h"

#define N_FILOSOFI 50
#define POSTI_SALA_ATTESA (N_FILOSOFI - 1)
#define PASTI_PER_FILOSOFO 6

my_semaphore sala_attesa;
my_semaphore bacchette[N_FILOSOFI];

int pasti_consumati[N_FILOSOFI] = {0};
bool finito = false;
pthread_mutex_t finito_lock = PTHREAD_MUTEX_INITIALIZER;

int my_sem_init(my_semaphore *ms, unsigned int v) {
    if (ms == NULL) return -1;
    
    ms->V = v;
    
    if (pthread_mutex_init(&ms->lock, NULL) != 0) return -1;
    if (pthread_cond_init(&ms->varcond, NULL) != 0) {
        pthread_mutex_destroy(&ms->lock);
        return -1;
    }
    
    return 0;
}

int my_sem_wait(my_semaphore *ms) {
    if (ms == NULL) return -1;
    
    pthread_mutex_lock(&ms->lock);
    
    while (ms->V == 0) {
        pthread_cond_wait(&ms->varcond, &ms->lock);
    }
    
    ms->V--;
    
    pthread_mutex_unlock(&ms->lock);
    return 0;
}

int my_sem_signal(my_semaphore *ms) {
    if (ms == NULL) return -1;
    
    pthread_mutex_lock(&ms->lock);
    
    ms->V++;
    
    // Usare broadcast invece di signal per risvegliare più thread
    // quando si vuole terminare il programma
    pthread_cond_signal(&ms->varcond);
    
    pthread_mutex_unlock(&ms->lock);
    return 0;
}

int my_sem_destroy(my_semaphore *ms) {
    if (ms == NULL) return -1;
    
    pthread_mutex_destroy(&ms->lock);
    pthread_cond_destroy(&ms->varcond);
    
    return 0;
}

void* filosofo(void* arg) {
    int id = *(int*)arg;
    
    while (1) {
        // Verificare se abbiamo finito
        pthread_mutex_lock(&finito_lock);
        if (finito) {
            pthread_mutex_unlock(&finito_lock);
            break;
        }
        pthread_mutex_unlock(&finito_lock);
        
        // Pensare
        printf("Filosofo %d sta pensando...\n", id+1);
        usleep(rand() % 500000);
        
        // Entrare in sala d'attesa (solo N-1 possono provare a mangiare)
        my_sem_wait(&sala_attesa);
        printf("Filosofo %d entra in sala d'attesa\n", id+1);
        
        // Prendere le bacchette
        my_sem_wait(&bacchette[id]);
        my_sem_wait(&bacchette[(id + 1) % N_FILOSOFI]);
        
        // Mangiare
        pasti_consumati[id]++;
        printf("Filosofo %d sta mangiando (pasto %d di %d)...\n", 
               id+1, pasti_consumati[id], PASTI_PER_FILOSOFO);
        usleep(rand() % 500000);
        
        // Rilasciare le bacchette
        my_sem_signal(&bacchette[id]);
        my_sem_signal(&bacchette[(id + 1) % N_FILOSOFI]);
        
        // Uscire dalla sala d'attesa
        my_sem_signal(&sala_attesa);
        printf("Filosofo %d esce dalla sala d'attesa\n", id+1);
    }
    
    printf("Filosofo %d ha finito! Ha mangiato %d pasti.\n", id+1, pasti_consumati[id]);
    return NULL;
}

int main() {
    pthread_t filosofi[N_FILOSOFI];
    int ids[N_FILOSOFI];
    
    srand(time(NULL));
    
    // Inizializzare i semafori
    my_sem_init(&sala_attesa, POSTI_SALA_ATTESA);
    
    for (int i = 0; i < N_FILOSOFI; i++) {
        my_sem_init(&bacchette[i], 1);
    }
    
    // Creare i thread dei filosofi
    for (int i = 0; i < N_FILOSOFI; i++) {
        ids[i] = i;
        pthread_create(&filosofi[i], NULL, filosofo, &ids[i]);
    }
    
    // Attendere che tutti i filosofi abbiano mangiato il numero richiesto di pasti
    bool tutti_finito = false;
    while (!tutti_finito) {
        sleep(1);
        tutti_finito = true;
        for (int i = 0; i < N_FILOSOFI; i++) {
            if (pasti_consumati[i] < PASTI_PER_FILOSOFO) {
                tutti_finito = false;
                break;
            }
        }
    }
    
    // Segnalare ai filosofi di terminare
    pthread_mutex_lock(&finito_lock);
    finito = true;
    pthread_mutex_unlock(&finito_lock);
    
    // Risvegliare eventuali filosofi in attesa sui semafori
    for (int i = 0; i < POSTI_SALA_ATTESA; i++) {
        my_sem_signal(&sala_attesa);
    }
    
    // Attendere la terminazione di tutti i filosofi
    for (int i = 0; i < N_FILOSOFI; i++) {
        pthread_join(filosofi[i], NULL);
    }
    
    printf("\n=== TUTTI I FILOSOFI HANNO FINITO ===\n");
    for (int i = 0; i < N_FILOSOFI; i++) {
        printf("Filosofo %d: %d pasti consumati\n", i+1, pasti_consumati[i]);
    }
    
    // Distruggere i semafori
    my_sem_destroy(&sala_attesa);
    for (int i = 0; i < N_FILOSOFI; i++) {
        my_sem_destroy(&bacchette[i]);
    }
    
    pthread_mutex_destroy(&finito_lock);
    
    return 0;
}