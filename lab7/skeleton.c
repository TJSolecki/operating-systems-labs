// Name: Thomas Solecki
// Date: 5/21/2024
// Title: Lab7 – Step 3
// Description: This program iteratively pipes the page numbers from
// testInput.txt to standard out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct { // to
    int pageno;
} ref_page;

int main(int argc, char *argv[]) {
    char pageCache[100]; // Cache that holds the input from test file

    int i;

    while (fgets(pageCache, 100, stdin)) {
        int page_num =
            atoi(pageCache); // Stores number read from file as an int
        printf("%d\n", page_num);
    }

    return 0;
}
