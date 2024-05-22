// Name: Thomas Solecki
// Date: 5/21/2024
// Title: Lab7 – Step 3
// Description: This program simulates the efficiency of the second chance page
// replacement algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define True 1
#define False 0
#define bool int

typedef struct { // to
    int pageno;
    u_short ref;
} ref_page;

int replace_and_update(int page_num, ref_page *cache, int cache_size,
                       int pointer) {
    while (True) {
        if (cache[pointer].ref == 0) {
            cache[pointer].pageno = page_num;
            return (pointer + 1) % cache_size;
        }
        cache[pointer].ref = 0;
        pointer = (pointer + 1) % cache_size;
    }
}

bool find_and_update(int page_num, ref_page *cache, int cache_size) {
    for (int i = 0; i < cache_size; i++) {
        if (cache[i].pageno == page_num) {
            cache[i].ref = 1;
            return True;
        }
    }
    return False;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <cache_size>", argv[1]);
        exit(1);
    }
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[C_SIZE];     // Cache that stores pages
    char pageCache[100];        // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;

    for (i = 0; i < C_SIZE; i++) { // initialise cache array
        cache[i].pageno = -1;
        cache[i].ref = 0;
    }

    while (fgets(pageCache, 100, stdin)) {
        int page_num =
            atoi(pageCache); // Stores number read from file as an int
        if (find_and_update(page_num, cache, C_SIZE) == False) {
            placeInArray =
                replace_and_update(page_num, cache, C_SIZE, placeInArray);
            printf("%d\n", page_num);
            totalFaults++;
        }
    }

    return 0;
}
