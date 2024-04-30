// Name: Thomas Solecki
// Date: 4/30/2024
// Title: Lab5 – Step 2
// Description: This program demonstrates how to use mutex locks to syncronize
// threads

// Thread Synchronization - Mutex Locks
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 10
#define SIGINT 2

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main() {
    signal(SIGINT, cleanup);
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Could not create mutex");
        exit(1);
    }
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);
    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("Could not destroy mutex");
        exit(1);
    }
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n", (int)(unsigned long)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",
           (int)(unsigned long)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void cleanup(int sigtype) {
    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("Could not destroy mutex");
        exit(1);
    }
    printf("\n Terminating\n");
    exit(0);
}
