// Name: Thomas Solecki
// Date: 5/21/2024
// Title: Lab7 – Step 2
// Description: This program generates a test input for the page replacement
// algorithm tests

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_page_nums> <max_page_num>", argv[0]);
        exit(1);
    }
    int num_page_nums = atoi(argv[1]);
    int max_page_num = atoi(argv[2]) + 1;
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i = 0; i < num_page_nums; i++) {
        sprintf(buffer, "%d\n", rand() % max_page_num);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}
