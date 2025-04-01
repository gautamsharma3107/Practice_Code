# Basic Concepts in C++

## Variables and Data Types

Variables are named storage locations that hold data. Each variable in C++ has a specific type that determines the size and layout of the variable's memory, the range of values that can be stored, and the set of operations that can be applied.

### Fundamental Data Types

| Data Type | Description | Size (typical) | Range (typical) |
|-----------|-------------|----------------|-----------------|
| `int` | Integer numbers | 4 bytes | -2,147,483,648 to 2,147,483,647 |
| `float` | Single precision floating-point | 4 bytes | ±3.4E±38 (7 digits precision) |
| `double` | Double precision floating-point | 8 bytes | ±1.7E±308 (15 digits precision) |
| `char` | Single character | 1 byte | -128 to 127 or 0 to 255 |
| `bool` | Boolean value (true/false) | 1 byte | true or false |

### Declaring Variables

```cpp
// Declaring variables
int age;             // Integer variable
float price;         // Float variable
double pi;           // Double variable
char grade;          // Character variable
bool isActive;       // Boolean variable

// Declaring and initializing variables
int score = 95;
float average = 85.5f;  // 'f' suffix for float literals
double distance = 45.78;
char letter = 'A';     // Single quotes for char literals
bool isValid = true;   // Boolean values are true or false
```

### Type Modifiers

C++ provides type modifiers to alter the size and range of fundamental data types:

- `short`: Typically 2 bytes
- `long`: Typically 4-8 bytes (platform dependent)
- `long long`: Typically 8 bytes
- `unsigned`: Only non-negative values, doubles the positive range
- `signed`: Default, can represent negative values

```cpp
short int smallNumber = 32767;
long int bigNumber = 2147483647;
long long int veryBigNumber = 9223372036854775807LL;  // 'LL' suffix for long long literals
unsigned int positiveOnly = 4294967295;
```

## Constants and Literals

Constants are variables whose values cannot be changed after initialization.

### Defining Constants

```cpp
// Using const keyword
const int MAX_SCORE = 100;
const double PI = 3.14159;

// Using #define (preprocessor directive)
#define WIDTH 80
#define HEIGHT 25
```

### Literals

Literals are fixed values used in the code:

```cpp
// Integer literals
int decimal = 42;       // Decimal (base 10)
int octal = 052;        // Octal (base 8) - prefix with 0
int hex = 0x2A;         // Hexadecimal (base 16) - prefix with 0x
int binary = 0b101010;  // Binary (C++14) - prefix with 0b

// Floating-point literals
double d1 = 3.14159;    // Double literal
float f1 = 3.14159f;    // Float literal (f suffix)

// Character literals
char c1 = 'A';          // Character literal
char c2 = '\n';         // Escape sequence (newline)
char c3 = '\t';         // Escape sequence (tab)
char c4 = '\\';         // Escape sequence (backslash)

// String literals
const char* s1 = "Hello";            // C-style string
std::string s2 = "Hello C++";        // std::string (requires #include <string>)

// Boolean literals
bool b1 = true;
bool b2 = false;
```

## Input/Output Operations

C++ provides input/output functionality through the `<iostream>` library.

### Output with cout

```cpp
#include <iostream>

int main() {
    int age = 25;
    std::cout << "Hello, World!" << std::endl;
    std::cout << "I am " << age << " years old." << std::endl;
    
    // Output formatting
    std::cout << "Line 1" << std::endl;  // Outputs with newline and flushes buffer
    std::cout << "Line 2\n";            // Outputs with newline only
    
    return 0;
}
```

### Input with cin

```cpp
#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);  // Read entire line including spaces
    
    std::cout << "Enter your age: ";
    std::cin >> age;               // Read a single value
    
    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
    
    return 0;
}
```

### Common Input Issues

