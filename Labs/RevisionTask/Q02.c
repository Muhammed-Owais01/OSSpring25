#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
int array[SIZE] = {9, 4, 7, 3, 1, 8, 5, 2, 6, 0};

typedef struct {
    int start;
    int end;
} ThreadArgs;

void* sort_part(void* args) {
    ThreadArgs* targs = (ThreadArgs*) args;
    int start = targs->start;
    int end = targs->end;

    for (int i = start; i < end; i++) {
        for (int j = start; j < end - (i - start) - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    pthread_exit(NULL);
}

void merge(int start, int mid, int end) {
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int* left = malloc(left_size * sizeof(int));
    int* right = malloc(right_size * sizeof(int));

    for (int i = 0; i < left_size; i++)
        left[i] = array[start + i];
    for (int i = 0; i < right_size; i++)
        right[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = start;
    while (i < left_size && j < right_size) {
        array[k++] = (left[i] < right[j]) ? left[i++] : right[j++];
    }

    while (i < left_size)
        array[k++] = left[i++];
    while (j < right_size)
        array[k++] = right[j++];

    free(left);
    free(right);
}

int main() {
    pthread_t tid1, tid2;
    ThreadArgs t1_args = {0, SIZE / 2};
    ThreadArgs t2_args = {SIZE / 2, SIZE};

    pthread_create(&tid1, NULL, sort_part, &t1_args);
    pthread_create(&tid2, NULL, sort_part, &t2_args);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    merge(0, SIZE / 2 - 1, SIZE - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}
