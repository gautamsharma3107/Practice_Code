# Basic Concepts in C++

## Variables and Data Types

Variables are named storage locations in memory that hold data which can be modified during program execution. Each variable has a specific data type that determines what kind of values it can store and how much memory it occupies.

### Common Data Types

| Data Type | Description | Size (typical) | Example |
|-----------|-------------|----------------|---------|
| `int` | Integer values | 4 bytes | `int age = 25;` |
| `float` | Single precision floating-point | 4 bytes | `float price = 19.99f;` |
| `double` | Double precision floating-point | 8 bytes | `double pi = 3.14159265359;` |
| `char` | Single character | 1 byte | `char grade = 'A';` |
| `bool` | Boolean value (true/false) | 1 byte | `bool isActive = true;` |
| `string` | Text string (from `<string>` library) | Variable | `string name = "John";` |

### Example: Working with Different Data Types

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declaring and initializing variables
    int count = 50;
    float temperature = 98.6f;
    double pi = 3.14159265359;
    char initial = 'G';
    bool isRaining = false;
    string name = "John Doe";
    
    // Displaying values and memory sizes
    cout << "Integer value: " << count << ", Size: " << sizeof(count) << " bytes" << endl;
    cout << "Float value: " << temperature << ", Size: " << sizeof(temperature) << " bytes" << endl;
    cout << "Double value: " << pi << ", Size: " << sizeof(pi) << " bytes" << endl;
    cout << "Character value: " << initial << ", Size: " << sizeof(initial) << " byte" << endl;
    cout << "Boolean value: " << isRaining << ", Size: " << sizeof(isRaining) << " byte" << endl;
    cout << "String value: " << name << ", Size: " << sizeof(name) << " bytes" << endl;
    
    return 0;
}
```

### Type Modifiers

Variables can be modified with qualifiers like:
- `short`: Reduces size (e.g., `short int`)
- `long`: Increases size (e.g., `long int`, `long double`)
- `signed`/`unsigned`: Determines whether the variable can hold negative values

```cpp
unsigned long int bigPositiveNum = 4294967295;
short int smallNum = 32767;
```

### Problem Exercises
1. Create a program that declares variables of different data types and prints their sizes.
   - [Link to Problem](https://www.hackerrank.com/challenges/c-tutorial-variables/problem)
2. Create a student record system that stores and displays name, age, GPA, and enrollment status.

## Constants and Literals

Constants are fixed values that cannot be altered during program execution. They improve code readability and maintainability.

### Types of Constants

1. **Literal Constants**: Direct values in code like `100`, `3.14`, `'X'`, `"Hello"`
2. **Defined Constants**: Using `#define` preprocessor directive
3. **Constant Variables**: Using the `const` keyword

### Example: Working with Constants

```cpp
#include <iostream>
#define PI_MACRO 3.14159  // Preprocessor constant
using namespace std;

int main() {
    // Constant variable
    const double PI_CONST = 3.14159;
    
    // Literals
    int intLiteral = 100;         // Integer literal
    double doubleLiteral = 3.14;  // Floating-point literal
    char charLiteral = 'X';       // Character literal
    bool boolLiteral = true;      // Boolean literal
    const char* stringLiteral = "Hello, C++!";  // String literal
    
    // Using constants
    double radius = 5.0;
    double area1 = PI_MACRO * radius * radius;
    double area2 = PI_CONST * radius * radius;
    
    cout << "Area calculated with macro: " << area1 << endl;
    cout << "Area calculated with constant variable: " << area2 << endl;
    
    return 0;
}
```

### Practical Differences

- **#define constants** are processed by the preprocessor (simple text replacement)
- **const variables** are processed by the compiler (type checking, memory allocation)
- Generally, `const` variables are preferred in modern C++ for better type safety

### Problem Exercises
1. Write a program that uses constants to define the value of Pi and calculates the area of a circle.
   - [Link to Problem](https://www.codewars.com/kata/5a2b1c1c8f27c0001b5c1f3e)
2. Create a temperature conversion program that uses constants for freezing and boiling points.

## Input/Output Operations

C++ provides stream-based I/O operations through the `iostream` library. The standard objects are:
- `cin`: Standard input stream (keyboard)
- `cout`: Standard output stream (console)
- `cerr`: Standard error stream (console)
- `clog`: Standard logging stream (console)

### Basic Input/Output Operations

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Variable declarations
    string name;
    int age;
    double height;
    
    // Output to console
    cout << "Welcome to the C++ I/O demonstration!" << endl;
    
    // Input from user
    cout << "Enter your name: ";
    getline(cin, name);  // Reads entire line including spaces
    
    cout << "Enter your age: ";
    cin >> age;
    
    cout << "Enter your height in meters: ";
    cin >> height;
    
    // Output with formatting
    cout << "\n----- User Information -----" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << " years" << endl;
    cout << "Height: " << height << " meters" << endl;
    
    return 0;
}
```

### Input/Output Manipulators

C++ provides manipulators to format output:

```cpp
#include <iostream>
#include <iomanip>  // Required for most manipulators
using namespace std;

