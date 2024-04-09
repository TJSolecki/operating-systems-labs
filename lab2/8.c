// Name: Thomas Solecki
// Date: 4/9/2024
// Title: Lab2 – Step 8
// Description: This program spawns 2 threads which iterate 10 times each and
// print to standard out on each iteration.
#include <pthread.h>
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */

struct ThreadData {
    int n;
    int thread_number;
};

void *thread(void *arg) {
    struct ThreadData data = *(struct ThreadData *)arg;
    int i;
    for (i = 0; i < 10; i++) {
        printf("I am the child thread %d displaying iteration %d\n",
               data.thread_number, i);
        usleep(data.n);
    }
    return NULL;
}
/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc != 2) {
        fprintf(stderr, "usage: %s <delay_in_ms>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]); // n microseconds is taken as command-line argument
    int i;
    pthread_t tid1, tid2;
    int return_value;
    struct ThreadData data1, data2;
    data1.n = n;
    data1.thread_number = 1;
    data2.n = n;
    data2.thread_number = 2;
    // Create thread 1
    return_value = pthread_create(&tid1, NULL, thread, &data1);
    if (return_value != 0) {
        fprintf(stderr, "pthread_create failed with error code %d\n",
                return_value);
        exit(1);
    }
    // Create thread 2
    return_value = pthread_create(&tid2, NULL, thread, &data2);
    if (return_value != 0) {
        fprintf(stderr, "pthread_create failed with error code %d\n",
                return_value);
        exit(1);
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
