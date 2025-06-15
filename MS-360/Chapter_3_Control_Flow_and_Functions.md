# Chapter 3: Control Flow & Functions

## 3.1 Conditional Statements (if, else, switch)

Conditional statements allow your program to make decisions and execute different code blocks based on certain conditions.

### if Statement

The `if` statement executes a block of code if a specified condition evaluates to true.

```cpp
if (condition) {
    // Code executed if condition is true
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    if (x > 5) {
        cout << "x is greater than 5" << endl;
    }
    
    return 0;
}
```

### if-else Statement

The `if-else` statement provides an alternative execution path when the condition is false.

```cpp
if (condition) {
    // Code executed if condition is true
} else {
    // Code executed if condition is false
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 75;
    
    if (score >= 60) {
        cout << "You passed!" << endl;
    } else {
        cout << "You failed." << endl;
    }
    
    return 0;
}
```

### if-else if-else Statement

For multiple conditions, you can chain together `if` and `else if` statements.

```cpp
if (condition1) {
    // Code executed if condition1 is true
} else if (condition2) {
    // Code executed if condition1 is false and condition2 is true
} else {
    // Code executed if both condition1 and condition2 are false
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 85;
    
    if (score >= 90) {
        cout << "Grade A" << endl;
    } else if (score >= 80) {
        cout << "Grade B" << endl;
    } else if (score >= 70) {
        cout << "Grade C" << endl;
    } else if (score >= 60) {
        cout << "Grade D" << endl;
    } else {
        cout << "Grade F" << endl;
    }
    
    return 0;
}
```

### Nested if Statements

You can place an `if` statement inside another `if` or `else` block.

```cpp
if (condition1) {
    // Code executed if condition1 is true
    if (condition2) {
        // Code executed if both condition1 and condition2 are true
    }
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    bool hasLicense = true;
    
    if (age >= 18) {
        cout << "You are an adult." << endl;
        
        if (hasLicense) {
            cout << "You can drive." << endl;
        } else {
            cout << "You cannot drive without a license." << endl;
        }
    } else {
        cout << "You are a minor." << endl;
    }
    
    return 0;
}
```

### switch Statement

The `switch` statement tests a variable against multiple values and executes the corresponding code block.

```cpp
switch (expression) {
    case constant1:
        // Code executed if expression equals constant1
        break;
    case constant2:
        // Code executed if expression equals constant2
        break;
    // Additional cases
    default:
        // Code executed if expression doesn't match any case
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int day = 3;
    
    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Invalid day number" << endl;
    }
    
    return 0;
}
```

#### Key Points About switch
- The expression must evaluate to an integral or enumeration type (int, char, enum)
- Each case must be a constant expression (literals or const values)
- The `break` statement terminates the switch block
- Without `break`, execution "falls through" to the next case
- The `default` case is executed if no case matches (optional)

#### Fall-through Behavior
```cpp
#include <iostream>
using namespace std;

int main() {
    int month = 3;
    
    switch (month) {
        case 12:
        case 1:
        case 2:
            cout << "Winter" << endl;
            break;
        case 3:
        case 4:
        case 5:
            cout << "Spring" << endl;
            break;
        case 6:
        case 7:
        case 8:
            cout << "Summer" << endl;
            break;
        case 9:
        case 10:
        case 11:
            cout << "Fall" << endl;
            break;
        default:
            cout << "Invalid month" << endl;
    }
    
    return 0;
}
```

### Best Practices for Conditional Statements

1. **Be Clear and Concise**
   - Keep conditions simple and readable
   - Use parentheses to clarify complex conditions

2. **Consider the Order of Conditions**
   - Place the most common conditions first for efficiency
   - Ensure mutually exclusive conditions are properly ordered

3. **Avoid Common Pitfalls**
   - Don't use assignment (`=`) when you mean equality (`==`)
   - Be cautious with boolean expressions (use `if (isReady)` instead of `if (isReady == true)`)

4. **Choose the Right Tool**
   - Use `if/else if/else` for complex conditions with different types
   - Use `switch` for comparing a single value against multiple constants

5. **Guard Against Edge Cases**
   - Consider boundary conditions
   - Handle unexpected values with default cases

## 3.2 Loops (for, while, do-while)

Loops allow you to execute a block of code repeatedly. There are three main types of loops in C++.

### for Loop

The `for` loop executes a block of code for a specified number of iterations.

```cpp
for (initialization; condition; update) {
    // Code to be repeated
}
```

