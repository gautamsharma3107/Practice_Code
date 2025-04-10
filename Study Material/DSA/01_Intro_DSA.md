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
  - **Best-case analysis**: The minimum time taken by an algorithm for any input of size n.
  - **Average-case analysis**: The expected time taken by an algorithm for a random input of size n.

## 3. Time Complexity
- **Definition**: Time complexity is a computational complexity that describes the amount of time it takes to run an algorithm as a function of the length of the input.
- **Common Time Complexities**:
  - Constant Time: O(1)
  - Logarithmic Time: O(log n)
  - Linear Time: O(n)
  - Linearithmic Time: O(n log n)
  - Quadratic Time: O(n^2)
  - Exponential Time: O(2^n)

## 4. Space Complexity
- **Definition**: Space complexity is the amount of memory space required by an algorithm to execute as a function of the length of the input.
- **Components**:
  - **Fixed Part**: Space required for constants, simple variables, fixed-size variable components, etc.
  - **Variable Part**: Space required for dynamically allocated memory, recursion stack space, etc.

## 5. Asymptotic Notation
- **Purpose**: To describe the limiting behavior of an algorithm's time or space complexity.
- **Common Notations**:
  - **Big O Notation (O)**: Describes the upper bound of the time complexity.
  - **Omega Notation (Ω)**: Describes the lower bound of the time complexity.
  - **Theta Notation (Θ)**: Describes the tight bound of the time complexity.

## Problem Exercises
1. **Exercise 1**: Write a simple algorithm to find the maximum of three numbers. Analyze its time complexity.
   - [Problem Link](https://www.example.com/problem1)

2. **Exercise 2**: Implement a function that calculates the factorial of a number using recursion. Analyze its space complexity.
   - [Problem Link](https://www.example.com/problem2)

3. **Exercise 3**: Create an algorithm that sorts an array of integers using bubble sort. Discuss its time complexity in the worst and average cases.
   - [Problem Link](https://www.example.com/problem3)

4. **Exercise 4**: Analyze the time complexity of the binary search algorithm and implement it in C++.
   - [Problem Link](https://www.example.com/problem4)

5. **Exercise 5**: Compare the time complexities of linear search and binary search. Implement both algorithms and test them with large datasets.
   - [Problem Link](https://www.example.com/problem5)