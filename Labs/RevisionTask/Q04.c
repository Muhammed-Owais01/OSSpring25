#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ORDERS 10
#define NUM_CUSTOMERS 5

typedef struct {
    int orders[MAX_ORDERS];
    int front;
    int rear;
    int count;
} OrderQueue;

OrderQueue orderQueue = {.front = 0, .rear = 0, .count = 0};
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t chef_sem;

int order_id = 1;

void enqueue_order(int order) {
    if (orderQueue.count == MAX_ORDERS) {
        printf("Order queue is full! Order %d not placed.\n", order);
        return;
    }
    orderQueue.orders[orderQueue.rear] = order;
    orderQueue.rear = (orderQueue.rear + 1) % MAX_ORDERS;
    orderQueue.count++;
}

int dequeue_order() {
    if (orderQueue.count == 0)
        return -1;
    int order = orderQueue.orders[orderQueue.front];
    orderQueue.front = (orderQueue.front + 1) % MAX_ORDERS;
    orderQueue.count--;
    return order;
}

void* customer_thread(void* arg) {
    int id = *(int*)arg;
    free(arg);

    sleep(rand() % 2);

    pthread_mutex_lock(&queue_mutex);
    int my_order = order_id++;
    enqueue_order(my_order);
    printf("Customer %d placed order #%d\n", id, my_order);
    pthread_mutex_unlock(&queue_mutex);

    return NULL;
}

void* chef_thread(void* arg) {
    int id = *(int*)arg;
    free(arg);

    while (1) {
        sem_wait(&chef_sem);

        pthread_mutex_lock(&queue_mutex);
        int order = dequeue_order();
        pthread_mutex_unlock(&queue_mutex);

        if (order != -1) {
            printf("Chef %d started preparing order #%d\n", id, order);
            sleep(2); 
            printf("Chef %d finished order #%d\n", id, order);
        } else {
            sem_post(&chef_sem);
            break; 
        }

        sem_post(&chef_sem);
    }

    return NULL;
}

int main() {
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t chefs[2];

    sem_init(&chef_sem, 0, 2);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customers[i], NULL, customer_thread, id);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++)
        pthread_join(customers[i], NULL);

    for (int i = 0; i < 2; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&chefs[i], NULL, chef_thread, id);
    }

    for (int i = 0; i < 2; i++)
        pthread_join(chefs[i], NULL);

    sem_destroy(&chef_sem);
    pthread_mutex_destroy(&queue_mutex);

    printf("All orders have been prepared.\n");

    return 0;
}