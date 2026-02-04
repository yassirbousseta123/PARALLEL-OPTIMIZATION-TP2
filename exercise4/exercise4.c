#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 512  // Matrix size (N x N)

double A[N][N], B[N][N], C[N][N];
double noise[N];

// SEQUENTIAL - each element depends on previous (O(N))
void generate_noise() {
    noise[0] = 1.0;
    for (int i = 1; i < N; i++) {
        noise[i] = noise[i-1] * 1.0000001;
    }
}

// PARALLEL - no dependencies (O(N^2))
void init_matrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = noise[i % N] + i + j;
            B[i][j] = noise[j % N] + i - j;
        }
    }
}

// PARALLEL - no dependencies (O(N^3))
void matmul() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    generate_noise();
    init_matrix();
    matmul();

    // Prevent optimization
    double sum = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += C[i][j];
    printf("Result: %f\n", sum);

    return 0;
}
