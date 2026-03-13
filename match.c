#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#define fab(a,b) for(int i=a;i<b;i++)

int score = 0,ballnum=0,overnum=1;
bool hit = false;

pthread_mutex_t scorelock;
pthread_mutex_t fieldlock;
pthread_cond_t hitcond;

sem_t crease;

void* bowler(void* arg){
    pthread_mutex_lock(&fieldlock);
    printf("Bowler delivered %d ball\n",ballnum);
    hit = true;
    pthread_cond_signal(&hitcond);
    pthread_mutex_unlock(&fieldlock);

    return NULL;
}

void* batsman(void* arg){
    sem_wait(&crease);
    pthread_mutex_lock(&fieldlock);
    while(!hit)
        pthread_cond_wait(&hitcond, &fieldlock);

    hit=false;
    pthread_mutex_unlock(&fieldlock);
    pthread_mutex_lock(&scorelock);

    //int runs = rand() % 7;
    int arr[] = {1,1,1,1,1,2,2,2,2,2,4,4,4,4,4,6,6,6,3,3,5};
    int runs = arr[rand() % 21];
    score += runs;

    printf("Stats after Ball %d  : scored %d runs. Total score = %d\n", ballnum ,runs, score);
    pthread_mutex_unlock(&scorelock);
    sem_post(&crease);

    return NULL;
}
    int main(){

    srand(time(NULL));

    pthread_mutex_init(&scorelock,NULL);
    pthread_mutex_init(&fieldlock,NULL);
    pthread_cond_init(&hitcond,NULL);
    sem_init(&crease,0,2);

    pthread_t bowler_thread;
    pthread_t batsman_thread;

    fab(1,7){
        ballnum=i;
    pthread_create(&bowler_thread,NULL,bowler,NULL);
    pthread_create(&batsman_thread,NULL,batsman,NULL);

    pthread_join(bowler_thread,NULL);
    pthread_join(batsman_thread,NULL);
    printf("\n");
    }
    printf("%d over has been completed",overnum);
    sem_destroy(&crease);
    pthread_mutex_destroy(&scorelock);
    pthread_mutex_destroy(&fieldlock);
    pthread_cond_destroy(&hitcond);

    return 0;
}