- **Initialization**: Executed once before the loop begins
- **Condition**: Checked before each iteration; loop continues while true
- **Update**: Executed after each iteration

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    // Print numbers from 1 to 5
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;  // Output: 1 2 3 4 5
    
    return 0;
}
```

#### Variations of for Loop

1. **Multiple Initialization/Update Expressions**:
```cpp
for (int i = 0, j = 10; i < j; i++, j--) {
    cout << "i = " << i << ", j = " << j << endl;
}
```

2. **Omitting Parts**:
```cpp
int i = 0;
for (; i < 5; i++) {  // Initialization omitted
    cout << i << " ";
}

for (int j = 0; j < 5;) {  // Update omitted
    cout << j << " ";
    j++;
}

int k = 0;
for (;;) {  // All parts omitted (infinite loop)
    cout << k << " ";
    k++;
    if (k >= 5) break;
}
```

3. **Range-based for Loop (C++11)**:
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Iterate through each element in numbers
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;  // Output: 1 2 3 4 5
    
    // Using auto for type deduction
    for (auto num : numbers) {
        cout << num * 2 << " ";
    }
    cout << endl;  // Output: 2 4 6 8 10
    
    // Using reference to modify elements
    for (auto& num : numbers) {
        num *= 3;
    }
    
    // Print modified elements
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;  // Output: 3 6 9 12 15
    
    return 0;
}
```

### while Loop

The `while` loop executes a block of code as long as a specified condition is true.

```cpp
while (condition) {
    // Code to be repeated
}
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int count = 1;
    
    while (count <= 5) {
        cout << count << " ";
        count++;
    }
    cout << endl;  // Output: 1 2 3 4 5
    
    return 0;
}
```

#### Use Cases for while Loop

1. **When the number of iterations is unknown beforehand**:
```cpp
#include <iostream>
using namespace std;

int main() {
    int number = 100;
    
    // Count how many divisions by 2 until number < 1
    int steps = 0;
    while (number >= 1) {
        number /= 2;
        steps++;
    }
    
    cout << "Steps needed: " << steps << endl;  // Output: Steps needed: 7
    
    return 0;
}
```

2. **Input validation**:
```cpp
#include <iostream>
using namespace std;

int main() {
    int input;
    
    cout << "Enter a positive number: ";
    cin >> input;
    
    while (input <= 0) {
        cout << "Invalid input. Enter a positive number: ";
        cin >> input;
    }
    
    cout << "You entered: " << input << endl;
    
    return 0;
}
```

### do-while Loop

The `do-while` loop executes a block of code once, then repeats as long as a specified condition is true.

```cpp
do {
    // Code to be repeated
} while (condition);
```

Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int count = 1;
    
    do {
        cout << count << " ";
        count++;
    } while (count <= 5);
    cout << endl;  // Output: 1 2 3 4 5
    
    return 0;
}
```

#### do-while vs while

The key difference is that a `do-while` loop always executes the code block at least once, even if the condition is initially false:

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    // while loop - condition is false, block never executes
    while (x < 10) {
        cout << "This will not be printed (while)" << endl;
    }
    
    // do-while loop - block executes once even though condition is false
    do {
        cout << "This will be printed once (do-while)" << endl;
    } while (x < 10);
    
    return 0;
}
```

#### Common Use Case: Menus

```cpp
#include <iostream>
using namespace std;

int main() {
    int choice;
    
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Option One" << endl;
        cout << "2. Option Two" << endl;
        cout << "3. Option Three" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "You selected Option One" << endl;
                break;
            case 2:
                cout << "You selected Option Two" << endl;
                break;
            case 3:
                cout << "You selected Option Three" << endl;
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 4);
    
    return 0;
}
```

### Nested Loops

You can place one loop inside another loop.

```cpp
#include <iostream>
using namespace std;

int main() {
    // Print a 3x3 pattern
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i << "," << j << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

Output:
```
1,1 1,2 1,3 
2,1 2,2 2,3 
3,1 3,2 3,3 
```

#### Common Applications of Nested Loops

1. **Matrix Operations**:
```cpp
#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Print matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

2. **Pattern Printing**:
```cpp
#include <iostream>
using namespace std;

int main() {
    // Print triangle pattern
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    
    return 0;
}
```

Output:
```
* 
* * 
* * * 
* * * * 
* * * * * 
```

### Loop Control & Efficiency

1. **Loop Variables**
   - Use meaningful variable names
   - Prefer smaller data types when appropriate (e.g., `size_t` for array indices)

2. **Loop Invariant Code Motion**
   - Move calculations outside the loop when possible

