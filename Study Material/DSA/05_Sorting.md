# Sorting Algorithms

Sorting algorithms are fundamental algorithms in computer science that arrange the elements of a list or array in a specific order, typically in ascending or descending order. This document covers various sorting algorithms, their implementations, and problem exercises to practice.

## 1. Bubble Sort
- **Description**: A simple comparison-based algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
- **Time Complexity**: O(n^2) in the worst and average cases, O(n) in the best case (when the array is already sorted).
- **Space Complexity**: O(1)

### Implementation
```cpp
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
```

### Problem Exercises
- [Bubble Sort Practice Problems](https://www.geeksforgeeks.org/selection-sort/)
- [LeetCode: Sort Colors](https://leetcode.com/problems/sort-colors/)

## 2. Selection Sort
- **Description**: An in-place comparison sorting algorithm that divides the input list into two parts: a sorted and an unsorted part. It repeatedly selects the smallest (or largest) element from the unsorted part and moves it to the sorted part.
- **Time Complexity**: O(n^2) for all cases.
- **Space Complexity**: O(1)

### Implementation
```cpp
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}
```

### Problem Exercises
- [Selection Sort Practice Problems](https://www.geeksforgeeks.org/selection-sort/)
- [LeetCode: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

## 3. Insertion Sort
- **Description**: Builds a sorted array one element at a time by repeatedly taking the next element from the input data and inserting it into the correct position in the sorted part of the array.
- **Time Complexity**: O(n^2) in the worst and average cases, O(n) in the best case (when the array is already sorted).
- **Space Complexity**: O(1)

### Implementation
```cpp
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

### Problem Exercises
- [Insertion Sort Practice Problems](https://www.geeksforgeeks.org/insertion-sort/)
- [LeetCode: Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)

## 4. Merge Sort
- **Description**: A divide-and-conquer algorithm that divides the unsorted list into n sublists, each containing one element, and then repeatedly merges sublists to produce new sorted sublists until there is only one sublist remaining.
- **Time Complexity**: O(n log n) for all cases.
- **Space Complexity**: O(n)

### Implementation
```cpp
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
```

### Problem Exercises
- [Merge Sort Practice Problems](https://www.geeksforgeeks.org/merge-sort/)
- [LeetCode: Merge Intervals](https://leetcode.com/problems/merge-intervals/)

## 5. Quick Sort
- **Description**: A divide-and-conquer algorithm that selects a 'pivot' element from the array and partitions the other elements into two sub-arrays according to whether they are less than or greater than the pivot.
- **Time Complexity**: O(n log n) on average, O(n^2) in the worst case.
- **Space Complexity**: O(log n) for the recursive stack.

### Implementation
```cpp
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

### Problem Exercises
- [Quick Sort Practice Problems](https://www.geeksforgeeks.org/quick-sort/)
- [LeetCode: Sort an Array](https://leetcode.com/problems/sort-an-array/)

## 6. Heap Sort
- **Description**: A comparison-based sorting technique based on a binary heap data structure. It first builds a max heap from the input data and then repeatedly extracts the maximum element from the heap and rebuilds the heap.
- **Time Complexity**: O(n log n) for all cases.
- **Space Complexity**: O(1)

### Implementation
```cpp
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

### Problem Exercises
- [Heap Sort Practice Problems](https://www.geeksforgeeks.org/heap-sort/)
- [LeetCode: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

## 7. Radix Sort
- **Description**: A non-comparison-based sorting algorithm that sorts numbers by processing individual digits. It works by distributing the numbers into buckets based on each digit's value.
- **Time Complexity**: O(nk), where n is the number of elements and k is the number of digits in the largest number.
- **Space Complexity**: O(n + k)

### Implementation
```cpp
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}
```

### Problem Exercises
- [Radix Sort Practice Problems](https://www.geeksforgeeks.org/radix-sort/)
- [LeetCode: Sort an Array](https://leetcode.com/problems/sort-an-array/)

## 8. Counting Sort
- **Description**: A non-comparison-based sorting algorithm that counts the number of occurrences of each unique element in the input array and uses this information to place each element in its correct position.
- **Time Complexity**: O(n + k), where n is the number of elements and k is the range of the input.
- **Space Complexity**: O(k)

### Implementation
```cpp
void countingSort(int arr[], int n) {
    int output[n];
    int count[256] = {0};
    for (int i = 0; i < n; ++i)
        count[arr[i]]++;
    for (int i = 1; i < 256; ++i)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
```

### Problem Exercises
- [Counting Sort Practice Problems](https://www.geeksforgeeks.org/counting-sort/)
- [LeetCode: Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)

## Conclusion
Sorting algorithms are essential for organizing data efficiently. Understanding their implementations and complexities is crucial for optimizing performance in various applications. Practice the exercises linked above to strengthen your understanding of sorting algorithms.