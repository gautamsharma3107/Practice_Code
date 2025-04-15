# Sorting Algorithms

Sorting algorithms are fundamental algorithms in computer science that arrange the elements of a list or array in a specific order, typically in ascending or descending order. This comprehensive guide covers various sorting algorithms, their implementations, step-by-step examples, and practice exercises.

## 1. Bubble Sort

### Description
Bubble Sort is a simple comparison-based sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The process is repeated until no more swaps are needed, indicating that the list is sorted. The algorithm gets its name because smaller elements "bubble" to the top of the list with each iteration.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n) when the array is already sorted (with optimization)
  - Average Case: O(n²)
  - Worst Case: O(n²) when the array is reverse sorted
- **Space Complexity**: O(1) as it only requires a temporary variable for swapping
- **Stability**: Stable (preserves the relative order of equal elements)

### Implementation
```cpp
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // If no swapping occurred in this pass, array is sorted
        if (!swapped)
            break;
    }
}
```

### Step-by-Step Example
Consider the array: `[5, 1, 4, 2, 8]`

**First Pass:**
- Compare 5 > 1: Swap → `[1, 5, 4, 2, 8]`
- Compare 5 > 4: Swap → `[1, 4, 5, 2, 8]`
- Compare 5 > 2: Swap → `[1, 4, 2, 5, 8]`
- Compare 5 > 8: No swap → `[1, 4, 2, 5, 8]`

**Second Pass:**
- Compare 1 > 4: No swap → `[1, 4, 2, 5, 8]`
- Compare 4 > 2: Swap → `[1, 2, 4, 5, 8]`
- Compare 4 > 5: No swap → `[1, 2, 4, 5, 8]`
- Compare 5 > 8: No swap → `[1, 2, 4, 5, 8]`

**Third Pass:**
- No swaps occur, algorithm terminates → `[1, 2, 4, 5, 8]` is sorted

### When to Use Bubble Sort
- Educational purposes to understand basic sorting concepts
- When the array is almost sorted
- When simplicity is more important than efficiency
- When space is a major constraint

