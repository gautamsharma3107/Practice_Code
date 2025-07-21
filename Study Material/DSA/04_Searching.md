# Searching Algorithms

This document provides an in-depth exploration of various searching algorithms, their implementations in C++, time and space complexity analysis, and problem exercises to enhance understanding and practical application.

## 1. Linear Search
- **Description**: A simple searching algorithm that sequentially checks each element in a collection until the target element is found or the entire collection has been traversed.
- **Time Complexity**: 
  - Best Case: O(1) - when the element is found at the first position
  - Average Case: O(n/2) - simplifies to O(n)
  - Worst Case: O(n) - when the element is at the last position or not present
- **Space Complexity**: O(1) - requires constant extra space

### Implementation
```cpp
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Return the index of the target
        }
    }
    return -1; // Target not found
}
```

### Enhanced Implementation with Template
```cpp
template <typename T>
int linearSearch(T arr[], int size, T target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Return the index of the target
        }
    }
    return -1; // Target not found
}
```

### Example Usage
```cpp
#include <iostream>
#include <string>
using namespace std;

template <typename T>
int linearSearch(T arr[], int size, T target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    int intArray[] = {10, 20, 30, 40, 50};
    string strArray[] = {"apple", "banana", "cherry", "date", "elderberry"};
    
    int intResult = linearSearch(intArray, 5, 30);
    int strResult = linearSearch(strArray, 5, string("cherry"));
    
    cout << "Integer 30 found at index: " << intResult << endl;
    cout << "String 'cherry' found at index: " << strResult << endl;
    
    return 0;
}
```

### When to Use Linear Search
- When the array is unsorted
- When the array is small
- When performing a single search operation
- When searching in data structures that only allow sequential access

