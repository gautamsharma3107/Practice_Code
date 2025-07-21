# Recursion

## Overview
Recursion is a programming technique where a function calls itself to solve a problem. It is often used to break down complex problems into simpler sub-problems. In recursion, the solution to the original problem depends on solutions to smaller instances of the same problem.

## Key Concepts

### 1. Recursive Thinking
- Recursion involves breaking down a problem into one or more simpler versions of the same problem.
- Every recursive solution has two main components:
  1. **Base Case**: The simplest scenario with a direct answer
  2. **Recursive Case**: Breaking down into smaller sub-problems
- The recursive leap of faith: Trust that your recursive function works correctly for smaller inputs.

**Example - Recursive Thinking:**
```cpp
// Thinking about counting down recursively:
// 1. Base case: When we reach 0, stop counting
// 2. Recursive case: Print current number, then count down from (n-1)

void countDown(int n) {
    // Base case
    if (n <= 0) {
        cout << "Done!" << endl;
        return;
    }
    
    // Current operation
    cout << n << endl;
    
    // Recursive call with smaller problem
    countDown(n - 1);
}
```

### 2. Base Cases
- The condition under which the recursion stops.
- Without proper base cases, recursion would continue indefinitely, causing a stack overflow.
- There may be multiple base cases for complex problems.

**Example - Base Cases:**
```cpp
// Factorial function with base case
int factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n <= 1) {
        return 1;
    }
    
    // Recursive case
    return n * factorial(n - 1);
}
```

### 3. Recursive vs Iterative Solutions
- Recursive solutions often map more naturally to the problem's structure.
- Recursive solutions may be less efficient due to function call overhead and stack usage.
- Any recursive algorithm can be translated into an iterative one using a stack.

**Example - Recursive vs Iterative Approaches:**
```cpp
// Recursive factorial
int recursiveFactorial(int n) {
    if (n <= 1) return 1;
    return n * recursiveFactorial(n - 1);
}

// Iterative factorial
int iterativeFactorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

### 4. Call Stack
- Each recursive call creates a new stack frame containing the function's local variables and return address.
- The call stack grows with each recursive call and shrinks as functions complete.
- Stack overflow occurs when the recursion depth exceeds the available stack space.

**Example - Visualizing the Call Stack:**
```cpp
// For understanding how call stack works with recursion
void printCallStack(int n, string indent = "") {
    cout << indent << "Enter function: n = " << n << endl;
    
    if (n <= 0) {
        cout << indent << "Base case reached" << endl;
    } else {
        cout << indent << "Calling with n-1..." << endl;
        printCallStack(n - 1, indent + "  ");
        cout << indent << "Returned from recursive call" << endl;
    }
    
    cout << indent << "Exit function: n = " << n << endl;
}

// Usage: printCallStack(3);
// This will print a visual representation of how the call stack grows and shrinks
```

### 5. Tail Recursion
- A special form of recursion where the recursive call is the last operation in the function.
- Tail recursion can be optimized by compilers to use the same stack frame (tail call optimization).
- This optimization eliminates the risk of stack overflow for deep recursion.

**Example - Normal vs Tail Recursion:**
```cpp
// Normal recursion (not tail recursive)
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1); // Must perform multiplication after recursive call returns
}

// Tail recursive version
int factorialTail(int n, int accumulator = 1) {
    if (n <= 1) return accumulator;
    return factorialTail(n - 1, n * accumulator); // Last operation is the recursive call
}

// Usage: factorialTail(5) instead of factorial(5)
```

### 6. Common Recursion Patterns

#### 6.1 Linear Recursion
- Makes one recursive call per function invocation.
- Example: factorial, power calculation, etc.

```cpp
// Linear recursion to calculate x^n
int power(int x, int n) {
    if (n == 0) return 1;
    return x * power(x, n - 1);
}
```

#### 6.2 Binary Recursion
- Makes two recursive calls per function invocation.
- Example: Fibonacci, binary tree traversal, etc.

```cpp
// Binary recursion for Fibonacci
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

#### 6.3 Multiple Recursion
- Makes more than two recursive calls per function invocation.
- Example: Permutations, combinations, etc.

```cpp
// Example of multiple recursion: generating all subsets
void generateSubsets(vector<int>& nums, vector<vector<int>>& result, 
                    vector<int>& subset, int index) {
    // Base case: add current subset to result
    result.push_back(subset);
    
    // Try including each remaining element
    for (int i = index; i < nums.size(); i++) {
        // Include nums[i]
        subset.push_back(nums[i]);
        
        // Recursively generate subsets with nums[i] included
        generateSubsets(nums, result, subset, i + 1);
        
        // Backtrack (exclude nums[i])
        subset.pop_back();
    }
}
```

#### 6.4 Mutual Recursion
- Two or more functions that call each other recursively.
- Example: even/odd checking, parsing context-free grammars.

```cpp
// Mutual recursion example: checking even/odd
bool isEven(int n);  // Forward declaration

bool isOdd(int n) {
    if (n == 0) return false;
    return isEven(n - 1);
}

bool isEven(int n) {
    if (n == 0) return true;
    return isOdd(n - 1);
}
```

### 7. Memoization and Dynamic Programming
- Memoization: Storing the results of expensive recursive calls to avoid redundant calculations.
- Top-down (memoized recursion) vs. Bottom-up (iterative construction) approaches.
- Significantly improves performance for problems with overlapping subproblems.

**Example - Memoized Fibonacci:**
```cpp
// Memoized Fibonacci
int fibMemoized(int n, unordered_map<int, int>& memo) {
    // Check if we've already computed this value
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    
    // Base cases
    if (n <= 1) {
        return n;
    }
    
    // Compute and store result
    memo[n] = fibMemoized(n - 1, memo) + fibMemoized(n - 2, memo);
    return memo[n];
}

// Wrapper function
int fibonacci(int n) {
    unordered_map<int, int> memo;
    return fibMemoized(n, memo);
}
```

