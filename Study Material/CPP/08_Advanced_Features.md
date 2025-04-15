# Advanced C++ Features

This document provides a comprehensive overview of advanced C++ programming features, including exception handling, custom exceptions, file I/O operations, templates, namespaces, preprocessor directives, and type casting. Each section includes detailed explanations, practical examples, and problem exercises with links to relevant coding platforms.

## 1. Exception Handling

### Overview
Exception handling is a powerful mechanism in C++ that allows you to separate error-handling code from normal code. It provides a structured approach to detecting and responding to runtime anomalies through the use of three keywords:
- `try`: Contains code that might throw an exception
- `catch`: Handles the exception if one is thrown in the try block
- `throw`: Signals that an exception has occurred

### Example
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw runtime_error("Division by zero!");
    }
    return a / b;
}

int main() {
    try {
        cout << "Result: " << divide(10, 2) << endl;  // Works fine
        cout << "Result: " << divide(10, 0) << endl;  // Throws exception
    } 
    catch (const runtime_error& e) {
        cerr << "Runtime error: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown exception caught!" << endl;
    }
    
    cout << "Program continues after exception handling" << endl;
    return 0;
}
```

### Advanced Example: Multiple Exception Types
```cpp
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

void processInput(int value) {
    if (value < 0) {
        throw invalid_argument("Negative value not allowed");
    } else if (value > 100) {
        throw out_of_range("Value exceeds maximum limit");
    } else if (value == 0) {
        throw runtime_error("Zero value causes runtime error");
    }
    cout << "Processing value: " << value << endl;
}

int main() {
    int inputs[] = {-5, 50, 150, 0};
    
    for (int input : inputs) {
        try {
            cout << "Trying to process: " << input << endl;
            processInput(input);
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Out of range: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "Standard exception: " << e.what() << endl;
        }
        cout << "--------------------" << endl;
    }
    
    return 0;
}
```

### Problem Exercises
- [HackerRank: Exception Handling](https://www.hackerrank.com/domains/cpp/cpp-exceptions)
- [LeetCode: Error Handling Problems](https://leetcode.com/problemset/all/)
- [GeeksforGeeks: Exception Handling Practice](https://practice.geeksforgeeks.org/explore?category=cpp)

## 2. Custom Exceptions

### Overview
C++ allows you to create your own exception classes by inheriting from the standard exception classes. This enables you to define application-specific exceptions with custom error information and behavior.

Custom exceptions offer several advantages:
- Providing specific error information
- Creating a hierarchy of related exceptions
- Distinguishing between different error types
- Making error handling more descriptive

### Basic Example
```cpp
#include <iostream>
#include <exception>
#include <string>
using namespace std;

