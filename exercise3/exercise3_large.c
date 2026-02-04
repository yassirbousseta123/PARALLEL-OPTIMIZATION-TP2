#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Use larger N for Valgrind profiling (still within memory limits)
#define N 50000000

double a[N], b[N], c[N];

// SEQUENTIAL - each element depends on previous
void add_noise() {
    a[0] = 1.0;
    for (int i = 1; i < N; i++) {
        a[i] = a[i-1] * 1.0000001;
    }
}

// PARALLEL - no dependencies
void init_b() {
    for (int i = 0; i < N; i++) {
        b[i] = 2.0;
    }
}

// PARALLEL - no dependencies
void compute_addition() {
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
}

// PARALLEL - reduction pattern
double reduction() {
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += c[i];
    }
    return sum;
}

int main() {
    add_noise();
    init_b();
    compute_addition();
    double result = reduction();
    printf("Result: %f\n", result);
    return 0;
}
