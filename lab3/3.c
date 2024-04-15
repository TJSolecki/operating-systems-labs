#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork() == 0) {
        dup2(fds[1], 0);
        close(fds[0]);
        execlp("ls", "ls", 0);
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
