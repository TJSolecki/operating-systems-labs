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
    long mtype;           /* Message type. */
    char mtext[MSG_SIZE]; /* Message text. */
};

int main(int argc, char *argv[]) {
    key_t key = 10;
    struct info message;

    // Create a shared memory segment
    int id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (id == -1) {
        printf("ERROR: failed to create message queue. Operation failed "
               "with error code %d\n",
               errno);
        exit(1);
    }

    // Attach the shared memory segment
    char *shmaddr = shmat(id, NULL, 0);
    if (shmaddr == (char *)-1) {
        printf("ERROR: There was an issue attaching to the shared memory "
               "segment\n");
        exit(1);
    }

    // Create a message queue
    int msq_id = msgget(key, IPC_CREAT | 0644);

    if (fork() != 0) {
        printf("This is the producer process for the message queue\n\n");

        printf("Provide a message to send to the consumer:\n");
        fgets(message.mtext, MSG_SIZE, stdin);
        message.mtype = 1;

        if (msgsnd(msq_id, &message, sizeof(message), 0) == -1) {
            printf("ERROR: could not send message\n");
            exit(1);
        }

        printf("Writing to shared memory: %s\n", message.mtext);
        strncpy(shmaddr, message.mtext, SHM_SIZE);
        exit(0);
    } else {
        int running = 1;
        while (running) {
            if (msgrcv(msq_id, &message, sizeof(message), 1, 0) == -1) {
                printf("ERROR: issue recieving message from message queue\n");
                exit(1);
            }

            // Check to see if a message has been recieved
            if (strcmp(message.mtext, "") != 0) {
                printf("\nConsumer child process\n");
                printf("Recived downstream: %s", message.mtext);
                running = 0;
                continue;
            }
            exit(0);
        }
    }
    return 0;
}
