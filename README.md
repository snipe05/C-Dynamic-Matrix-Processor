# C Dynamic Matrix Processor
A low-level C program demonstrating advanced dynamic memory allocation (using triple pointers `double***`), file I/O operations, and matrix manipulation algorithms.

## Features
- Dynamically allocates a 2D matrix of pointers to `double`.
- Parses numerical data from an input text file.
- Normalizes columns based on their maximum values.
- Sorts the matrix columns using an in-place bubble sort algorithm.

## Usage
Compile with GCC:
`gcc matrix_processor.c -o processor`
Run with arguments (filename, rows, cols):
`./processor input-AE-OZ.txt 5 6`