```cpp
// Less efficient
for (int i = 0; i < n; i++) {
    result += data[i] * (10 * factor / 2);
}

// More efficient
double temp = 10 * factor / 2;
for (int i = 0; i < n; i++) {
    result += data[i] * temp;
}
```

3. **Loop Unrolling**
   - Manually repeating loop body to reduce overhead of loop control
   - Modern compilers often do this automatically

```cpp
// Standard loop
for (int i = 0; i < 1000; i++) {
    array[i] = i * 2;
}

// Manually unrolled loop (4x)
for (int i = 0; i < 1000; i += 4) {
    array[i] = i * 2;
    array[i+1] = (i+1) * 2;
    array[i+2] = (i+2) * 2;
    array[i+3] = (i+3) * 2;
}
```

4. **Compiler Optimizations**
   - Modern compilers may optimize away loops that don't have side effects
   - Be cautious with micro-optimization - focus on algorithm quality first

## 3.3 Break, Continue, Goto

C++ provides control statements to alter the normal flow of loops and conditional statements.

### break Statement

The `break` statement terminates the innermost enclosing loop or switch statement.

#### In Loops
```cpp
#include <iostream>
using namespace std;

int main() {
    // Find the first number divisible by 7 between 1 and 100
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            cout << "First number divisible by 7: " << i << endl;
            break;  // Exit the loop once found
        }
    }
    
    return 0;
}
```

#### In switch Statements
```cpp
#include <iostream>
using namespace std;

int main() {
    int choice = 2;
    
    switch (choice) {
        case 1:
            cout << "Option 1 selected" << endl;
            break;  // Exit switch statement
        case 2:
            cout << "Option 2 selected" << endl;
            break;  // Exit switch statement
        default:
            cout << "Invalid option" << endl;
    }
    
    return 0;
}
```

#### In Nested Loops
`break` only terminates the innermost loop:

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 3; i++) {
        cout << "i = " << i << endl;
        
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                break;  // Terminates only the inner loop
            }
            cout << "  j = " << j << endl;
        }
    }
    
    return 0;
}
```

Output:
```
i = 1
  j = 1
  j = 2
i = 2
  j = 1
  j = 2
i = 3
  j = 1
  j = 2
```

### continue Statement

The `continue` statement skips the rest of the current iteration and proceeds to the next iteration of the loop.

```cpp
#include <iostream>
using namespace std;

int main() {
    // Print only odd numbers from 1 to 10
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        cout << i << " ";
    }
    cout << endl;  // Output: 1 3 5 7 9
    
    return 0;
}
```

#### With Nested Loops
`continue` only affects the innermost loop:

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 3; i++) {
        cout << "i = " << i << endl;
        
        for (int j = 1; j <= 5; j++) {
            if (j % 2 == 0) {
                continue;  // Skip even j values
            }
            cout << "  j = " << j << endl;
        }
    }
    
    return 0;
}
```

Output:
```
i = 1
  j = 1
  j = 3
  j = 5
i = 2
  j = 1
  j = 3
  j = 5
i = 3
  j = 1
  j = 3
  j = 5
```

### goto Statement

The `goto` statement transfers control to a labeled statement within the same function.

```cpp
#include <iostream>
using namespace std;

int main() {
    int i = 1;
    
start:  // Label
    if (i <= 5) {
        cout << i << " ";
        i++;
        goto start;  // Jump to the labeled statement
    }
    cout << endl;  // Output: 1 2 3 4 5
    
    return 0;
}
```

#### Avoiding goto in Modern C++

While `goto` exists in the language, its use is generally discouraged in modern C++ for several reasons:

1. **Reduces code readability** - Makes control flow hard to follow
2. **Makes debugging difficult** - Leads to "spaghetti code"
3. **Complicates maintenance** - Harder to understand and modify
4. **Better alternatives exist** - Loop statements, functions, exceptions

#### Limited Valid Use Cases

1. **Breaking out of nested loops**
```cpp
#include <iostream>
using namespace std;

int main() {
    bool found = false;
    int target = 42;
    int matrix[3][3] = {{1, 5, 9}, {10, 42, 99}, {7, 13, 21}};
    
    // Search for target in matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == target) {
                cout << "Found at position (" << i << "," << j << ")" << endl;
                goto end_search;  // Break out of both loops
            }
        }
    }
    cout << "Target not found" << endl;
    
end_search:
    // Continue with program
    
    return 0;
}
```

2. **Error handling in resource cleanup** (though exceptions or RAII are preferred in modern C++)

### Best Practices for Control Flow Statements

1. **Use break and continue judiciously**
   - Break when you need to exit a loop early
   - Continue when you need to skip an iteration
   - Use them to simplify logic and avoid deeply nested conditions

