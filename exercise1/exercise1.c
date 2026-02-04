/*
 * Exercise 1: Loop Unrolling Optimization Analysis
 *
 * This program benchmarks the impact of loop unrolling on array summation
 * performance using double precision floating point numbers.
 *
 * Author: TP2 Parallel Computing
 * Date: 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

// Configuration
#define N 1000000           // Array size
#define NUM_ITERATIONS 100  // Number of timing iterations
#define WARMUP_ITERATIONS 10 // Warmup iterations

// High-resolution timing functions
#ifdef __APPLE__
static mach_timebase_info_data_t timebase_info;

static void init_timing(void) {
    mach_timebase_info(&timebase_info);
}

static double get_time_ns(void) {
    uint64_t time = mach_absolute_time();
    return (double)time * timebase_info.numer / timebase_info.denom;
}
#else
static void init_timing(void) {}

static double get_time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}
#endif

// Prevent compiler from optimizing away the result
static volatile double sink;

// ============================================================================
// Summation functions with different unrolling factors
// ============================================================================

// U = 1 (no unrolling - baseline)
__attribute__((noinline))
double sum_unroll_1(const double *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// U = 2
__attribute__((noinline))
double sum_unroll_2(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 1; i += 2) {
        sum += a[i];
        sum += a[i + 1];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// U = 4
__attribute__((noinline))
double sum_unroll_4(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// U = 8
__attribute__((noinline))
double sum_unroll_8(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
        sum += a[i + 4];
        sum += a[i + 5];
        sum += a[i + 6];
        sum += a[i + 7];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// U = 16
__attribute__((noinline))
double sum_unroll_16(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 15; i += 16) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
        sum += a[i + 4];
        sum += a[i + 5];
        sum += a[i + 6];
        sum += a[i + 7];
        sum += a[i + 8];
        sum += a[i + 9];
        sum += a[i + 10];
        sum += a[i + 11];
        sum += a[i + 12];
        sum += a[i + 13];
        sum += a[i + 14];
        sum += a[i + 15];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// U = 32
__attribute__((noinline))
double sum_unroll_32(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 31; i += 32) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
        sum += a[i + 4];
        sum += a[i + 5];
        sum += a[i + 6];
        sum += a[i + 7];
        sum += a[i + 8];
        sum += a[i + 9];
        sum += a[i + 10];
        sum += a[i + 11];
        sum += a[i + 12];
        sum += a[i + 13];
        sum += a[i + 14];
        sum += a[i + 15];
        sum += a[i + 16];
        sum += a[i + 17];
        sum += a[i + 18];
        sum += a[i + 19];
        sum += a[i + 20];
        sum += a[i + 21];
        sum += a[i + 22];
        sum += a[i + 23];
        sum += a[i + 24];
        sum += a[i + 25];
        sum += a[i + 26];
        sum += a[i + 27];
        sum += a[i + 28];
        sum += a[i + 29];
        sum += a[i + 30];
        sum += a[i + 31];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// ============================================================================
// Improved versions with multiple accumulators (ILP optimization)
// ============================================================================

// U = 4 with 4 accumulators
__attribute__((noinline))
double sum_unroll_4_ilp(const double *a, int n) {
    double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum0 += a[i];
        sum1 += a[i + 1];
        sum2 += a[i + 2];
        sum3 += a[i + 3];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum0 += a[i];
    }
    return sum0 + sum1 + sum2 + sum3;
}

// U = 8 with 8 accumulators
__attribute__((noinline))
double sum_unroll_8_ilp(const double *a, int n) {
    double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
    double sum4 = 0.0, sum5 = 0.0, sum6 = 0.0, sum7 = 0.0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum0 += a[i];
        sum1 += a[i + 1];
        sum2 += a[i + 2];
        sum3 += a[i + 3];
        sum4 += a[i + 4];
        sum5 += a[i + 5];
        sum6 += a[i + 6];
        sum7 += a[i + 7];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum0 += a[i];
    }
    return (sum0 + sum1) + (sum2 + sum3) + (sum4 + sum5) + (sum6 + sum7);
}

// ============================================================================
// Benchmarking infrastructure
// ============================================================================

typedef double (*sum_func_t)(const double*, int);

typedef struct {
    const char *name;
    sum_func_t func;
    int unroll_factor;
} benchmark_t;

benchmark_t benchmarks[] = {
    {"U=1  (baseline)",      sum_unroll_1,      1},
    {"U=2",                  sum_unroll_2,      2},
    {"U=4",                  sum_unroll_4,      4},
    {"U=8",                  sum_unroll_8,      8},
    {"U=16",                 sum_unroll_16,     16},
    {"U=32",                 sum_unroll_32,     32},
    {"U=4  (4 accum, ILP)",  sum_unroll_4_ilp,  4},
    {"U=8  (8 accum, ILP)",  sum_unroll_8_ilp,  8},
};

#define NUM_BENCHMARKS (sizeof(benchmarks) / sizeof(benchmarks[0]))

double run_benchmark(sum_func_t func, const double *a, int n, double *min_time, double *max_time) {
    double total_time = 0.0;
    *min_time = 1e18;
    *max_time = 0.0;

    // Warmup
    for (int i = 0; i < WARMUP_ITERATIONS; i++) {
        sink = func(a, n);
    }

    // Timed runs
    for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
        double start = get_time_ns();
        double result = func(a, n);
        double end = get_time_ns();
        sink = result;  // Prevent optimization

        double elapsed = end - start;
        total_time += elapsed;
        if (elapsed < *min_time) *min_time = elapsed;
        if (elapsed > *max_time) *max_time = elapsed;
    }

    return total_time / NUM_ITERATIONS;  // Average time in ns
}

int main(int argc, char *argv[]) {
    printf("=============================================================\n");
    printf("Exercise 1: Loop Unrolling Optimization Analysis\n");
    printf("=============================================================\n\n");

    // Initialize timing
    init_timing();

    // Allocate and initialize array
    double *a = (double *)aligned_alloc(64, N * sizeof(double));
    if (!a) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    // Initialize array to 1.0 (expected sum = N)
    for (int i = 0; i < N; i++) {
        a[i] = 1.0;
    }

    printf("Configuration:\n");
    printf("  Array size N:        %d elements\n", N);
    printf("  Data type:           double (8 bytes)\n");
    printf("  Total data size:     %.2f MB\n", (double)N * sizeof(double) / (1024 * 1024));
    printf("  Iterations:          %d\n", NUM_ITERATIONS);
    printf("  Expected sum:        %d\n\n", N);

    // Theoretical minimum time calculation
    // M4 Max memory bandwidth: ~400 GB/s
    double bandwidth_gb_s = 400.0;
    double data_size_bytes = (double)N * sizeof(double);
    double theoretical_min_ns = (data_size_bytes / (bandwidth_gb_s * 1e9)) * 1e9;

    printf("Theoretical Analysis:\n");
    printf("  Memory bandwidth:    %.0f GB/s (M4 Max estimate)\n", bandwidth_gb_s);
    printf("  Data to transfer:    %.2f MB\n", data_size_bytes / (1024 * 1024));
    printf("  Theoretical min:     %.2f ns (memory-bound limit)\n\n", theoretical_min_ns);

    // Run benchmarks
    printf("%-25s %12s %12s %12s %10s %12s\n",
           "Method", "Avg (ns)", "Min (ns)", "Max (ns)", "Speedup", "BW (GB/s)");
    printf("--------------------------------------------------------------------------------\n");

    double baseline_time = 0.0;
    double best_time = 1e18;
    const char *best_method = "";

    for (size_t i = 0; i < NUM_BENCHMARKS; i++) {
        double min_time, max_time;
        double avg_time = run_benchmark(benchmarks[i].func, a, N, &min_time, &max_time);

        // Verify correctness
        double result = benchmarks[i].func(a, N);
        if (fabs(result - N) > 1e-6) {
            printf("ERROR: %s returned %.2f, expected %d\n",
                   benchmarks[i].name, result, N);
        }

        if (i == 0) baseline_time = avg_time;

        double speedup = baseline_time / avg_time;
        double bandwidth = data_size_bytes / (avg_time / 1e9) / 1e9;

        printf("%-25s %12.2f %12.2f %12.2f %9.2fx %11.2f\n",
               benchmarks[i].name, avg_time, min_time, max_time, speedup, bandwidth);

        if (avg_time < best_time) {
            best_time = avg_time;
            best_method = benchmarks[i].name;
        }
    }

    printf("--------------------------------------------------------------------------------\n\n");

    // Summary
    printf("Summary:\n");
    printf("  Baseline (U=1):      %.2f ns\n", baseline_time);
    printf("  Best method:         %s\n", best_method);
    printf("  Best time:           %.2f ns\n", best_time);
    printf("  Best speedup:        %.2fx\n", baseline_time / best_time);
    printf("  Theoretical min:     %.2f ns\n", theoretical_min_ns);
    printf("  Efficiency:          %.1f%% of theoretical peak\n",
           (theoretical_min_ns / best_time) * 100);

    free(a);
    return 0;
}
