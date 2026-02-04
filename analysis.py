#!/usr/bin/env python3
"""
TP2 - Foundations of Parallel Computing
Analysis and Visualization Script

Generates plots for:
- Exercise 1: Loop Unrolling Optimization
- Exercise 3: Vector Operations with Amdahl's and Gustafson's Laws
- Exercise 4: Matrix Operations with Amdahl's and Gustafson's Laws
"""

import matplotlib.pyplot as plt
import numpy as np
import os

# Set style for professional plots
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 11
plt.rcParams['axes.titlesize'] = 14
plt.rcParams['axes.labelsize'] = 12
plt.rcParams['legend.fontsize'] = 10
plt.rcParams['lines.linewidth'] = 2
plt.rcParams['lines.markersize'] = 8

# Color scheme
COLORS = {
    'O0': '#e74c3c',      # Red
    'O2': '#3498db',      # Blue
    'O3': '#2ecc71',      # Green
    'ILP_O0': '#e67e22',  # Orange
    'ILP_O2': '#9b59b6',  # Purple
    'amdahl': '#2c3e50',  # Dark blue
    'gustafson': '#27ae60', # Green
    'ex3': '#e74c3c',     # Red
    'ex4': '#3498db',     # Blue
    'max_line': '#7f8c8d' # Gray
}

# Output directory (project root)
OUTPUT_DIR = '/Users/boussetayassir/Desktop/parralel computing/TP2'

