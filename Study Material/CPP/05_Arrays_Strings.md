# Arrays and Strings in C++

## 1. One-Dimensional Arrays

### Basic Concepts
A one-dimensional array is a linear collection of elements of the same data type, stored in contiguous memory locations. Arrays in C++ are zero-indexed, meaning the first element is at index 0.

### Declaration and Initialization
```cpp
// Declaration without initialization
int numbers[5];  // Creates an array that can hold 5 integers

// Declaration with initialization
int scores[5] = {95, 85, 90, 80, 88};  // Explicit size

// Size inference from initializer list
int grades[] = {95, 85, 90, 80, 88};  // Compiler determines size as 5

// Partial initialization (remaining elements are set to 0)
int partial[5] = {10, 20};  // becomes {10, 20, 0, 0, 0}

// Initialize all elements to zero
int zeros[10] = {0};  // All elements set to 0
```

### Accessing and Modifying Elements
```cpp
int marks[5] = {88, 76, 90, 61, 69};

// Accessing elements
int firstMark = marks[0];  // Gets 88
int lastMark = marks[4];   // Gets 69

// Modifying elements
marks[2] = 95;  // Changes 90 to 95

// Iterating through an array
for (int i = 0; i < 5; i++) {
    cout << "Element at index " << i << ": " << marks[i] << endl;
}

// Using range-based for loop (C++11 and later)
for (int mark : marks) {
    cout << mark << " ";
}
cout << endl;
```

### Memory Representation
Arrays are stored in contiguous memory blocks. For an array of integers:
```cpp
int arr[5] = {10, 20, 30, 40, 50};
```

The memory layout would be:
```
Memory Address: 1000  1004  1008  1012  1016
Array Index:    [0]   [1]   [2]   [3]   [4]
Values:         10    20    30    40    50
```
(Assuming an int is 4 bytes)

### Common Operations

#### Finding the length of an array
```cpp
int numbers[] = {1, 2, 3, 4, 5};
int length = sizeof(numbers) / sizeof(numbers[0]);
cout << "Array length: " << length << endl;  // Outputs: 5
```

#### Finding the sum of array elements
```cpp
int numbers[] = {1, 2, 3, 4, 5};
int sum = 0;
int size = sizeof(numbers) / sizeof(numbers[0]);

for (int i = 0; i < size; i++) {
    sum += numbers[i];
}
cout << "Sum: " << sum << endl;  // Outputs: 15
```

#### Finding the maximum element
```cpp
int numbers[] = {34, 12, 78, 56, 45};
int max = numbers[0];
int size = sizeof(numbers) / sizeof(numbers[0]);

for (int i = 1; i < size; i++) {
    if (numbers[i] > max) {
        max = numbers[i];
    }
}
cout << "Maximum element: " << max << endl;  // Outputs: 78
```

### Problem Exercises:
1. Create an array of integers and find the sum of its elements. [Link to problem](https://www.example.com/problem1)
2. Write a program to reverse an array. [Link to problem](https://www.example.com/problem2)
3. Find the second largest element in an array. [Link to problem](https://www.example.com/additional1)
4. Implement a program to remove duplicates from an array. [Link to problem](https://www.example.com/additional2)

## 2. Multi-Dimensional Arrays

### Basic Concepts
Multi-dimensional arrays are essentially arrays of arrays. The most common is the two-dimensional array, which represents a table with rows and columns.

### Declaration and Initialization
```cpp
// Declaration of a 3x3 matrix without initialization
int matrix[3][3];

// Declaration with initialization
int grid[3][3] = {
    {1, 2, 3},  // First row
    {4, 5, 6},  // Second row
    {7, 8, 9}   // Third row
};

// Partial initialization (unspecified elements are set to 0)
int partial[3][3] = {
    {1, 2},     // Row 0: {1, 2, 0}
    {4}         // Row 1: {4, 0, 0}, Row 2: {0, 0, 0}
};

// 3D array example
int cube[2][3][4] = {
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    },
    {
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
    }
};
```

### Accessing and Modifying Elements
```cpp
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Accessing elements
int element = matrix[1][2];  // Gets 6 (row 1, column 2)

// Modifying elements
matrix[0][0] = 10;  // Changes 1 to 10

// Iterating through a 2D array
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}

// Using range-based for loop (C++11 and later)
for (auto& row : matrix) {
    for (int element : row) {
        cout << element << " ";
    }
    cout << endl;
}
```

### Memory Representation
For a 2D array, memory is allocated in row-major order:
```cpp
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

Memory layout:
```
Memory Address: 1000  1004  1008  1012  1016  1020
Array Index:    [0][0] [0][1] [0][2] [1][0] [1][1] [1][2]
Values:         1      2      3      4      5      6
```

### Common Operations

#### Matrix Addition
```cpp
int A[2][2] = {{1, 2}, {3, 4}};
int B[2][2] = {{5, 6}, {7, 8}};
int C[2][2];

// Add matrices A and B
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
        C[i][j] = A[i][j] + B[i][j];
    }
}

// Display the result
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
        cout << C[i][j] << " ";
    }
    cout << endl;
}
// Output:
// 6 8
// 10 12
```

#### Matrix Transposition
```cpp
int original[3][2] = {{1, 2}, {3, 4}, {5, 6}};
int transposed[2][3];

