#!/bin/bash
#
# Exercise 1: Run all benchmarks and save results
#

RESULTS_FILE="results.txt"
cd "$(dirname "$0")"

echo "=============================================================="
echo "Exercise 1: Loop Unrolling Optimization Benchmarks"
echo "=============================================================="
echo ""

# Compile all versions
echo "Compiling benchmarks..."
make clean > /dev/null 2>&1
make all

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful."
echo ""

# Start results file
{
echo "================================================================================"
echo "Exercise 1: Loop Unrolling Optimization Analysis - Results"
echo "================================================================================"
echo ""
echo "Generated on: $(date)"
echo "System: $(uname -a)"
echo ""

# Get CPU info
if [ "$(uname)" == "Darwin" ]; then
    echo "CPU Info:"
    sysctl -n machdep.cpu.brand_string 2>/dev/null || echo "  Unknown CPU"
    echo "  Cores: $(sysctl -n hw.ncpu)"
    echo "  Memory: $(( $(sysctl -n hw.memsize) / 1024 / 1024 / 1024 )) GB"
fi
echo ""

echo "================================================================================"
echo "PART 1: Main Benchmark (double type) - Different Optimization Levels"
echo "================================================================================"

echo ""
echo "--------------------------------------------------------------------------------"
echo "1.1 Without compiler optimization (-O0)"
echo "     Manual unrolling should show significant improvement"
echo "--------------------------------------------------------------------------------"
./exercise1_O0

echo ""
echo "--------------------------------------------------------------------------------"
echo "1.2 With compiler optimization (-O2)"
echo "     Compiler may auto-unroll; manual unrolling may show less improvement"
echo "--------------------------------------------------------------------------------"
./exercise1_O2

echo ""
echo "--------------------------------------------------------------------------------"
echo "1.3 With aggressive optimization (-O3)"
echo "     Compiler performs more aggressive optimizations"
echo "--------------------------------------------------------------------------------"
./exercise1_O3

echo ""
echo "================================================================================"
echo "PART 2: Different Data Types Comparison"
echo "================================================================================"

echo ""
echo "--------------------------------------------------------------------------------"
echo "2.1 All data types WITHOUT compiler optimization (-O0)"
echo "--------------------------------------------------------------------------------"
./exercise1_types_O0

echo ""
echo "--------------------------------------------------------------------------------"
echo "2.2 All data types WITH compiler optimization (-O2)"
echo "--------------------------------------------------------------------------------"
./exercise1_types_O2

echo ""
echo "================================================================================"
echo "PART 3: Analysis and Conclusions"
echo "================================================================================"

echo ""
echo "Key Observations:"
echo "-----------------"
echo ""
echo "1. Loop Unrolling Benefits:"
echo "   - At -O0: Manual unrolling significantly reduces loop overhead"
echo "   - At -O2/-O3: Compiler auto-unrolling reduces manual unrolling benefit"
echo "   - ILP versions with multiple accumulators help break dependency chains"
echo ""
echo "2. Why Performance Improves Then Saturates:"
echo "   - Initial improvement: Reduces loop overhead (increment, compare, branch)"
echo "   - Saturation occurs when memory bandwidth becomes the bottleneck"
echo "   - Beyond optimal U, cache pressure and code size hurt performance"
echo "   - Theoretical limit: Tmin = DataSize / MemoryBandwidth"
echo ""
echo "3. Data Type Impact:"
echo "   - Smaller types (short, int) transfer less data = faster"
echo "   - BUT: Modern CPUs often vectorize differently per type"
echo "   - SIMD width affects optimal unrolling factor"
echo ""
echo "4. Theoretical Minimum Times (at 400 GB/s bandwidth):"
echo "   - double (8B): 1M * 8B = 8MB => ~20 microseconds"
echo "   - float  (4B): 1M * 4B = 4MB => ~10 microseconds"
echo "   - int    (4B): 1M * 4B = 4MB => ~10 microseconds"
echo "   - short  (2B): 1M * 2B = 2MB => ~5 microseconds"
echo ""
echo "5. -O0 Unrolled vs -O2 Original Loop:"
echo "   - Manual unrolling at -O0 can sometimes MATCH or BEAT -O2 original"
echo "   - This shows loop overhead is significant at -O0"
echo "   - -O2 with manual unrolling usually gives best results"
echo ""
echo "================================================================================"
echo "END OF RESULTS"
echo "================================================================================"

} > "$RESULTS_FILE"

echo "Results saved to: $RESULTS_FILE"
echo ""
echo "Quick summary:"
echo "--------------"

# Run quick summary
./exercise1_O2 2>/dev/null | tail -10

echo ""
echo "See $RESULTS_FILE for complete analysis."
