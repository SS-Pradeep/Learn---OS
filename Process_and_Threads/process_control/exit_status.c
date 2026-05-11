#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();

    if(pid < 0){
        perror("Fork failed");
        return 1;
    } else if(pid == 0) {
        printf("Child is exiting with status 42! PID: %d\n", getpid());
        exit(42);
    } else {
        int status;
        wait(&status); // Wait for the child process to finish

        if(WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child exited with status: %d\n", exit_status);
        } else {
            printf("Child did not exit normally.\n");
        }
    }
    return 0;
}