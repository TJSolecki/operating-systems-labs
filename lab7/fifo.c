// Name: Thomas Solecki
// Date: 5/21/2024
// Title: Lab7 – Step 3
// Description: This program simulates the efficiency of the FIFO page
// replacement algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define True 1
#define False 0
#define bool int

typedef struct { // to
    int pageno;
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
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;

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
                break; // break out loop because found page_num in cache
            }
        }
        if (foundInCache == False) {
            // You may print the page that caused the page fault
            printf("%d\n", page_num);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}
