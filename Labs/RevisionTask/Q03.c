#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int shared_balance = 500;
pthread_mutex_t mutex;

void* modify_balance(void* arg) {
    int num = *((int *)arg);
    pthread_mutex_lock(&mutex);
    shared_balance -= num;
    pthread_mutex_unlock(&mutex);
    
}

int main() {
    pthread_t threads[3];
    int amount = 50;
    for (int i = 0; i < 3; ++i) {
        pthread_create(&threads[i], NULL, modify_balance, (void *)&amount);
    }

    for (int i = 0; i < 3; ++i) pthread_join(threads[i], NULL);
    printf("%d\n", shared_balance);
}