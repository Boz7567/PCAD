#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_FILOSOFI 5

const int id[N_FILOSOFI] = {0,1,2,3,4};


void *test(void* a);

int main(){

    // int* id = malloc(sizeof(int) * N_FILOSOFI);
    // for(int i = 0; i<N_FILOSOFI; i++){
    //     id[i] = i+1;
    // }


    pthread_t* filosofi;

    filosofi = malloc(sizeof(pthread_t) * N_FILOSOFI);

    if(filosofi == NULL){
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

    free(filosofi);
    return 0;
}


void* test(void* a){
    int* s = (int *)a;
    printf("Sono il filosofo %d\n", *s);

}