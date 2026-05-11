#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;
p_thread_mutex_t mutexLock;

void* increment(void* arg) {
    for(int i=0;i<100000;i++) {
        mutex_lock(&mutexLock); // Lock the mutex before modifying the counter
        counter++;
        mutex_unlock(&mutexLock); // Unlock the mutex after modifying the counter
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutexLock, NULL); // Initialize the mutex

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);
    pthread_mutex_destroy(&mutexLock); // Destroy the mutex
    return 0;
}