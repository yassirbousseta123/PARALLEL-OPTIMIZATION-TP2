#include <stdio.h>
#include <time.h>

#define N 100000000

int main() {
    double a = 1.5, b = 2.5;

    // Manual optimization 1: Precompute a*b outside the loop
    double ab = a * b;  // Constant folding - computed once

    // Manual optimization 2: Multiple accumulators for ILP
    double x1 = 0.0, x2 = 0.0, x3 = 0.0, x4 = 0.0;
    double y1 = 0.0, y2 = 0.0, y3 = 0.0, y4 = 0.0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Manual optimization 3: Loop unrolling by factor of 4
    for (int i = 0; i < N; i += 4) {
        // Stream 1: 4 independent accumulations
        x1 = x1 + ab;
        x2 = x2 + ab;
        x3 = x3 + ab;
        x4 = x4 + ab;

        // Stream 2: 4 independent accumulations
        y1 = y1 + ab;
        y2 = y2 + ab;
        y3 = y3 + ab;
        y4 = y4 + ab;
    }

    // Combine accumulators
    double x = x1 + x2 + x3 + x4;
    double y = y1 + y2 + y3 + y4;

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time: %.6f seconds\n", time);
    printf("x = %f, y = %f\n", x, y);  // Prevent optimization

    return 0;
}