2. **Avoid goto in modern code**
   - Use structured programming constructs instead
   - If you must use goto, limit it to very specific scenarios
   - Comment thoroughly to explain your reasoning

3. **Consider alternatives to complex control flow**
   - Extract complex logic into separate functions
   - Use early returns for guard clauses
   - Use the algorithm library for common operations

4. **Be consistent with your approach**
   - Team conventions often dictate which control flow patterns are preferred
   - Document unusual control patterns

## 3.4 Functions: Declaration, Definition, Calling

Functions are reusable blocks of code that perform a specific task. They help organize code, reduce redundancy, and improve maintainability.

### Function Declaration (Prototype)

A function declaration tells the compiler about a function's name, return type, and parameters.

```cpp
return_type function_name(parameter_list);
```

Example:
```cpp
int add(int a, int b);  // Function prototype
double calculateArea(double radius);
void displayMessage();
```

### Function Definition

A function definition includes the function's implementation.

```cpp
return_type function_name(parameter_list) {
    // Function body
    return value;  // If return_type is not void
}
```

Example:
```cpp
int add(int a, int b) {
    return a + b;
}

double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

void displayMessage() {
    cout << "Hello, world!" << endl;
    // No return statement needed for void functions
}
```

### Function Calling

To use a function, you call it by name and provide any required arguments.

```cpp
#include <iostream>
using namespace std;

// Function declaration
int add(int a, int b);

int main() {
    // Function calls
    int sum = add(5, 3);
    cout << "5 + 3 = " << sum << endl;
    
    cout << "7 + 2 = " << add(7, 2) << endl;  // Call and use result directly
    
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}
```

### Parts of a Function

1. **Return Type**: The data type of the value returned by the function
2. **Function Name**: Identifier used to call the function
3. **Parameters**: Variables that receive values passed when the function is called
4. **Function Body**: Code that executes when the function is called
5. **Return Statement**: Returns a value and exits the function

### Void Functions

Functions that do not return a value have the `void` return type.

```cpp
#include <iostream>
using namespace std;

void printStars(int count) {
    for (int i = 0; i < count; i++) {
        cout << "*";
    }
    cout << endl;
}

int main() {
    printStars(5);  // Outputs: *****
    printStars(10); // Outputs: **********
    
    return 0;
}
```

### Return Statement

The `return` statement ends a function's execution and optionally returns a value.

```cpp
#include <iostream>
using namespace std;

bool isEven(int number) {
    if (number % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

// More concise version
bool isEvenConcise(int number) {
    return number % 2 == 0;
}

int main() {
    cout << "Is 4 even? " << (isEven(4) ? "Yes" : "No") << endl;
    cout << "Is 7 even? " << (isEven(7) ? "Yes" : "No") << endl;
    
    return 0;
}
```

### Early Return

You can use multiple return statements, which is useful for handling special cases or implementing guard clauses.

```cpp
#include <iostream>
#include <cmath>
using namespace std;

double squareRoot(double x) {
    if (x < 0) {
        cout << "Error: Cannot calculate square root of negative number" << endl;
        return -1; // Error indicator
    }
    
    return sqrt(x);
}

int main() {
    cout << "Square root of 16: " << squareRoot(16) << endl;
    cout << "Square root of -4: " << squareRoot(-4) << endl;
    
    return 0;
}
```

### Function Scope

Variables declared inside a function are local to that function.

```cpp
#include <iostream>
using namespace std;

void function1() {
    int x = 10;
    cout << "In function1, x = " << x << endl;
}

void function2() {
    int x = 20;  // Different variable, same name
    cout << "In function2, x = " << x << endl;
}

int main() {
    function1();  // Outputs: In function1, x = 10
    function2();  // Outputs: In function2, x = 20
    
    // cout << x << endl;  // Error: x is not defined in this scope
    
    return 0;
}
```

### Forward Declaration

Forward declaration allows you to use a function before its definition appears in the code.

```cpp
#include <iostream>
using namespace std;

// Forward declarations
int multiply(int a, int b);
void displayResult(int result);

int main() {
    int product = multiply(4, 5);
    displayResult(product);
    
    return 0;
}

// Function definitions
int multiply(int a, int b) {
    return a * b;
}

void displayResult(int result) {
    cout << "The result is: " << result << endl;
}
```

### Function Signatures

A function signature includes the function name and parameter types (not the return type).

