#include <stdio.h>
#include <pthread.h>

pthread_t ntid[8];
int count=0;

void * thr_fn(void *arg) {
    int i;
    count=count+1;
    return NULL;
}

int main(void){
    int i;
    void* res;

    for (i=0; i<2; i++)
        pthread_create(&ntid[i], NULL, thr_fn, NULL);

    printf("count=%d\n", count);
    return 0;
}