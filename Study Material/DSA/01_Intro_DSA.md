# DSA/01_Intro_DSA.md

# Introduction to Data Structures and Algorithms

## 1. Algorithm Definition and Characteristics
- **Definition**: An algorithm is a step-by-step procedure or formula for solving a problem.
- **Characteristics**:
  - **Finiteness**: An algorithm must always terminate after a finite number of steps.
  - **Definiteness**: Each step of the algorithm must be precisely defined.
  - **Input**: An algorithm can have zero or more inputs.
  - **Output**: An algorithm can produce one or more outputs.
  - **Effectiveness**: The operations to be performed must be basic enough to be done in a finite amount of time.

## 2. Algorithm Analysis
- **Purpose**: To evaluate the efficiency of an algorithm in terms of time and space.
- **Types of Analysis**:
  - **Worst-case analysis**: The maximum time taken by an algorithm for any input of size n.
  - **Best-case analysis**: The minimum time taken by an algorithm for any input of size n. This represents the ideal scenario when the input is in the most favorable configuration.
    - *Example*: In a sorted array, the best-case for linear search is O(1) when the element is at the first position.
  - **Average-case analysis**: The expected time taken by an algorithm for a random input of size n. This often requires probabilistic analysis.
    - *Example*: For quicksort, the average-case time complexity is O(n log n), assuming random pivot selection.

## 3. Time Complexity
- **Definition**: Time complexity is a computational complexity that describes the amount of time it takes to run an algorithm as a function of the length of the input.
- **Common Time Complexities**:
  - **Constant Time: O(1)**: Execution time remains constant regardless of input size.
    - *Example*: Accessing an array element by index.
    ```cpp
    // O(1) - Constant time example
    int getElement(int arr[], int index) {
        return arr[index]; // Direct access - constant time
    }
    ```

  - **Logarithmic Time: O(log n)**: Execution time grows logarithmically as input size increases. Usually seen in algorithms that divide the problem in half each time.
    - *Example*: Binary search in a sorted array.
    ```cpp
    // O(log n) - Binary search example
    int binarySearch(int arr[], int left, int right, int target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target)
                return mid;  // Found the element
                
            if (arr[mid] < target)
                left = mid + 1;  // Search in the right half
            else
                right = mid - 1;  // Search in the left half
        }
        return -1;  // Element not found
    }
    ```

  - **Linear Time: O(n)**: Execution time grows linearly with input size.
    - *Example*: Finding the maximum element in an unsorted array.
    ```cpp
    // O(n) - Linear time example
    int findMax(int arr[], int size) {
        int max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }
    ```

  - **Linearithmic Time: O(n log n)**: Efficient sorting algorithms typically have this complexity.
    - *Example*: Merge sort algorithm.
    ```cpp
    // O(n log n) - Merge sort example
    void merge(int arr[], int left, int mid, int right) {
        // Implementation of merge operation
        // ...
    }
    
    void mergeSort(int arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            // Sort first and second halves
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            
            // Merge the sorted halves
            merge(arr, left, mid, right);
        }
    }
    ```

  - **Quadratic Time: O(n²)**: Execution time grows quadratically with input size.
    - *Example*: Bubble sort algorithm.
    ```cpp
    // O(n²) - Bubble sort example
    void bubbleSort(int arr[], int n) {
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (arr[j] > arr[j+1]) {
                    // Swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
    ```

  - **Exponential Time: O(2ⁿ)**: Execution time doubles with each addition to the input.
    - *Example*: Recursive calculation of Fibonacci numbers without memoization.
    ```cpp
    // O(2ⁿ) - Exponential time example
    int fibonacci(int n) {
        if (n <= 1)
            return n;
        return fibonacci(n-1) + fibonacci(n-2);
    }
    ```

  - **Factorial Time: O(n!)**: Among the slowest growing complexities.
    - *Example*: Brute force solution to the traveling salesman problem.
    ```cpp
    // O(n!) - Generating all permutations example
    void generatePermutations(string str, int l, int r) {
        if (l == r)
            cout << str << endl;
        else {
            for (int i = l; i <= r; i++) {
                swap(str[l], str[i]);
                generatePermutations(str, l+1, r);
                swap(str[l], str[i]); // backtrack
            }
        }
    }
    ```

## 4. Space Complexity
- **Definition**: Space complexity is the amount of memory space required by an algorithm to execute as a function of the length of the input.
- **Components**:
  - **Fixed Part**: Space required for constants, simple variables, fixed-size variable components, etc.
  - **Variable Part**: Space required for dynamically allocated memory, recursion stack space, etc.

- **Examples**:
  - **O(1) - Constant Space**: 
    ```cpp
    // Constant space example
    int sum(int arr[], int n) {
        int result = 0;  // Only one variable regardless of input size
        for (int i = 0; i < n; i++) {
            result += arr[i];
        }
        return result;
    }
    ```

  - **O(n) - Linear Space**:
    ```cpp
    // Linear space example
    int* duplicateArray(int arr[], int n) {
        int* result = new int[n];  // Space grows linearly with input
        for (int i = 0; i < n; i++) {
            result[i] = arr[i];
        }
        return result;
    }
    ```

  - **O(n²) - Quadratic Space**:
    ```cpp
    // Quadratic space example
    int** createAdjacencyMatrix(int n) {
        int** matrix = new int*[n];  // Space grows quadratically with input
        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 0;
            }
        }
        return matrix;
    }
    ```

