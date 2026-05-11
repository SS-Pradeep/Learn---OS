#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process is running! PID: %d\n", getpid());
        sleep(2); // Simulate some work in the child process
        printf("Child process is exiting! PID: %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process is running! PID: %d, Child PID: %d\n", getpid(), pid);
        wait(NULL); // Wait for the child process to finish
        printf("Parent is resuming after child process has finished! PID: %d\n", getpid());
    }

    return 0;
}