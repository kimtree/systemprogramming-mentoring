#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
int counter = 0;
#define NUM_THREAD 2
pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thr_main1(void* arg) {
    puts("thread 1 start\n");
    pthread_mutex_lock(&lock1);
    sleep(1);
    pthread_mutex_lock(&lock2);
    counter++;
    sleep(1);
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return ((void*)1);
}

void* thr_main2(void* arg) {
    puts("thread 2 start\n");
    pthread_mutex_lock(&lock2);
    sleep(1);
    pthread_mutex_lock(&lock1);
    counter++;
    sleep(1);
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return ((void*)1);
}

int main (void) {
    int err, i;
    pthread_t tid[NUM_THREAD];
    void *tret;

    err = pthread_create(&tid[0], NULL, thr_main1, NULL);
    if (err != 0) exit(1);
    err = pthread_create(&tid[1], NULL, thr_main2, NULL);
    if (err != 0) exit(1);

    for (i=0; i<NUM_THREAD; i++) {
        if (pthread_join(tid[i], &tret)) exit(2);
    }
    printf("done %d!\n", counter);
    return 0;
}
