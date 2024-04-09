// Name: Thomas Solecki
// Date: 4/9/2024
// Title: Lab2 – Step 1
// Description: This program demonstrates the use of fork()

/*
 * Observations:
 * I observed that the two processes, the child and the parent, executed
 * concurrently. I saw that just about every line printed to the console
 * alternated between being from the parent and child process. However, there
 * was one point in execution where the child printed two lines in a row and so
 * did the parent.
 *
 */
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
/* main function */
int main() {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and
                     // child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid) {
        // Parent process: pid is > 0
        for (i = 0; i < 10; i++) {
            printf(
                "\t \t \t I am the parent Process displaying iteration %d \n",
                i);
            usleep(n);
        }
    } else {
        // Child process: pid = 0
        for (i = 0; i < 10; i++) {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n);
        }
    }
    return 0;
}
