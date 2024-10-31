#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 3
#define ARRAY_SIZE 7500

pthread_mutex_t the_mutex;

int array[7500];
int TOTAL = 0;

void* Calculate(void* arg){
    int tid = (int)(size_t)arg;
    int start = tid * (ARRAY_SIZE / NUMBER_OF_THREADS);
    int end = start + (ARRAY_SIZE / NUMBER_OF_THREADS);

    for (int i = start; i < end; i++){
        pthread_mutex_lock(&the_mutex);
        TOTAL = TOTAL + array[i];
        pthread_mutex_unlock(&the_mutex);
        
    }
    pthread_exit(NULL);

}

int main(int argc, char *argv[]){
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    for (int i = 0; i < ARRAY_SIZE; ++i){
        array[i] = i + 1;
    }

    pthread_mutex_init(&the_mutex,NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        status = pthread_create(&threads[i], NULL, Calculate,(void*)(size_t)i);
        if(status != 0){
            printf("Opps. Pthread_create returned error code %d", status);
            exit(-1);
        }

    }

    for (int i = 0;i< NUMBER_OF_THREADS; i++){
        pthread_join(threads[i],NULL);

    }

    pthread_mutex_destroy(&the_mutex);
    printf("The total is %d", TOTAL);
}