```cpp
#include <iostream>
using namespace std;

// These functions have different signatures
void display(int x);
void display(double x);
void display(int x, int y);

int main() {
    display(5);        // Calls display(int)
    display(3.14);     // Calls display(double)
    display(10, 20);   // Calls display(int, int)
    
    return 0;
}

void display(int x) {
    cout << "Integer: " << x << endl;
}

void display(double x) {
    cout << "Double: " << x << endl;
}

void display(int x, int y) {
    cout << "Two integers: " << x << " and " << y << endl;
}
```

### Best Practices for Functions

1. **Single Responsibility Principle**
   - Each function should do one thing and do it well
   - Break complex tasks into smaller functions

2. **Meaningful Names**
   - Use descriptive function names (verbs for actions)
   - Parameter names should clearly indicate purpose

3. **Keep Functions Short**
   - Aim for less than 20-30 lines per function
   - Longer functions are harder to test and maintain

4. **Consistent Parameter Order**
   - Keep similar parameters in the same order across functions
   - Consider using named parameters for complex interfaces

5. **Documentation**
   - Comment purpose, parameters, return values, and exceptions
   - Include examples for complex functions

6. **Error Handling**
   - Define how errors are reported (return codes, exceptions)
   - Validate input parameters

## 3.5 Function Parameters: Call by Value & Reference

Function parameters can be passed in different ways, which affects how the function can interact with the arguments.

### Call by Value

In call by value, a copy of the argument is passed to the function. Changes to the parameter inside the function do not affect the original argument.

```cpp
#include <iostream>
using namespace std;

void incrementValue(int x) {
    x++;  // Modifies the local copy, not the original
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 10;
    
    cout << "Before function call: num = " << num << endl;
    incrementValue(num);
    cout << "After function call: num = " << num << endl;
    
    return 0;
}
```

Output:
```
Before function call: num = 10
Inside function: x = 11
After function call: num = 10
```

#### Advantages of Call by Value
- Original value is protected from changes
- Prevents unintended side effects
- Makes function behavior more predictable

#### Disadvantages of Call by Value
- Copying large objects can be inefficient
- Cannot modify the original argument

### Call by Reference

In call by reference, a reference to the original argument is passed to the function. Changes to the parameter inside the function affect the original argument.

```cpp
#include <iostream>
using namespace std;

void incrementReference(int& x) {
    x++;  // Modifies the original value
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 10;
    
    cout << "Before function call: num = " << num << endl;
    incrementReference(num);
    cout << "After function call: num = " << num << endl;
    
    return 0;
}
```

Output:
```
Before function call: num = 10
Inside function: x = 11
After function call: num = 11
```

#### Advantages of Call by Reference
- No copy is made, which is efficient for large objects
- Allows functions to modify the original argument
- Can return multiple values via reference parameters

#### Disadvantages of Call by Reference
- Original value can be changed (may be unintended)
- The relationship between argument and parameter is less obvious

### Const References

To get the efficiency of call by reference without allowing modifications, use const references:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Efficient (no copying) but prevents modification
void displayDetails(const string& name, const int& age) {
    cout << "Name: " << name << ", Age: " << age << endl;
    // name = "John";  // Error: cannot modify a const reference
}

int main() {
    string person = "Alice";
    int years = 30;
    
    displayDetails(person, years);
    
    return 0;
}
```

### Call by Pointer

Another way to achieve call by reference is by using pointers:

```cpp
#include <iostream>
using namespace std;

void incrementPointer(int* x) {
    (*x)++;  // Dereference and increment
    cout << "Inside function: *x = " << *x << endl;
}

int main() {
    int num = 10;
    
    cout << "Before function call: num = " << num << endl;
    incrementPointer(&num);  // Pass the address of num
    cout << "After function call: num = " << num << endl;
    
    return 0;
}
```

Output:
```
Before function call: num = 10
Inside function: *x = 11
After function call: num = 11
```

#### References vs. Pointers

1. **Syntax**
   - References: `void func(int& x)`
   - Pointers: `void func(int* x)`

2. **Calling Convention**
   - References: `func(num)`
   - Pointers: `func(&num)`

3. **Nullability**
   - References: Cannot be null, must be initialized
   - Pointers: Can be null, must be checked

4. **Reassignment**
   - References: Cannot be reassigned to reference another variable
   - Pointers: Can be redirected to point to different variables

### When to Use Each Method

1. **Call by Value**:
   - For small, primitive types (int, char, bool)
   - When you don't need to modify the original value
   - When you want to ensure function doesn't modify arguments

2. **Call by Reference**:
   - For large objects to avoid copying
   - When you need to modify the original value
   - When returning multiple results

3. **Call by Const Reference**:
   - For large objects when you only need to read them
   - Most string and container parameters

4. **Call by Pointer**:
   - When parameter might be null
   - When you need to reassign the parameter
   - When working with C-style APIs

### Multiple Return Values via References

```cpp
#include <iostream>
using namespace std;

