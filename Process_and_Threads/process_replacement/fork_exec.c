#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        peeror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process is executing a new program using exec! PID: %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL); // Replace the
        printf("After exec, this line will not be printed if exec is successful.\n");
        return 0;
    } else {
        printf("Parent process is waiting for child to finish... Parent PID: %d, Child PID: %d\n", getpid(), pid);
        wait(NULL); // Wait for the child process to finish
        printf("Child process has finished! Parent PID: %d\n", getpid());
        return 0;
    }
    return 0;
}