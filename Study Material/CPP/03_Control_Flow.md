# Control Flow in C++

Control flow statements allow you to dictate the flow of execution in your C++ programs. These statements determine how your program runs, which code blocks are executed, and in what order. This document provides a comprehensive overview of control flow mechanisms in C++.

## 1. Conditional Statements
Conditional statements allow you to execute certain blocks of code based on specific conditions being evaluated as true or false.

### If Statement

The simplest form of conditional statement that executes a block of code only if the specified condition is true.

```cpp
if (condition) {
    // code to be executed if condition is true
}

// Example
int age = 20;
if (age >= 18) {
    std::cout << "You are eligible to vote." << std::endl;
}
```

### If-Else Statement

Extends the If statement by providing an alternative execution path when the condition is false.

```cpp
if (condition) {
    // code to be executed if condition is true
} else {
    // code to be executed if condition is false
}

// Example
int number = 15;
if (number % 2 == 0) {
    std::cout << number << " is even." << std::endl;
} else {
    std::cout << number << " is odd." << std::endl;
}
```

### Else If Ladder

Used when you need to check multiple conditions in sequence.

```cpp
if (condition1) {
    // code to be executed if condition1 is true
} else if (condition2) {
    // code to be executed if condition1 is false but condition2 is true
} else if (condition3) {
    // code to be executed if condition1 and condition2 are false but condition3 is true
} else {
    // code to be executed if all conditions are false
}

// Example
int score = 85;
if (score >= 90) {
    std::cout << "Grade: A" << std::endl;
} else if (score >= 80) {
    std::cout << "Grade: B" << std::endl;
} else if (score >= 70) {
    std::cout << "Grade: C" << std::endl;
} else if (score >= 60) {
    std::cout << "Grade: D" << std::endl;
} else {
    std::cout << "Grade: F" << std::endl;
}
```

### Nested If Statements

When one conditional statement is placed inside another.

```cpp
if (outer_condition) {
    // code
    if (nested_condition) {
        // code to execute when both outer_condition and nested_condition are true
    }
}

// Example
bool isRaining = true;
bool hasUmbrella = true;

if (isRaining) {
    std::cout << "It's raining outside." << std::endl;
    if (hasUmbrella) {
        std::cout << "Good thing you have an umbrella!" << std::endl;
    } else {
        std::cout << "You should stay inside." << std::endl;
    }
}
```

### Ternary Operator

A shorthand way to write simple if-else statements in a single line.

```cpp
condition ? expression_if_true : expression_if_false;

// Example
int age = 20;
std::string status = (age >= 18) ? "Adult" : "Minor";
std::cout << "Status: " << status << std::endl;
```

### Switch Statement

The switch statement provides an efficient way to select one of many code blocks for execution based on the value of a variable or expression.

```cpp
switch (expression) {
    case constant1:
        // code to be executed if expression equals constant1
        break;
    case constant2:
        // code to be executed if expression equals constant2
        break;
    case constant3:
    case constant4:
        // code to be executed if expression equals constant3 or constant4
        break;
    default:
        // code to be executed if expression doesn't match any constant
}

// Example
int day = 4;
switch (day) {
    case 1:
        std::cout << "Monday" << std::endl;
        break;
    case 2:
        std::cout << "Tuesday" << std::endl;
        break;
    case 3:
        std::cout << "Wednesday" << std::endl;
        break;
    case 4:
        std::cout << "Thursday" << std::endl;
        break;
    case 5:
        std::cout << "Friday" << std::endl;
        break;
    case 6:
    case 7:
        std::cout << "Weekend" << std::endl;
        break;
    default:
        std::cout << "Invalid day" << std::endl;
}
```

Important notes about switch statements:
- The expression must evaluate to an integral or enumeration type
- Each case label must be a constant expression
- The `break` statement is used to terminate the switch block
- Without a break, execution will "fall through" to subsequent cases
- The `default` case is optional and handles all values not explicitly listed

## 2. Loops

Loops are used to execute a block of code repeatedly as long as a specified condition is true or for a specific number of iterations.

### For Loop

The for loop is ideal when you know exactly how many times you want to execute a block of code.

```cpp
for (initialization; condition; increment/decrement) {
    // code to be executed
}

// Example: Print numbers from 1 to 5
for (int i = 1; i <= 5; i++) {
    std::cout << i << " ";
}
// Output: 1 2 3 4 5

// Example: Iterate through an array
int numbers[] = {10, 20, 30, 40, 50};
for (int i = 0; i < 5; i++) {
    std::cout << numbers[i] << " ";
}
// Output: 10 20 30 40 50
```