```cpp
#include <iostream>
#include <string>

int main() {
    int number;
    std::string text;
    
    std::cout << "Enter a number: ";
    std::cin >> number;
    
    // cin leaves the newline character in the input buffer
    // which will be read by getline, resulting in an empty string
    std::cin.ignore(1000, '\n');  // Clear the input buffer
    
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    
    std::cout << "Number: " << number << ", Text: " << text << std::endl;
    
    return 0;
}
```

## Operators

C++ provides various types of operators for performing operations on variables and values.

### Arithmetic Operators

```cpp
int a = 10, b = 3;

int sum = a + b;        // Addition: 13
int difference = a - b; // Subtraction: 7
int product = a * b;    // Multiplication: 30
int quotient = a / b;   // Division: 3 (integer division)
int remainder = a % b;  // Modulus: 1 (remainder of a/b)

// Floating-point division
double result = 10.0 / 3.0;  // 3.33333...
```

### Increment and Decrement Operators

```cpp
int x = 5;

// Prefix operators
++x;  // Increment x to 6, then use the new value
--x;  // Decrement x to 5, then use the new value

// Postfix operators
x++;  // Use current value of x (5), then increment to 6
x--;  // Use current value of x (6), then decrement to 5

// Difference in expressions
int a = 5, b;
b = ++a;  // a is incremented to 6, then b is assigned 6
int c = 5, d;
d = c++;  // d is assigned 5, then c is incremented to 6
```

### Assignment Operators

```cpp
int x = 10;  // Simple assignment

x += 5;      // Equivalent to: x = x + 5;  (x becomes 15)
x -= 3;      // Equivalent to: x = x - 3;  (x becomes 12)
x *= 2;      // Equivalent to: x = x * 2;  (x becomes 24)
x /= 4;      // Equivalent to: x = x / 4;  (x becomes 6)
x %= 4;      // Equivalent to: x = x % 4;  (x becomes 2)
```

### Relational Operators

```cpp
int a = 10, b = 20;

bool equal = (a == b);          // Equal to: false
bool notEqual = (a != b);       // Not equal to: true
bool greater = (a > b);         // Greater than: false
bool less = (a < b);            // Less than: true
bool greaterEqual = (a >= b);   // Greater than or equal to: false
bool lessEqual = (a <= b);      // Less than or equal to: true
```

### Logical Operators

```cpp
bool condition1 = true;
bool condition2 = false;

bool andResult = condition1 && condition2;  // Logical AND: false
bool orResult = condition1 || condition2;   // Logical OR: true
bool notResult = !condition1;               // Logical NOT: false

// Short-circuit evaluation
bool shortCircuit = (false && someFunction());  // someFunction() is not called
```

### Bitwise Operators

```cpp
int a = 5;  // Binary: 0101
int b = 3;  // Binary: 0011

int bitwiseAND = a & b;   // Bitwise AND: 0001 (1 in decimal)
int bitwiseOR = a | b;    // Bitwise OR: 0111 (7 in decimal)
int bitwiseXOR = a ^ b;   // Bitwise XOR: 0110 (6 in decimal)
int bitwiseNOT = ~a;      // Bitwise NOT: 1111...1010 (-6 in decimal with two's complement)
int leftShift = a << 1;   // Left shift: 1010 (10 in decimal)
int rightShift = a >> 1;  // Right shift: 0010 (2 in decimal)
```

## Type Conversions

C++ allows conversion between different data types.

### Implicit Type Conversion (Automatic)

```cpp
int intValue = 10;
double doubleValue = intValue;  // int to double (no data loss)

double pi = 3.14159;
int intPi = pi;  // double to int (data loss, intPi becomes 3)

bool boolValue = 42;  // Non-zero to bool (boolValue becomes true)
int fromBool = true;  // bool to int (fromBool becomes 1)
```

### Explicit Type Conversion (Casting)

```cpp
// C-style casting (should be avoided in modern C++)
double d = 3.14;
int i = (int)d;  // Explicitly convert double to int

// C++ style casting
double value = 3.14159;
int intValue = static_cast<int>(value);  // Modern C++ cast

// Other C++ casts
// dynamic_cast: Safe downcasting of polymorphic objects
// const_cast: Add or remove const qualifier
// reinterpret_cast: Low-level reinterpreting of bit patterns
```

