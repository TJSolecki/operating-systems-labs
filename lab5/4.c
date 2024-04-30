// Name: Thomas Solecki
// Date: 4/30/2024
// Title: Lab5 – Step 4
// Description: This program demonstrates how to use mutex locks and conditional
// variables to syncronize a producer and consumer thread that use a shared
// buffer

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int N;
int in = 0, out = 0;
int *buffer;
pthread_mutex_t mutex;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER,
               full = PTHREAD_COND_INITIALIZER;
pthread_t producer_thread_id, consumer_thread_id;

void *producer() {
    for (int i = 0; i < 10; i++) {
        // produce next item
        int item = i;

        // wait for an empty buffer
        pthread_mutex_lock(&mutex);
        while ((in + 1) % N == out) {
            pthread_cond_wait(&empty, &mutex);
        }

        // add item to buffer
        buffer[in] = item;
        in = (in + 1) % N;
        printf("Produced item: %d\n", item);

        // signal full
        pthread_cond_signal(&full);

        // unlock mutex
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
    return NULL;
}

void *consumer() {
    for (int i = 0; i < 10; i++) {
        // wait for a full buffer
        pthread_mutex_lock(&mutex);
        while (in == out) {
            pthread_cond_wait(&full, &mutex);
        }

        // remove item from buffer
        int item = buffer[out];
        out = (out + 1) % N;

        // signal empty
        pthread_cond_signal(&empty);

        // unlock mutex
        pthread_mutex_unlock(&mutex);

        // consume item
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

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Could not create mutex");
        exit(1);
    }

    pthread_create(&producer_thread_id, NULL, producer, NULL);
    pthread_create(&consumer_thread_id, NULL, consumer, NULL);

    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);

    free(buffer);

    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("Could not destroy mutex");
        exit(1);
    }
    return 0;
}
