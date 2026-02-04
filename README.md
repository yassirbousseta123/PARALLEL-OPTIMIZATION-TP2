# TP2: Parallel Computing Foundations

Practical exercises exploring compiler optimizations, instruction-level parallelism (ILP), and parallel speedup laws.

## System Requirements

- **Platform:** Apple Silicon (ARM64) or x86_64
- **Compiler:** GCC or Clang with `-O0`, `-O2`, `-O3` support
- **Profiler:** Valgrind/Callgrind (via Docker on macOS)

## Repository Structure

```
.
├── exercise1/          # Loop unrolling & ILP
├── exercise2/          # Instruction scheduling
├── exercise3/          # Amdahl's Law (vector ops)
├── exercise4/          # Gustafson's Law (matrix mult)
├── *.png               # Result plots
├── analysis.py         # Plot generation script
├── results.md          # Full results report
├── Dockerfile          # Valgrind environment
└── TP2.pdf             # Assignment specification
```

## Exercises Overview

### Exercise 1: Loop Unrolling

Analyzes how loop unrolling and multiple accumulators affect performance.

| File | Description |
|------|-------------|
| `exercise1.c` | Main benchmark with unrolling factors 1-32 |
| `exercise1_types.c` | Data type comparison (double, float, int, short) |
| `Makefile` | Build at -O0, -O2, -O3 |
| `run_benchmarks.sh` | Automated benchmark runner |
| `*_O0`, `*_O2`, `*_O3` | Compiled binaries |

**Key finding:** 8 independent accumulators achieve **6.93x speedup** at -O2.

### Exercise 2: Instruction Scheduling

Compares compiler-generated assembly across optimization levels.

| File | Description |
|------|-------------|
| `exercise2.c` | Original code |
| `exercise2_manual.c` | Manually optimized version |
| `O0.s`, `O2.s` | Assembly output comparison |
| `analysis.txt` | Detailed assembly analysis |

**Key finding:** Manual + compiler optimization achieves **7.12x speedup**.

### Exercise 3: Amdahl's Law

Profiles vector operations to calculate sequential fraction and speedup limits.

| File | Description |
|------|-------------|
| `exercise3.c` | Vector operations with sequential dependency |
| `exercise3_small/medium/large.c` | Different problem sizes |
| `results.txt` | Callgrind profiling output |

**Key finding:** 26.3% sequential fraction limits max speedup to **3.8x**.

### Exercise 4: Matrix Multiplication

Demonstrates near-ideal parallelization with O(N³) parallel work.

| File | Description |
|------|-------------|
| `exercise4.c` | Matrix multiplication benchmark |
| `results.txt` | Callgrind profiling output |

**Key finding:** 0.00027% sequential fraction allows **369,004x** theoretical speedup.

## Generated Plots

| Plot | Description |
|------|-------------|
| `exercise1_unrolling.png` | Unrolling performance vs optimization level |
| `exercise1_types.png` | Data type comparison |
| `exercise3_amdahl.png` | Amdahl's Law speedup curve |
| `exercise3_gustafson.png` | Gustafson's Law scaling |
| `exercise4_scaling.png` | Matrix multiplication scaling |
| `comparison_scaling.png` | Exercise 3 vs 4 comparison |

## Building & Running

```bash
# Exercise 1
cd exercise1
make all
./run_benchmarks.sh

# Exercise 2
cd exercise2
gcc -O0 exercise2.c -o exercise2_O0
gcc -O2 exercise2.c -o exercise2_O2
gcc -O0 -S exercise2.c -o O0.s
gcc -O2 -S exercise2.c -o O2.s

# Profiling with Docker (for macOS)
docker build -t valgrind-env .
docker run -v $(pwd):/work valgrind-env valgrind --tool=callgrind ./exercise3
```

## Key Takeaways

1. **ILP matters more than unrolling** - Multiple accumulators break dependency chains
2. **Trust the compiler** - `-O2` handles most optimizations automatically
3. **Algorithm complexity determines parallelism** - O(N³) vs O(N) work ratios are crucial
4. **Amdahl's Law is pessimistic** - Gustafson's Law shows scaling potential with larger problems

## Full Report

See [`results.md`](results.md) for complete analysis with tables and detailed findings.
