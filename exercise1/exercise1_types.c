/*
 * Exercise 1: Loop Unrolling Analysis for Different Data Types
 *
 * This program benchmarks the impact of loop unrolling on array summation
 * performance across different data types: double, float, int, short
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
#define WARMUP_ITERATIONS 10

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

// Prevent compiler from optimizing away results
static volatile double sink_d;
static volatile float sink_f;
static volatile long long sink_i;

// ============================================================================
// DOUBLE (8 bytes) summation functions
// ============================================================================

__attribute__((noinline))
double sum_double_1(const double *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
double sum_double_2(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 1; i += 2) {
        sum += a[i]; sum += a[i+1];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
double sum_double_4(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
double sum_double_8(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
double sum_double_16(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 15; i += 16) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
double sum_double_32(const double *a, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n - 31; i += 32) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
        sum += a[i+16]; sum += a[i+17]; sum += a[i+18]; sum += a[i+19];
        sum += a[i+20]; sum += a[i+21]; sum += a[i+22]; sum += a[i+23];
        sum += a[i+24]; sum += a[i+25]; sum += a[i+26]; sum += a[i+27];
        sum += a[i+28]; sum += a[i+29]; sum += a[i+30]; sum += a[i+31];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

// ILP version with multiple accumulators
__attribute__((noinline))
double sum_double_8_ilp(const double *a, int n) {
    double s0=0, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        s0 += a[i]; s1 += a[i+1]; s2 += a[i+2]; s3 += a[i+3];
        s4 += a[i+4]; s5 += a[i+5]; s6 += a[i+6]; s7 += a[i+7];
    }
    for (; i < n; i++) s0 += a[i];
    return (s0+s1) + (s2+s3) + (s4+s5) + (s6+s7);
}

// ============================================================================
// FLOAT (4 bytes) summation functions
// ============================================================================

__attribute__((noinline))
float sum_float_1(const float *a, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_2(const float *a, int n) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < n - 1; i += 2) {
        sum += a[i]; sum += a[i+1];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_4(const float *a, int n) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_8(const float *a, int n) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_16(const float *a, int n) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < n - 15; i += 16) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_32(const float *a, int n) {
    float sum = 0.0f;
    int i;
    for (i = 0; i < n - 31; i += 32) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
        sum += a[i+16]; sum += a[i+17]; sum += a[i+18]; sum += a[i+19];
        sum += a[i+20]; sum += a[i+21]; sum += a[i+22]; sum += a[i+23];
        sum += a[i+24]; sum += a[i+25]; sum += a[i+26]; sum += a[i+27];
        sum += a[i+28]; sum += a[i+29]; sum += a[i+30]; sum += a[i+31];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
float sum_float_8_ilp(const float *a, int n) {
    float s0=0, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        s0 += a[i]; s1 += a[i+1]; s2 += a[i+2]; s3 += a[i+3];
        s4 += a[i+4]; s5 += a[i+5]; s6 += a[i+6]; s7 += a[i+7];
    }
    for (; i < n; i++) s0 += a[i];
    return (s0+s1) + (s2+s3) + (s4+s5) + (s6+s7);
}

// ============================================================================
// INT (4 bytes) summation functions
// ============================================================================

__attribute__((noinline))
long long sum_int_1(const int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_2(const int *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 1; i += 2) {
        sum += a[i]; sum += a[i+1];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_4(const int *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_8(const int *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_16(const int *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 15; i += 16) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_32(const int *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 31; i += 32) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
        sum += a[i+16]; sum += a[i+17]; sum += a[i+18]; sum += a[i+19];
        sum += a[i+20]; sum += a[i+21]; sum += a[i+22]; sum += a[i+23];
        sum += a[i+24]; sum += a[i+25]; sum += a[i+26]; sum += a[i+27];
        sum += a[i+28]; sum += a[i+29]; sum += a[i+30]; sum += a[i+31];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_int_8_ilp(const int *a, int n) {
    long long s0=0, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        s0 += a[i]; s1 += a[i+1]; s2 += a[i+2]; s3 += a[i+3];
        s4 += a[i+4]; s5 += a[i+5]; s6 += a[i+6]; s7 += a[i+7];
    }
    for (; i < n; i++) s0 += a[i];
    return (s0+s1) + (s2+s3) + (s4+s5) + (s6+s7);
}

// ============================================================================
// SHORT (2 bytes) summation functions
// ============================================================================

__attribute__((noinline))
long long sum_short_1(const short *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_2(const short *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 1; i += 2) {
        sum += a[i]; sum += a[i+1];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_4(const short *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_8(const short *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_16(const short *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 15; i += 16) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_32(const short *a, int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n - 31; i += 32) {
        sum += a[i]; sum += a[i+1]; sum += a[i+2]; sum += a[i+3];
        sum += a[i+4]; sum += a[i+5]; sum += a[i+6]; sum += a[i+7];
        sum += a[i+8]; sum += a[i+9]; sum += a[i+10]; sum += a[i+11];
        sum += a[i+12]; sum += a[i+13]; sum += a[i+14]; sum += a[i+15];
        sum += a[i+16]; sum += a[i+17]; sum += a[i+18]; sum += a[i+19];
        sum += a[i+20]; sum += a[i+21]; sum += a[i+22]; sum += a[i+23];
        sum += a[i+24]; sum += a[i+25]; sum += a[i+26]; sum += a[i+27];
        sum += a[i+28]; sum += a[i+29]; sum += a[i+30]; sum += a[i+31];
    }
    for (; i < n; i++) sum += a[i];
    return sum;
}

__attribute__((noinline))
long long sum_short_8_ilp(const short *a, int n) {
    long long s0=0, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
    int i;
    for (i = 0; i < n - 7; i += 8) {
        s0 += a[i]; s1 += a[i+1]; s2 += a[i+2]; s3 += a[i+3];
        s4 += a[i+4]; s5 += a[i+5]; s6 += a[i+6]; s7 += a[i+7];
    }
    for (; i < n; i++) s0 += a[i];
    return (s0+s1) + (s2+s3) + (s4+s5) + (s6+s7);
}

// ============================================================================
// Benchmark runners for each type
// ============================================================================

typedef struct {
    const char *name;
    int unroll_factor;
    double avg_time_ns;
    double min_time_ns;
    double max_time_ns;
    double bandwidth_gb_s;
    double speedup;
} result_t;

void print_header(const char *type_name, int type_size) {
    printf("\n");
    printf("================================================================================\n");
    printf("Data Type: %s (%d bytes)\n", type_name, type_size);
    printf("Data size: %.2f MB\n", (double)N * type_size / (1024*1024));
    printf("================================================================================\n");
    printf("%-20s %12s %12s %12s %10s %12s\n",
           "Method", "Avg (ns)", "Min (ns)", "Max (ns)", "Speedup", "BW (GB/s)");
    printf("--------------------------------------------------------------------------------\n");
}

void print_result(const char *name, double avg, double min, double max,
                  double speedup, double bandwidth) {
    printf("%-20s %12.2f %12.2f %12.2f %9.2fx %11.2f\n",
           name, avg, min, max, speedup, bandwidth);
}

// ============================================================================
// DOUBLE benchmarks
// ============================================================================

void benchmark_double(double *results_baseline, double *results_best) {
    double *a = (double *)aligned_alloc(64, N * sizeof(double));
    for (int i = 0; i < N; i++) a[i] = 1.0;

    print_header("double", sizeof(double));
    double data_bytes = (double)N * sizeof(double);

    // Function pointers and names
    double (*funcs[])(const double*, int) = {
        sum_double_1, sum_double_2, sum_double_4, sum_double_8,
        sum_double_16, sum_double_32, sum_double_8_ilp
    };
    const char *names[] = {"U=1", "U=2", "U=4", "U=8", "U=16", "U=32", "U=8 (ILP)"};
    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    double baseline = 0, best = 1e18;

    for (int f = 0; f < num_funcs; f++) {
        // Warmup
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            sink_d = funcs[f](a, N);
        }

        double total = 0, min_t = 1e18, max_t = 0;
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            double start = get_time_ns();
            double result = funcs[f](a, N);
            double end = get_time_ns();
            sink_d = result;
            double elapsed = end - start;
            total += elapsed;
            if (elapsed < min_t) min_t = elapsed;
            if (elapsed > max_t) max_t = elapsed;
        }
        double avg = total / NUM_ITERATIONS;
        if (f == 0) baseline = avg;
        if (avg < best) best = avg;

        double speedup = baseline / avg;
        double bw = data_bytes / (avg / 1e9) / 1e9;
        print_result(names[f], avg, min_t, max_t, speedup, bw);
    }

    *results_baseline = baseline;
    *results_best = best;
    free(a);
}

// ============================================================================
// FLOAT benchmarks
// ============================================================================

void benchmark_float(double *results_baseline, double *results_best) {
    float *a = (float *)aligned_alloc(64, N * sizeof(float));
    for (int i = 0; i < N; i++) a[i] = 1.0f;

    print_header("float", sizeof(float));
    double data_bytes = (double)N * sizeof(float);

    float (*funcs[])(const float*, int) = {
        sum_float_1, sum_float_2, sum_float_4, sum_float_8,
        sum_float_16, sum_float_32, sum_float_8_ilp
    };
    const char *names[] = {"U=1", "U=2", "U=4", "U=8", "U=16", "U=32", "U=8 (ILP)"};
    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    double baseline = 0, best = 1e18;

    for (int f = 0; f < num_funcs; f++) {
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            sink_f = funcs[f](a, N);
        }

        double total = 0, min_t = 1e18, max_t = 0;
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            double start = get_time_ns();
            float result = funcs[f](a, N);
            double end = get_time_ns();
            sink_f = result;
            double elapsed = end - start;
            total += elapsed;
            if (elapsed < min_t) min_t = elapsed;
            if (elapsed > max_t) max_t = elapsed;
        }
        double avg = total / NUM_ITERATIONS;
        if (f == 0) baseline = avg;
        if (avg < best) best = avg;

        double speedup = baseline / avg;
        double bw = data_bytes / (avg / 1e9) / 1e9;
        print_result(names[f], avg, min_t, max_t, speedup, bw);
    }

    *results_baseline = baseline;
    *results_best = best;
    free(a);
}

// ============================================================================
// INT benchmarks
// ============================================================================

void benchmark_int(double *results_baseline, double *results_best) {
    int *a = (int *)aligned_alloc(64, N * sizeof(int));
    for (int i = 0; i < N; i++) a[i] = 1;

    print_header("int", sizeof(int));
    double data_bytes = (double)N * sizeof(int);

    long long (*funcs[])(const int*, int) = {
        sum_int_1, sum_int_2, sum_int_4, sum_int_8,
        sum_int_16, sum_int_32, sum_int_8_ilp
    };
    const char *names[] = {"U=1", "U=2", "U=4", "U=8", "U=16", "U=32", "U=8 (ILP)"};
    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    double baseline = 0, best = 1e18;

    for (int f = 0; f < num_funcs; f++) {
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            sink_i = funcs[f](a, N);
        }

        double total = 0, min_t = 1e18, max_t = 0;
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            double start = get_time_ns();
            long long result = funcs[f](a, N);
            double end = get_time_ns();
            sink_i = result;
            double elapsed = end - start;
            total += elapsed;
            if (elapsed < min_t) min_t = elapsed;
            if (elapsed > max_t) max_t = elapsed;
        }
        double avg = total / NUM_ITERATIONS;
        if (f == 0) baseline = avg;
        if (avg < best) best = avg;

        double speedup = baseline / avg;
        double bw = data_bytes / (avg / 1e9) / 1e9;
        print_result(names[f], avg, min_t, max_t, speedup, bw);
    }

    *results_baseline = baseline;
    *results_best = best;
    free(a);
}

// ============================================================================
// SHORT benchmarks
// ============================================================================

void benchmark_short(double *results_baseline, double *results_best) {
    short *a = (short *)aligned_alloc(64, N * sizeof(short));
    for (int i = 0; i < N; i++) a[i] = 1;

    print_header("short", sizeof(short));
    double data_bytes = (double)N * sizeof(short);

    long long (*funcs[])(const short*, int) = {
        sum_short_1, sum_short_2, sum_short_4, sum_short_8,
        sum_short_16, sum_short_32, sum_short_8_ilp
    };
    const char *names[] = {"U=1", "U=2", "U=4", "U=8", "U=16", "U=32", "U=8 (ILP)"};
    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    double baseline = 0, best = 1e18;

    for (int f = 0; f < num_funcs; f++) {
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            sink_i = funcs[f](a, N);
        }

        double total = 0, min_t = 1e18, max_t = 0;
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            double start = get_time_ns();
            long long result = funcs[f](a, N);
            double end = get_time_ns();
            sink_i = result;
            double elapsed = end - start;
            total += elapsed;
            if (elapsed < min_t) min_t = elapsed;
            if (elapsed > max_t) max_t = elapsed;
        }
        double avg = total / NUM_ITERATIONS;
        if (f == 0) baseline = avg;
        if (avg < best) best = avg;

        double speedup = baseline / avg;
        double bw = data_bytes / (avg / 1e9) / 1e9;
        print_result(names[f], avg, min_t, max_t, speedup, bw);
    }

    *results_baseline = baseline;
    *results_best = best;
    free(a);
}

// ============================================================================
// Main
// ============================================================================

int main(int argc, char *argv[]) {
    init_timing();

    printf("================================================================================\n");
    printf("Exercise 1: Loop Unrolling Analysis for Different Data Types\n");
    printf("================================================================================\n");
    printf("\nConfiguration:\n");
    printf("  Array size N:     %d elements\n", N);
    printf("  Iterations:       %d (+ %d warmup)\n", NUM_ITERATIONS, WARMUP_ITERATIONS);
    printf("  Expected sum:     %d\n", N);

    // Theoretical bandwidth (M4 Max)
    double bw_theoretical = 400.0;  // GB/s
    printf("\nTheoretical Analysis:\n");
    printf("  Memory bandwidth: %.0f GB/s (M4 Max estimate)\n", bw_theoretical);
    printf("  Min time double:  %.2f ns (%.2f MB @ %.0f GB/s)\n",
           ((double)N * 8 / (bw_theoretical * 1e9)) * 1e9, (double)N * 8 / (1024*1024), bw_theoretical);
    printf("  Min time float:   %.2f ns (%.2f MB @ %.0f GB/s)\n",
           ((double)N * 4 / (bw_theoretical * 1e9)) * 1e9, (double)N * 4 / (1024*1024), bw_theoretical);
    printf("  Min time int:     %.2f ns (%.2f MB @ %.0f GB/s)\n",
           ((double)N * 4 / (bw_theoretical * 1e9)) * 1e9, (double)N * 4 / (1024*1024), bw_theoretical);
    printf("  Min time short:   %.2f ns (%.2f MB @ %.0f GB/s)\n",
           ((double)N * 2 / (bw_theoretical * 1e9)) * 1e9, (double)N * 2 / (1024*1024), bw_theoretical);

    double baseline_d, best_d, baseline_f, best_f, baseline_i, best_i, baseline_s, best_s;

    benchmark_double(&baseline_d, &best_d);
    benchmark_float(&baseline_f, &best_f);
    benchmark_int(&baseline_i, &best_i);
    benchmark_short(&baseline_s, &best_s);

    // Summary
    printf("\n================================================================================\n");
    printf("SUMMARY\n");
    printf("================================================================================\n");
    printf("%-12s %12s %12s %12s %10s\n", "Type", "Size", "Baseline", "Best", "Speedup");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-12s %10d B %10.2f ns %10.2f ns %9.2fx\n", "double", 8, baseline_d, best_d, baseline_d/best_d);
    printf("%-12s %10d B %10.2f ns %10.2f ns %9.2fx\n", "float", 4, baseline_f, best_f, baseline_f/best_f);
    printf("%-12s %10d B %10.2f ns %10.2f ns %9.2fx\n", "int", 4, baseline_i, best_i, baseline_i/best_i);
    printf("%-12s %10d B %10.2f ns %10.2f ns %9.2fx\n", "short", 2, baseline_s, best_s, baseline_s/best_s);

    return 0;
}