#### Range-Based For Loop (C++11 and later)

A simplified loop for iterating through arrays, vectors, and other containers.

```cpp
for (declaration : collection) {
    // code to be executed
}

// Example
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (int num : numbers) {
    std::cout << num << " ";
}
// Output: 1 2 3 4 5

// Using auto keyword for type inference
for (auto num : numbers) {
    std::cout << num * 2 << " ";
}
// Output: 2 4 6 8 10
```

### While Loop

The while loop executes a block of code as long as the specified condition is true. The condition is checked before each iteration.

```cpp
while (condition) {
    // code to be executed
}

// Example: Print numbers from 1 to 5
int i = 1;
while (i <= 5) {
    std::cout << i << " ";
    i++;
}
// Output: 1 2 3 4 5

// Example: Read user input until a specific value is entered
int input;
std::cout << "Enter a number (0 to quit): ";
std::cin >> input;
while (input != 0) {
    std::cout << "You entered: " << input << std::endl;
    std::cout << "Enter another number (0 to quit): ";
    std::cin >> input;
}
```

### Do-While Loop

The do-while loop is similar to the while loop, but the condition is checked after each iteration. This ensures that the code block is executed at least once.

```cpp
do {
    // code to be executed
} while (condition);

// Example: Print numbers from 1 to 5
int i = 1;
do {
    std::cout << i << " ";
    i++;
} while (i <= 5);
// Output: 1 2 3 4 5

// Example: Menu-driven program
int choice;
do {
    std::cout << "\nMenu:\n";
    std::cout << "1. Option One\n";
    std::cout << "2. Option Two\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    // Process the choice
    switch (choice) {
        case 1:
            std::cout << "You selected Option One\n";
            break;
        case 2:
            std::cout << "You selected Option Two\n";
            break;
        case 3:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
} while (choice != 3);
```

### Nested Loops

Loops can be nested within other loops to perform more complex operations.

```cpp
// Example: Print a multiplication table
for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= 5; j++) {
        std::cout << i * j << "\t";
    }
    std::cout << std::endl;
}
/* Output:
   1    2    3    4    5
   2    4    6    8    10
   3    6    9    12   15
   4    8    12   16   20
   5    10   15   20   25
*/
```

## 3. Jump Statements

Jump statements alter the flow of execution by transferring control to another part of the program.

### Break Statement

The break statement terminates the execution of the nearest enclosing loop or switch statement.

```cpp
// Example: Find the first occurrence of a number in an array
int numbers[] = {10, 20, 30, 40, 50};
int target = 30;
bool found = false;

for (int i = 0; i < 5; i++) {
    if (numbers[i] == target) {
        std::cout << "Found " << target << " at index " << i << std::endl;
        found = true;
        break; // Exit the loop once the target is found
    }
}

if (!found) {
    std::cout << "Target not found" << std::endl;
}
```

### Continue Statement

The continue statement skips the current iteration of a loop and proceeds with the next iteration.

```cpp
// Example: Print only odd numbers between 1 and 10
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue; // Skip even numbers
    }
    std::cout << i << " ";
}
// Output: 1 3 5 7 9
```

### Return Statement

The return statement terminates the execution of a function and returns control to the calling function. It can also return a value from a function.

```cpp
// Example: Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false; // Not prime
    }
    
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false; // Not prime
        }
    }
    
    return true; // Prime
}
```

### Goto Statement

The goto statement allows you to jump to a specific labeled statement within a function. It's generally discouraged in modern programming due to its potential to create unstructured "spaghetti code."

```cpp
// Example: Using goto to handle errors
void processFile() {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        goto error_handler;
    }
    
    // Process file
    fclose(file);
    return;
    
error_handler:
    std::cout << "Error: Could not open file." << std::endl;
    return;
}
```

## 4. Advanced Control Flow Techniques

### Short-Circuit Evaluation

In logical expressions, C++ uses short-circuit evaluation for the `&&` (AND) and `||` (OR) operators. This means that evaluation stops as soon as the result is determined.

