// Date: 4/16/2024
// Name: Thomas Solecki
// Title: Lab3 – Step 4
// Description: This program demonstrates piping the output from one unix
// program into another
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("grep", "grep", "root", 0);
    }
    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("cat", "cat", "/etc/passwd", 0);
    } else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
