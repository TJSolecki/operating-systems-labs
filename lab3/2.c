// Name: Thomas Solecki
// Date: 4/16/2024
// Title: Lab3 – Step 1
// Description: This program demonstrates the usage of pipe with user provided
// input
/*
 * Observations:
 * When I run the program and provide arguments the program first prints the
 * number of arguments I passed. Then the program loops through each character
 * used in the arguments and prints them to standard out separated by spaces
 * with a maximum of 61 characters on each line (not including spaces). I also
 * noticed that argv[0], the program name, is also included in this output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork() == 0) {
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",
               argc);
        close(fds[0]);
        for (i = 0; i < argc; i++) {
            write(fds[1], argv[i], strlen(argv[i]));
        }
        exit(0);
    } else if (fork() == 0) {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while ((count = read(fds[0], buff, 60)) > 0) {
            for (i = 0; i < count; i++) {
                write(1, buff + i, 1);
                write(1, " ", 1);
            }
            printf("\n");
        }
        exit(0);
    } else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
