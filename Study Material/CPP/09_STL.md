# Standard Template Library (STL) Notes

This document provides an overview of the Standard Template Library (STL) in C++. The STL is a powerful set of C++ template classes to provide general-purpose classes and functions with templates.

## 1. Overview of STL
- The Standard Template Library (STL) is a powerful set of C++ template classes.
- It provides generic classes and functions to handle data structures and algorithms.
- Key components of STL include containers, algorithms, and iterators.

## 2. Container Types
STL provides several types of containers:

### 2.1 Sequence Containers
- **Vector**: Dynamic array that can resize itself.
- **Deque**: Double-ended queue that allows insertion and deletion at both ends.
- **List**: Doubly linked list allowing fast insertion and deletion.

### 2.2 Associative Containers
- **Set**: Collection of unique elements, sorted by value.
- **Map**: Collection of key-value pairs, where keys are unique.
- **Multiset**: Similar to set but allows duplicate elements.
- **Multimap**: Similar to map but allows duplicate keys.

### 2.3 Unordered Containers
- **Unordered Set**: Collection of unique elements, not sorted.
- **Unordered Map**: Collection of key-value pairs, keys are unique and not sorted.
- **Unordered Multiset**: Allows duplicate elements, not sorted.
- **Unordered Multimap**: Allows duplicate keys, not sorted.

### 2.4 Container Adapters
- **Stack**: LIFO (Last In First Out) data structure.
- **Queue**: FIFO (First In First Out) data structure.
- **Priority Queue**: Elements are ordered by priority.

## 3. Iterators
- Iterators are used to traverse the elements of a container.
- Types of iterators:
  - **Input Iterator**: Read-only access to the container.
  - **Output Iterator**: Write-only access to the container.
  - **Forward Iterator**: Can read and write, can only move forward.
  - **Bidirectional Iterator**: Can move both forward and backward.
  - **Random Access Iterator**: Can access elements at any position.

## 4. Algorithms
STL provides a rich set of algorithms that can be applied to containers:
- **Sorting**: `std::sort`, `std::stable_sort`
- **Searching**: `std::binary_search`, `std::find`
- **Manipulation**: `std::reverse`, `std::shuffle`
- **Set Operations**: `std::set_union`, `std::set_intersection`

## 5. Function Objects
- Function objects (functors) are objects that can be called as if they are functions.
- They can be used to customize the behavior of algorithms.

## 6. Lambda Expressions
- Introduced in C++11, lambda expressions allow you to define anonymous functions.
- Syntax: `[capture](parameters) -> return_type { body }`
- Example:
  ```cpp
  auto add = [](int a, int b) { return a + b; };
  ```

## Problem Exercises
1. **Implement a Stack using STL**: Create a stack using `std::stack` and perform push, pop, and display operations.
   - [LeetCode Stack Problems](https://leetcode.com/tag/stack/)
   
2. **Sorting a Vector**: Use `std::sort` to sort a vector of integers.
   - [LeetCode Sorting Problems](https://leetcode.com/tag/sorting/)
   
3. **Using Maps**: Count the frequency of words in a text using `std::map`.
   - [GeeksforGeeks Map Problems](https://www.geeksforgeeks.org/map-associative-containers-c-stl/)
   
4. **Lambda Expressions**: Write a program that uses lambda expressions to filter even numbers from a vector.
   - [C++ Lambda Expressions](https://www.geeksforgeeks.org/lambda-expressions-in-c/)

5. **Custom Comparator**: Create a custom comparator for sorting a vector of pairs based on the second element.
   - [GeeksforGeeks Custom Comparator](https://www.geeksforgeeks.org/sorting-a-vector-of-pairs-in-c/)

This concludes the notes on the Standard Template Library (STL) in C++. For further reading, refer to the official C++ documentation and STL resources.