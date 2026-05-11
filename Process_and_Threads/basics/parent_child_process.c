#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    else if(pid == 0) {
        // This is the child process
        printf("Hello from the child process! PID: %d\n", getpid());
        printf("Child's parent PID: %d\n", getppid());
    }

    else {
        // This is the parent process
        printf("Hello from the parent process! PID: %d, Child PID: %d\n", getpid(), pid);
    }
}