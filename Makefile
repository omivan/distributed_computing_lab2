# Define the compiler and flags
CC = gcc
CFLAGS = -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp

# Targets to compile and run each file

# Target to compile and run 1.c
run1: 1.c
	$(CC) $(CFLAGS) 1.c -o 1_executable
	./1_executable

# Target to compile and run 2_matrix_multiplication.c
run2: 2_matrix_multiplication.c
	$(CC) $(CFLAGS) 2_matrix_multiplication.c -o 2_executable
	./2_executable

# Target to compile and run 3_matrix_sum.c
run3: 3_matrix_sum.c
	$(CC) $(CFLAGS) 3_matrix_sum.c -o 3_executable
	./3_executable

run4: 3_row_sum.c
	$(CC) $(CFLAGS) 3_row_sum.c -o 4_executable
	./4_executable

# Clean target to remove generated files
clean:
	rm -f 1_executable 2_executable 3_executable 4_executable

.PHONY: run1 run2 run3 run4 clean
