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

## Resources

- [CPlusPlus.com](https://cplusplus.com/doc/tutorial/)
- [C++ Reference](https://en.cppreference.com/)
- [Learn C++](https://www.learncpp.com/)