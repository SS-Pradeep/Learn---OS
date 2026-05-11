#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void create_tree(int levels) {
    if(levels <= 0) {
        return;
    }

    pid_t pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return;
    }

    else if (pid == 0) {
        // This is the child process
        printf("Hello from the child process! PID: %d, Level: %d\n", getpid(), levels);
        create_tree(levels - 1);
    }

    else {
        // This is the parent process
        wait(NULL); // Wait for the child process to finish
    }
}

int main() {
    int levels = 3;

    create_tree(levels);
    return 0;
}