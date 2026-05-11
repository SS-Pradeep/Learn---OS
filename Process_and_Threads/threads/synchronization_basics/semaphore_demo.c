#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore; // Declare a semaphore

void* task(void* arg) {
    sem_wait(&semaphore); // Wait (decrement) the semaphore before entering the critical section
    printf("Hello from the thread! Thread ID: %lu\n", pthread_self());
    sleep(1); // Simulate some work in the critical section
    sem_post(&semaphore); // Signal (increment) the semaphore after leaving the critical section
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    sem_init(&semaphore, 0, 1); // Initialize the semaphore with a value of 1

    // Create the first thread
    pthread_create(&thread1, NULL, task , NULL);
    // Create the second thread
    pthread_create(&thread2, NULL, task , NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Hello from the main thread! Main Thread ID: %lu\n", pthread_self());
    sem_destroy(&semaphore); // Destroy the semaphore   
    return 0;
}