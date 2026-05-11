#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if(pid == 0) {
        printf("Hello from the child process! PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(2); // Simulate some work in the child process
    }
    else {
        printf("Parent waiting for child process to finish... Parent PID: %d, Child PID: %d\n", getpid(), pid);
        waitpid(pid, NULL, 0); // Wait for the child process to finish
        printf("Child process has finished! Parent PID: %d\n", getpid());
    }

    return 0;
}