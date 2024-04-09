// Name: Thomas Solecki
// Date: 4/9/2024
// Title: Lab2 – Step 5
// Description: This program spawns 4 processes with differing delays in a loop
// which prints to standard out 10 times. The user can specifiy the delay for
// each process via a command line argument.
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

pid_t fork_and_loop(int delay, int process_number);

/* main function */
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr,
                "usage: %s <delay_in_ms_process_1> <delay_in_ms_process_2> "
                "<delay_in_ms_process_3> <delay_in_ms_process_4>\n",
                argv[0]);
        exit(1);
    }
    pid_t pid_2, pid_3, pid_4;
    // delay microseconds is taken as command-line argument for each process int
    int p1_delay = atoi(argv[1]);
    int p2_delay = atoi(argv[2]);
    int p3_delay = atoi(argv[3]);
    int p4_delay = atoi(argv[4]);
    int i;
    // child iterations
    printf("\n Before forking.\n");
    pid_2 = fork_and_loop(p2_delay, 2);
    pid_3 = fork_and_loop(p3_delay, 3);
    pid_4 = fork_and_loop(p4_delay, 4);
    for (i = 0; i < 10; i++) {
        printf("I am the parent Process (process 1) displaying "
               "iteration %d \n",
               i);
        usleep(p1_delay);
    }
    wait(&pid_2);
    wait(&pid_3);
    wait(&pid_4);
    return 0;
}

pid_t fork_and_loop(int delay, int process_number) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid == 0) {
        for (int i = 0; i < 10; i++) {
            printf("I am process %d displaying iteration %d\n", process_number,
                   i);
            usleep(delay);
        }
        exit(0);
    }
    return pid;
}
