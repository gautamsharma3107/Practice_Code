# Memory Concepts in C++

## Stack vs Heap Memory
- **Stack Memory**: 
  - Automatically managed by the compiler.
  - Stores local variables and function call information.
  - Memory is allocated and deallocated in a Last In First Out (LIFO) manner.
  - Limited in size; can lead to stack overflow if too much memory is used.

- **Heap Memory**: 
  - Managed manually by the programmer using `new` and `delete`.
  - Used for dynamic memory allocation.
  - Larger in size compared to stack memory.
  - Can lead to memory leaks if not properly deallocated.

## Pointers
- A pointer is a variable that stores the memory address of another variable.
- Syntax: `int* ptr;` // Declares a pointer to an integer.
- Pointers can be used to dynamically allocate memory and to manipulate arrays and strings.

## Pointer Arithmetic
- Allows arithmetic operations on pointers to navigate through memory.
- Example:
  - `int arr[5];`
  - `int* ptr = arr;`
  - `ptr++;` // Moves the pointer to the next integer in the array.

## References
- A reference is an alias for another variable.
- Syntax: `int& ref = original;` // `ref` is a reference to `original`.
- References must be initialized when declared and cannot be changed to refer to another variable.

## Dynamic Memory Allocation
- Use `new` to allocate memory on the heap:
  - `int* arr = new int[10];` // Allocates an array of 10 integers.
- Use `delete` to free allocated memory:
  - `delete[] arr;` // Deallocates the array.

## Memory Management and Leaks
- Memory leaks occur when dynamically allocated memory is not deallocated.
- Tools like Valgrind can help detect memory leaks.
- Always ensure that every `new` has a corresponding `delete`.

## Smart Pointers
- Smart pointers are objects that manage the lifetime of dynamically allocated memory.
- Types of smart pointers:
  - `std::unique_ptr`: Owns a resource exclusively.
  - `std::shared_ptr`: Allows multiple pointers to share ownership of a resource.
  - `std::weak_ptr`: A non-owning reference to a resource managed by `shared_ptr`.

## Problem Exercises
1. **Stack vs Heap**: Write a program that demonstrates the difference between stack and heap memory allocation.
   - [LeetCode Problem](https://leetcode.com)
   
2. **Pointer Arithmetic**: Create a program that uses pointer arithmetic to traverse an array.
   - [HackerRank Problem](https://www.hackerrank.com)

3. **Dynamic Memory Allocation**: Implement a dynamic array that can grow in size.
   - [CodeSignal Problem](https://codesignal.com)

4. **Memory Leak Detection**: Write a program that intentionally creates a memory leak and then use a tool to detect it.
   - [GeeksforGeeks Problem](https://www.geeksforgeeks.org)

5. **Smart Pointers**: Rewrite a program using smart pointers instead of raw pointers.
   - [Codewars Problem](https://www.codewars.com)

## Additional Resources
- [C++ Memory Management](https://www.learncpp.com/cpp-tutorial/dynamic-memory/)
- [Understanding Smart Pointers](https://www.geeksforgeeks.org/smart-pointers-c-11/)

This file provides a comprehensive overview of memory concepts in C++, along with exercises to reinforce learning.