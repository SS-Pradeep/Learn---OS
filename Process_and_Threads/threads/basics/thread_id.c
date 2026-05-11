#include <stdio.h>
#include <pthread.h>

void* task(void* arg) {
    printf("Hello from the thread! Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, task, NULL);
    pthread_join(thread_id, NULL); // It is similar to waiting for a process to finish
    printf("Hello from the main thread! Main Thread ID: %lu\n", pthread_self());
    return 0;
}