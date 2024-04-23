// Name: Thomas Solecki
// Date: 4/23/2024
// Title: Lab4 – Step 4
// Description: This program computes matrix multiplication for two random
// matrixes of sizes defined by the user. The computation is done using a thread
// to compute each individual cell of the resulting matrix
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int N, M, L;
// initialize matrix with random values
void initializeMatrix(int r, int c, double ***matrix);

void printMatrix(int r, int c, double **matrix); // print matrix

void *multiplyCell(void *arg); // thread multiply function
                               // creating N threads, each multiplying ith row
                               // of matrixA by each column of matrixB to
                               // produce the row of matrixC
// A, B, C matrices
double **matrixA, **matrixB, **matrixC;

int main(int argc, char *argv[]) { // read N, M, and L as command-line arguments
    if (argc != 4) {
        fprintf(stderr, "usage: %s <N> <M> <L>\n", argv[0]);
        exit(1);
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);

    pthread_t *threads = malloc(N * L * sizeof(pthread_t));

    initializeMatrix(N, M, &matrixA);
    initializeMatrix(M, L, &matrixB);
    initializeMatrix(N, L, &matrixC);

    printMatrix(N, M, matrixA);
    puts("");
    printMatrix(M, L, matrixB);
    puts("");

    int i;
    for (i = 0; i < N * L; i++) {
        pthread_create(&threads[i], NULL, multiplyCell, (void *)(size_t)i);
    }

    for (i = 0; i < N * L; i++) {
        pthread_join(threads[i], NULL);
    }

    printMatrix(N, L, matrixC);

    free(threads);
    for (i = N - 1; i >= 0; i--) {
        free(matrixC[i]);
    }
    free(matrixC);

    // Free memory for matrixA
    for (i = 0; i < N; i++) {
        free(matrixA[i]);
    }
    free(matrixA);

    // Free memory for matrixB
    for (i = 0; i < M; i++) {
        free(matrixB[i]);
    }
    free(matrixB);

    return 0;
}

void initializeMatrix(int r, int c, double ***matrix) {
    *matrix = malloc(r * sizeof(double *));
    if (*matrix == NULL) {
        printf("ERROR: Could not allocate memory for matrix\n");
        exit(1);
    }

    for (int i = 0; i < r; i++) {
        (*matrix)[i] = malloc(c * sizeof(double));
        if ((*matrix)[i] == NULL) {
            printf("ERROR: Could not allocate memory for row %d of matrix\n",
                   i);
            exit(1);
        }
    }

    srand(time(NULL));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            (*matrix)[i][j] = rand() % 4;
        }
    }
}

void *multiplyCell(void *arg) {
    int i = (int)(unsigned long)(size_t *)arg;
    int r = i / N;
    int c = i % L;
    double temp = 0.0;
    for (int k = 0; k < M; k++) {
        temp += matrixA[r][k] * matrixB[k][c];
    }
    matrixC[r][c] = temp;
    pthread_exit(NULL);
}

void printMatrix(int r, int c, double **matrix) {
    int i, j;
    for (i = 0; i < r; i++) {
        printf("[ ");
        for (j = 0; j < c; j++) {
            printf("%.1f ", matrix[i][j]);
        }
        puts("]");
    }
}
