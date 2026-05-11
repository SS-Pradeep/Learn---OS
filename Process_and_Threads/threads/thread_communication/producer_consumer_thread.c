#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
pthread_mutex_t mutexLock;
pthread_cond_t fullCond, emptyCond;

void* producer_thread(void* arg) {
    for (int i=0; i<20; i++) {
        pthread_mutex_lock(&mutexLock); // Lock the mutex before accessing the buffer
        while (count == BUFFER_SIZE) { // Wait until there is space in the buffer
            pthread_cond_wait(&emptyCond, &mutexLock); // Wait for the empty condition
        }
        buffer[count++] = i; // Produce an item and add it to the buffer
        printf("Produced: %d\n", i);
        pthread_cond_signal(&fullCond); // Signal that there is a new item in the buffer
        pthread_mutex_unlock(&mutexLock); // Unlock the mutex
    }
    return NULL;
}

void* consumer_thread(void* arg) {
    for (int i=0; i<20; i++) {
        pthread_mutex_lock(&mutexLock); // Lock the mutex before accessing the buffer
        while (count == 0) { // Wait until there is at least one item in the buffer
            pthread_cond_wait(&fullCond, &mutexLock); // Wait for the full condition
        }
        int item = buffer[--count]; // Consume an item from the buffer
        printf("Consumed: %d\n", item);
        pthread_cond_signal(&emptyCond); // Signal that there is now space in the buffer
        pthread_mutex_unlock(&mutexLock); // Unlock the mutex
    }
    return NULL;
}


int main() {
    pthread_t producer, consumer;
    pthread_mutex_init(&mutexLock, NULL);
    pthread_cond_init(&fullCond, NULL);
    pthread_cond_init(&emptyCond, NULL);

    // Create producer and consumer threads
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    // Wait for both threads to finish
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // Clean up mutex and condition variables
    pthread_mutex_destroy(&mutexLock);
    pthread_cond_destroy(&fullCond);
    pthread_cond_destroy(&emptyCond);

    return 0;
}