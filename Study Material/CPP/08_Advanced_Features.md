# Advanced C++ Features

This document covers advanced features of C++ programming, including exception handling, custom exceptions, file I/O, templates, namespaces, preprocessor directives, and type casting. Each section includes explanations, examples, and problem exercises with links to relevant coding platforms.

## 1. Exception Handling

### Overview
Exception handling in C++ allows you to manage errors and exceptional situations in a controlled manner. It uses three keywords: `try`, `catch`, and `throw`.

### Example
```cpp
#include <iostream>
using namespace std;

void checkAge(int age) {
    if (age < 18) {
        throw "Age must be 18 or older.";
    }
}

int main() {
    try {
        checkAge(15);
    } catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
    return 0;
}
```

### Problem Exercises
- [Exception Handling Practice Problems](https://www.hackerrank.com/domains/tutorials/10-days-of-cpp)

## 2. Custom Exceptions

### Overview
You can create your own exception classes by inheriting from the standard exception class.

### Example
```cpp
#include <iostream>
#include <exception>
using namespace std;

class CustomException : public exception {
public:
    const char* what() const noexcept override {
        return "This is a custom exception!";
    }
};

int main() {
    try {
        throw CustomException();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}
```

### Problem Exercises
- [Custom Exceptions Practice Problems](https://www.geeksforgeeks.org/c-throwing-custom-exceptions/)

## 3. File I/O

### Overview
C++ provides file handling capabilities through the fstream library, allowing you to read from and write to files.

### Example
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("example.txt");
    outFile << "Hello, File I/O!" << endl;
    outFile.close();

    ifstream inFile("example.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    return 0;
}
```

### Problem Exercises
- [File I/O Practice Problems](https://www.hackerrank.com/challenges/cpp-file-io)

## 4. Templates

### Overview
Templates allow you to write generic and reusable code. You can create function templates and class templates.

### Example
```cpp
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add<int>(5, 3) << endl; // Outputs 8
    cout << add<double>(5.5, 3.2) << endl; // Outputs 8.7
    return 0;
}
```

### Problem Exercises
- [Templates Practice Problems](https://www.geeksforgeeks.org/templates-c/)

## 5. Namespaces

### Overview
Namespaces help avoid name conflicts in larger projects by grouping identifiers.

### Example
```cpp
#include <iostream>
using namespace std;

namespace MyNamespace {
    void display() {
        cout << "Hello from MyNamespace!" << endl;
    }
}

int main() {
    MyNamespace::display();
    return 0;
}
```

### Problem Exercises
- [Namespaces Practice Problems](https://www.hackerrank.com/challenges/cpp-namespace)

## 6. Preprocessor Directives

### Overview
Preprocessor directives are commands that are processed before compilation, such as `#include`, `#define`, and `#ifdef`.

### Example
```cpp
#include <iostream>
#define PI 3.14

int main() {
    std::cout << "Value of PI: " << PI << std::endl;
    return 0;
}
```

### Problem Exercises
- [Preprocessor Directives Practice Problems](https://www.geeksforgeeks.org/preprocessor-c/)

## 7. Type Casting

### Overview
C++ provides several ways to cast types, including `static_cast`, `dynamic_cast`, `const_cast`, and `reinterpret_cast`.

### Example
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; }
};

class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};

int main() {
    Base* b = new Derived();
    Derived* d = dynamic_cast<Derived*>(b);
    if (d) {
        d->show(); // Outputs "Derived class"
    }
    delete b;
    return 0;
}
```

### Problem Exercises
- [Type Casting Practice Problems](https://www.geeksforgeeks.org/typecasting-c/)

## Conclusion

This document provides an overview of advanced C++ features. For further practice, refer to the problem exercises linked above.