void calculateStats(const int arr[], int size, double& average, int& min, int& max) {
    if (size <= 0) return;
    
    int sum = 0;
    min = arr[0];
    max = arr[0];
    
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    average = static_cast<double>(sum) / size;
}

int main() {
    int data[] = {5, 3, 8, 1, 9, 4};
    int size = sizeof(data) / sizeof(data[0]);
    
    double avg;
    int minimum, maximum;
    
    calculateStats(data, size, avg, minimum, maximum);
    
    cout << "Average: " << avg << endl;
    cout << "Minimum: " << minimum << endl;
    cout << "Maximum: " << maximum << endl;
    
    return 0;
}
```

### Using References for Efficiency

When working with large objects, passing by reference is much more efficient:

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Inefficient: copies the entire vector
void processByValue(vector<string> data) {
    // Function body
}

// Efficient: uses a reference
void processByReference(const vector<string>& data) {
    // Function body
}

int main() {
    vector<string> largeData(10000, "Large String");
    
    processByValue(largeData);     // Copies 10,000 strings
    processByReference(largeData); // No copying
    
    return 0;
}
```

## 3.6 Recursion in C++

Recursion is a technique where a function calls itself to solve a problem by breaking it down into smaller instances of the same problem.

### Basic Recursion Concept

A recursive function has two main components:
1. **Base Case**: The condition(s) under which the function stops calling itself
2. **Recursive Case**: The condition(s) under which the function calls itself

```cpp
#include <iostream>
using namespace std;

void countdown(int n) {
    // Base case
    if (n <= 0) {
        cout << "Blastoff!" << endl;
        return;
    }
    
    // Current step
    cout << n << endl;
    
    // Recursive case
    countdown(n - 1);
}

int main() {
    countdown(5);
    return 0;
}
```

Output:
```
5
4
3
2
1
Blastoff!
```

### Factorial Calculation

A classic example of recursion is calculating the factorial of a number.

```cpp
#include <iostream>
using namespace std;

// Recursive factorial function
unsigned long long factorial(unsigned int n) {
    // Base case
    if (n == 0 || n == 1) {
        return 1;
    }
    
    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    cout << "5! = " << factorial(5) << endl;  // 120
    cout << "10! = " << factorial(10) << endl;  // 3628800
    
    return 0;
}
```

### Fibonacci Sequence

Another common example is generating Fibonacci numbers.

```cpp
#include <iostream>
using namespace std;

int fibonacci(int n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << "Fibonacci sequence (first 10 numbers):" << endl;
    for (int i = 0; i < 10; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;  // Output: 0 1 1 2 3 5 8 13 21 34
    
    return 0;
}
```

### Understanding the Call Stack

Each recursive call adds a new frame to the call stack, which stores local variables and the return address.

```
Execution of factorial(5):

Call Stack (bottom to top):
main()
factorial(5)
    return 5 * factorial(4)
    factorial(4)
        return 4 * factorial(3)
        factorial(3)
            return 3 * factorial(2)
            factorial(2)
                return 2 * factorial(1)
                factorial(1)
                    return 1
                returns: 2 * 1 = 2
            returns: 3 * 2 = 6
        returns: 4 * 6 = 24
    returns: 5 * 24 = 120
final result: 120
```

### Recursion vs. Iteration

Both recursion and iteration can solve the same problems, but they have different characteristics:

1. **Memory Usage**:
   - Recursion: Uses more memory due to call stack overhead
   - Iteration: Typically uses less memory

2. **Code Clarity**:
   - Recursion: Often more elegant and clear for certain problems
   - Iteration: Can be more straightforward for simple problems

3. **Performance**:
   - Recursion: Often slower due to function call overhead
   - Iteration: Usually faster

Example of factorial using iteration:

```cpp
#include <iostream>
using namespace std;

unsigned long long factorialIterative(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    cout << "5! = " << factorialIterative(5) << endl;  // 120
    return 0;
}
```

### Tail Recursion

Tail recursion is a special form of recursion where the recursive call is the last operation in the function. Modern compilers can optimize tail-recursive functions to use constant stack space.

