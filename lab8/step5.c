// Name: Thomas Solecki
// Date: 5/28/2024
// Title: Lab8 – Step 5
// Description: This program creates a <num_threads> copies of the provided file
// with a specified buffer size in parrallel using multi-threading

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *copy_file(void *args);

char src_filename[256];
char dst_filename[256];
int buffer_size;

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <buffer_size> <num_threads>\n",
                argv[0]);
        exit(1);
    }

    // Set global variables needed by each thread
    buffer_size = atoi(argv[2]);
    strncpy(src_filename, argv[1], sizeof(src_filename) - 1);
    strncpy(dst_filename, argv[1], sizeof(dst_filename) - 1);
    strcat(dst_filename, ".copy");

    // Create <num_thread> threads which each create a separate copy of the
    // source file
    int i;
    int num_threads = atoi(argv[3]);
    pthread_t threads[num_threads];

    for (i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, copy_file, (void *)(size_t)i);
    }

    // Wait for all threads to terminate before exiting the program
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void *copy_file(void *arg) {
    // Initialize buffer
    char buffer[buffer_size];
    memset(buffer, 0, sizeof(buffer));

    // Add the thread number to the end of the destination filename
    char thread_dst_filename[256];
    strcpy(thread_dst_filename, dst_filename);
    int thread_num = (int)(unsigned long)arg;
    char thread_num_str[32];
    sprintf(thread_num_str, "%d", thread_num);
    strcat(thread_dst_filename, thread_num_str);

    // opens a file for writing; erases old file/creates a new file
    FILE *dst = fopen(thread_dst_filename, "w");
    if (dst == NULL) {
        perror("Error opening destination file");
        pthread_exit(NULL);
    }
    // opens provided source file for reading
    FILE *fp = fopen(src_filename, "rb");
    if (fp == NULL) {
        perror("Error opening source file");
        fclose(dst);
        pthread_exit(NULL);
    }

    // copy the file
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, buffer_size, fp)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }

    // close file handlers
    fclose(fp);
    fclose(dst);

    // exit
    pthread_exit(NULL);
}