```cpp
// Example: Short-circuit evaluation
int x = 5;
if (x > 0 && x++ < 10) {
    std::cout << "Condition is true, x = " << x << std::endl;
}
// Output: Condition is true, x = 6

int y = 5;
if (y < 0 || y++ < 10) {
    std::cout << "Condition is true, y = " << y << std::endl;
}
// Output: Condition is true, y = 6
```

### Null Statements

A null statement is simply a semicolon (`;`) and does nothing. It's useful when the syntax requires a statement but no action is needed.

```cpp
// Example: Finding the highest power of 2 less than n
int n = 100;
int power = 1;
for (; power * 2 <= n; power *= 2)
    ; // Null statement

std::cout << "Highest power of 2 less than " << n << " is " << power << std::endl;
// Output: Highest power of 2 less than 100 is 64
```

## 5. Problem Exercises

1. Write a program that checks if a number is even or odd using conditional statements.
   ```cpp
   #include <iostream>
   
   int main() {
       int number;
       std::cout << "Enter a number: ";
       std::cin >> number;
       
       if (number % 2 == 0) {
           std::cout << number << " is even." << std::endl;
       } else {
           std::cout << number << " is odd." << std::endl;
       }
       
       return 0;
   }
   ```

2. Create a program that uses a switch statement to display the name of the day based on a number input.
   ```cpp
   #include <iostream>
   
   int main() {
       int day;
       std::cout << "Enter a day number (1-7): ";
       std::cin >> day;
       
       switch (day) {
           case 1:
               std::cout << "Monday" << std::endl;
               break;
           case 2:
               std::cout << "Tuesday" << std::endl;
               break;
           case 3:
               std::cout << "Wednesday" << std::endl;
               break;
           case 4:
               std::cout << "Thursday" << std::endl;
               break;
           case 5:
               std::cout << "Friday" << std::endl;
               break;
           case 6:
               std::cout << "Saturday" << std::endl;
               break;
           case 7:
               std::cout << "Sunday" << std::endl;
               break;
           default:
               std::cout << "Invalid day number. Please enter 1-7." << std::endl;
       }
       
       return 0;
   }
   ```

3. Implement a program that prints all prime numbers between 1 and 100 using loops.
   ```cpp
   #include <iostream>
   #include <cmath>
   
   bool isPrime(int n) {
       if (n <= 1) return false;
       if (n <= 3) return true;
       if (n % 2 == 0 || n % 3 == 0) return false;
       
       for (int i = 5; i * i <= n; i += 6) {
           if (n % i == 0 || n % (i + 2) == 0) {
               return false;
           }
       }
       return true;
   }
   
   int main() {
       std::cout << "Prime numbers between 1 and 100:" << std::endl;
       
       for (int i = 2; i <= 100; i++) {
           if (isPrime(i)) {
               std::cout << i << " ";
           }
       }
       
       return 0;
   }
   ```

4. Write a program that demonstrates the use of break and continue statements in a loop.
   ```cpp
   #include <iostream>
   
   int main() {
       std::cout << "Demonstrating break statement (stopping at 5):" << std::endl;
       for (int i = 1; i <= 10; i++) {
           std::cout << i << " ";
           if (i == 5) {
               std::cout << "(breaking here)" << std::endl;
               break;
           }
       }
       
       std::cout << "\nDemonstrating continue statement (skipping even numbers):" << std::endl;
       for (int i = 1; i <= 10; i++) {
           if (i % 2 == 0) {
               continue;
           }
           std::cout << i << " ";
       }
       
       return 0;
   }
   ```

5. Create a program that uses a goto statement to implement a simple menu system.
   ```cpp
   #include <iostream>
   
   int main() {
       int choice;
       
   menu:
       std::cout << "\n----- Menu -----" << std::endl;
       std::cout << "1. Option One" << std::endl;
       std::cout << "2. Option Two" << std::endl;
       std::cout << "3. Exit" << std::endl;
       std::cout << "Enter your choice: ";
       std::cin >> choice;
       
       switch (choice) {
           case 1:
               std::cout << "You selected Option One" << std::endl;
               goto menu;
           case 2:
               std::cout << "You selected Option Two" << std::endl;
               goto menu;
           case 3:
               std::cout << "Exiting program..." << std::endl;
               break;
           default:
               std::cout << "Invalid choice. Please try again." << std::endl;
               goto menu;
       }
       
       return 0;
   }
   ```

These exercises will help reinforce your understanding of control flow in C++. Practice is essential for mastering these concepts.