int main() {
    double pi = 3.14159265359;
    
    cout << "Default display: " << pi << endl;
    cout << "Fixed notation with 3 decimal places: " 
         << fixed << setprecision(3) << pi << endl;
    
    cout << "Scientific notation: " 
         << scientific << pi << endl;
    
    cout << "Hexadecimal: " 
         << hex << 255 << endl;
    
    cout << "Field width of 10, right-aligned: |" 
         << setw(10) << "Hello" << "|" << endl;
    
    return 0;
}
```

### Problem Exercises
1. Create a program that takes user input for two numbers and outputs their sum.
   - [Link to Problem](https://www.hackerrank.com/challenges/c-tutorial-hello-world/problem)
2. Build a simple calculator that reads an operation (+, -, *, /) and two numbers, then displays the result.

## Operators

Operators are symbols that tell the compiler to perform specific mathematical or logical operations.

### Types of Operators

#### Arithmetic Operators
- `+`: Addition
- `-`: Subtraction
- `*`: Multiplication
- `/`: Division
- `%`: Modulus (remainder)
- `++`: Increment
- `--`: Decrement

#### Relational Operators
- `==`: Equal to
- `!=`: Not equal to
- `>`: Greater than
- `<`: Less than
- `>=`: Greater than or equal to
- `<=`: Less than or equal to

#### Logical Operators
- `&&`: Logical AND
- `||`: Logical OR
- `!`: Logical NOT

#### Bitwise Operators
- `&`: Bitwise AND
- `|`: Bitwise OR
- `^`: Bitwise XOR
- `~`: Bitwise NOT
- `<<`: Left shift
- `>>`: Right shift

#### Assignment Operators
- `=`: Simple assignment
- `+=`, `-=`, `*=`, `/=`, `%=`, etc.: Compound assignment

### Example: Using Different Operators

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;
    
    // Arithmetic operators
    cout << "Arithmetic Operations:" << endl;
    cout << "a + b = " << (a + b) << endl;
    cout << "a - b = " << (a - b) << endl;
    cout << "a * b = " << (a * b) << endl;
    cout << "a / b = " << (a / b) << " (integer division)" << endl;
    cout << "a % b = " << (a % b) << " (remainder)" << endl;
    
    // Increment/Decrement
    int c = a++;  // Post-increment
    int d = ++b;  // Pre-increment
    cout << "After a++: a = " << a << ", c = " << c << endl;
    cout << "After ++b: b = " << b << ", d = " << d << endl;
    
    // Relational operators
    cout << "\nRelational Operations:" << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a > b: " << (a > b) << endl;
    cout << "a < b: " << (a < b) << endl;
    
    // Logical operators
    bool p = true, q = false;
    cout << "\nLogical Operations:" << endl;
    cout << "p && q: " << (p && q) << endl;
    cout << "p || q: " << (p || q) << endl;
    cout << "!p: " << (!p) << endl;
    
    // Bitwise operators
    int x = 5;  // 101 in binary
    int y = 3;  // 011 in binary
    cout << "\nBitwise Operations:" << endl;
    cout << "x & y: " << (x & y) << endl;  // 001 = 1
    cout << "x | y: " << (x | y) << endl;  // 111 = 7
    cout << "x ^ y: " << (x ^ y) << endl;  // 110 = 6
    cout << "~x: " << (~x) << endl;        // Inverts all bits
    cout << "x << 1: " << (x << 1) << endl; // 1010 = 10
    cout << "x >> 1: " << (x >> 1) << endl; // 10 = 2
    
    // Assignment operators
    a = 10;
    cout << "\nAssignment Operations:" << endl;
    cout << "a += 5: " << (a += 5) << endl;  // a = a + 5
    cout << "a -= 3: " << (a -= 3) << endl;  // a = a - 3
    cout << "a *= 2: " << (a *= 2) << endl;  // a = a * 2
    
    return 0;
}
```

### Operator Precedence

C++ operators follow a specific precedence order (e.g., multiplication before addition). Use parentheses to override the default precedence.

