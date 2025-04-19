#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000000
#define NUM_THREADS 10

float *A, *B, *C;

typedef struct {
    int start;
    int end;
} ThreadData;

void *add_arrays(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i < data->end; i++) {
        C[i] = A[i] + B[i];
    }
    return NULL;
}

int main() {
    A = malloc(sizeof(float) * SIZE);
    B = malloc(sizeof(float) * SIZE);
    C = malloc(sizeof(float) * SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        A[i] = i * 1.0f;
        B[i] = (SIZE - i) * 1.0f;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    int chunk_size = SIZE / NUM_THREADS;

    clock_t start = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, add_arrays, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Concurrent execution time with %d threads: %f seconds\n", NUM_THREADS, time_spent);

    free(A);
    free(B);
    free(C);

    return 0;
}