```cpp
#include <iostream>
using namespace std;

// Non-tail-recursive factorial
unsigned long long factorial(unsigned int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);  // Must multiply after the recursive call returns
}

// Tail-recursive factorial
unsigned long long factorialTail(unsigned int n, unsigned long long accumulator = 1) {
    if (n == 0 || n == 1) return accumulator;
    return factorialTail(n - 1, n * accumulator);  // No pending operations after the recursive call
}

int main() {
    cout << "5! = " << factorial(5) << endl;
    cout << "5! (tail recursive) = " << factorialTail(5) << endl;
    
    return 0;
}
```

### Indirect Recursion

Indirect recursion occurs when function A calls function B, which in turn calls function A.

```cpp
#include <iostream>
using namespace std;

void functionB(int n);  // Forward declaration

void functionA(int n) {
    if (n > 0) {
        cout << "A: " << n << endl;
        functionB(n - 1);
    }
}

void functionB(int n) {
    if (n > 0) {
        cout << "B: " << n << endl;
        functionA(n - 1);
    }
}

int main() {
    functionA(3);
    return 0;
}
```

Output:
```
A: 3
B: 2
A: 1
B: 0
```

### Common Applications of Recursion

1. **Tree and Graph Traversal**:
```cpp
void traverseTree(TreeNode* node) {
    if (node == nullptr) return;
    
    // Process current node
    cout << node->value << " ";
    
    // Recursively process children
    traverseTree(node->left);
    traverseTree(node->right);
}
```

2. **Divide and Conquer Algorithms**:
```cpp
int binarySearch(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        
        if (arr[mid] > target)
            return binarySearch(arr, left, mid - 1, target);
        
        return binarySearch(arr, mid + 1, right, target);
    }
    
    return -1;  // Not found
}
```

3. **Backtracking**:
```cpp
bool solveNQueens(int board[N][N], int col) {
    // Base case: if all queens are placed
    if (col >= N) return true;
    
    // Try placing queen in each row of the current column
    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            // Place this queen in board[row][col]
            board[row][col] = 1;
            
            // Recur to place rest of the queens
            if (solveNQueens(board, col + 1))
                return true;
            
            // If placing queen doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }
    
    return false;  // No solution found
}
```

### Pitfalls of Recursion

1. **Stack Overflow**:
If recursion is too deep, it can exhaust the available stack space.
```cpp
// This will cause stack overflow for large values of n
int badRecursion(int n) {
    return badRecursion(n-1) + badRecursion(n-2);  // Missing base case!
}
```

2. **Redundant Calculations**:
Naive recursive implementations can repeat calculations.
```cpp
// Inefficient fibonacci - many calculations are repeated
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);  // fib(n-2) is calculated multiple times
}
```

3. **Solutions**:
   - **Memoization**: Store already computed results
   - **Dynamic Programming**: Build solutions from bottom-up
   - **Iteration**: Convert to iterative form when appropriate

### Memoization Example

```cpp
#include <iostream>
#include <vector>
using namespace std;

int fibMemoized(int n, vector<int>& memo) {
    if (n <= 1) return n;
    
    // Return cached result if available
    if (memo[n] != -1) return memo[n];
    
    // Calculate and cache the result
    memo[n] = fibMemoized(n - 1, memo) + fibMemoized(n - 2, memo);
    return memo[n];
}

int fibonacci(int n) {
    // Initialize memoization array with -1
    vector<int> memo(n + 1, -1);
    return fibMemoized(n, memo);
}

int main() {
    cout << "Fibonacci(40): " << fibonacci(40) << endl;  // Much faster than naive recursion
    return 0;
}
```

## 3.7 Inline Functions

Inline functions are a C++ enhancement to improve performance by avoiding function call overhead, especially for small functions.

### Function Call Overhead

When a function is called, several operations occur:
1. Parameter values are pushed onto the stack
2. Control jumps to the function location
3. Local variables are allocated
4. The function executes
5. Return value is placed where the caller can access it
6. Control returns to the caller
7. Stack is cleaned up

For small functions, this overhead can be significant relative to the function's actual work.

### Inline Functions Concept

Inline functions suggest to the compiler that it should try to replace the function call with the function's code at the call site.

```cpp
#include <iostream>
using namespace std;

// Inline function declaration
inline int square(int x) {
    return x * x;
}

int main() {
    int result = square(5);  // The compiler may replace this with: int result = 5 * 5;
    
    cout << "The square is: " << result << endl;
    
    return 0;
}
```

### Defining Inline Functions

Two common ways to define inline functions:

1. **Using the `inline` keyword**:
```cpp
inline int max(int a, int b) {
    return (a > b) ? a : b;
}
```

2. **Defining the function within a class definition** (implicitly inline):
```cpp
class Rectangle {
public:
    // Implicitly inline
    int area() {
        return width * height;
    }
    
    int width;
    int height;
};
```