// Transpose the matrix
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
        transposed[j][i] = original[i][j];
    }
}

// Display the transposed matrix
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
        cout << transposed[i][j] << " ";
    }
    cout << endl;
}
// Output:
// 1 3 5
// 2 4 6
```

### Problem Exercises:
1. Write a program to add two matrices. [Link to problem](https://www.example.com/problem3)
2. Implement a program to transpose a matrix. [Link to problem](https://www.example.com/problem4)
3. Multiply two matrices. [Link to problem](https://www.example.com/additional3)
4. Find the determinant of a 3x3 matrix. [Link to problem](https://www.example.com/additional4)

## 3. Array Initialization and Access

### Different Initialization Techniques
```cpp
// Standard initialization
int numbers[5] = {1, 2, 3, 4, 5};

// Zero initialization
int zeros[10] = {}; // All elements set to 0
int moreZeros[5] = {0}; // All elements set to 0

// Designated initializers (C++20)
int positions[6] = {[1]=10, [3]=30, [5]=50};
// Equivalent to {0, 10, 0, 30, 0, 50}

// Array initialization with variables
const int size = 5;
int dynamicSize[size]; // Valid in C++ (but still stack allocated)

// Initialize with a loop
int sequence[10];
for (int i = 0; i < 10; i++) {
    sequence[i] = i * 2; // {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}
}
```

### Array Access Patterns

#### Using Standard Loops
```cpp
int numbers[5] = {10, 20, 30, 40, 50};

// Forward traversal
for (int i = 0; i < 5; i++) {
    cout << numbers[i] << " "; // 10 20 30 40 50
}
cout << endl;

// Backward traversal
for (int i = 4; i >= 0; i--) {
    cout << numbers[i] << " "; // 50 40 30 20 10
}
cout << endl;

// Step traversal
for (int i = 0; i < 5; i += 2) {
    cout << numbers[i] << " "; // 10 30 50
}
cout << endl;
```

#### Using Range-based For Loop (C++11)
```cpp
int numbers[5] = {10, 20, 30, 40, 50};

// Simple iteration
for (int num : numbers) {
    cout << num << " "; // 10 20 30 40 50
}
cout << endl;

// Modifying elements (use reference)
for (int &num : numbers) {
    num *= 2;
}

// Display modified array
for (int num : numbers) {
    cout << num << " "; // 20 40 60 80 100
}
cout << endl;
```

#### Using Standard Library Algorithms
```cpp
#include <algorithm>
#include <iostream>

int numbers[5] = {10, 20, 30, 40, 50};

// Use for_each algorithm
std::for_each(numbers, numbers + 5, [](int num) {
    cout << num << " "; // 10 20 30 40 50
});
cout << endl;

// Find an element
int* found = std::find(numbers, numbers + 5, 30);
if (found != numbers + 5) {
    cout << "Found 30 at position " << (found - numbers) << endl;
}

// Sort an array
int unsorted[5] = {50, 30, 10, 40, 20};
std::sort(unsorted, unsorted + 5);
for (int num : unsorted) {
    cout << num << " "; // 10 20 30 40 50
}
cout << endl;
```

### Problem Exercises:
1. Create an array of 10 integers and print them using a loop. [Link to problem](https://www.example.com/problem5)
2. Initialize an array with the first 20 Fibonacci numbers. [Link to problem](https://www.example.com/additional5)
3. Implement binary search on a sorted array. [Link to problem](https://www.example.com/additional6)

## 4. Character Arrays and C-Style Strings

### Character Arrays Basics
```cpp
// Character array declaration
char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

// Accessing individual characters
char firstVowel = vowels[0]; // 'a'
char lastVowel = vowels[4];  // 'u'

// Iterating through the character array
for (int i = 0; i < 5; i++) {
    cout << vowels[i] << " ";
}
cout << endl;
```

### C-Style Strings
C-style strings are character arrays terminated with a null character `'\0'`.

```cpp
// String literal initialization (null-terminator is added automatically)
char greeting[] = "Hello"; // Equivalent to {'H','e','l','l','o','\0'}

