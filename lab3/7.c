// Date: 4/16/2024
// Name: Thomas Solecki
// Title: Lab3 – Step 7
// Description: This program demonstrates the issue of using shared memory in
// threads
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Observations:
 * 10 Threads are created and values of i that are passed change on each
 * execution due to a race condition. Becuase the threads are passed a reference
 * to i and not the value of i itself, each thread prints the iteration number
 * that the main thread is currently and not always the iteration it is created
 * on due to the fact that threads share memory with the main process.
 *
 */

void *go(void *);

#define NTHREADS 10

pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",
           (int)(unsigned long)pthread_self(), *(int *)arg);
    return 0;
}
