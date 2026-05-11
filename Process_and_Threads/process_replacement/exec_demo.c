#include <stdio.h>
#include <unistd.h>

int main() {
    printf("The process is executing a new program using exec! PID: %d\n", getpid());
    execl("/bin/ls", "ls", "-l", NULL); // Replace the current process with the "ls -l" command 

    printf("After exec, this line will not be printed if exec is successful.\n");
    return 0;
}