## Scope of Variables

The scope of a variable defines where the variable is accessible in the code.

### Local Scope

```cpp
#include <iostream>

void exampleFunction() {
    int localVar = 10;  // Local variable
    std::cout << "Inside function: " << localVar << std::endl;
    // localVar is only accessible within this function
}

int main() {
    // localVar is not accessible here
    
    int blockVar;  // Local to the main function
    
    {  // Start of a new block
        int innerVar = 20;  // Local to this block
        blockVar = 30;      // Can access variables from containing scopes
        std::cout << "Inside block: " << innerVar << std::endl;
    }  // End of block, innerVar is destroyed
    
    // innerVar is not accessible here
    std::cout << "blockVar is still accessible: " << blockVar << std::endl;
    
    exampleFunction();
    // Can't access localVar here
    
    return 0;
}
```

### Global Scope

```cpp
#include <iostream>

// Global variable
int globalVar = 100;

void function1() {
    std::cout << "In function1, globalVar: " << globalVar << std::endl;
    globalVar = 200;  // Modifies the global variable
}

void function2() {
    // This local variable hides the global one
    int globalVar = 300;
    std::cout << "Local globalVar in function2: " << globalVar << std::endl;
    
    // Access the global variable using the scope resolution operator
    std::cout << "Global globalVar in function2: " << ::globalVar << std::endl;
}

int main() {
    std::cout << "Initial globalVar: " << globalVar << std::endl;
    
    function1();
    std::cout << "After function1, globalVar: " << globalVar << std::endl;
    
    function2();
    std::cout << "After function2, globalVar: " << globalVar << std::endl;
    
    return 0;
}
```

## Practice Exercises

### Basic Variables and Data Types

1. **Data Type Explorer**: Write a program that declares variables of each basic data type, assigns values, and prints them out with appropriate labels.

2. **Memory Size**: Create a program that prints the size of each data type using `sizeof` operator.
   ```cpp
   #include <iostream>
   
   int main() {
       std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
       // TODO: Print sizes for other data types
       return 0;
   }
   ```

3. **Type Limits**: Write a program to display the minimum and maximum values that can be held by different integer types. (Hint: Use `<limits>` header)

### Constants and Literals

4. **Temperature Converter**: Create a program with constants for freezing and boiling points of water in Celsius and Fahrenheit. Use these constants to convert temperatures entered by the user.

5. **Circle Calculator**: Write a program that uses a constant for π and calculates the area and circumference of a circle based on a user-provided radius.

6. **Different Numbering Systems**: Create a program that demonstrates the use of decimal, octal, hexadecimal, and binary literals to express the same value (e.g., 42).

### Input/Output Operations

7. **Personal Information Collector**: Create a program that asks for the user's name, age, height (in meters), and whether they are a student (yes/no). Then display all information in a formatted output.

8. **Calculator App**: Write a program that reads two numbers and an operator (+, -, *, /) from the user, then performs the appropriate calculation and displays the result.

9. **Formatted Output**: Create a program that displays a table of numbers and their squares and cubes, aligned in columns with proper spacing.
   ```cpp
   #include <iostream>
   #include <iomanip>  // For std::setw
   
   int main() {
       std::cout << std::setw(10) << "Number" << std::setw(10) << "Square" << std::setw(10) << "Cube" << std::endl;
       // TODO: Add rows for numbers 1-10
       return 0;
   }
   ```

### Operators

10. **Arithmetic Operations**: Write a program where the user enters two numbers, and the program shows the result of all arithmetic operations on these numbers.

11. **Even or Odd Detector**: Create a program that determines whether a number entered by the user is even or odd using the modulus operator.

12. **Bitwise Calculator**: Write a program that performs bitwise operations (AND, OR, XOR, NOT) on two integers entered by the user and displays the results in binary format.
    ```cpp
    #include <iostream>
    #include <bitset>  // For binary representation
    
    int main() {
        int a, b;
        std::cout << "Enter two integers: ";
        std::cin >> a >> b;
        
        std::cout << "a in binary: " << std::bitset<8>(a) << std::endl;
        std::cout << "b in binary: " << std::bitset<8>(b) << std::endl;
        
        // TODO: Perform and display bitwise operations
        
        return 0;
    }
    ```

