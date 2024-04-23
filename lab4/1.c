// Name: Thomas Solecki
// Date: 4/23/2024
// Title: Lab4 – Step 1
// Description: This program demonstrates the usage pthread and serves as an
// example of pre-tread variables vs shared-memory variables
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Observations:
 * Step 1:
 * When I run the program I notice that a different number of threads actually
 * run each time, most often 19 or 20. This is because the main thread does not
 * wait for the threads to complete running so the program can exit before some
 * of the threads can start processing. None of the threads "complete" per say
 * since each thread has a 15 second call to sleep, but the program finishes
 * executing in under a second.
 *
 * Step 2:
 * The parameter arg in the go function is a per-thread variable. Each thread
 * recives a copy of i arg. The compiler stores the value of arg on the stack
 * of each thread.
 *
 * Step 3:
 * The variable i in the main function is a per-thread variable. The variable
 * that is created is stored on the stack of the main therad but is copied to
 * other threads on each iteration in the call to pthread.
 *
 */

void *go(void *);

#define NTHREADS 20

pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",
           (int)(unsigned long)pthread_self(),
           (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}