## 5. Asymptotic Notation
- **Purpose**: To describe the limiting behavior of an algorithm's time or space complexity.
- **Common Notations**:
  - **Big O Notation (O)**: Describes the upper bound of the time complexity. It represents the worst-case scenario.
    - *Example*: If f(n) = 3n² + 2n + 1, then f(n) = O(n²).
    
  - **Omega Notation (Ω)**: Describes the lower bound of the time complexity. It represents the best-case scenario.
    - *Example*: For a linear search, Ω(1) represents the best case when the element is found at the first position.
    
  - **Theta Notation (Θ)**: Describes the tight bound of the time complexity. It represents both upper and lower bounds.
    - *Example*: For merge sort, Θ(n log n) indicates that the algorithm always performs at this complexity regardless of input arrangement.

- **Comparison Example**:
  ```cpp
  // Linear search algorithm
  int linearSearch(int arr[], int n, int target) {
      // Best-case: O(1) - Target is the first element
      // Worst-case: O(n) - Target is the last element or not present
      // Average-case: O(n) - Target could be anywhere
      for (int i = 0; i < n; i++) {
          if (arr[i] == target)
              return i;
      }
      return -1;
  }
  ```

## 6. Recurrence Relations
- **Definition**: Equations that describe the time complexity of algorithms in terms of their recursive calls.
- **Common Forms**:
  - **Binary Recursive Algorithms**: T(n) = 2T(n/2) + f(n)
    - *Example*: Merge sort with T(n) = 2T(n/2) + O(n) yields T(n) = O(n log n)
  - **Divide and Conquer**: T(n) = aT(n/b) + f(n)
    - *Example*: Binary search with T(n) = T(n/2) + O(1) yields T(n) = O(log n)

## 7. Problem Exercises

### Exercise 1: Finding Maximum of Three Numbers
Write a simple algorithm to find the maximum of three numbers and analyze its time complexity.

```cpp
// Time Complexity: O(1) - constant operations regardless of input values
int findMaxOfThree(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}
```

**Analysis**: This function performs a fixed number of comparisons (2 at most) regardless of the values of the inputs. Therefore, the time complexity is O(1) - constant time.

### Exercise 2: Factorial Calculation with Recursion
Implement a function that calculates the factorial of a number using recursion and analyze its space complexity.

```cpp
// Time Complexity: O(n)
// Space Complexity: O(n) due to the recursion stack
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n-1);
}
```

**Analysis**: 
- **Time Complexity**: O(n) as we make n recursive calls.
- **Space Complexity**: O(n) due to the recursion stack that grows linearly with the input size.

### Exercise 3: Bubble Sort Implementation
Create an algorithm that sorts an array of integers using bubble sort and discuss its time complexity.

```cpp
// Time Complexity: 
// - Worst-case: O(n²) when array is reverse sorted
// - Best-case: O(n) when array is already sorted (with optimization)
// - Average-case: O(n²)
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        // If no swaps occurred in this pass, the array is sorted
        if (!swapped) break;
    }
}
```

**Analysis**:
- **Worst-case**: O(n²) when the array is sorted in reverse order, requiring maximum number of comparisons and swaps.
- **Best-case**: O(n) when the array is already sorted (with the optimization of breaking when no swaps occur).
- **Average-case**: O(n²) for random arrangements of data.

### Exercise 4: Binary Search Implementation
Analyze the time complexity of binary search and implement it in C++.

```cpp
// Time Complexity: O(log n)
// Space Complexity: O(1) for iterative version, O(log n) for recursive version
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if target is present at mid
        if (arr[mid] == target)
            return mid;
            
        // If target greater, ignore left half
        if (arr[mid] < target)
            left = mid + 1;
        // If target smaller, ignore right half
        else
            right = mid - 1;
    }
    
    // Target not present in array
    return -1;
}
```

**Analysis**:
- **Time Complexity**: O(log n) because in each step we divide the search space in half.
- **Space Complexity**: O(1) for the iterative version as we use constant extra space.

### Exercise 5: Linear Search vs Binary Search
Compare the time complexities of linear search and binary search. Implement both algorithms and discuss their use cases.

**Linear Search**:
```cpp
// Time Complexity: O(n)
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1; // Not found
}
```

**Binary Search**:
```cpp
// Time Complexity: O(log n)
// Requires sorted array
int binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return mid;
            
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1; // Not found
}
```

**Comparison**:
- **Linear Search**:
  - Time Complexity: O(n)
  - Works on both sorted and unsorted arrays
  - Simpler implementation
  - Preferred for small datasets or when searching once in an unsorted array
  
- **Binary Search**:
  - Time Complexity: O(log n)
  - Requires sorted array
  - More complex implementation
  - Much faster for large datasets
  - Worth sorting first if multiple searches will be performed

**Testing with Large Dataset**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void testSearchAlgorithms(int size) {
    // Create and fill array with random values
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000000;
    }
    
    // Sort array for binary search
    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());
    
    // Value to search for (exists in array)
    int target = sortedArr[size/2];
    
    // Test linear search
    auto start = std::chrono::high_resolution_clock::now();
    linearSearch(&arr[0], size, target);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Linear Search time: " << duration.count() << " microseconds" << std::endl;
    
    // Test binary search
    start = std::chrono::high_resolution_clock::now();
    binarySearch(&sortedArr[0], size, target);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Binary Search time: " << duration.count() << " microseconds" << std::endl;
}

int main() {
    testSearchAlgorithms(1000000); // Test with 1 million elements
    return 0;
}