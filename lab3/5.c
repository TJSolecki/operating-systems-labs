// Date: 4/16/2024
// Name: Thomas Solecki
// Title: Lab3 – Step 5
// Description: This program demonstrates using pipe to implement
// producer-consumer communication between processes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSG_SIZE 256

int main(int argc, char *argv[]) {
    int fds[2];
    char buff[MSG_SIZE];
    int count;
    int i;
    pipe(fds);
    if (fork() == 0) {
        printf("Producer on the upstream end of the pipe\n");
        close(fds[0]);
        fgets(buff, MSG_SIZE, stdin);
        write(fds[1], buff, strlen(buff));
        exit(0);
    } else if (fork() == 0) {
        close(fds[1]);
        if (read(fds[0], buff, MSG_SIZE) > 0) {
            printf("\nReader on the downstream end of the pipe \n");
            printf("%s\n", buff);
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