// Manual initialization with null-terminator
char message[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

// Determining the size
int sizeWithNull = sizeof(greeting); // 6 (5 chars + null character)
cout << "Size including null: " << sizeWithNull << endl;

// Printing the string
cout << greeting << endl; // Prints "Hello"

// Character array without null-terminator is NOT a string
char notAString[5] = {'H', 'e', 'l', 'l', 'o'};
cout << notAString << endl; // Undefined behavior, may print "Hello" followed by garbage
```

### Common C-Style String Functions
```cpp
#include <cstring> // Required for string functions

// strlen - returns length of string (excluding null-terminator)
char text[] = "C++ Programming";
cout << "Length: " << strlen(text) << endl; // 15

// strcpy - copies one string to another
char source[] = "Hello";
char destination[10];
strcpy(destination, source);
cout << "Copied: " << destination << endl; // Hello

// strcat - concatenates strings
char first[] = "Hello, ";
char second[] = "World!";
char result[20];
strcpy(result, first);
strcat(result, second);
cout << "Concatenated: " << result << endl; // Hello, World!

// strcmp - compares two strings
char str1[] = "apple";
char str2[] = "banana";
int comparison = strcmp(str1, str2);
if (comparison < 0)
    cout << str1 << " comes before " << str2 << endl;
else if (comparison > 0)
    cout << str1 << " comes after " << str2 << endl;
else
    cout << str1 << " is equal to " << str2 << endl;
// Output: apple comes before banana
```

### Common Pitfalls with C-Style Strings
```cpp
// Buffer overflow risk
char small[5];
strcpy(small, "This is too long"); // DANGER! Buffer overflow

// Safe alternative using strncpy
char buffer[10];
strncpy(buffer, "Hello World", 9); // Copies at most 9 characters
buffer[9] = '\0'; // Ensure null-termination
cout << buffer << endl; // "Hello Wor"
```

### Problem Exercises:
1. Write a program to count the number of vowels in a string. [Link to problem](https://www.example.com/problem6)
2. Implement a function to compare two C-style strings. [Link to problem](https://www.example.com/problem7)
3. Reverse a C-style string in place. [Link to problem](https://www.example.com/additional7)

## 5. std::string Class

### Basic Operations
```cpp
#include <string>

// Declaration and initialization
std::string greeting = "Hello";
std::string message("World");
std::string empty;

// Assignment
empty = "No longer empty";

// Concatenation
std::string fullGreeting = greeting + " " + message + "!";
cout << fullGreeting << endl; // "Hello World!"

// Appending
std::string text = "Start";
text += " and continue";
cout << text << endl; // "Start and continue"

// Length and size (equivalent)
cout << "Length: " << fullGreeting.length() << endl; // 12
cout << "Size: " << fullGreeting.size() << endl; // 12

// Accessing characters
char firstChar = fullGreeting[0]; // 'H'
char lastChar = fullGreeting[fullGreeting.length() - 1]; // '!'

// Using at() with bounds checking
try {
    char ch = fullGreeting.at(100); // Throws out_of_range exception
} catch (const std::out_of_range& e) {
    cout << "Exception: " << e.what() << endl;
}
```

### String Manipulation

```cpp
std::string sentence = "The quick brown fox jumps over the lazy dog";

// Substring
std::string animal = sentence.substr(16, 3); // "fox"
cout << animal << endl;

// Find
size_t position = sentence.find("fox");
if (position != std::string::npos) {
    cout << "Found 'fox' at position " << position << endl; // 16
}

// Find with starting position
size_t pos = sentence.find("the", 0);
if (pos != std::string::npos) {
    cout << "Found 'the' at position " << pos << endl; // 31
}

// Find last occurrence
pos = sentence.rfind("the");
if (pos != std::string::npos) {
    cout << "Last 'the' at position " << pos << endl; // 31
}

// Replace
std::string modified = sentence;
modified.replace(16, 3, "cat");
cout << modified << endl; // "The quick brown cat jumps over the lazy dog"

// Insert
modified.insert(0, "Look! ");
cout << modified << endl; // "Look! The quick brown cat jumps over the lazy dog"

// Erase
modified.erase(0, 6); // Remove "Look! "
cout << modified << endl; // "The quick brown cat jumps over the lazy dog"
```

### String Comparison

```cpp
std::string str1 = "apple";
std::string str2 = "banana";
std::string str3 = "apple";

// Using comparison operators
if (str1 == str3) {
    cout << "str1 equals str3" << endl;
}

if (str1 != str2) {
    cout << "str1 is not equal to str2" << endl;
}

if (str1 < str2) {
    cout << "str1 comes before str2 lexicographically" << endl;
}

// Using compare() method
int result = str1.compare(str2);
if (result < 0)
    cout << "str1 is less than str2" << endl;
else if (result > 0)
    cout << "str1 is greater than str2" << endl;
else
    cout << "str1 is equal to str2" << endl;
```

### String Conversion

```cpp
// String to numeric conversions
std::string numStr = "42";
int num = std::stoi(numStr);
cout << "Converted to int: " << num << endl;

std::string floatStr = "3.14159";
double pi = std::stod(floatStr);
cout << "Converted to double: " << pi << endl;

// Numeric to string conversion
int value = 123;
std::string valueStr = std::to_string(value);
cout << "Converted to string: " << valueStr << endl;
```

### Problem Exercises:
1. Write a program to find the first occurrence of a character in a string. [Link to problem](https://www.example.com/problem8)
2. Create a program that checks if a string is a palindrome. [Link to problem](https://www.example.com/problem9)
3. Count occurrences of a substring in a string. [Link to problem](https://www.example.com/additional8)
4. Implement a function to split a string by a delimiter. [Link to problem](https://www.example.com/additional9)

## 6. Modern C++ Array Features

### std::array (C++11)
```cpp
#include <array>

// Declaration and initialization
std::array<int, 5> numbers = {1, 2, 3, 4, 5};

// Size
cout << "Size: " << numbers.size() << endl; // 5

// Access elements
cout << "First element: " << numbers[0] << endl;
cout << "Last element: " << numbers.back() << endl;
cout << "Element at index 2: " << numbers.at(2) << endl; // With bounds checking

// Check if empty
if (!numbers.empty()) {
    cout << "Array is not empty" << endl;
}

// Fill with a value
numbers.fill(10);
for (int num : numbers) {
    cout << num << " "; // 10 10 10 10 10
}
cout << endl;
```

### Dynamic Arrays with std::vector
```cpp
#include <vector>

// Declaration and initialization
std::vector<int> vec = {1, 2, 3, 4, 5};
std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
std::vector<double> empty_vector;

// Adding elements
vec.push_back(6);
vec.push_back(7);

// Inserting elements
vec.insert(vec.begin() + 2, 99); // Insert 99 at index 2

// Removing elements
vec.pop_back(); // Remove the last element
vec.erase(vec.begin()); // Remove the first element

// Size and capacity
cout << "Size: " << vec.size() << endl;
cout << "Capacity: " << vec.capacity() << endl;

// Clear all elements
vec.clear();
cout << "Size after clear: " << vec.size() << endl;

// Resizing
vec.resize(10, 5); // Resize to 10 elements, fill new ones with 5
```

### Range-Based For Loop with Arrays
```cpp
// With standard arrays
int numbers[] = {1, 2, 3, 4, 5};
for (int num : numbers) {
    cout << num << " ";
}
cout << endl;

// With std::array
std::array<int, 3> arr = {10, 20, 30};
for (int num : arr) {
    cout << num << " ";
}
cout << endl;

// With std::vector
std::vector<std::string> fruits = {"apple", "banana", "cherry"};
for (const auto& fruit : fruits) {
    cout << fruit << " ";
}
cout << endl;
```

### C++17 Structured Bindings
```cpp
#include <array>
#include <utility> // for std::pair

// With std::pair
std::pair<std::string, int> person = {"Alice", 30};
auto [name, age] = person;
cout << name << " is " << age << " years old." << endl;

// With std::array
std::array<int, 3> coords = {10, 20, 30};
auto [x, y, z] = coords;
cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl;

// With C-style arrays using std::tie
int point[2] = {5, 7};
int a, b;
std::tie(a, b) = std::tuple<int&, int&>(point[0], point[1]);
cout << "Point: (" << a << ", " << b << ")" << endl;
```

### Problem Exercises:
1. Implement a dynamic array using std::vector that automatically removes duplicates. [Link to problem](https://www.example.com/additional10)
2. Use std::array to implement a fixed-size stack. [Link to problem](https://www.example.com/additional11)

## Conclusion
Understanding arrays and strings is fundamental in C++ programming. This guide has covered essential concepts from basic array declarations to modern C++ features like std::array and std::vector. Practice the exercises linked above to strengthen your skills.

## Additional Resources
- [C++ Reference: Arrays](https://en.cppreference.com/w/cpp/language/array)
- [C++ Reference: std::string](https://en.cppreference.com/w/cpp/string/basic_string)
- [C++ Reference: std::array](https://en.cppreference.com/w/cpp/container/array)
- [C++ Reference: std::vector](https://en.cppreference.com/w/cpp/container/vector)