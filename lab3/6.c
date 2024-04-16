// Date: 4/16/2024
// Name: Thomas Solecki
// Title: Lab3 – Step 6
// Description: This program demonstrates using shared memory
// producer-consumer communication between processes

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define MSG_SIZE 256

struct info {
    int written;          /* Flag indicating if the message has been written*/
    char mtext[MSG_SIZE]; /* Message text. */
};

int main(int argc, char *argv[]) {
    key_t key = 10;

    // Create a shared memory segment
    int id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (id == -1) {
        printf("ERROR: failed to create message queue. Operation failed "
               "with error code %d\n",
               errno);
        exit(1);
    }

    // Attach the shared memory segment
    struct info *shmaddr = (struct info *)shmat(id, NULL, 0);
    if (shmaddr == (void *)-1) {
        printf("ERROR: There was an issue attaching to the shared memory "
               "segment\n");
        exit(1);
    }

    shmaddr->written = 0;

    if (fork() != 0) {
        while (1) {
            // Check if the message has been written
            if (shmaddr->written) {
                printf("Consumed message: %s", shmaddr->mtext);

                break;
            }
        }
    } else {
        printf("This is the producer process for the message queue\n\n");

        printf("Provide a message to send to the consumer:\n");
        fgets(shmaddr->mtext, MSG_SIZE, stdin);
        printf("Writing to shared memory: %s\n", shmaddr->mtext);
        shmaddr->written = 1;

        exit(0);
    }
    shmdt(shmaddr);
    return 0;
}
