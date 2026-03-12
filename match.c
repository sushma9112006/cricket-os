#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int score = 0;
bool hit = false;

pthread_mutex_t scorelock;
pthread_mutex_t fieldlock;
pthread_cond_t hitcond;

sem_t crease;

int main(){
    pthread_mutex_init(&scorelock,NULL);
    pthread_mutex_init(&fieldlock,NULL);
    pthread_cond_init(&hitcond,NULL);
    sem_init(&crease,0,2);
    return 0;
}
