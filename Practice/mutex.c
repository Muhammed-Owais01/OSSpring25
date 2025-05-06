#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define NUM_THREADS 5

int shared_data = 0;
pthread_mutex_t mutex;

void* thread_function(void* arg) {
    int thread_id = *((int *)arg);
    
    pthread_mutex_lock(&mutex);
    ++shared_data;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) pthread_join(threads[i], NULL);
    printf("%d\n", shared_data);

    pthread_mutex_destroy(&mutex);

    return 0;
}