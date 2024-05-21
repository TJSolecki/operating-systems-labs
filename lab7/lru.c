// Name: Thomas Solecki
// Date: 5/21/2024
// Title: Lab7 – Step 3
// Description: This program simulates the efficiency of the LRU page
// replacement algorithm

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define True 1
#define False 0
#define bool int

typedef struct { // to
    int pageno;
    int last_used;
} ref_page;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <cache_size>", argv[1]);
        exit(1);
    }
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[C_SIZE];     // Cache that stores pages
    char pageCache[100];        // Cache that holds the input from test file

    int i;
    int counter = 0;
    int totalFaults = 0; // keeps track of the total page faults

    for (i = 0; i < C_SIZE; i++) { // initialise cache array
        cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)) {
        int page_num =
            atoi(pageCache); // Stores number read from file as an int

        bool foundInCache = False;
        for (i = 0; i < C_SIZE; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = True;
                cache[i].last_used = counter;
                break; // break out loop because found page_num in cache
            }
        }
        if (foundInCache == False) {
            totalFaults++;
            bool inserted = False;
            for (i = 0; i < C_SIZE; i++) {
                if (cache[i].pageno == -1) {
                    cache[i].pageno = page_num;
                    cache[i].last_used = counter;
                    inserted = True;
                    break;
                }
            }
            if (inserted == False) {
                int least_recently_used_count = INT_MAX;
                int index_to_remove = 0;

                for (i = 0; i < C_SIZE; i++) {
                    if (cache[i].last_used < least_recently_used_count) {
                        index_to_remove = i;
                        least_recently_used_count = cache[i].last_used;
                    }
                }
                cache[index_to_remove].pageno = page_num;
                cache[index_to_remove].last_used = counter;
            }
            printf("%d\n", page_num);
        }
        counter++;
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}