def plot_exercise1_unrolling():
    """
    Exercise 1: U vs Execution Time
    Multiple lines for -O0, -O2, -O3 and ILP versions
    """
    # Data from results.txt
    U_values = [1, 2, 4, 8, 16, 32]

    # Standard unrolling times (ns)
    times_O0 = [727499.58, 1471181.25, 1953738.33, 1904750.83, 1999012.92, 2146025.00]
    times_O2 = [527333.75, 518794.58, 516044.17, 500467.92, 506552.08, 504284.17]
    times_O3 = [675220.42, 490155.00, 486986.25, 475339.17, 479971.67, 479042.92]

    # ILP versions (U=4 and U=8 with multiple accumulators)
    U_ILP = [4, 8]
    times_ILP_O0 = [404463.33, 413403.33]
    times_ILP_O2 = [176005.42, 76088.33]
    times_ILP_O3 = [164072.08, 76588.75]

    fig, ax = plt.subplots(figsize=(12, 7))

    # Plot standard unrolling
    ax.plot(U_values, times_O0, 'o-', color=COLORS['O0'], label='-O0 (Standard)', alpha=0.8)
    ax.plot(U_values, times_O2, 's-', color=COLORS['O2'], label='-O2 (Standard)', alpha=0.8)
    ax.plot(U_values, times_O3, '^-', color=COLORS['O3'], label='-O3 (Standard)', alpha=0.8)

    # Plot ILP versions
    ax.plot(U_ILP, times_ILP_O0, 'o--', color=COLORS['ILP_O0'], label='-O0 (ILP)',
            markersize=10, linewidth=2.5)
    ax.plot(U_ILP, times_ILP_O2, 's--', color=COLORS['ILP_O2'], label='-O2 (ILP)',
            markersize=10, linewidth=2.5)
    ax.plot(U_ILP, times_ILP_O3, '^--', color='#16a085', label='-O3 (ILP)',
            markersize=10, linewidth=2.5)

    ax.set_xlabel('Unrolling Factor (U)')
    ax.set_ylabel('Execution Time (ns)')
    ax.set_title('Exercise 1: Loop Unrolling vs Execution Time (double type)\nArray Size: 1,000,000 elements')
    ax.set_xticks(U_values)
    ax.set_xticklabels(['1', '2', '4', '8', '16', '32'])
    ax.legend(loc='upper left', framealpha=0.9)
    ax.set_yscale('log')

    # Add annotation for best result
    ax.annotate('Best: 76,088 ns\n(U=8 ILP, -O2)',
                xy=(8, 76088.33), xytext=(12, 150000),
                arrowprops=dict(arrowstyle='->', color='black'),
                fontsize=10, ha='center')

    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'exercise1_unrolling.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def plot_exercise1_types():
    """
    Exercise 1: Type Comparison
    Bar chart comparing double, float, int, short performance
    """
    types = ['double', 'float', 'int', 'short']

    # At -O2 (optimized)
    baseline_O2 = [576860, 486317, 36006, 46120]
    best_O2 = [73279, 66697, 35462, 46120]

    # At -O0 (no optimization)
    baseline_O0 = [719338, 633134, 596690, 606154]
    best_O0 = [414410, 427034, 418937, 446730]

    x = np.arange(len(types))
    width = 0.2

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

    # -O0 comparison
    bars1 = ax1.bar(x - width/2, baseline_O0, width, label='Baseline (U=1)',
                    color=COLORS['O0'], alpha=0.8)
    bars2 = ax1.bar(x + width/2, best_O0, width, label='Best (U=8 ILP)',
                    color=COLORS['ILP_O0'], alpha=0.8)

    ax1.set_xlabel('Data Type')
    ax1.set_ylabel('Execution Time (ns)')
    ax1.set_title('Type Comparison at -O0 (No Optimization)')
    ax1.set_xticks(x)
    ax1.set_xticklabels(types)
    ax1.legend()
    ax1.set_ylim(0, max(baseline_O0) * 1.15)

    # Add value labels
    for bar in bars1:
        height = bar.get_height()
        ax1.annotate(f'{height/1000:.0f}k',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3), textcoords="offset points",
                    ha='center', va='bottom', fontsize=9)

    # -O2 comparison
    bars3 = ax2.bar(x - width/2, baseline_O2, width, label='Baseline (U=1)',
                    color=COLORS['O2'], alpha=0.8)
    bars4 = ax2.bar(x + width/2, best_O2, width, label='Best',
                    color=COLORS['ILP_O2'], alpha=0.8)

    ax2.set_xlabel('Data Type')
    ax2.set_ylabel('Execution Time (ns)')
    ax2.set_title('Type Comparison at -O2 (Optimized)')
    ax2.set_xticks(x)
    ax2.set_xticklabels(types)
    ax2.legend()
    ax2.set_ylim(0, max(baseline_O2) * 1.15)

    # Add value labels
    for bar in bars3:
        height = bar.get_height()
        ax2.annotate(f'{height/1000:.0f}k',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3), textcoords="offset points",
                    ha='center', va='bottom', fontsize=9)

    plt.suptitle('Exercise 1: Data Type Performance Comparison', fontsize=14, fontweight='bold', y=1.02)
    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'exercise1_types.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def plot_exercise3_amdahl():
    """
    Exercise 3: Amdahl Speedup Curve
    fs = 26.3%
    """
    fs = 0.263

    # Processors
    p = np.array([1, 2, 4, 8, 16, 32, 64])
    p_continuous = np.linspace(1, 64, 100)

    # Amdahl's Law: S(p) = 1 / (fs + (1-fs)/p)
    def amdahl(p, fs):
        return 1 / (fs + (1 - fs) / p)

    speedup = amdahl(p, fs)
    speedup_continuous = amdahl(p_continuous, fs)
    max_speedup = 1 / fs

    fig, ax = plt.subplots(figsize=(10, 7))

    # Theoretical curve
    ax.plot(p_continuous, speedup_continuous, '-', color=COLORS['amdahl'],
            label=f"Amdahl's Law (fs = {fs*100:.1f}%)", linewidth=2.5)

    # Discrete points
    ax.plot(p, speedup, 'o', color=COLORS['amdahl'], markersize=10)

    # Maximum speedup line
    ax.axhline(y=max_speedup, color=COLORS['max_line'], linestyle='--',
               label=f'Maximum Speedup (Smax = 1/fs = {max_speedup:.2f}x)', linewidth=2)

    # Linear scaling reference
    ax.plot(p_continuous, p_continuous, ':', color='gray', alpha=0.5,
            label='Ideal Linear Scaling', linewidth=1.5)

    # Add data points annotation
    for i, (pi, si) in enumerate(zip(p, speedup)):
        ax.annotate(f'{si:.2f}x', xy=(pi, si), xytext=(5, 5),
                   textcoords='offset points', fontsize=9)

    ax.set_xlabel('Number of Processors (p)')
    ax.set_ylabel('Speedup S(p)')
    ax.set_title("Exercise 3: Amdahl's Law Speedup for Vector Operations\n(Sequential Fraction fs = 26.3%)")
    ax.legend(loc='upper left', framealpha=0.9)
    ax.set_xlim(0, 68)
    ax.set_ylim(0, max_speedup * 1.3)
    ax.grid(True, alpha=0.3)

    # Shade region between actual and ideal
    ax.fill_between(p_continuous, speedup_continuous, p_continuous,
                    alpha=0.15, color=COLORS['amdahl'],
                    label='Lost parallelism')

    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'exercise3_amdahl.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def plot_exercise3_gustafson():
    """
    Exercise 3: Gustafson Speedup Curve
    fs = 26.3%
    """
    fs = 0.263

    # Processors
    p = np.array([1, 2, 4, 8, 16, 32, 64])
    p_continuous = np.linspace(1, 64, 100)

    # Gustafson's Law: S(p) = fs + p * (1 - fs)
    def gustafson(p, fs):
        return fs + p * (1 - fs)

    speedup = gustafson(p, fs)
    speedup_continuous = gustafson(p_continuous, fs)

    fig, ax = plt.subplots(figsize=(10, 7))

    # Theoretical curve
    ax.plot(p_continuous, speedup_continuous, '-', color=COLORS['gustafson'],
            label=f"Gustafson's Law (fs = {fs*100:.1f}%)", linewidth=2.5)

    # Discrete points
    ax.plot(p, speedup, 'o', color=COLORS['gustafson'], markersize=10)

    # Linear scaling reference
    ax.plot(p_continuous, p_continuous, ':', color='gray', alpha=0.5,
            label='Ideal Linear Scaling', linewidth=1.5)

    # Add data points annotation
    for i, (pi, si) in enumerate(zip(p, speedup)):
        ax.annotate(f'{si:.1f}x', xy=(pi, si), xytext=(5, -15),
                   textcoords='offset points', fontsize=9)

    ax.set_xlabel('Number of Processors (p)')
    ax.set_ylabel('Scaled Speedup S(p)')
    ax.set_title("Exercise 3: Gustafson's Law Scaled Speedup for Vector Operations\n(Sequential Fraction fs = 26.3%)")
    ax.legend(loc='upper left', framealpha=0.9)
    ax.set_xlim(0, 68)
    ax.set_ylim(0, 52)
    ax.grid(True, alpha=0.3)

    # Show near-linear scaling with annotation
    slope = 1 - fs
    ax.annotate(f'Slope = 1 - fs = {slope:.3f}\n(Near-linear scaling)',
                xy=(40, gustafson(40, fs)), xytext=(45, 20),
                arrowprops=dict(arrowstyle='->', color='black'),
                fontsize=10, ha='left')

    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'exercise3_gustafson.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def plot_exercise4_scaling():
    """
    Exercise 4: Amdahl + Gustafson Combined
    fs = 0.00027%
    """
    fs = 0.00000271

    # Processors (extended range for matrix ops)
    p = np.array([1, 2, 4, 8, 16, 32, 64, 128, 256, 512])
    p_continuous = np.linspace(1, 512, 200)

    # Amdahl's Law
    def amdahl(p, fs):
        return 1 / (fs + (1 - fs) / p)

    # Gustafson's Law
    def gustafson(p, fs):
        return fs + p * (1 - fs)

    speedup_amdahl = amdahl(p, fs)
    speedup_gustafson = gustafson(p, fs)
    speedup_amdahl_cont = amdahl(p_continuous, fs)
    speedup_gustafson_cont = gustafson(p_continuous, fs)

    fig, ax = plt.subplots(figsize=(12, 7))

    # Amdahl curve
    ax.plot(p_continuous, speedup_amdahl_cont, '-', color=COLORS['amdahl'],
            label=f"Amdahl's Law (fs = {fs*100:.5f}%)", linewidth=2.5)
    ax.plot(p, speedup_amdahl, 'o', color=COLORS['amdahl'], markersize=8)

    # Gustafson curve (will overlap significantly)
    ax.plot(p_continuous, speedup_gustafson_cont, '--', color=COLORS['gustafson'],
            label=f"Gustafson's Law (fs = {fs*100:.5f}%)", linewidth=2.5)
    ax.plot(p, speedup_gustafson, 's', color=COLORS['gustafson'], markersize=8)

    # Linear scaling reference
    ax.plot(p_continuous, p_continuous, ':', color='gray', alpha=0.5,
            label='Ideal Linear Scaling', linewidth=1.5)

    ax.set_xlabel('Number of Processors (p)')
    ax.set_ylabel('Speedup S(p)')
    ax.set_title("Exercise 4: Amdahl's and Gustafson's Laws for Matrix Multiplication\n(Sequential Fraction fs = 0.00027% - Near-perfect parallelism)")
    ax.legend(loc='upper left', framealpha=0.9)
    ax.set_xlim(0, 540)
    ax.set_ylim(0, 550)
    ax.grid(True, alpha=0.3)

    # Annotation
    ax.annotate('Both laws show\nnear-linear scaling\ndue to tiny fs',
                xy=(256, 256), xytext=(350, 150),
                arrowprops=dict(arrowstyle='->', color='black'),
                fontsize=10, ha='left',
                bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.8))

    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'exercise4_scaling.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def plot_comparison_scaling():
    """
    Comparison: Exercise 3 vs 4
    Overlay Amdahl curves for both exercises
    """
    fs_ex3 = 0.263
    fs_ex4 = 0.00000271

    p = np.array([1, 2, 4, 8, 16, 32, 64])
    p_continuous = np.linspace(1, 64, 100)

    def amdahl(p, fs):
        return 1 / (fs + (1 - fs) / p)

    speedup_ex3 = amdahl(p, fs_ex3)
    speedup_ex4 = amdahl(p, fs_ex4)
    speedup_ex3_cont = amdahl(p_continuous, fs_ex3)
    speedup_ex4_cont = amdahl(p_continuous, fs_ex4)

    max_ex3 = 1 / fs_ex3
    max_ex4 = 1 / fs_ex4  # Very large, won't show on plot

    fig, ax = plt.subplots(figsize=(12, 7))

    # Exercise 3 (Vector Operations)
    ax.plot(p_continuous, speedup_ex3_cont, '-', color=COLORS['ex3'],
            label=f'Ex3: Vector Ops (fs = {fs_ex3*100:.1f}%)', linewidth=2.5)
    ax.plot(p, speedup_ex3, 'o', color=COLORS['ex3'], markersize=10)
    ax.axhline(y=max_ex3, color=COLORS['ex3'], linestyle='--', alpha=0.5,
               linewidth=1.5)

    # Exercise 4 (Matrix Multiplication)
    ax.plot(p_continuous, speedup_ex4_cont, '-', color=COLORS['ex4'],
            label=f'Ex4: Matrix Mult (fs = {fs_ex4*100:.5f}%)', linewidth=2.5)
    ax.plot(p, speedup_ex4, 's', color=COLORS['ex4'], markersize=10)

    # Linear scaling reference
    ax.plot(p_continuous, p_continuous, ':', color='gray', alpha=0.5,
            label='Ideal Linear Scaling', linewidth=1.5)

    ax.set_xlabel('Number of Processors (p)')
    ax.set_ylabel('Speedup S(p)')
    ax.set_title("Comparison: Amdahl's Law Speedup\nVector Operations (Ex3) vs Matrix Multiplication (Ex4)")
    ax.legend(loc='upper left', framealpha=0.9)
    ax.set_xlim(0, 68)
    ax.set_ylim(0, 70)
    ax.grid(True, alpha=0.3)

    # Annotations
    ax.annotate(f'Ex3 Max: {max_ex3:.2f}x',
                xy=(64, max_ex3), xytext=(50, max_ex3 + 8),
                arrowprops=dict(arrowstyle='->', color=COLORS['ex3']),
                fontsize=10, color=COLORS['ex3'])

    ax.annotate(f'Ex4: Near-linear scaling\n(Max = {max_ex4:,.0f}x)',
                xy=(48, amdahl(48, fs_ex4)), xytext=(25, 55),
                arrowprops=dict(arrowstyle='->', color=COLORS['ex4']),
                fontsize=10, color=COLORS['ex4'],
                bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.8))

    # Shade the gap to highlight the difference
    ax.fill_between(p_continuous, speedup_ex3_cont, speedup_ex4_cont,
                    alpha=0.2, color='yellow',
                    label='Performance gap')

    plt.tight_layout()
    filepath = os.path.join(OUTPUT_DIR, 'comparison_scaling.png')
    plt.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Created: {filepath}")


def main():
    """Generate all plots"""
    print("=" * 60)
    print("TP2 Analysis - Generating Plots")
    print("=" * 60)
    print()

    # Exercise 1 plots
    print("Generating Exercise 1 plots...")
    plot_exercise1_unrolling()
    plot_exercise1_types()

    # Exercise 3 plots
    print("\nGenerating Exercise 3 plots...")
    plot_exercise3_amdahl()
    plot_exercise3_gustafson()

    # Exercise 4 plots
    print("\nGenerating Exercise 4 plots...")
    plot_exercise4_scaling()

    # Comparison plot
    print("\nGenerating comparison plot...")
    plot_comparison_scaling()

    print()
    print("=" * 60)
    print("All plots generated successfully!")
    print("=" * 60)
    print("\nGenerated files:")
    for fname in ['exercise1_unrolling.png', 'exercise1_types.png',
                  'exercise3_amdahl.png', 'exercise3_gustafson.png',
                  'exercise4_scaling.png', 'comparison_scaling.png']:
        fpath = os.path.join(OUTPUT_DIR, fname)
        if os.path.exists(fpath):
            print(f"  - {fname}")


if __name__ == "__main__":
    main()
