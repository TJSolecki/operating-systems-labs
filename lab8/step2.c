// Name: Thomas Solecki
// Date: 5/28/2024
// Title: Lab8 – Step 2
// Description: This program reads the provided file

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <src_filename>\n", argv[0]);
        exit(1);
    }
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while (fread(buffer, sizeof(buffer), 1, fp)) {
    }
    fclose(fp);
    return 0;
}
