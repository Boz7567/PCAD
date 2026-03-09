#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM_PHILOS 5
int id [NUM_PHILOS] = {0,1,2,3,4} ;
char *status [NUM_PHILOS] = {"Sta pensando","ha la sua bacchetta sinistra", "ha la sua bacchetta destra", "sta mangiando","ha rilasciato le sue due bacchette"};


int main(){
    pthread_t philosophers[NUM_PHILOS];
    
}

void test(){
    for (int i = 0; i < NUM_PHILOS; i++){
        printf("Il filosofo %d %s\n", id[i], status[i]);
    }
}