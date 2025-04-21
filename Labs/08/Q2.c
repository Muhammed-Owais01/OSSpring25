#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* numbers;
    int count;
} ThreadData;

void* calculate_average(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int sum = 0;
    for (int i = 0; i < data->count; i++) {
        sum += data->numbers[i];
    }
    int* avg = malloc(sizeof(int));
    *avg = sum / data->count;
    return avg;
}

void* calculate_min(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int min = data->numbers[0];
    for (int i = 1; i < data->count; i++) {
        if (data->numbers[i] < min) {
            min = data->numbers[i];
        }
    }
    int* result = malloc(sizeof(int));
    *result = min;
    return result;
}

void* calculate_max(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int max = data->numbers[0];
    for (int i = 1; i < data->count; i++) {
        if (data->numbers[i] > max) {
            max = data->numbers[i];
        }
    }
    int* result = malloc(sizeof(int));
    *result = max;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int* numbers = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    ThreadData data = { numbers, count };
    pthread_t avg_thread, min_thread, max_thread;

    int *avg_result, *min_result, *max_result;

    pthread_create(&avg_thread, NULL, calculate_average, &data);
    pthread_create(&min_thread, NULL, calculate_min, &data);
    pthread_create(&max_thread, NULL, calculate_max, &data);

    pthread_join(avg_thread, (void**)&avg_result);
    pthread_join(min_thread, (void**)&min_result);
    pthread_join(max_thread, (void**)&max_result);

    printf("The average value is %d.\n", *avg_result);
    printf("The minimum value is %d.\n", *min_result);
    printf("The maximum value is %d.\n", *max_result);

    free(avg_result);
    free(min_result);
    free(max_result);
    free(numbers);

    return 0;
}
