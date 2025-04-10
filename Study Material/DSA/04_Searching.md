# Searching Algorithms

This document covers various searching algorithms, their implementations, and problem exercises to enhance understanding and application.

## 1. Linear Search
- **Description**: A simple searching algorithm that checks each element in the list until the desired element is found or the list ends.
- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

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

### Problem Exercises
- [Linear Search Problem 1](https://example.com/linear-search-problem1)
- [Linear Search Problem 2](https://example.com/linear-search-problem2)

## 2. Binary Search
- **Description**: A more efficient algorithm that works on sorted arrays by repeatedly dividing the search interval in half.
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1)

### Implementation
```cpp
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Return the index of the target
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Target not found
}
```

### Problem Exercises
- [Binary Search Problem 1](https://example.com/binary-search-problem1)
- [Binary Search Problem 2](https://example.com/binary-search-problem2)

## 3. Interpolation Search
- **Description**: An improvement over binary search for uniformly distributed sorted arrays, estimating the position of the target.
- **Time Complexity**: O(log log n) on average, O(n) in the worst case
- **Space Complexity**: O(1)

### Implementation
```cpp
int interpolationSearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        int pos = low + ((double)(high - low) / (arr[high] - arr[low]) * (target - arr[low]));
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

### Problem Exercises
- [Interpolation Search Problem 1](https://example.com/interpolation-search-problem1)
- [Interpolation Search Problem 2](https://example.com/interpolation-search-problem2)

## 4. Jump Search
- **Description**: A searching algorithm for sorted arrays that jumps ahead by fixed steps and then performs a linear search within the block.
- **Time Complexity**: O(√n)
- **Space Complexity**: O(1)

### Implementation
```cpp
int jumpSearch(int arr[], int size, int target) {
    int jump = sqrt(size);
    int prev = 0;
    while (arr[min(jump, size) - 1] < target) {
        prev = jump;
        jump += sqrt(size);
        if (prev >= size) return -1;
    }
    while (arr[prev] < target) {
        prev++;
        if (prev == min(jump, size)) return -1;
    }
    if (arr[prev] == target) return prev;
    return -1; // Target not found
}
```

### Problem Exercises
- [Jump Search Problem 1](https://example.com/jump-search-problem1)
- [Jump Search Problem 2](https://example.com/jump-search-problem2)

## 5. Exponential Search
- **Description**: A searching algorithm that works on sorted arrays, combining binary search with exponential growth to find the range for binary search.
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1)

### Implementation
```cpp
int exponentialSearch(int arr[], int size, int target) {
    if (arr[0] == target) return 0;
    int i = 1;
    while (i < size && arr[i] <= target) {
        i *= 2;
    }
    return binarySearch(arr, min(i, size), target);
}
```

### Problem Exercises
- [Exponential Search Problem 1](https://example.com/exponential-search-problem1)
- [Exponential Search Problem 2](https://example.com/exponential-search-problem2)

## Conclusion
Understanding these searching algorithms is crucial for efficient data retrieval. Practice the exercises linked above to solidify your knowledge and improve your problem-solving skills.