#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define N_FILOSOFI 5

const int id[N_FILOSOFI] = {0,1,2,3,4};


pthread_t* filosofi;
pthread_mutex_t* bacchette;

bool think();
void *test(void* a);

int main(){
    srand(time(NULL));
    filosofi = malloc(sizeof(pthread_t) * N_FILOSOFI);
    bacchette = malloc(sizeof(pthread_mutex_t) * N_FILOSOFI);

    for(int i = 0; i<N_FILOSOFI; i++){
        pthread_mutex_init(&bacchette[i], NULL);
    }

    if(filosofi == NULL || bacchette == NULL){
        printf("Errore allocazione memoria\n");
        return 1;
    }
    // printf("Memoria allocata correttamente\n");

    for(int i = 0; i < N_FILOSOFI; i++){
        if(pthread_create(&filosofi[i], NULL, test, &id[i]) != 0)
        {
            printf("palle");
            return 1;
        }   
    }

    for(int i = 0; i < N_FILOSOFI; i++){
        pthread_join(filosofi[i], NULL);
    }

    for(int i = 0; i < N_FILOSOFI; i++){
        pthread_mutex_destroy(&bacchette[i]);
    }

    free(filosofi);
    return 0;
}


void* test(void* a){
    int* s = (int *)a;
    // printf("Sono il filosofo %d\n", *s);
    bool b = think();
    if(!b){
        printf("Filosofo %d, sta pensando\n", *s);
    }
    else{
        if(pthread_mutex_lock(&bacchette[*s]) == 0){
            printf("Filosofo %d, ha la bacchetta sinistra\n");
            if(pthread_mutex_lock(&bacchette[((*s)+1)%N_FILOSOFI]) == 0){
                printf("Filosofo %d, ha la bacchetta destra\n", *s);
                printf("Filosofo %d, sta mangiando\n", *s);


                //finito di mangiare
                int temp1 = pthread_mutex_unlock(&bacchette[*s]);
                int temp2 = pthread_mutex_unlock(&bacchette[((*s)+1)%N_FILOSOFI]);
                if(temp1 == 0 && temp2 == 0){
                    printf("Filosofo %d, ha finito di mangiare\n");
                }
            }
        }
    }


}

bool think(){
    return rand()%2;
}