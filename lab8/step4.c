// Name: Thomas Solecki
// Date: 5/28/2024
// Title: Lab8 – Step 4
// Description: This program creates a copy of the provided file with a
// specified buffer size

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    char buffer[atoi(argv[2])];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    // append .copy to the src filename to be used for the dst filename
    strcat(argv[1], ".copy");
    // opens a file for writing; erases old file/creates a new file
    FILE *dst = fopen(argv[1], "w");

    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(buffer), 1, fp)) > 0) {
        fwrite(buffer, sizeof(buffer), bytes_read, dst);
    }

    fclose(fp);
    fclose(dst);
    return 0;
}
