# Sorting Algorithm Benchmark

This project implements and benchmarks four sorting algorithms in C++: 

- Bubble Sort
- Selection Sort
- Insertion Sort
- Quick Sort

The algorithms are tested using random, sorted, and reverse-sorted vectors with input sizes of 1,000, 5,000, and 10,000 elements. Each sorting algorithm runs five times for each input, and we measure the average execution time in microseconds. The isSorted() function checks that each algorithm correctly sorts the input. 

# How to Compile 

Compile the program using a C++ compiler: 
g++ -std=c++17 sorting_algorithms.cpp -o sorting_algorithms

# How to Run

Run the compiled program: 

On Windows:
sorting_algorithms.exe

On Mac/Linux:
./sorting_algorithms
