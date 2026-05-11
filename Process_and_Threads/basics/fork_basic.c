#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello from the child process! PID: %d\n", getpid());
    } else {
        // Parent process
        printf("Hello from the parent process! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}