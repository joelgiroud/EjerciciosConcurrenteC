#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SLOTS 100
#define ITEMS 100

sem_t mutex, slots, items;


void* producir(void* threadid){
    int i;
    long taskid = (long) threadid;
    for(i=0; i<ITEMS; i++){
        sem_wait(&slots);
        sem_wait(&mutex);
        printf("Se produjo (hilo %ld): %d\n", taskid, i+1);
        sem_post(&mutex);
        sem_post(&items);
    }
    //return NULL;
    pthread_exit(NULL);
}

void* consumir(void* threadid){
    int i;
    long taskid = (long) threadid;
    for(i=0; i<ITEMS; i++){
        sem_wait(&items);
        sem_wait(&mutex);
        printf("Se ha consumido (hilo %ld): %d\n", taskid, i+1); //DEVUELVE EL ID DEL HILO
        sem_post(&mutex);
        sem_post(&items);
    }
    //return NULL;
    pthread_exit(NULL);
}

int main(){
    pthread_t tcons, tpro;
    sem_init(&mutex, 0, 1);
    sem_init(&slots, 0, SLOTS);
    sem_init(&items, 0, 0);
    
    pthread_create(&tcons, NULL, consumir, NULL);
    pthread_create(&tpro, NULL, producir, NULL);
    pthread_join(tcons, NULL);
    pthread_join(tpro, NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&slots);
    sem_destroy(&items);
    
    return 0;
}
