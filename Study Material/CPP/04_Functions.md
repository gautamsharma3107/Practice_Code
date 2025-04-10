# Functions in C++

## Function Declaration and Definition
- A function is a block of code that performs a specific task.
- **Declaration**: Tells the compiler about the function's name, return type, and parameters.
- **Definition**: Contains the actual body of the function.

### Example:
```cpp
int add(int a, int b); // Declaration
int add(int a, int b) { // Definition
    return a + b;
}
```

## Parameter Passing
- **Pass by Value**: A copy of the variable is passed to the function.
- **Pass by Reference**: A reference to the variable is passed, allowing the function to modify the original variable.

### Example:
```cpp
void modifyValue(int &x) {
    x = 10; // Modifies the original variable
}
```

## Return Types
- Functions can return values of various types, including `int`, `float`, `char`, etc.
- If no value is returned, the return type should be `void`.

### Example:
```cpp
float divide(int a, int b) {
    return static_cast<float>(a) / b;
}
```

## Default Arguments
- Default values can be specified for function parameters, allowing the function to be called with fewer arguments.

### Example:
```cpp
void printMessage(const std::string &message = "Hello, World!") {
    std::cout << message << std::endl;
}
```

## Function Overloading
- Multiple functions can have the same name with different parameter lists (types or number of parameters).

### Example:
```cpp
int multiply(int a, int b);
double multiply(double a, double b);
```

## Inline Functions
- Inline functions are defined with the `inline` keyword to suggest to the compiler to insert the function's body where the function is called, reducing function call overhead.

### Example:
```cpp
inline int square(int x) {
    return x * x;
}
```

## Recursion Basics
- A function that calls itself is known as a recursive function.
- Must have a base case to terminate the recursion.

### Example:
```cpp
int factorial(int n) {
    if (n <= 1) return 1; // Base case
    return n * factorial(n - 1); // Recursive case
}
```

## Problem Exercises
1. Write a function to calculate the power of a number using recursion.
   - [Problem Link](https://www.example.com/power-function)
   
2. Implement a function that swaps two numbers using pass by reference.
   - [Problem Link](https://www.example.com/swap-numbers)
   
3. Create an overloaded function to calculate the area of a rectangle and a circle.
   - [Problem Link](https://www.example.com/area-calculation)

4. Write a program that demonstrates the use of inline functions for simple arithmetic operations.
   - [Problem Link](https://www.example.com/inline-arithmetic)

5. Implement a function that uses default arguments to print a greeting message.
   - [Problem Link](https://www.example.com/default-arguments)

These notes provide a comprehensive overview of functions in C++, including their declaration, definition, and various features. Practice the exercises to reinforce your understanding.