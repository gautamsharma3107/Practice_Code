# Functions in C++

## Function Declaration and Definition
- A function is a block of code that performs a specific task, helping to organize code into modular and reusable components.
- **Declaration**: Tells the compiler about the function's name, return type, and parameters (also called function prototype).
- **Definition**: Contains the actual body of the function with the implementation.
- Declaration and definition can be separate, which is useful in larger programs.

### Example:
```cpp
// Function declaration (prototype)
int add(int a, int b);  

// Function definition
int add(int a, int b) {
    return a + b;
}

// Usage
int main() {
    int sum = add(5, 3);  // Function call
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
```

## Parameter Passing

### Pass by Value
- A copy of the variable is passed to the function
- Changes to the parameter inside the function do not affect the original variable
- Efficient for small data types (int, char, etc.)

```cpp
void incrementValue(int x) {
    x++;  // Only modifies the local copy
    std::cout << "Inside function: " << x << std::endl;
}

int main() {
    int num = 5;
    incrementValue(num);  // Passes a copy of num
    std::cout << "Original value: " << num << std::endl;  // Still 5
    return 0;
}
```

### Pass by Reference
- A reference to the variable is passed, allowing the function to modify the original variable
- More efficient for large data structures as it avoids copying
- Denoted by `&` symbol in the parameter list

```cpp
void incrementValue(int &x) {
    x++;  // Modifies the original variable
    std::cout << "Inside function: " << x << std::endl;
}

int main() {
    int num = 5;
    incrementValue(num);  // Passes a reference to num
    std::cout << "Modified value: " << num << std::endl;  // Now 6
    return 0;
}
```

### Pass by Pointer
- Similar to pass by reference, but uses pointers
- Allows for null checks and pointer arithmetic

```cpp
void incrementValue(int *x) {
    if (x != nullptr) {
        (*x)++;  // Modifies the value at the pointer's address
    }
}

int main() {
    int num = 5;
    incrementValue(&num);  // Pass address of num
    std::cout << "Modified value: " << num << std::endl;  // Now 6
    return 0;
}
```

### Pass by Const Reference
- Passes a reference but prevents the function from modifying the value
- Combines the efficiency of pass by reference with the safety of pass by value

```cpp
void printValue(const int &x) {
    // x = 10; // Error! Cannot modify a const reference
    std::cout << "Value: " << x << std::endl;
}
```

## Return Types
- Functions can return values of various types, including `int`, `float`, `char`, etc.
- If no value is returned, the return type should be `void`.
- Functions can return by value, reference, or pointer.

### Basic Return Types
```cpp
// Return by value
int add(int a, int b) {
    return a + b;
}

// Return floating point result
float divide(int a, int b) {
    if (b == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        return 0;
    }
    return static_cast<float>(a) / b;
}

// Return nothing
void printMessage(const std::string &message) {
    std::cout << message << std::endl;
    // No return statement needed
}
```

### Return by Reference
```cpp
// Return reference to an element in an array
int& getElement(std::vector<int>& vec, int index) {
    return vec[index];  // Returns a reference to the element
}

int main() {
    std::vector<int> numbers = {10, 20, 30};
    getElement(numbers, 1) = 25;  // Modifies the second element
    std::cout << numbers[1] << std::endl;  // Outputs 25
    return 0;
}
```

### Return by Pointer
```cpp
int* createDynamicInt(int value) {
    int* ptr = new int(value);  // Allocate memory on the heap
    return ptr;  // Return pointer to the allocated memory
}

int main() {
    int* dynamicNum = createDynamicInt(42);
    std::cout << *dynamicNum << std::endl;  // Outputs 42
    delete dynamicNum;  // Remember to free the memory
    return 0;
}
```

## Default Arguments
- Default values can be specified for function parameters
- Allows the function to be called with fewer arguments than it is defined to accept
- Default arguments must be the rightmost parameters

```cpp
// Function with multiple default arguments
void showDetails(std::string name, int age = 30, std::string country = "Unknown") {
    std::cout << "Name: " << name << ", Age: " << age 
              << ", Country: " << country << std::endl;
}

int main() {
    showDetails("Alice");  // Uses defaults for age and country
    showDetails("Bob", 25);  // Uses default for country
    showDetails("Charlie", 42, "Canada");  // No defaults used
    return 0;
}
```

## Function Overloading
- Multiple functions can have the same name with different parameter lists
- The compiler selects the appropriate function based on the arguments provided
- Overloading works with different parameter types, number of parameters, or both

```cpp
// Overloaded functions with different parameter types
int add(int a, int b) {
    std::cout << "Adding integers" << std::endl;
    return a + b;
}

double add(double a, double b) {
    std::cout << "Adding doubles" << std::endl;
    return a + b;
}

// Overloaded function with different number of parameters
int add(int a, int b, int c) {
    std::cout << "Adding three integers" << std::endl;
    return a + b + c;
}

int main() {
    std::cout << add(5, 3) << std::endl;        // Calls int version
    std::cout << add(5.2, 3.7) << std::endl;    // Calls double version
    std::cout << add(1, 2, 3) << std::endl;     // Calls three-parameter version
    return 0;
}
```