### Problem Exercises
- [Bubble Sort Practice Problems](https://www.geeksforgeeks.org/bubble-sort/)
- [LeetCode: Sort Colors](https://leetcode.com/problems/sort-colors/)

## 2. Selection Sort

### Description
Selection Sort is an in-place comparison sorting algorithm that divides the input list into two parts: a sorted sublist built up from left to right and the remaining unsorted sublist. It repeatedly selects the smallest (or largest) element from the unsorted sublist, swaps it with the leftmost unsorted element, and moves the sublist boundaries one element to the right.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n²)
  - Average Case: O(n²)
  - Worst Case: O(n²)
- **Space Complexity**: O(1) as it only uses a constant amount of extra space
- **Stability**: Not stable (relative order of equal elements may change)

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
        // Swap the found minimum element with the element at index i
        if (minIndex != i) {
            swap(arr[minIndex], arr[i]);
        }
    }
}
```

### Step-by-Step Example
Consider the array: `[64, 25, 12, 22, 11]`

**First Pass:**
- Find minimum in `[64, 25, 12, 22, 11]`: 11 at index 4
- Swap 64 and 11: `[11, 25, 12, 22, 64]`

**Second Pass:**
- Find minimum in `[25, 12, 22, 64]`: 12 at index 2
- Swap 25 and 12: `[11, 12, 25, 22, 64]`

**Third Pass:**
- Find minimum in `[25, 22, 64]`: 22 at index 3
- Swap 25 and 22: `[11, 12, 22, 25, 64]`

**Fourth Pass:**
- Find minimum in `[25, 64]`: 25 at index 3
- No swap needed: `[11, 12, 22, 25, 64]`

**Fifth Pass:**
- Only one element remains, sorting is complete: `[11, 12, 22, 25, 64]`

### When to Use Selection Sort
- When memory writes are expensive (as it makes O(n) swaps)
- When the array size is small
- When simplicity is desired over efficiency
- When auxiliary memory is limited

### Problem Exercises
- [Selection Sort Practice Problems](https://www.geeksforgeeks.org/selection-sort/)
- [LeetCode: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

## 3. Insertion Sort

### Description
Insertion Sort builds the final sorted array one item at a time. It iterates through an array, consuming one input element at each step and growing a sorted output list. At each iteration, it removes one element from the input data, finds its correct position within the sorted list, and inserts it there. It operates much like sorting playing cards in your hands.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n) when the array is already sorted
  - Average Case: O(n²)
  - Worst Case: O(n²) when the array is reverse sorted
- **Space Complexity**: O(1) as it sorts in-place
- **Stability**: Stable (preserves the relative order of equal elements)

### Implementation
```cpp
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Element to be inserted
        int j = i - 1;
        
        // Move elements greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Insert the key at its correct position
    }
}
```

### Step-by-Step Example
Consider the array: `[12, 11, 13, 5, 6]`

**Initial state**: `[12]` is considered sorted

**Insert 11:**
- Compare 11 < 12: Shift 12 right → `[_, 12]`
- Insert 11 at position 0: `[11, 12]`

**Insert 13:**
- Compare 13 > 12: No shift needed
- Insert 13 at position 2: `[11, 12, 13]`

**Insert 5:**
- Compare 5 < 13: Shift 13 right → `[11, 12, _, 13]`
- Compare 5 < 12: Shift 12 right → `[11, _, 12, 13]`
- Compare 5 < 11: Shift 11 right → `[_, 11, 12, 13]`
- Insert 5 at position 0: `[5, 11, 12, 13]`

**Insert 6:**
- Compare 6 < 13: Shift 13 right → `[5, 11, 12, _, 13]`
- Compare 6 < 12: Shift 12 right → `[5, 11, _, 12, 13]`
- Compare 6 < 11: Shift 11 right → `[5, _, 11, 12, 13]`
- Compare 6 > 5: No shift needed
- Insert 6 at position 1: `[5, 6, 11, 12, 13]`

### When to Use Insertion Sort
- Small data sets or nearly sorted data
- Online sorting (elements are sorted as they come)
- When additional elements arrive one at a time
- Adaptive sorting (performs better when data is partially sorted)

### Problem Exercises
- [Insertion Sort Practice Problems](https://www.geeksforgeeks.org/insertion-sort/)
- [LeetCode: Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)

## 4. Merge Sort

### Description
Merge Sort is a divide-and-conquer algorithm that divides the input array into two halves, recursively sorts them, and then merges the sorted halves. The key process is the merging of two sorted subarrays to produce a single sorted array.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n log n)
- **Space Complexity**: O(n) due to the temporary arrays used in merging
- **Stability**: Stable (preserves the relative order of equal elements)

### Implementation
```cpp
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *L = new int[n1];
    int *R = new int[n2];
    
    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    
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
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}
```

### Step-by-Step Example
Consider the array: `[38, 27, 43, 3, 9, 82, 10]`

**Divide Phase:**
1. Split into `[38, 27, 43, 3]` and `[9, 82, 10]`
2. Split `[38, 27, 43, 3]` into `[38, 27]` and `[43, 3]`
3. Split `[38, 27]` into `[38]` and `[27]`
4. Split `[43, 3]` into `[43]` and `[3]`
5. Split `[9, 82, 10]` into `[9]` and `[82, 10]`
6. Split `[82, 10]` into `[82]` and `[10]`

**Merge Phase:**
1. Merge `[38]` and `[27]` → `[27, 38]`
2. Merge `[43]` and `[3]` → `[3, 43]`
3. Merge `[27, 38]` and `[3, 43]` → `[3, 27, 38, 43]`
4. Merge `[9]` and `[10, 82]` → `[9, 10, 82]`
5. Merge `[3, 27, 38, 43]` and `[9, 10, 82]` → `[3, 9, 10, 27, 38, 43, 82]`

### When to Use Merge Sort
- When stable sorting is required
- When worst-case O(n log n) time complexity is needed
- When sorting linked lists (as it doesn't require random access to data)
- When dealing with large datasets that don't fit in memory (external sorting)

### Problem Exercises
- [Merge Sort Practice Problems](https://www.geeksforgeeks.org/merge-sort/)
- [LeetCode: Merge Intervals](https://leetcode.com/problems/merge-intervals/)

## 5. Quick Sort

### Description
Quick Sort is a highly efficient divide-and-conquer algorithm that selects a 'pivot' element from the array and partitions the other elements into two sub-arrays according to whether they are less than or greater than the pivot. The sub-arrays are then recursively sorted.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n²) when the pivot is always the smallest/largest element
- **Space Complexity**: O(log n) for the recursive call stack
- **Stability**: Not stable (relative order of equal elements may change)

### Implementation
```cpp
int partition(int arr[], int low, int high) {
    // Choose the rightmost element as pivot
    int pivot = arr[high];
    
    // Index of smaller element
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Place pivot in its correct position
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Find the partitioning index
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

### Step-by-Step Example
Consider the array: `[10, 80, 30, 90, 40, 50, 70]`

**First Partition (pivot = 70):**
- Initialize i = -1
- j = 0: 10 < 70, increment i = 0, swap arr[0] and arr[0] (no change) → `[10, 80, 30, 90, 40, 50, 70]`
- j = 1: 80 > 70, no swap → `[10, 80, 30, 90, 40, 50, 70]`
- j = 2: 30 < 70, increment i = 1, swap arr[1] and arr[2] → `[10, 30, 80, 90, 40, 50, 70]`
- j = 3: 90 > 70, no swap → `[10, 30, 80, 90, 40, 50, 70]`
- j = 4: 40 < 70, increment i = 2, swap arr[2] and arr[4] → `[10, 30, 40, 90, 80, 50, 70]`
- j = 5: 50 < 70, increment i = 3, swap arr[3] and arr[5] → `[10, 30, 40, 50, 80, 90, 70]`
- Swap arr[i+1] and arr[high] → `[10, 30, 40, 50, 70, 90, 80]`
- Pivot 70 is now at index 4

**Recursive Sort:**
- quickSort([10, 30, 40, 50], 0, 3)
  - Further recursive partitioning of left subarray
- quickSort([90, 80], 5, 6)
  - Further recursive partitioning of right subarray

**Final sorted array:** `[10, 30, 40, 50, 70, 80, 90]`

### When to Use Quick Sort
- When average case performance is important
- When in-place sorting is desired
- For arrays (as it has good cache locality)
- When space is a constraint
- As a general-purpose sorting algorithm in many programming libraries

### Problem Exercises
- [Quick Sort Practice Problems](https://www.geeksforgeeks.org/quick-sort/)
- [LeetCode: Sort an Array](https://leetcode.com/problems/sort-an-array/)

## 6. Heap Sort

### Description
Heap Sort is a comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max heap from the input data, then repeatedly extracts the maximum element from the heap and rebuilds the heap until it's empty.

### Complexity Analysis
- **Time Complexity**: 
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n log n)
- **Space Complexity**: O(1) for in-place implementation
- **Stability**: Not stable (relative order of equal elements may change)

### Implementation
```cpp
// To heapify a subtree rooted with node i
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
        
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
```

### Step-by-Step Example
Consider the array: `[4, 10, 3, 5, 1]`

**Build Heap Phase:**
1. Starting with i = 1 (n/2 - 1):
   - Heapify at index 1 (value 10): No change needed, already satisfies heap property
   - Heap: `[4, 10, 3, 5, 1]`
2. Heapify at index 0 (value 4):
   - Left child (10) > 4, so largest = 10
   - Swap arr[0] and arr[1]: `[10, 4, 3, 5, 1]`
   - Recursively heapify at index 1: No further changes needed
   - Heap: `[10, 5, 3, 4, 1]`

**Extract Phase:**
1. Swap arr[0] and arr[4]: `[1, 5, 3, 4, 10]`
   - Heapify at index 0 with heap size 4: after heapify, heap becomes `[5, 4, 3, 1, 10]`
2. Swap arr[0] and arr[3]: `[1, 4, 3, 5, 10]`
   - Heapify at index 0 with heap size 3: after heapify, heap becomes `[4, 1, 3, 5, 10]`
3. Swap arr[0] and arr[2]: `[3, 1, 4, 5, 10]`
   - Heapify at index 0 with heap size 2: after heapify, heap becomes `[3, 1, 4, 5, 10]`
4. Swap arr[0] and arr[1]: `[1, 3, 4, 5, 10]`
   - Heapify at index 0 with heap size 1: No change needed

**Final sorted array:** `[1, 3, 4, 5, 10]`

### When to Use Heap Sort
- When guaranteed O(n log n) time complexity is required
- When space is a constraint (as it's in-place)
- When building a priority queue
- When finding the kth largest/smallest element efficiently

### Problem Exercises
- [Heap Sort Practice Problems](https://www.geeksforgeeks.org/heap-sort/)
- [LeetCode: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

## 7. Radix Sort

### Description
Radix Sort is a non-comparison-based sorting algorithm that sorts numbers by processing individual digits. It sorts numbers digit by digit, starting from the least significant digit to the most significant digit. It uses counting sort as a subroutine to sort the digits.

### Complexity Analysis
- **Time Complexity**: O(d * (n + k)) where d is the number of digits, n is the number of elements, and k is the range of a digit (usually 10 for decimal)
- **Space Complexity**: O(n + k) for the counting sort subroutine
- **Stability**: Stable (preserves the relative order of equal elements)

### Implementation
```cpp
// Get the maximum value in arr[]
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// A function to do counting sort according to the digit represented by exp
void countSort(int arr[], int n, int exp) {
    int output[n]; // output array
    int count[10] = {0};
    
    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    // Change count[i] so that count[i] contains
    // position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy the output array to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to sort arr[] using Radix Sort
void radixSort(int arr[], int n) {
    // Find the maximum number to know number of digits
    int max = getMax(arr, n);
    
    // Do counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
```

### Step-by-Step Example
Consider the array: `[170, 45, 75, 90, 802, 24, 2, 66]`

**First Pass (Sort by ones place):**
- Extract the ones digit from each number: `[0, 5, 5, 0, 2, 4, 2, 6]`
- After counting sort by ones place: `[170, 90, 802, 2, 24, 45, 75, 66]`

**Second Pass (Sort by tens place):**
- Extract the tens digit from each number: `[7, 9, 0, 0, 0, 2, 7, 6]`
- After counting sort by tens place: `[802, 2, 24, 45, 66, 170, 75, 90]`

**Third Pass (Sort by hundreds place):**
- Extract the hundreds digit from each number: `[1, 0, 8, 0, 0, 0, 0, 0]`
- After counting sort by hundreds place: `[2, 24, 45, 66, 75, 90, 170, 802]`

**Final sorted array:** `[2, 24, 45, 66, 75, 90, 170, 802]`

### When to Use Radix Sort
- When dealing with integers or strings of fixed length
- When the range of values is not significantly larger than the number of items
- When a stable sort is required
- When distribution of values is uniform

### Problem Exercises
- [Radix Sort Practice Problems](https://www.geeksforgeeks.org/radix-sort/)
- [LeetCode: Sort an Array](https://leetcode.com/problems/sort-an-array/)

## 8. Counting Sort

### Description
Counting Sort is a non-comparison-based sorting algorithm that works by counting the number of objects having distinct key values. It works by using an auxiliary array to determine the position of each object in the output sequence.

### Complexity Analysis
- **Time Complexity**: O(n + k) where n is the number of elements and k is the range of input
- **Space Complexity**: O(n + k) for the count array and output array
- **Stability**: Stable (if implemented correctly)

### Implementation
```cpp
void countingSort(int arr[], int n) {
    // Find the maximum element in arr[]
    int max = *max_element(arr, arr + n);
    
    // Create a count array to store count of individual elements
    // and initialize count array as 0
    int* count = new int[max + 1]();
    
    // Store count of each element
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    
    // Change count[i] so that count[i] now contains actual
    // position of this element in output array
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    int* output = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    delete[] count;
    delete[] output;
}
```

### Step-by-Step Example
Consider the array: `[4, 2, 2, 8, 3, 3, 1]`

**Step 1: Find maximum element**
- max = 8

**Step 2: Initialize count array**
- count[0..8] = {0, 0, 0, 0, 0, 0, 0, 0, 0}

**Step 3: Store the count of each element**
- count[1] = 1 (one occurrence of 1)
- count[2] = 2 (two occurrences of 2)
- count[3] = 2 (two occurrences of 3)
- count[4] = 1 (one occurrence of 4)
- count[8] = 1 (one occurrence of 8)
- count[0..8] = {0, 1, 2, 2, 1, 0, 0, 0, 1}

**Step 4: Calculate cumulative count**
- count[0..8] = {0, 1, 3, 5, 6, 6, 6, 6, 7}

**Step 5: Place elements in sorted order**
- Process 1: place at index 0, count[1] becomes 0
- Process 2: place at index 2, count[2] becomes 2
- Process 2: place at index 1, count[2] becomes 1
- Process 3: place at index 4, count[3] becomes 4
- Process 3: place at index 3, count[3] becomes 3
- Process 4: place at index 5, count[4] becomes 5
- Process 8: place at index 6, count[8] becomes 6

**Final sorted array:** `[1, 2, 2, 3, 3, 4, 8]`

### When to Use Counting Sort
- When sorting integers with a limited range
- When the range of potential values is not significantly greater than the number of values to sort
- When extra space is available
- When a stable sort is required

### Problem Exercises
- [Counting Sort Practice Problems](https://www.geeksforgeeks.org/counting-sort/)
- [LeetCode: Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)

## Comparison of Sorting Algorithms

| Algorithm | Time Complexity (Best) | Time Complexity (Avg) | Time Complexity (Worst) | Space Complexity | Stable | In-Place |
|-----------|------------------------|----------------------|------------------------|-----------------|--------|----------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No | Yes |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | No |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No | Yes |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No | Yes |
| Radix Sort | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes | No |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(n+k) | Yes | No |

## How to Choose a Sorting Algorithm

1. **Small datasets**: Use Insertion Sort for its simplicity and good performance on small arrays
2. **Nearly sorted data**: Insertion Sort or Bubble Sort with early termination
3. **Limited memory**: Use in-place sorts like Quick Sort, Heap Sort, or Selection Sort
4. **Concerned about worst-case scenarios**: Use Merge Sort or Heap Sort
5. **Stability required**: Use Merge Sort, Insertion Sort, Bubble Sort, or Counting Sort
6. **Non-comparison based sorting**: Consider Counting Sort (for small ranges) or Radix Sort (for integers)
7. **General purpose**: Quick Sort is often the best choice due to its good average performance
8. **External sorting** (data doesn't fit in memory): Use Merge Sort

## Conclusion
Sorting algorithms are essential for organizing data efficiently. Understanding their implementations, complexities, and use cases is crucial for optimizing performance in various applications. Each algorithm has its strengths and weaknesses, making them suitable for different scenarios.

Practice the exercises linked above to strengthen your understanding of sorting algorithms, as they form the foundation for many other algorithms and data structures in computer science.