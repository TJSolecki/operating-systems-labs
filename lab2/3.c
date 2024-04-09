// Name: Thomas Solecki
// Date: 4/9/2024
// Title: Lab2 – Step 3
// Description: This program spawns processes with differing delays in a loop
// which prints to standard out 10 times. The user can specifiy the delay via a
// command line argument
/*
 * Step 4: What happens when you change the delay to 500 and 5000?
 * When changing the delay to 500 the program executes slighly faster and when
 * changed to 5000 executes slightly slower. I noticed that both outputs looked
 * the same and that most print statements would alternaate between child and
 * parent but would have one or two instances of the same process printing twice
 * in a row.
 */
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait */
#include <unistd.h>    /* fork */
/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc != 2) {
        fprintf(stderr, "usage: %s <delay_in_ms>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]); // n microseconds is taken as command-line argument
    int i;
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
    wait(&pid);
    return 0;
}
