#include <iostream>

void printArray(const int* arr, int size, const std::string& label);

int* generateWorstCase(int n) {
    if (n <= 0) return nullptr;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = n - 1 - i;
    }
    return arr;
}

int* generateBestCase(int n) {
    if (n <= 0) return nullptr;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
    return arr;
}

class InsertionSort {
private:
    int* data;
    int arraySize;
    int comparisonCount;

    bool isLessThan(int a, int b) {
        comparisonCount++;
        return a < b;
    }

    void swap(int i, int j) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

public:
    InsertionSort(int* arr, int size) : data(arr), arraySize(size), comparisonCount(0) {}

    void sort() {
        comparisonCount = 0;
        if (arraySize < 2) return;

        for (int i = 1; i < arraySize; ++i) {
            int j = i;

            while (j > 0 && isLessThan(data[j], data[j-1])) {
                swap(j, j - 1);
                j--;
            }
        }
    }


    long long getComparisonCount() const {
        return comparisonCount;
    }
};

void printArray(const int* arr, int size, const std::string& label) {
    std::cout << label;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << (i == size - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

int main() {
    const int N = 20;

    int* worstCaseArray = generateWorstCase(N);
    printArray(worstCaseArray, N, "Worst Case (Before Sort): ");

    InsertionSort sorterWorst(worstCaseArray, N);
    sorterWorst.sort();
    
    printArray(worstCaseArray, N, "Worst Case (After Sort):  ");
    std::cout << "Comparisons for Worst Case: " << sorterWorst.getComparisonCount() << std::endl;
    std::cout << "Theoretical worst case comparisons for n=" << N << ": O(N^2) ~ " << N*(N-1)/2 << " (for this implementation)" << std::endl;
    std::cout << std::endl;

    delete[] worstCaseArray;

    int* bestCaseArray = generateBestCase(N);
    printArray(bestCaseArray, N, "Best Case (Before Sort):  ");

    InsertionSort sorterBest(bestCaseArray, N);
    sorterBest.sort();

    printArray(bestCaseArray, N, "Best Case (After Sort):   ");
    std::cout << "Comparisons for Best Case: " << sorterBest.getComparisonCount() << std::endl;
    std::cout << "Theoretical best case comparisons for n=" << N << ": O(N) ~ " << N-1 << " (for this implementation)" << std::endl;

    delete[] bestCaseArray;

    return 0;
}