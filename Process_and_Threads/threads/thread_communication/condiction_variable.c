#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutexLock;
pthread_cond_t condVar;

int ready = 0;

void* task1(void* arg) {
    pthread_mutex_lock(&mutexLock); // Lock the mutex before checking the condition
    while (ready == 0) { // Wait until the condition is met
        pthread_cond_wait(&condVar, &mutexLock); // Wait for the condition variable to be signaled
    }
    printf("Thread 1: Condition met! Proceeding with work...\n");
    pthread_mutex_unlock(&mutexLock); // Unlock the mutex after checking the condition
    return NULL;
}
int main() {

    pthead_t thread1, thread2;
    pthread_mutex_init(&mutexLock, NULL);
    pthread_cond_init(&condVar, NULL);

    // Simulate some work in the main thread
    thread_create(&thread1, NULL, task1, NULL);
    thread_create(&thread2, NULL, task1, NULL);
    sleep(2);
    // Lock the mutex before modifying the shared variable
    pthread_mutex_lock(&mutexLock);
    ready = 1; // Set the shared variable to indicate that the condition is met
    pthread_cond_signal(&condVar); // Signal the waiting thread that the condition is met
    pthread_mutex_unlock(&mutexLock); // Unlock the mutex
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutexLock);
    pthread_cond_destroy(&condVar);

    return 0;
}