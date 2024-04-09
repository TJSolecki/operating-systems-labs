// Name: Thomas Solecki
// Date: 4/9/2024
// Title: Lab2 – Step 7
// Description: This program spawns a child process which executes ls. The
// parent process waits for the child process to exit before terminating.
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>
#include <unistd.h> /* fork */
/* main function */
int main() {
    pid_t pid;
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid) {
        wait(0);
        printf("Child has completed the task! \n");
        exit(0);
    } else {
        execlp("/bin/ls", "ls", 0);
    }
    return 0;
}
