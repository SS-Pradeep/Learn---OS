#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* task(void* arg) {
    printf("Hello from the thread! Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create the first thread
    pthread_create(&thread1, NULL, task, NULL);
    // Create the second thread
    pthread_create(&thread2, NULL, task, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Hello from the main thread! Main Thread ID: %lu\n", pthread_self());
    return 0;
}