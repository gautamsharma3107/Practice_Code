# Control Flow in C++

Control flow statements allow you to dictate the flow of execution in your C++ programs. This file covers the following topics:

## 1. Conditional Statements
Conditional statements allow you to execute certain blocks of code based on specific conditions.

### If Statement
```cpp
if (condition) {
    // code to be executed if condition is true
}
```

### If-Else Statement
```cpp
if (condition) {
    // code to be executed if condition is true
} else {
    // code to be executed if condition is false
}
```

### Else If Ladder
```cpp
if (condition1) {
    // code to be executed if condition1 is true
} else if (condition2) {
    // code to be executed if condition2 is true
} else {
    // code to be executed if both conditions are false
}
```

### Switch Statement
The switch statement is used to execute one block of code among many alternatives.
```cpp
switch (expression) {
    case constant1:
        // code to be executed if expression equals constant1
        break;
    case constant2:
        // code to be executed if expression equals constant2
        break;
    default:
        // code to be executed if expression doesn't match any constant
}
```

## 2. Loops
Loops are used to execute a block of code repeatedly.

### For Loop
```cpp
for (initialization; condition; increment) {
    // code to be executed
}
```

### While Loop
```cpp
while (condition) {
    // code to be executed
}
```

### Do-While Loop
```cpp
do {
    // code to be executed
} while (condition);
```

## 3. Break and Continue Statements
- **Break Statement**: Terminates the loop or switch statement.
- **Continue Statement**: Skips the current iteration and proceeds to the next iteration of the loop.

### Example
```cpp
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break; // exits the loop when i is 5
    }
}

for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue; // skips the even numbers
    }
    // code to execute for odd numbers
}
```

## 4. Goto Statement
The goto statement allows you to jump to a specific label in the code. It is generally discouraged due to readability issues.

### Example
```cpp
goto label;

label:
    // code to be executed
```

## Problem Exercises
1. Write a program that checks if a number is even or odd using conditional statements.
   - [Link to Problem](https://www.example.com/problem1)

2. Create a program that uses a switch statement to display the name of the day based on a number input (1 for Monday, 2 for Tuesday, etc.).
   - [Link to Problem](https://www.example.com/problem2)

3. Implement a program that prints all prime numbers between 1 and 100 using loops.
   - [Link to Problem](https://www.example.com/problem3)

4. Write a program that demonstrates the use of break and continue statements in a loop.
   - [Link to Problem](https://www.example.com/problem4)

5. Create a program that uses a goto statement to jump to a specific part of the code based on user input.
   - [Link to Problem](https://www.example.com/problem5)

These exercises will help reinforce your understanding of control flow in C++.