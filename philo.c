#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t bacchette[N];

void* filosofo(void* arg) {
    int id = *(int*)arg;
    int sx = id;
    int dx = (id + 1) % N;

    for (int i = 0; i < 5; i++) { 
        printf("Filosofo %d: sta pensando\n", id);
        
        pthread_mutex_lock(&bacchette[sx]);
        printf("Filosofo %d: ha la sua bacchetta sinistra\n", id);
        
        sleep(1); 

        pthread_mutex_lock(&bacchette[dx]);
        printf("Filosofo %d: ha la sua bacchetta destra\n", id);
        
        printf("Filosofo %d: sta mangiando\n", id);
        
        pthread_mutex_unlock(&bacchette[dx]);
        pthread_mutex_unlock(&bacchette[sx]);
        printf("Filosofo %d: ha rilasciato le sue due bacchette\n", id);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];
    for (int i = 0; i < N; i++) pthread_mutex_init(&bacchette[i], NULL);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);
    return 0;
}