# Getting Started with C++

## Introduction to C++

C++ is a powerful, general-purpose programming language developed by Bjarne Stroustrup as an extension of the C language. Key features:

- Object-oriented programming
- Low-level memory manipulation
- High performance
- Rich standard library
- Cross-platform compatibility

C++ is widely used in:
- Systems programming
- Game development
- Real-time systems
- High-performance applications
- Resource-constrained environments

## Setting Up Development Environment

### Windows Setup
1. **Visual Studio Community**:
   - Download from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/)
   - Select "Desktop development with C++" during installation

2. **VS Code + MinGW**:
   - Install VS Code from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install MinGW from [mingw-w64.org](https://www.mingw-w64.org/)
   - Add C++ extension in VS Code
   - Configure compiler path

### Environment Testing
- Create a simple test.cpp file
- Compile and run it to verify setup

## First Program (Hello World)

```cpp
// Hello World Program
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Code Explanation:
- `#include <iostream>`: Includes the input/output stream library
- `int main()`: Entry point of the program
- `std::cout << "Hello, World!" << std::endl;`: Prints text to console
- `return 0;`: Indicates successful program termination

## Basic Syntax and Structure

### Elements of C++ Program:
1. **Preprocessor Directives**: `#include`, `#define`, etc.
2. **Namespaces**: `std::`, `using namespace`
3. **Functions**: `main()` and user-defined functions
4. **Statements and Expressions**: End with semicolons (`;`)
5. **Comments**: `// Single line` or `/* Multi-line */`
6. **Variables and Data Types**: `int`, `float`, `char`, etc.

### Coding Conventions:
- Use meaningful variable and function names
- Consistent indentation (typically 2 or 4 spaces)
- One statement per line
- Use comments to explain complex logic

## Compilation Process

1. **Preprocessing**: Expands macros and includes header files
2. **Compilation**: Converts source code to object code
3. **Linking**: Combines object files and libraries
4. **Execution**: Running the final executable

### Command Line Compilation:
```bash
# Using g++ compiler
g++ hello.cpp -o hello

# Executing the program
./hello
```

## Practice Exercises

1. Create a program that prints your name and age
2. Modify the Hello World program to print multiple lines
3. Experiment with different compiler flags

4. **Basic Input**: Write a program that asks the user for two numbers and displays their sum.
   ```cpp
   #include <iostream>
   
   int main() {
       int num1, num2;
       std::cout << "Enter first number: ";
       std::cin >> num1;
       std::cout << "Enter second number: ";
       std::cin >> num2;
       std::cout << "Sum: " << num1 + num2 << std::endl;
       return 0;
   }
   ```

5. **Interactive Greeting**: Create a program that asks for the user's name and age, then outputs a personalized greeting.

6. **Area Calculator**: Write a program that calculates and displays the area of a rectangle based on user input for length and width.

7. **Temperature Converter**: Create a program that converts temperatures between Celsius and Fahrenheit based on user choice.

8. **Simple Math Quiz**: Design a program that presents the user with simple addition problems and checks their answers.

9. **Multiple Outputs**: Write a program that prints the numbers 1 to 10, each on a new line, using a single cout statement.

10. **Compilation Flags**: Create a simple program and compile it using different optimization flags (like -O0, -O1, -O2, -O3). Measure if there are performance differences.

11. **Command-line Arguments**: Modify your Hello World program to accept a name from the command line:
    ```cpp
    #include <iostream>
    
    int main(int argc, char* argv[]) {
        if (argc > 1) {
            std::cout << "Hello, " << argv[1] << "!" << std::endl;
        } else {
            std::cout << "Hello, World!" << std::endl;
        }
        return 0;
    }
    ```

12. **ASCII Art**: Write a program that displays your initials using ASCII art (made of asterisks or other characters).

13. **Simple Debug Mode**: Create a program with both normal and debug output using preprocessor directives:
    ```cpp
    #include <iostream>
    
    // Comment/uncomment to toggle debug output
    #define DEBUG
    
    int main() {
        int x = 10, y = 20;
        
        #ifdef DEBUG
        std::cout << "Debug: x = " << x << ", y = " << y << std::endl;
        #endif
        
        std::cout << "Result: " << x + y << std::endl;
        return 0;
    }
    ```

14. **Error Messages**: Write a program with deliberate syntax errors. Compile it and try to understand the error messages. Then fix each error one by one.

15. **Separate Compilation**: Create a simple program split across multiple files:
    - A header file with function declarations
    - A source file with function implementations
    - A main file that uses these functions
    
    Then compile and link them together.

## Resources

- [CPlusPlus.com](https://cplusplus.com/doc/tutorial/)
- [C++ Reference](https://en.cppreference.com/)
- [Learn C++](https://www.learncpp.com/)