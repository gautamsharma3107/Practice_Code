# Arrays and Strings in C++

## 1. One-Dimensional Arrays
- Definition: A one-dimensional array is a linear collection of elements of the same type.
- Declaration: 
  ```cpp
  int arr[5]; // Declaration of an array of 5 integers
  ```
- Initialization:
  ```cpp
  int arr[5] = {1, 2, 3, 4, 5}; // Initialization with values
  ```
- Accessing Elements:
  ```cpp
  int firstElement = arr[0]; // Accessing the first element
  ```

### Problem Exercises:
1. Create an array of integers and find the sum of its elements. [Link to problem](https://www.example.com/problem1)
2. Write a program to reverse an array. [Link to problem](https://www.example.com/problem2)

## 2. Multi-Dimensional Arrays
- Definition: An array of arrays, typically used to represent matrices.
- Declaration:
  ```cpp
  int matrix[3][3]; // Declaration of a 3x3 matrix
  ```
- Initialization:
  ```cpp
  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; // Initialization
  ```
- Accessing Elements:
  ```cpp
  int element = matrix[1][2]; // Accessing element at row 1, column 2
  ```

### Problem Exercises:
1. Write a program to add two matrices. [Link to problem](https://www.example.com/problem3)
2. Implement a program to transpose a matrix. [Link to problem](https://www.example.com/problem4)

## 3. Array Initialization and Access
- Different ways to initialize arrays:
  ```cpp
  int arr1[5] = {0}; // All elements initialized to 0
  int arr2[] = {1, 2, 3}; // Size inferred from initializer
  ```
- Accessing elements using loops:
  ```cpp
  for (int i = 0; i < 5; i++) {
      cout << arr[i] << " "; // Print each element
  }
  ```

### Problem Exercises:
1. Create an array of 10 integers and print them using a loop. [Link to problem](https://www.example.com/problem5)

## 4. Character Arrays
- Definition: An array of characters used to store strings.
- Declaration:
  ```cpp
  char str[20]; // Declaration of a character array
  ```
- Initialization:
  ```cpp
  char str[] = "Hello"; // String initialization
  ```

### Problem Exercises:
1. Write a program to count the number of vowels in a string. [Link to problem](https://www.example.com/problem6)

## 5. C-Style Strings and Operations
- C-style strings are null-terminated character arrays.
- Common operations:
  - Length: `strlen(str)`
  - Copy: `strcpy(dest, src)`
  - Concatenation: `strcat(dest, src)`

### Problem Exercises:
1. Implement a function to compare two C-style strings. [Link to problem](https://www.example.com/problem7)

## 6. std::string Class and Methods
- The `std::string` class provides a more flexible way to handle strings.
- Common methods:
  - Length: `str.length()`
  - Substring: `str.substr(start, length)`
  - Find: `str.find("substring")`

### Problem Exercises:
1. Write a program to find the first occurrence of a character in a string. [Link to problem](https://www.example.com/problem8)
2. Create a program that checks if a string is a palindrome. [Link to problem](https://www.example.com/problem9)

## Conclusion
Understanding arrays and strings is fundamental in C++ programming. Practice the exercises linked above to strengthen your skills.