#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000

int main() {
    float *A = malloc(sizeof(float) * SIZE);
    float *B = malloc(sizeof(float) * SIZE);
    float *C = malloc(sizeof(float) * SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        A[i] = i * 1.0f;
        B[i] = (SIZE - i) * 1.0f;
    }

    clock_t start = clock();

    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Serial execution time: %f seconds\n", time_spent);

    free(A);
    free(B);
    free(C);

    return 0;
}
