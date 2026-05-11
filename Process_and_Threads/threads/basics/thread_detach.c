#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* background_task(void* arg) {
    printf("[THREAD] Working in the background...\n");
    sleep(3);
    printf("[THREAD] Work finished. I am exiting and cleaning myself up!\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    // 1. Create the thread
    if (pthread_create(&thread_id, NULL, background_task, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // 2. Detach the thread
    // Once detached, you CANNOT call pthread_join on it.
    pthread_detach(thread_id);
    printf("[MAIN] Thread detached. I won't wait for it.\n");

    // 3. Main continues its own work
    printf("[MAIN] Main is doing other things...\n");
    
    // We sleep here just so the program doesn't exit before the detached thread prints
    sleep(5); 

    printf("[MAIN] Main exiting.\n");
    return 0;
}