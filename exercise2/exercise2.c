#include <stdio.h>
#include <time.h>

#define N 100000000

int main() {
    double a = 1.5, b = 2.5;
    double x = 0.0, y = 0.0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < N; i++) {
        x = a * b + x;  // stream 1
        y = a * b + y;  // independent stream 2
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time: %.6f seconds\n", time);
    printf("x = %f, y = %f\n", x, y);  // Prevent optimization

    return 0;
}
