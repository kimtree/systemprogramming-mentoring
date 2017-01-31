#include <stdio.h>
#include <pthread.h>
pthread_t ntid[8];

struct SharedData
{
    int count;
    // (1)
    pthread_mutex_t lock;
    // (2)
};

void * thr_fn(void *arg){
    struct SharedData* pd=(struct SharedData*) arg;
    int i;
    // (3)
    for (i=0; i<10000; i++) {
        // (4)
        pd->count = pd->count + 1;
        // (5)
    }
    // (6)
    return((void *)0);
}

int main(void){
    struct SharedData d;
    struct SharedData *pd=&d;
    int i;
    d.count=0;
    // (7)
    for (i=0; i<8; i++) {
        // (8)
        pthread_create(&ntid[i], NULL, thr_fn, (void*)pd);
        // (9)
    }
    for (i=0; i<8; i++) {
        // (10)
        pthread_join(ntid[i], NULL);
        // (11)
    }
    // (12)
    printf("count=%d\n", d.count);
    // (13)
    return 0;
}