### Problem Exercises
1. **Find Frequency**: Write a function to find the frequency of a given element in an array
2. **Find Min/Max**: Implement a function to find the minimum and maximum values in an unsorted array
3. **Find Multiple Occurrences**: Return all indices where a target element appears
4. [Linear Search Problem 1](https://example.com/linear-search-problem1)
5. [Linear Search Problem 2](https://example.com/linear-search-problem2)

## 2. Binary Search
- **Description**: An efficient algorithm for finding an element in a sorted array by repeatedly dividing the search interval in half.
- **Time Complexity**: 
  - Best Case: O(1) - when the element is at the middle
  - Average and Worst Case: O(log n)
- **Space Complexity**: 
  - Iterative: O(1)
  - Recursive: O(log n) due to call stack

### Iterative Implementation
```cpp
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        // Use this instead of (left + right) / 2 to avoid potential overflow
        int mid = left + (right - left) / 2;
        
        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }
        
        // If target is greater, ignore left half
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Element is not present
    return -1;
}
```

### Recursive Implementation
```cpp
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        
        // If the element is present at the middle
        if (arr[mid] == target) {
            return mid;
        }
        
        // If element is smaller than mid, search in left subarray
        if (arr[mid] > target) {
            return binarySearchRecursive(arr, left, mid - 1, target);
        }
        
        // Else search in right subarray
        return binarySearchRecursive(arr, mid + 1, right, target);
    }
    
    // Element is not present
    return -1;
}
```

### Example Usage
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for std::binary_search
using namespace std;

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int sortedArray[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int size = sizeof(sortedArray) / sizeof(sortedArray[0]);
    
    int result = binarySearch(sortedArray, size, 60);
    
    if (result != -1) {
        cout << "Element found at index " << result << endl;
    } else {
        cout << "Element not found in the array" << endl;
    }
    
    // Using C++ Standard Library
    vector<int> vec = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    bool found = binary_search(vec.begin(), vec.end(), 60);
    cout << "Element " << (found ? "found" : "not found") << " using std::binary_search" << endl;
    
    return 0;
}
```

### Common Binary Search Variations
1. **Finding First Occurrence**:
```cpp
int findFirstOccurrence(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid; // Save this result
            right = mid - 1; // Continue searching on the left side
        } 
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    
    return result;
}
```

2. **Finding Last Occurrence**:
```cpp
int findLastOccurrence(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid; // Save this result
            left = mid + 1; // Continue searching on the right side
        } 
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    
    return result;
}
```

### Problem Exercises
1. **Finding Bounds**: Implement functions to find the upper and lower bounds of a value in a sorted array
2. **Rotated Array Search**: Search for an element in a sorted but rotated array
3. **Square Root**: Implement a function to find the square root of a number using binary search
4. **Peak Element**: Find a peak element in an array (an element greater than its neighbors)
5. [Binary Search Problem 1](https://example.com/binary-search-problem1)
6. [Binary Search Problem 2](https://example.com/binary-search-problem2)

## 3. Interpolation Search
- **Description**: An improvement over binary search for uniformly distributed sorted arrays, which estimates the likely position of the target value
- **Time Complexity**: 
  - Average Case: O(log log n) - when elements are uniformly distributed
  - Worst Case: O(n) - when elements are exponentially distributed
- **Space Complexity**: O(1)

### Implementation
```cpp
int interpolationSearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) {
                return low;
            }
            return -1;
        }
        
        // Formula to estimate the position
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);
        
        if (arr[pos] == target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1; // Target not found
}
```

### Example Usage
```cpp
#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        
        // Probing position with uniform distribution
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);
        
        if (arr[pos] == target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

int main() {
    // Uniformly distributed array
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 70;
    
    int index = interpolationSearch(arr, size, target);
    
    if (index != -1) {
        cout << "Element " << target << " found at index " << index << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }
    
    return 0;
}
```

### When to Use Interpolation Search
- When the elements in the array are uniformly distributed
- When the array is sorted
- When searching large arrays where binary search might be too slow

### Problem Exercises
1. **Compare Performance**: Implement a program that compares the performance of interpolation search vs binary search on different types of distributions
2. **Adaptive Search**: Create a hybrid search algorithm that uses interpolation search for uniform distributions and binary search for others
3. [Interpolation Search Problem 1](https://example.com/interpolation-search-problem1)
4. [Interpolation Search Problem 2](https://example.com/interpolation-search-problem2)

## 4. Jump Search
- **Description**: A searching algorithm for sorted arrays that jumps ahead by fixed steps and then performs a linear search within the block
- **Time Complexity**: O(√n) - optimal jump size is √n
- **Space Complexity**: O(1)

### Implementation
```cpp
#include <cmath>
#include <algorithm> // For std::min

int jumpSearch(int arr[], int size, int target) {
    int jump = sqrt(size);
    int prev = 0;
    
    // Finding the block where element may be present
    while (prev < size && arr[min(jump, size) - 1] < target) {
        prev = jump;
        jump += sqrt(size);
        if (prev >= size) {
            return -1;
        }
    }
    
    // Linear search within the identified block
    while (prev < min(jump, size)) {
        if (arr[prev] == target) {
            return prev;
        }
        prev++;
    }
    
    return -1; // Target not found
}
```

### Example Usage
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int jumpSearch(int arr[], int size, int target) {
    int jump = sqrt(size);
    int prev = 0;
    
    // Find the block where element may be present
    while (prev < size && arr[min(jump, size) - 1] < target) {
        prev = jump;
        jump += sqrt(size);
        if (prev >= size) {
            return -1;
        }
    }
    
    // Linear search within the block
    while (prev < min(jump, size)) {
        if (arr[prev] == target) {
            return prev;
        }
        prev++;
    }
    
    return -1;
}

int main() {
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 55;
    
    int index = jumpSearch(arr, size, target);
    
    if (index != -1) {
        cout << "Element " << target << " found at index " << index << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }
    
    return 0;
}
```

### When to Use Jump Search
- When the array is sorted
- When jumping forward and backward operations are costly
- When binary search has too much overhead for simple searches

### Problem Exercises
1. **Optimize Jump Size**: Experiment with different jump sizes and analyze the impact on performance
2. **Backward Jump Search**: Implement a variation that can jump backward efficiently
3. [Jump Search Problem 1](https://example.com/jump-search-problem1)
4. [Jump Search Problem 2](https://example.com/jump-search-problem2)

## 5. Exponential Search
- **Description**: A searching algorithm that works on sorted arrays, combining exponential jumps with binary search to find the range for binary search
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1) for iterative implementation, O(log n) for recursive binary search

### Implementation
```cpp
#include <algorithm> // For std::min

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int exponentialSearch(int arr[], int size, int target) {
    // If target is at the first position
    if (arr[0] == target) {
        return 0;
    }
    
    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < size && arr[i] <= target) {
        i *= 2;
    }
    
    // Perform binary search on the identified range
    return binarySearch(arr, i / 2, min(i, size - 1), target);
}
```

### Example Usage
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int exponentialSearch(int arr[], int size, int target) {
    // If target is at first position
    if (arr[0] == target) {
        return 0;
    }
    
    // Find range for binary search
    int i = 1;
    while (i < size && arr[i] <= target) {
        i *= 2;
    }
    
    // Call binary search for the found range
    return binarySearch(arr, i / 2, min(i, size - 1), target);
}

int main() {
    int arr[] = {2, 3, 4, 10, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 70;
    
    int index = exponentialSearch(arr, size, target);
    
    if (index != -1) {
        cout << "Element " << target << " found at index " << index << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }
    
    return 0;
}
```

### When to Use Exponential Search
- When searching in unbounded or infinite arrays
- When the target element is likely to be located near the beginning of the array
- When you need a sub-linear search algorithm but don't know the range

### Problem Exercises
1. **Unbounded Search**: Use exponential search to locate an element in an infinitely sized sorted array
2. **First and Last Occurrence**: Modify exponential search to find the first and last occurrence of an element
3. [Exponential Search Problem 1](https://example.com/exponential-search-problem1)
4. [Exponential Search Problem 2](https://example.com/exponential-search-problem2)

## 6. Fibonacci Search
- **Description**: A comparison-based search algorithm that uses Fibonacci numbers to divide the array
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1)

### Implementation
```cpp
#include <algorithm> // For std::min

int fibonacciSearch(int arr[], int size, int target) {
    // Initialize Fibonacci numbers
    int fibMMm2 = 0; // (m-2)'th Fibonacci number
    int fibMMm1 = 1; // (m-1)'th Fibonacci number
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci number
    
    // Find the smallest Fibonacci number greater than or equal to size
    while (fibM < size) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    
    // Marks the eliminated range from front
    int offset = -1;
    
    // While there are elements to be inspected
    while (fibM > 1) {
        // Check if fibMMm2 is a valid location
        int i = min(offset + fibMMm2, size - 1);
        
        // If target is greater than the value at index fibMMm2,
        // cut the subarray from offset to i
        if (arr[i] < target) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        // If target is less than the value at index fibMMm2,
        // cut the subarray after i+1
        else if (arr[i] > target) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        // Element found
        else {
            return i;
        }
    }
    
    // Compare the last element
    if (fibMMm1 && arr[offset + 1] == target) {
        return offset + 1;
    }
    
    // Element not found
    return -1;
}
```

### Example Usage
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int fibonacciSearch(int arr[], int size, int target) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    
    while (fibM < size) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    
    int offset = -1;
    
    while (fibM > 1) {
        int i = min(offset + fibMMm2, size - 1);
        
        if (arr[i] < target) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i] > target) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            return i;
        }
    }
    
    if (fibMMm1 && arr[offset + 1] == target) {
        return offset + 1;
    }
    
    return -1;
}

int main() {
    int arr[] = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 85;
    
    int index = fibonacciSearch(arr, size, target);
    
    if (index != -1) {
        cout << "Element " << target << " found at index " << index << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }
    
    return 0;
}
```

### When to Use Fibonacci Search
- When binary search operations are expensive
- When the array is stored on disk or external storage
- When division operation is expensive (uses only addition and subtraction)

### Problem Exercises
1. **Compare with Binary Search**: Write a program to compare the performance of Fibonacci search vs binary search
2. **Memory-Efficient Search**: Implement a variation that minimizes memory usage
3. [Fibonacci Search Problem 1](https://example.com/fibonacci-search-problem1)

## Conclusion
Understanding various searching algorithms is crucial for efficient data retrieval and solving complex problems. Each algorithm has its strengths and ideal use cases:

- **Linear Search**: Simple but inefficient for large datasets; best for unsorted arrays
- **Binary Search**: Highly efficient for sorted arrays with O(log n) complexity
- **Interpolation Search**: Excellent for uniformly distributed sorted data
- **Jump Search**: Good middle ground between linear and binary search
- **Exponential Search**: Efficient for unbounded arrays and when elements are near the beginning
- **Fibonacci Search**: Useful when division operations are costly

Practice the provided exercises to solidify your understanding and improve your algorithm implementation skills. Remember that choosing the right algorithm for your specific use case can significantly impact performance.