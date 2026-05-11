#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } 

    if (pid == 0) {
        fork();
        printf("Hello from the child process! PID: %d\n", getpid());
    }

    printf("Hello from the parent process! PID: %d\n", getpid());

    return 0;
}