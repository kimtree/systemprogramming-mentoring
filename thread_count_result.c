#include <stdio.h>
#include <pthread.h>
pthread_t ntid[8];

/////////////////// HERE

void * thr_fn(void *arg) {
    int count=0; // COUNT_VARIABLE
    int i;
    for (i=0; i<10000; i++)
        count++;

    return((void *)count);
}

int main(void) {
    int i;
    void* res;
    for (i=0; i<2; i++)
        pthread_create(&ntid[i], NULL, thr_fn,NULL);

    for (i=0; i<2; i++) {
        pthread_join(ntid[i], &res);
        printf("count= %d\n", (int)res);
    }
    return 0;
}