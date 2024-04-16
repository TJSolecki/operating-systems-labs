// Name: Thomas Solecki
// Date: 4/16/2024
// Title: Lab3 – Step 1
// Description: This program demonstrates the usage of pipe with unix processes

/*
 * Observations:
 * When I run the program in a small terminal window I get a scrollable view of
 * the outputs of "ls -l" for my current working directory. But when the
 * terminal window can comfortably fit the entinre output, the output is normal
 * and does not show "more" at the bottom of the terminal.
 */

#include <sys/wait.h>
#include <unistd.h>

// main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0);
    }
    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", "-l", 0);
    } else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