## Problem Exercises with Solutions

### 1. Factorial Calculation
Write a recursive function to calculate the factorial of a number.

```cpp
// Factorial calculation using recursion
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    
    // Recursive case
    return n * factorial(n - 1);
}

// Example usage:
// factorial(5) = 5 * 4 * 3 * 2 * 1 = 120
```

### 2. Fibonacci Sequence
Implement a recursive function to find the nth Fibonacci number.

```cpp
// Simple recursive Fibonacci (inefficient)
int fibonacci(int n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Efficient memoized version
int fibonacciEfficient(int n) {
    vector<int> memo(n + 1, -1);
    
    function<int(int)> fib = [&](int k) {
        if (k <= 0) return 0;
        if (k == 1) return 1;
        if (memo[k] != -1) return memo[k];
        
        memo[k] = fib(k - 1) + fib(k - 2);
        return memo[k];
    };
    
    return fib(n);
}
```

### 3. Tower of Hanoi
Solve the Tower of Hanoi problem using recursion.

```cpp
// Tower of Hanoi solution
void towerOfHanoi(int n, char source, char auxiliary, char target) {
    // Base case: no disk to move
    if (n == 0) {
        return;
    }
    
    // Move n-1 disks from source to auxiliary using target as auxiliary
    towerOfHanoi(n - 1, source, target, auxiliary);
    
    // Move the nth disk from source to target
    cout << "Move disk " << n << " from rod " << source 
         << " to rod " << target << endl;
    
    // Move n-1 disks from auxiliary to target using source as auxiliary
    towerOfHanoi(n - 1, auxiliary, source, target);
}

// Example usage:
// towerOfHanoi(3, 'A', 'B', 'C');
```

### 4. Permutations of a String
Generate all permutations of a given string using recursion.

```cpp
// Generate all permutations of a string
void permute(string str, int l, int r) {
    // Base case: reached the end of string
    if (l == r) {
        cout << str << endl;
    } else {
        // Try each character at position l
        for (int i = l; i <= r; i++) {
            // Swap characters at positions l and i
            swap(str[l], str[i]);
            
            // Generate permutations for the rest of the string
            permute(str, l + 1, r);
            
            // Backtrack: restore the string
            swap(str[l], str[i]);
        }
    }
}

// Example usage:
// string s = "ABC";
// permute(s, 0, s.length() - 1);
```

### 5. Binary Search using Recursion
Implement binary search using recursion.

```cpp
// Binary search using recursion
int binarySearch(vector<int>& arr, int target, int left, int right) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }
    
    // Find middle element
    int mid = left + (right - left) / 2;
    
    // Check if middle element is the target
    if (arr[mid] == target) {
        return mid;
    }
    
    // If target is less than middle, search in left half
    if (arr[mid] > target) {
        return binarySearch(arr, target, left, mid - 1);
    }
    
    // If target is greater than middle, search in right half
    return binarySearch(arr, target, mid + 1, right);
}

// Example usage:
// vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// int index = binarySearch(arr, 7, 0, arr.size() - 1);
```

## Advanced Recursion Topics

### 1. Backtracking
Backtracking is an algorithmic technique that abandons a solution as soon as it determines that it can't be completed to a valid solution.

```cpp
// N-Queens problem using backtracking
bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check this row on left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }
    
    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    
    // Check lower diagonal on left side
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }
    
    return true;
}

bool solveNQueens(vector<vector<int>>& board, int col, int n) {
    // Base case: If all queens are placed
    if (col >= n) return true;
    
    // Try placing queen in all rows of this column
    for (int i = 0; i < n; i++) {
        // Check if queen can be placed on board[i][col]
        if (isSafe(board, i, col, n)) {
            // Place the queen
            board[i][col] = 1;
            
            // Recursively place rest of the queens
            if (solveNQueens(board, col + 1, n)) return true;
            
            // If placing queen doesn't lead to a solution
            board[i][col] = 0;  // backtrack
        }
    }
    
    // If queen can't be placed in any row in this column
    return false;
}
```

### 2. Divide and Conquer
This technique breaks a problem into simpler sub-problems, solves them recursively, and combines their solutions.

```cpp
// Merge sort implementation using divide and conquer
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    vector<int> L(n1), R(n2);
    
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temp arrays back into arr[left..right]
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
    
    // Copy the remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}
```

## Common Pitfalls and Best Practices

1. **Missing Base Case**: Always ensure at least one base case exists and is reachable.
2. **Stack Overflow**: Be mindful of the recursion depth. Consider using tail recursion or iteration for very deep recursions.
3. **Duplicate Calculations**: Use memoization when subproblems overlap.
4. **Incorrect State Management**: Carefully track and manage state variables that change during recursive calls.
5. **Choosing Recursion Wisely**: Not all problems benefit from recursive solutions. Consider:
   - Is the problem naturally recursive?
   - Would an iterative solution be clearer or more efficient?
   - Is the recursion depth reasonable for the available stack size?

## Additional Resources
- [GeeksforGeeks - Recursion](https://www.geeksforgeeks.org/recursion/)
- [Khan Academy - Recursion](https://www.khanacademy.org/computing/computer-science/algorithms/recursive-algorithms)
- [Visualizing Recursion](http://pythontutor.com/) - Python Tutor helps visualize recursion
- [Introduction to Algorithms](https://mitpress.mit.edu/books/introduction-algorithms-third-edition) - CLRS textbook
- [The Art of Computer Programming, Volume 1](https://www-cs-faculty.stanford.edu/~knuth/taocp.html) - by Donald Knuth