### When to Use Inline Functions

Inline functions are most beneficial when:

1. **The function is small** (a few lines of code)
2. **The function is called frequently**
3. **Function call overhead is significant relative to the function's work**
4. **Performance is critical** in that section of code

Common examples:
- Simple accessors and mutators (getters/setters)
- Small utility functions
- Simple mathematical operations

### Advantages of Inline Functions

1. **Reduced function call overhead**
2. **Potential for additional compiler optimizations** since the code is visible at the call site
3. **No stack operations** for parameters and return values
4. **Maintains the abstraction of functions** unlike macros

### Disadvantages of Inline Functions

1. **Code bloat**: If an inline function is large and called in many places, the compiled code size increases
2. **Limited debugging**: Breakpoints might behave unexpectedly
3. **Not suitable for functions that change frequently**: Changes require recompilation of all calling code
4. **The `inline` keyword is only a suggestion**: The compiler may ignore it

### Inline vs. Macros

Before inline functions, C-style macros served a similar purpose:

```cpp
// Macro definition
#define SQUARE(x) ((x) * (x))

// Inline function
inline int square(int x) {
    return x * x;
}
```

Advantages of inline functions over macros:
1. **Type safety**: Inline functions respect C++ type system
2. **No unexpected behavior**: Macros are simple text substitution which can lead to bugs
3. **Proper evaluation of arguments**: Each argument in a function is evaluated exactly once
4. **Debugging support**: Inline functions can be debugged; macros cannot

### Example of Macro Problems

```cpp
#include <iostream>
using namespace std;

#define SQUARE(x) (x * x)

int main() {
    int a = 5;
    cout << "SQUARE(a+1) = " << SQUARE(a+1) << endl;  // Expands to: (a+1 * a+1) = 5+1*5+1 = 11, not 36!
    
    return 0;
}
```

Corrected macro (but still not as good as inline function):
```cpp
#define SQUARE(x) ((x) * (x))
```

### Compiler Decisions on Inlining

Modern compilers make sophisticated decisions about inlining:

1. They may inline functions even without the `inline` keyword
2. They may refuse to inline functions marked as `inline` if they determine it's not beneficial
3. They consider factors like:
   - Function size
   - How often it's called
   - Call context
   - Optimization level

### Best Practices for Inline Functions

1. **Use inline for very small functions** (1-3 lines of code)
2. **Don't inline complex functions** with loops or complex control structures
3. **Be aware that `inline` is a suggestion**, not a command
4. **Let the compiler decide** when unsure (modern compilers are good at this)
5. **Profile before optimizing** to identify if function call overhead is actually a bottleneck
6. **Consider templates for type-generic inline functions**

### Example of a Practical Inline Function

```cpp
#include <iostream>
using namespace std;

class Vector3D {
private:
    double x, y, z;

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
    
    // Inline accessors
    inline double getX() const { return x; }
    inline double getY() const { return y; }
    inline double getZ() const { return z; }
    
    // Inline mutators
    inline void setX(double val) { x = val; }
    inline void setY(double val) { y = val; }
    inline void setZ(double val) { z = val; }
    
    // Inline utility function
    inline double dotProduct(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // Not a good candidate for inline due to complexity
    Vector3D crossProduct(const Vector3D& other) const;
};

// Complex function defined outside the class
Vector3D Vector3D::crossProduct(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

int main() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    
    // These calls may be inlined
    cout << "Dot product: " << v1.dotProduct(v2) << endl;
    
    // This call might not be inlined due to complexity
    Vector3D v3 = v1.crossProduct(v2);
    
    return 0;
}
```

### Function Inlining in Headers vs. Source Files

1. **Inline functions in headers**:
   - Must be fully defined in the header file
   - Each translation unit that includes the header gets its own copy
   - No linking issues when defined in multiple files

2. **Regular functions in headers**:
   - If defined (not just declared) in headers, cause multiple definition errors
   - Should only be declared in headers, with definition in one source file

```cpp
// In header file "utils.h"
inline int add(int a, int b) {
    return a + b;  // Definition in header is fine for inline functions
}

int subtract(int a, int b);  // Only declaration for regular functions

// In source file "utils.cpp"
#include "utils.h"

int subtract(int a, int b) {
    return a - b;  // Definition goes in source file
}
```
```

With these notes, the student will have comprehensive details on Chapter 3 topics including control flow statements, functions, function parameters, recursion, and inline functions. The content includes detailed explanations, code examples, best practices, and important concepts to help master these fundamental C++ concepts.
