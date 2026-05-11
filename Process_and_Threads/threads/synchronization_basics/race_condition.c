#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter = 0;
// This function will be run by both threads and will increment the shared counter
void* increment_counter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        shared_counter++; // This is the race condition
    }
    return NULL;
    // Note: In a real application, you would want to use mutexes or other synchronization mechanisms to protect access to shared resources like this counter.
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", shared_counter);
    return 0;
}