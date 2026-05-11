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
        sleep(20); // Simulate some work in the child process
        printf("Child process is exiting! PID: %d\n", getpid()); // Child process is still running, but parent has terminated, so it becomes an orphan
    } else {

        printf("Parent is terminated! Parent PID: %d, Child PID: %d\n", getpid(), pid);
        // Parent process is terminated immediately, child becomes an orphan
    }
    return 0;
}