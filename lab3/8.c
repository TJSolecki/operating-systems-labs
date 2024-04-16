// Date: 4/16/2024
// Name: Thomas Solecki
// Title: Lab3 – Step 8
// Description: This program demonstrates how to address the issue of shared
// memory by threads in the last step by creating copies

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *go(void *);

#define NTHREADS 10

pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&threads[i], NULL, go, arg);
    }
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