13. **Logical Expression Evaluator**: Create a program that evaluates and explains various logical expressions involving AND, OR, and NOT operators with different combinations of true/false values.

### Type Conversions

14. **Type Conversion Demonstrator**: Write a program that shows examples of implicit and explicit type conversions and their results.

15. **Data Loss Detector**: Create a program that demonstrates data loss due to type conversion, for example, by converting floating-point numbers to integers or large integers to smaller types.

16. **Character Codes**: Write a program that takes a character input and displays its ASCII value, then takes a numeric input and displays the corresponding ASCII character.

### Scope of Variables

17. **Scope Explorer**: Create a program with global variables, local variables in main, and local variables in functions. Demonstrate which variables are accessible from different parts of the program.

18. **Variable Shadowing**: Write a program that demonstrates variable shadowing by having a global variable and a local variable with the same name, and show how to access both.

19. **Block Scope Practice**: Create a program with nested blocks that demonstrates how variables defined in inner blocks are not accessible in outer blocks.

### Integrated Challenges

20. **Mini Banking System**: Create a simple bank account program that allows the user to deposit, withdraw, and check balance. Use appropriate data types and constants for minimum balance requirements.

21. **Grade Calculator**: Write a program that takes scores for multiple subjects, calculates the total and percentage, and assigns a letter grade based on the percentage range.

22. **Temperature Statistics**: Create a program that accepts multiple temperature readings, then calculates and displays the average, maximum, and minimum temperatures.

23. **Bit Manipulation Toolkit**: Write a program that offers various bit manipulation utilities for an integer: set a specific bit, clear a bit, toggle a bit, and check if a bit is set.

## Solutions to Selected Exercises

### Exercise 2: Memory Size
```cpp
#include <iostream>

int main() {
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of float: " << sizeof(float) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of bool: " << sizeof(bool) << " bytes" << std::endl;
    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "Size of long long: " << sizeof(long long) << " bytes" << std::endl;
    return 0;
}
```

### Exercise 5: Circle Calculator
```cpp
#include <iostream>

int main() {
    const double PI = 3.14159265358979323846;
    double radius;
    
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;
    
    double area = PI * radius * radius;
    double circumference = 2 * PI * radius;
    
    std::cout << "Area of the circle: " << area << std::endl;
    std::cout << "Circumference of the circle: " << circumference << std::endl;
    
    return 0;
}
```

### Exercise 11: Even or Odd Detector
```cpp
#include <iostream>

int main() {
    int number;
    
    std::cout << "Enter an integer: ";
    std::cin >> number;
    
    if (number % 2 == 0) {
        std::cout << number << " is even." << std::endl;
    } else {
        std::cout << number << " is odd." << std::endl;
    }
    
    return 0;
}
```

### Exercise 16: Character Codes
```cpp
#include <iostream>

int main() {
    char character;
    int ascii_value;
    
    std::cout << "Enter a character: ";
    std::cin >> character;
    
    ascii_value = static_cast<int>(character);
    std::cout << "ASCII value of '" << character << "' is " << ascii_value << std::endl;
    
    std::cout << "Enter an ASCII value (0-127): ";
    std::cin >> ascii_value;
    
    character = static_cast<char>(ascii_value);
    std::cout << "Character with ASCII value " << ascii_value << " is '" << character << "'" << std::endl;
    
    return 0;
}
```

## Additional Resources

- [C++ Reference - Data Types](https://en.cppreference.com/w/cpp/language/types)
- [C++ Reference - Operators](https://en.cppreference.com/w/cpp/language/operators)
- [C++ IO Streams](https://en.cppreference.com/w/cpp/io)
- [C++ Variable Scope](https://en.cppreference.com/w/cpp/language/scope)