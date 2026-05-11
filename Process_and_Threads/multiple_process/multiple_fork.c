#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    

    if (pid1 < 0 || pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (pid1 == 0 && pid2 == 0) {
        // Both processes
        printf("Hello from both processes! PID: %d\n", getpid());
    } else if (pid1 == 0) {
        // Child process 1
        printf("Hello from child process 1! PID: %d\n", getpid());
    } else if (pid2 == 0) {
        // Child process 2
        printf("Hello from child process 2! PID: %d\n", getpid());
    } else {
        // Parent process
        printf("Hello from parent process! PID: %d\n", getpid());
    }

    return 0;
}