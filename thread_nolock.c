#include <pthread.h>
pthread_t ntid[8];

struct SharedData
{
    int count;
    pthread_mutex_t lock;
};

void * thr_fn(void *arg){
    struct SharedData* pd=(struct SharedData*) arg;
    int i;

    for (i=0; i<10000; i++) {
        pd->count = pd->count + 1;
    }

    return((void *)0);
}

int main(void){
    struct SharedData d;
    struct SharedData *pd=&d;
    int i;
    d.count=0;

    for (i=0; i<8; i++) {
        pthread_create(&ntid[i], NULL, thr_fn, (void*)pd);
    }
    for (i=0; i<8; i++) {
        pthread_join(ntid[i], NULL);
    }

    printf("count=%d\n", d.count);

    return 0;
}