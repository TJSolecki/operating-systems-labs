// Name: Thomas Solecki
// Date: 4/30/2024
// Title: Lab5 – Step 3
// Description: This program demonstrates how to use semaphores to syncronize a
// producer and consumer thread that use a shared buffer

// Shared data: semaphores called full, empty, and mutex
// pool of n buffers, each can hold one item
// mutex semaphore provides mutual exclusion to the buffer pool
// empty and full semaphores count the number of empty and full buffers
// Initially: full = 0, empty = n, mutex = 1
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int N;
int in = 0, out = 0;
int *buffer;
sem_t *mutex, *empty, *full;
pthread_t producer_thread_id, consumer_thread_id;

void *producer() {
    for (int i = 0; i < 10; i++) {
        // produce next item
        int item = i;

        // wait for an empty buffer
        sem_wait(empty);

        // wait for mutex
        sem_wait(mutex);

        // add item to buffer
        buffer[in] = item;
        in = (in + 1) % N;
        printf("Produced item: %d\n", item);

        // signal mutex
        sem_post(mutex);

        // signal full
        sem_post(full);
    }
    pthread_exit(NULL);
    return NULL;
}

void *consumer() {
    for (int i = 0; i < 10; i++) {
        // wait for the buffer to be populated
        sem_wait(full);

        // wait for mutex
        sem_wait(mutex);

        // remove item from buffer
        int item = buffer[out];
        out = (out + 1) % N;

        // signal mutex
        sem_post(mutex);

        // signal empty
        sem_post(empty);

        // consume the item
        printf("Consumed item: %d\n", item);
    }
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <N>\n", argv[0]);
        exit(1);
    }

    N = atoi(argv[1]);
    buffer = malloc(sizeof(int) * N);

    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    if (mutex == SEM_FAILED) {
        sem_unlink("mutex");
        mutex = sem_open("mutex", O_CREAT, 0644, 1);
    }

    empty = sem_open("empty", O_CREAT, 0644, N);
    if (empty == SEM_FAILED) {
        sem_unlink("empty");
        empty = sem_open("empty", O_CREAT, 0644, 1);
    }

    full = sem_open("full", O_CREAT, 0644, 0);
    if (full == SEM_FAILED) {
        sem_unlink("full");
        full = sem_open("full", O_CREAT, 0644, 1);
    }

    pthread_create(&producer_thread_id, NULL, producer, NULL);
    pthread_create(&consumer_thread_id, NULL, consumer, NULL);

    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);

    sem_unlink("mutex");
    sem_close(mutex);

    sem_unlink("empty");
    sem_close(empty);

    sem_unlink("full");
    sem_close(full);

    free(buffer);
    return 0;
}