### Problem Exercises
1. Write a program that takes two integers and performs all arithmetic operations on them.
   - [Link to Problem](https://www.hackerrank.com/challenges/c-tutorial-operators/problem)
2. Create a program that demonstrates the use of bitwise operators to manipulate individual bits.

## Type Conversions

Type conversion is the process of converting a value from one data type to another.

### Implicit Type Conversion (Automatic)

The compiler automatically converts one data type to another when it makes sense:

```cpp
int x = 10;
double y = x;  // int implicitly converted to double (10.0)

char c = 'A';
int code = c;  // char implicitly converted to int (65, ASCII value)
```

### Explicit Type Conversion (Casting)

Programmers can manually convert values using casting:

#### C-style Casting
```cpp
double pi = 3.14159;
int intPi = (int)pi;  // Explicitly cast double to int (3)
```

#### C++ Style Casting
```cpp
double price = 29.99;
int dollars = static_cast<int>(price);  // Modern C++ cast (29)
```

### Example: Type Conversions

```cpp
#include <iostream>
using namespace std;

int main() {
    // Implicit conversions
    int intValue = 42;
    double doubleValue = intValue;  // int to double (42.0)
    cout << "Implicit int to double: " << doubleValue << endl;
    
    double pi = 3.14159;
    int truncatedPi = pi;  // double to int (3) - data loss!
    cout << "Implicit double to int (truncation): " << truncatedPi << endl;
    
    // Explicit conversions
    double price = 45.67;
    
    // C-style cast
    int dollars1 = (int)price;
    cout << "C-style cast: $" << dollars1 << endl;
    
    // C++ style cast
    int dollars2 = static_cast<int>(price);
    cout << "C++ static_cast: $" << dollars2 << endl;
    
    // Numeric promotion
    char letter = 'A';
    int asciiValue = letter;  // char promoted to int
    cout << "ASCII value of '" << letter << "': " << asciiValue << endl;
    
    // Numeric conversion issues
    int largeValue = 1000000;
    char smallType = largeValue;  // int to char - overflow!
    cout << "Overflow example: " << static_cast<int>(smallType) << endl;
    
    return 0;
}
```

### Problem Exercises
1. Create a program that demonstrates both implicit and explicit type conversions.
   - [Link to Problem](https://www.geeksforgeeks.org/type-conversion-c/)
2. Write a program that shows potential issues with type conversions like overflow and precision loss.

## Scope of Variables

Scope determines where a variable is accessible in a program.

### Types of Variable Scope

1. **Local Variables**: Declared inside a function or block, accessible only within that function/block
2. **Global Variables**: Declared outside all functions, accessible throughout the program
3. **Function Parameters**: Accessible only within the function
4. **Block Scope**: Variables declared within a block (between `{ }`) exist only in that block

### Example: Variable Scope

```cpp
#include <iostream>
using namespace std;

// Global variable - accessible from any function
int globalVar = 100;

void demoFunction(int paramVar) {  // paramVar is a parameter
    // Local variable - accessible only within demoFunction
    int localVar = 50;
    
    {
        // Block scope variable - accessible only within this block
        int blockVar = 25;
        
        cout << "Inside block:" << endl;
        cout << "globalVar: " << globalVar << endl;
        cout << "paramVar: " << paramVar << endl;
        cout << "localVar: " << localVar << endl;
        cout << "blockVar: " << blockVar << endl;
    }
    
    cout << "\nInside function, outside block:" << endl;
    cout << "globalVar: " << globalVar << endl;
    cout << "paramVar: " << paramVar << endl;
    cout << "localVar: " << localVar << endl;
    // cout << "blockVar: " << blockVar << endl;  // Error! blockVar out of scope
}

int main() {
    int mainVar = 200;  // Local to main
    
    cout << "Inside main:" << endl;
    cout << "globalVar: " << globalVar << endl;
    cout << "mainVar: " << mainVar << endl;
    // cout << "localVar: " << localVar << endl;  // Error! localVar not accessible
    
    demoFunction(300);
    
    return 0;
}
```

### Variable Shadowing

When a local variable has the same name as a global variable, the local variable "shadows" the global one:

```cpp
#include <iostream>
using namespace std;

int x = 10;  // Global x

int main() {
    cout << "Global x: " << x << endl;  // 10
    
    int x = 20;  // Local x shadows global x
    cout << "Local x: " << x << endl;   // 20
    
    // Access global x using scope resolution operator
    cout << "Global x again: " << ::x << endl;  // 10
    
    return 0;
}
```

### Problem Exercises
1. Write a program that demonstrates the difference between local and global variables.
   - [Link to Problem](https://www.hackerrank.com/challenges/c-tutorial-scope/problem)
2. Create a program that demonstrates variable shadowing and how to access shadowed variables.

## Conclusion

Understanding these basic concepts is crucial for mastering C++. Practice the exercises linked above to reinforce your knowledge. As you become more comfortable with these fundamentals, you'll be better prepared to tackle more advanced C++ topics like functions, classes, and memory management.

### Next Steps

1. Practice with simple programs that combine multiple concepts
2. Solve the practice problems linked to each section
3. Experiment with different data types and operators
4. Learn how to handle errors and debug C++ programs