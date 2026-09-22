#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void bubbleSort(std::vector<int>& values){
    for (int i = 0; i < values.size() - 1; i++){
        for (int j = 0; j < values.size() - i - 1; j++)
        if (values[j] > values[j + 1]) {
            int temp = values[j];
            values[j] = values[j + 1];
            values[j + 1] = temp;
        }
    }
}

void selectionSort(std::vector<int>& values) {
    for (int i = 0; i < values.size() - 1; i++) {
        int indexSmallest = i;

        for (int j = i + 1; j < values.size(); j++) {
            if (values[j] < values[indexSmallest]) {
                indexSmallest = j;
            }
        }

        int temp = values[i];
        values[i] = values[indexSmallest];
        values[indexSmallest] = temp;
    }
}

void insertionSort(std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        int j = i; 

        while (j > 0 && values[j] < values[j - 1]) {
            int temp = values[j];
            values[j] = values[j - 1];
            values[j - 1] = temp;

            j--;
        }
    }
}

int quickSortPartition(std::vector<int>& values, int low, int high){
    int middle = low + (high - low) / 2; 
    int pivot = values[middle];

    int i = low; 
    int j = high;
    
    while(i <= j){
        while (values[i] < pivot) {
            i++;

        }
        while (values[j] > pivot) {
            j--;
        }

        if (i <= j) {
            int temp = values[i];
            values[i] = values[j];
            values[j] = temp;

            i++;
            j--;
        }
    }

    return i; 
}

void quickSort(std::vector<int>& values, int low, int high) {
    if (low < high){
        int partitionIndex = quickSortPartition(values, low, high);

        quickSort(values, low, partitionIndex - 1);
        quickSort(values, partitionIndex, high);
    }
}

bool isSorted(const std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        if (values[i] < values[i - 1]) {
            return false;
        }
    }
    return true;
}

std::vector<int> createRandomVector(int size) {
    std::vector<int> values(size);

    std::random_device rd; 
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100000); 

    for (int i = 0; i < size; i++){
        values[i] = distribution(generator);
    }

    return values; 
}

std::vector<int> createSortedVector(int size){
    std::vector<int> values(size);

    for (int i = 0; i < size; i++){
        values[i] = i; 
    }
    
    return values; 
}

std::vector<int> createReverseVector(int size){
    std::vector<int> values(size);

    for (int i = 0; i < size; i++){
        values[i] = size - i; 
    }

    return values; 
}

double benchmarkSort(const std::vector<int>& values, int sortFunction) {
    
    double total = 0; 

    std::vector<int> testValues;

    for (int i = 0; i < 5; i++) {

        testValues = values;

        auto start = std::chrono::steady_clock::now();

         if (sortFunction == 1) {
            bubbleSort(testValues);
         }
         else if (sortFunction == 2) {
            selectionSort(testValues);
         }
         else if (sortFunction == 3) {
            insertionSort(testValues);
         }
         else if (sortFunction == 4) {
            quickSort(testValues, 0, testValues.size() - 1);
         }

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        total += duration.count();
    }

    if (!isSorted(testValues)){
        std::cout << "Sorting failed.\n";
    }

    return total / 5.0; 
}

void printResult(const std::vector<int>& values) {
    std::cout << "Bubble Sort: "
              << benchmarkSort(values, 1)
              << " microseconds\n";

    std::cout << "Selection Sort: "
              << benchmarkSort(values, 2)
              << " microseconds\n";

    std::cout << "Insertion Sort: "
              << benchmarkSort(values, 3)
              << " microseconds\n"; 
    
    std::cout << "Quick Sort: "
              << benchmarkSort(values, 4)
              << " microseconds\n";        
}

int main() {
    std::vector<int> sizes = {1000, 5000, 10000};

    for (int size: sizes){
        std::vector<int> randomValues = createRandomVector(size);
        std::vector<int> sortedValues = createSortedVector(size);
        std::vector<int> reverseSortedValues = createReverseVector(size);

        std::cout << "\nSize: " << size << "\n"; 

        std::cout << "\nRandom Values:\n";
        printResult(randomValues);

        std::cout << "\nSorted Values:\n";
        printResult(sortedValues);

        std::cout << "\nReverse Sorted Values:\n";
        printResult(reverseSortedValues);
    }

    return 0; 
}