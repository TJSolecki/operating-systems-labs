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

#define N 5

int in = 0, out = 0;
int buffer[N];
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

        // signal mutex
        sem_post(mutex);

        // signal full
        sem_post(full);

        printf("Produced item: %d\n", item);
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

int main() {
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, N);
    full = sem_open("full", O_CREAT, 0644, 0);

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
    return 0;
}