## Inline Functions
- Inline functions are defined with the `inline` keyword
- Suggests to the compiler to replace the function call with the function's code
- Reduces function call overhead for small, frequently used functions
- Best used for small functions (typically 1-3 lines)

```cpp
// Inline function definition
inline int square(int x) {
    return x * x;
}

int main() {
    // The compiler might replace this with "int result = 5 * 5;"
    int result = square(5);
    std::cout << "Square: " << result << std::endl;
    return 0;
}
```

## Function Templates
- Allow you to write a function that can operate on different data types
- The compiler generates the appropriate function based on the argument types

```cpp
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maximum(10, 15) << std::endl;      // int version
    std::cout << maximum(10.5, 15.5) << std::endl;  // double version
    std::cout << maximum('A', 'Z') << std::endl;    // char version
    return 0;
}
```

## Lambda Functions
- Anonymous functions defined inline
- Useful for short operations, especially with algorithms

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {4, 1, 3, 5, 2};
    
    // Sort using a lambda function
    std::sort(numbers.begin(), numbers.end(), 
              [](int a, int b) { return a > b; });  // Sort in descending order
              
    // Print using a lambda
    std::for_each(numbers.begin(), numbers.end(), 
                 [](int n) { std::cout << n << " "; });
                 
    return 0;
}
```

## Recursion
- A function that calls itself is known as a recursive function
- Must have a base case to terminate the recursion
- Often provides elegant solutions to problems that can be broken down into smaller identical subproblems

### Factorial Example:
```cpp
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;  
    }
    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    std::cout << "5! = " << factorial(5) << std::endl;  // Outputs 120
    return 0;
}
```

### Fibonacci Example:
```cpp
int fibonacci(int n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // Recursive case
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    std::cout << "Fibonacci(7) = " << fibonacci(7) << std::endl;  // Outputs 13
    return 0;
}
```

## Advanced Function Concepts

### Function Pointers
- Variables that store the address of a function
- Allow for runtime selection of which function to call

```cpp
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    // Declare a function pointer
    int (*operation)(int, int);
    
    operation = add;
    std::cout << "Addition: " << operation(5, 3) << std::endl;
    
    operation = subtract;
    std::cout << "Subtraction: " << operation(5, 3) << std::endl;
    
    return 0;
}
```

### std::function and Callbacks
- Modern way to handle function objects in C++11 and later

```cpp
#include <functional>

void processNumbers(int a, int b, std::function<int(int, int)> operation) {
    std::cout << "Result: " << operation(a, b) << std::endl;
}

int main() {
    processNumbers(5, 3, [](int a, int b) { return a + b; });  // Addition
    processNumbers(5, 3, [](int a, int b) { return a * b; });  // Multiplication
    return 0;
}
```

## Practice Problems
1. Write a recursive function to calculate the power of a number.
   ```cpp
   // Power function: base^exponent
   int power(int base, int exponent) {
       if (exponent == 0) return 1;
       return base * power(base, exponent - 1);
   }
   ```

2. Implement a swap function using references.
   ```cpp
   void swap(int &a, int &b) {
       int temp = a;
       a = b;
       b = temp;
   }
   ```

3. Create overloaded functions to calculate areas of different shapes.
   ```cpp
   double calculateArea(double length, double width) {  // Rectangle
       return length * width;
   }
   
   double calculateArea(double radius) {  // Circle
       return 3.14159 * radius * radius;
   }
   
   double calculateArea(double base, double height, bool isTriangle) {  // Triangle
       if (isTriangle) return 0.5 * base * height;
       return base * height;  // Default to rectangle if not triangle
   }
   ```

4. Write a function template that finds the minimum value in an array.
   ```cpp
   template <typename T>
   T findMin(T arr[], int size) {
       T min = arr[0];
       for (int i = 1; i < size; i++) {
           if (arr[i] < min) min = arr[i];
       }
       return min;
   }
   ```

5. Create a function that uses default arguments to format text.
   ```cpp
   std::string formatText(const std::string &text, 
                         bool bold = false,
                         bool italic = false,
                         const std::string &color = "black") {
       std::string result = text;
       if (bold) result = "<b>" + result + "</b>";
       if (italic) result = "<i>" + result + "</i>";
       result = "<span style='color:" + color + "'>" + result + "</span>";
       return result;
   }
   ```

## Conclusion
Functions are fundamental building blocks in C++ programming that enable code reuse, modularity, and organization. Understanding the various aspects of functions—from basic declarations to advanced concepts like templates and lambdas—is essential for writing effective C++ code.

Practice these concepts to strengthen your understanding and improve your programming skills.