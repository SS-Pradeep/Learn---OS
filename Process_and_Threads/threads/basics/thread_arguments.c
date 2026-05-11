#include <stdio.h>
#include <pthread.h>

void* task(void* arg) {
    int thread_arg = *((int*)arg); // Cast the argument back to an integer
    printf("Hello from the thread! Thread ID: %lu, Argument: %d\n", pthread_self(), thread_arg);
    return NULL;
}
int main() {
    pthread_t thread_id;
    int thread_arg = 42; // Argument to pass to the thread

    // Create the thread and pass the argument
    if (pthread_create(&thread_id, NULL, task, &thread_arg) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(thread_id, NULL); // Wait for the thread to finish
    printf("Hello from the main thread! Main Thread ID: %lu\n", pthread_self());
    return 0;
}