class CustomException : public exception {
private:
    string message;
    
public:
    CustomException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

int main() {
    try {
        throw CustomException("This is a custom exception with a specific message!");
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    return 0;
}
```

### Advanced Example: Exception Hierarchy
```cpp
#include <iostream>
#include <exception>
#include <string>
using namespace std;

// Base application exception
class ApplicationException : public exception {
protected:
    string message;
    
public:
    ApplicationException(const string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Specific exception types
class DatabaseException : public ApplicationException {
private:
    int errorCode;
    
public:
    DatabaseException(const string& msg, int code) 
        : ApplicationException("Database Error: " + msg), errorCode(code) {}
    
    int getErrorCode() const { return errorCode; }
};

class NetworkException : public ApplicationException {
private:
    string serverAddress;
    
public:
    NetworkException(const string& msg, const string& server) 
        : ApplicationException("Network Error: " + msg), serverAddress(server) {}
    
    string getServerAddress() const { return serverAddress; }
};

void connectToDatabase() {
    throw DatabaseException("Connection failed", 1001);
}

void connectToServer() {
    throw NetworkException("Timeout", "192.168.1.1");
}

int main() {
    try {
        int choice;
        cout << "Enter 1 for database or 2 for network: ";
        cin >> choice;
        
        if (choice == 1)
            connectToDatabase();
        else
            connectToServer();
    } 
    catch (const DatabaseException& e) {
        cerr << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    catch (const NetworkException& e) {
        cerr << e.what() << endl;
        cerr << "Server: " << e.getServerAddress() << endl;
    }
    catch (const ApplicationException& e) {
        cerr << "Application error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Standard exception: " << e.what() << endl;
    }
    
    return 0;
}
```

### Problem Exercises
- [GeeksforGeeks: Custom Exceptions Practice](https://www.geeksforgeeks.org/c-throwing-custom-exceptions/)
- [C++ Exception Handling Projects](https://www.programiz.com/cpp-programming/exception-handling)
- [Coderbyte C++ Challenges](https://www.coderbyte.com/)

## 3. File I/O

### Overview
C++ provides comprehensive file handling capabilities through the `<fstream>` library, enabling you to read from and write to files efficiently. The library includes three main classes:

- `ifstream`: For reading from files (input file stream)
- `ofstream`: For writing to files (output file stream)
- `fstream`: For both reading and writing (file stream)

These classes inherit from `istream`, `ostream`, and `iostream` respectively, allowing you to use familiar I/O operations.

### Basic File Operations

#### Writing to a File
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Open a file for writing
    ofstream outFile("data.txt");
    
    // Check if file opened successfully
    if (!outFile) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return 1;
    }
    
    // Write data to the file
    outFile << "Hello, File I/O in C++!" << endl;
    outFile << "This is line 2." << endl;
    outFile << "This is line 3." << endl;
    
    // Explicitly close the file (also happens automatically when outFile goes out of scope)
    outFile.close();
    
    cout << "Data has been written to file successfully." << endl;
    return 0;
}
```

#### Reading from a File
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Open a file for reading
    ifstream inFile("data.txt");
    
    // Check if file opened successfully
    if (!inFile) {
        cerr << "Error: Unable to open file for reading!" << endl;
        return 1;
    }
    
    // Read data from the file line by line
    cout << "File contents:" << endl;
    string line;
    int lineNum = 1;
    
    while (getline(inFile, line)) {
        cout << lineNum++ << ": " << line << endl;
    }
    
    // Close the file
    inFile.close();
    return 0;
}
```

### Advanced Example: Binary File I/O
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Person {
    char name[50];
    int age;
    double salary;
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Salary: $" << salary << endl;
    }
};

void writeBinaryFile(const vector<Person>& people, const string& filename) {
    ofstream outFile(filename, ios::binary | ios::out);
    
    if (!outFile) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    // Write number of records
    size_t size = people.size();
    outFile.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Write each person object
    for (const Person& person : people) {
        outFile.write(reinterpret_cast<const char*>(&person), sizeof(Person));
    }
    
    outFile.close();
    cout << "Binary data written successfully." << endl;
}

vector<Person> readBinaryFile(const string& filename) {
    ifstream inFile(filename, ios::binary | ios::in);
    vector<Person> people;
    
    if (!inFile) {
        cerr << "Error: Unable to open file for reading!" << endl;
        return people;
    }
    
    // Read number of records
    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Read each person object
    for (size_t i = 0; i < size; i++) {
        Person person;
        inFile.read(reinterpret_cast<char*>(&person), sizeof(Person));
        people.push_back(person);
    }
    
    inFile.close();
    cout << "Binary data read successfully." << endl;
    return people;
}

int main() {
    // Create sample data
    vector<Person> staff = {
        {"John Smith", 30, 55000.00},
        {"Jane Doe", 28, 62500.50},
        {"Mike Johnson", 35, 71000.75}
    };
    
    string filename = "personnel.dat";
    
    // Write data to binary file
    writeBinaryFile(staff, filename);
    
    // Read data from binary file
    vector<Person> loadedStaff = readBinaryFile(filename);
    
    // Display loaded data
    cout << "\nLoaded personnel data:" << endl;
    for (const Person& person : loadedStaff) {
        person.display();
    }
    
    return 0;
}
```

### File Positioning and Random Access
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    fstream file("random_access.txt", ios::in | ios::out | ios::trunc);
    
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Write data to the file
    file << "Line 1: This is the first line." << endl;
    file << "Line 2: This is the second line." << endl;
    file << "Line 3: This is the third line." << endl;
    file << "Line 4: This is the fourth line." << endl;
    
    // Get current position
    streampos end_pos = file.tellp();
    
    // Move to the beginning of the file
    file.seekg(0, ios::beg);
    
    // Read and display the file content
    string line;
    cout << "File contents:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    // Move to a specific position (beginning of third line)
    file.clear(); // Clear EOF flag
    file.seekg(0, ios::beg); // Go to beginning
    
    // Skip first two lines
    getline(file, line);
    getline(file, line);
    
    // Get position of third line
    streampos third_line_pos = file.tellg();
    
    // Read third line
    getline(file, line);
    cout << "\nThird line: " << line << endl;
    
    // Write to a specific position (replace third line)
    file.seekp(third_line_pos);
    file << "Line 3: This line has been modified!" << endl;
    
    // Display modified content
    file.seekg(0, ios::beg);
    cout << "\nModified file contents:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    file.close();
    return 0;
}
```

### Problem Exercises
- [GeeksforGeeks: File Handling in C++](https://www.geeksforgeeks.org/file-handling-cpp/)
- [HackerRank: C++ File I/O Challenges](https://www.hackerrank.com/domains/cpp)
- [Practical File I/O Projects](https://www.learncpp.com/cpp-tutorial/186-basic-file-io/)
- [CodeChef File Manipulation Problems](https://www.codechef.com/)

## Conclusion

This document covers advanced features of C++ programming, including exception handling, custom exceptions, file I/O, templates, namespaces, preprocessor directives, and type casting. These features provide powerful tools for creating robust, flexible, and maintainable C++ applications.

For further learning and practice, refer to the problem exercises linked in each section, and explore additional resources such as:

- [C++ Reference](https://en.cppreference.com/w/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [HackerRank C++ Domain](https://www.hackerrank.com/domains/cpp)
- [LeetCode](https://leetcode.com/)
- [C++ Books and Tutorials](https://www.learncpp.com/)

Remember that mastering these advanced features takes practice and application in real-world projects.