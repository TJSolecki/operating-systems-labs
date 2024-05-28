// Name: Thomas Solecki
// Date: 5/28/2024
// Title: Lab8 – Step 3
// Description: This program reads the provided file with a specified buffer
// size

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <src_filename> <buffer_size>\n", argv[0]);
        exit(1);
    }

    char buffer[atoi(argv[2])];
    FILE *fp;
    fp = fopen(argv[1], "rb");

    while (fread(buffer, sizeof(buffer), 1, fp)) {
    }

    fclose(fp);
    return 0;
}
