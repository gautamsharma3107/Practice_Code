# Recursion

## Overview
Recursion is a programming technique where a function calls itself to solve a problem. It is often used to break down complex problems into simpler sub-problems.

## Key Concepts

### 1. Recursive Thinking
- Understand how to approach problems recursively.
- Identify the base case and recursive case.

### 2. Base Cases
- The condition under which the recursion stops.
- Example: In a factorial function, the base case is when n = 0 or n = 1.

### 3. Recursive vs Iterative Solutions
- Recursive solutions can be more elegant and easier to understand.
- Iterative solutions may be more efficient in terms of memory usage.

### 4. Call Stack
- Each recursive call adds a new layer to the call stack.
- Understanding stack frames is crucial for debugging recursive functions.

### 5. Tail Recursion
- A special case of recursion where the recursive call is the last operation in the function.
- Tail recursion can be optimized by the compiler to avoid increasing the call stack.

### 6. Common Recursion Problems
- Factorial calculation
- Fibonacci sequence
- Tower of Hanoi
- Permutations and combinations

### 7. Memoization
- An optimization technique to store the results of expensive function calls and reuse them when the same inputs occur again.
- Useful in problems like Fibonacci sequence to avoid redundant calculations.

## Problem Exercises
1. **Factorial Calculation**
   - Write a recursive function to calculate the factorial of a number.
   - [Problem Link](https://leetcode.com/problems/factorial-trailing-zeroes/)

2. **Fibonacci Sequence**
   - Implement a recursive function to find the nth Fibonacci number.
   - [Problem Link](https://leetcode.com/problems/fibonacci-number/)

3. **Tower of Hanoi**
   - Solve the Tower of Hanoi problem using recursion.
   - [Problem Link](https://www.geeksforgeeks.org/c-program-tower-of-hanoi/)

4. **Permutations of a String**
   - Generate all permutations of a given string using recursion.
   - [Problem Link](https://leetcode.com/problems/permutations/)

5. **Memoized Fibonacci**
   - Implement the Fibonacci sequence using memoization.
   - [Problem Link](https://leetcode.com/problems/fibonacci-number/)

## Additional Resources
- [GeeksforGeeks - Recursion](https://www.geeksforgeeks.org/recursion/)
- [Khan Academy - Recursion](https://www.khanacademy.org/computing/computer-science/algorithms/recursion-in-algorithms)