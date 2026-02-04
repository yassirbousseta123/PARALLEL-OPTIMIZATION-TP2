# Exercise 1: Loop Unrolling Optimization Makefile
# Compiles benchmarks with different optimization levels

CC = clang
CFLAGS_COMMON = -Wall -Wextra

# Optimization levels
CFLAGS_O0 = $(CFLAGS_COMMON) -O0
CFLAGS_O1 = $(CFLAGS_COMMON) -O1
CFLAGS_O2 = $(CFLAGS_COMMON) -O2
CFLAGS_O3 = $(CFLAGS_COMMON) -O3
CFLAGS_Ofast = $(CFLAGS_COMMON) -Ofast

# Source files
SRC_MAIN = exercise1.c
SRC_TYPES = exercise1_types.c

# Targets
all: exercise1_O0 exercise1_O2 exercise1_O3 \
     exercise1_types_O0 exercise1_types_O2 exercise1_types_O3

# Main benchmark at different optimization levels
exercise1_O0: $(SRC_MAIN)
	$(CC) $(CFLAGS_O0) $< -o $@

exercise1_O1: $(SRC_MAIN)
	$(CC) $(CFLAGS_O1) $< -o $@

exercise1_O2: $(SRC_MAIN)
	$(CC) $(CFLAGS_O2) $< -o $@

exercise1_O3: $(SRC_MAIN)
	$(CC) $(CFLAGS_O3) $< -o $@

exercise1_Ofast: $(SRC_MAIN)
	$(CC) $(CFLAGS_Ofast) $< -o $@

# Types benchmark at different optimization levels
exercise1_types_O0: $(SRC_TYPES)
	$(CC) $(CFLAGS_O0) $< -o $@

exercise1_types_O1: $(SRC_TYPES)
	$(CC) $(CFLAGS_O1) $< -o $@

exercise1_types_O2: $(SRC_TYPES)
	$(CC) $(CFLAGS_O2) $< -o $@

exercise1_types_O3: $(SRC_TYPES)
	$(CC) $(CFLAGS_O3) $< -o $@

exercise1_types_Ofast: $(SRC_TYPES)
	$(CC) $(CFLAGS_Ofast) $< -o $@

clean:
	rm -f exercise1_O0 exercise1_O1 exercise1_O2 exercise1_O3 exercise1_Ofast
	rm -f exercise1_types_O0 exercise1_types_O1 exercise1_types_O2 exercise1_types_O3 exercise1_types_Ofast

.PHONY: all clean
