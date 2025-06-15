# Chapter 7: Advanced C++ Features (Part 1)

## 7.1 Templates (Function and Class)

Templates are one of the most powerful features in C++, enabling generic programming by allowing you to write code that works with any data type. They provide a way to create functions and classes that operate on different types without having to rewrite the same code for each type.

### Function Templates

Function templates allow you to define a function that can work with different types of parameters.

#### Basic Syntax

```cpp
template <typename T>  // 'class' can be used instead of 'typename'
T functionName(T parameter) {
    // Function body
    return parameter;
}
```

#### Simple Example

```cpp
#include <iostream>
using namespace std;

// A template function to find the maximum of two values
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // Using the template with different types
    cout << "Max of 3 and 7: " << findMax(3, 7) << endl;
    cout << "Max of 3.5 and 7.2: " << findMax(3.5, 7.2) << endl;
    cout << "Max of 'a' and 'z': " << findMax('a', 'z') << endl;
    cout << "Max of \"apple\" and \"zebra\": " << findMax(string("apple"), string("zebra")) << endl;
    
    return 0;
}
```

Output:
```
Max of 3 and 7: 7
Max of 3.5 and 7.2: 7.2
Max of 'a' and 'z': z
Max of "apple" and "zebra": zebra
```

#### Multiple Template Parameters

You can define templates with multiple type parameters:

```cpp
#include <iostream>
using namespace std;

// Template with multiple parameters
template <typename T, typename U>
T convert(U value) {
    return static_cast<T>(value);
}

int main() {
    // Converting between different types
    int i = convert<int>(3.14);
    double d = convert<double>(42);
    char c = convert<char>(65);  // ASCII for 'A'
    
    cout << "double to int: " << i << endl;
    cout << "int to double: " << d << endl;
    cout << "int to char: " << c << endl;
    
    return 0;
}
```

Output:
```
double to int: 3
int to double: 42
int to char: A
```

#### Template Specialization

Sometimes you need to handle specific types differently. Template specialization allows you to provide a different implementation for a particular type:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

// General template for any type
template <typename T>
bool areEqual(T a, T b) {
    return a == b;
}

// Specialization for C-style strings
template <>
bool areEqual<const char*>(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

int main() {
    // Using the general template
    cout << "Are 10 and 10 equal? " << areEqual(10, 10) << endl;  // 1 (true)
    cout << "Are 10 and 20 equal? " << areEqual(10, 20) << endl;  // 0 (false)
    
    // Using the specialized template for C-strings
    const char* str1 = "hello";
    const char* str2 = "hello";
    const char* str3 = "world";
    
    cout << "Are \"" << str1 << "\" and \"" << str2 << "\" equal? " 
         << areEqual(str1, str2) << endl;  // 1 (true)
    cout << "Are \"" << str1 << "\" and \"" << str3 << "\" equal? " 
         << areEqual(str1, str3) << endl;  // 0 (false)
    
    return 0;
}
```

### Class Templates

Class templates allow you to define classes that can work with different data types.

#### Basic Syntax

```cpp
template <typename T>
class ClassName {
private:
    T member;
    
public:
    void setMember(T value) {
        member = value;
    }
    
    T getMember() {
        return member;
    }
};
```

#### Simple Container Example

```cpp
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    T pop() {
        if (elements.empty()) {
            throw runtime_error("Stack underflow");
        }
        
        T top = elements.back();
        elements.pop_back();
        return top;
    }
    
    bool isEmpty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
    
    void print() const {
        cout << "Stack contents (top to bottom): ";
        for (int i = elements.size() - 1; i >= 0; i--) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create an integer stack
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    intStack.print();
    cout << "Popped: " << intStack.pop() << endl;
    intStack.print();
    
    // Create a double stack
    Stack<double> doubleStack;
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    doubleStack.print();
    
    // Create a string stack
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.print();
    
    return 0;
}
```

Output:
```
Stack contents (top to bottom): 30 20 10 
Popped: 30
Stack contents (top to bottom): 20 10 
Stack contents (top to bottom): 2.71 3.14 
Stack contents (top to bottom): World Hello 
```

#### Class Template with Multiple Parameters

```cpp
#include <iostream>
using namespace std;

template <typename KeyType, typename ValueType>
class Pair {
private:
    KeyType key;
    ValueType value;
    
public:
    Pair(const KeyType& k, const ValueType& v) : key(k), value(v) {}
    
    KeyType getKey() const { return key; }
    ValueType getValue() const { return value; }
    
    void setKey(const KeyType& k) { key = k; }
    void setValue(const ValueType& v) { value = v; }
    
    void display() const {
        cout << key << " => " << value << endl;
    }
};

int main() {
    // Pair with integer key and string value
    Pair<int, string> student(101, "Alice");
    student.display();
    
    // Pair with string key and double value
    Pair<string, double> temperature("Celsius", 25.5);
    temperature.display();
    
    // Modify values
    student.setValue("Bob");
    student.display();
    
    return 0;
}
```

Output:
```
101 => Alice
Celsius => 25.5
101 => Bob
```

#### Class Template Specialization

Like function templates, class templates can also be specialized for specific types:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Primary template
template <typename T>
class DataHandler {
private:
    T data;
    
public:
    DataHandler(T d) : data(d) {}
    
    void process() {
        cout << "Processing generic data: " << data << endl;
    }
};

// Full specialization for int
template <>
class DataHandler<int> {
private:
    int data;
    
public:
    DataHandler(int d) : data(d) {}
    
    void process() {
        cout << "Processing integer: " << data;
        cout << " (square: " << data * data << ")" << endl;
    }
};

// Full specialization for string
template <>
class DataHandler<string> {
private:
    string data;
    
public:
    DataHandler(string d) : data(d) {}
    
    void process() {
        cout << "Processing string: " << data;
        cout << " (length: " << data.length() << ")" << endl;
    }
};

int main() {
    DataHandler<int> intHandler(42);
    DataHandler<double> doubleHandler(3.14);
    DataHandler<string> stringHandler("Hello, templates!");
    DataHandler<char> charHandler('X');
    
    intHandler.process();
    doubleHandler.process();
    stringHandler.process();
    charHandler.process();
    
    return 0;
}
```

Output:
```
Processing integer: 42 (square: 1764)
Processing generic data: 3.14
Processing string: Hello, templates! (length: 17)
Processing generic data: X
```

### Non-Type Template Parameters

Templates can also have non-type parameters, such as integers, pointers, or references:

```cpp
#include <iostream>
#include <array>
using namespace std;

template <typename T, size_t SIZE>
class FixedArray {
private:
    array<T, SIZE> data;
    
public:
    FixedArray() {
        // Initialize elements to default values
        for (size_t i = 0; i < SIZE; ++i) {
            data[i] = T();
        }
    }
    
    T& operator[](size_t index) {
        if (index >= SIZE) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= SIZE) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    size_t size() const {
        return SIZE;
    }
    
    void fill(const T& value) {
        data.fill(value);
    }
};

int main() {
    // Create a fixed-size array of 5 integers
    FixedArray<int, 5> intArray;
    
    // Set values
    for (size_t i = 0; i < intArray.size(); ++i) {
        intArray[i] = i * 10;
    }
    
    // Display values
    cout << "Integer array: ";
    for (size_t i = 0; i < intArray.size(); ++i) {
        cout << intArray[i] << " ";
    }
    cout << endl;
    
    // Create a fixed-size array of 3 strings
    FixedArray<string, 3> strArray;
    strArray[0] = "Hello";
    strArray[1] = "Template";
    strArray[2] = "World";
    
    // Display values
    cout << "String array: ";
    for (size_t i = 0; i < strArray.size(); ++i) {
        cout << strArray[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

Output:
```
Integer array: 0 10 20 30 40 
String array: Hello Template World 
```

### Template Template Parameters

Template template parameters allow you to pass a template as a parameter to another template:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

// Template template parameter
template <typename T, template <typename, typename = allocator<T>> class Container>
class DataCollection {
private:
    Container<T> data;
    
public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    void display() const {
        for (const T& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
};

int main() {
    // Using vector as container
    DataCollection<int, vector> vecCollection;
    vecCollection.add(10);
    vecCollection.add(20);
    vecCollection.add(30);
    
    cout << "Vector collection: ";
    vecCollection.display();
    
    // Using list as container
    DataCollection<string, list> listCollection;
    listCollection.add("Hello");
    listCollection.add("World");
    
    cout << "List collection: ";
    listCollection.display();
    
    // Using deque as container
    DataCollection<double, deque> dequeCollection;
    dequeCollection.add(3.14);
    dequeCollection.add(2.71);
    
    cout << "Deque collection: ";
    dequeCollection.display();
    
    return 0;
}
```

Output:
```
Vector collection: 10 20 30 
List collection: Hello World 
Deque collection: 3.14 2.71 
```

### Variadic Templates (C++11)

Variadic templates allow you to define templates that take a variable number of arguments:

```cpp
#include <iostream>
using namespace std;

// Base case - no parameters
void print() {
    cout << endl;
}

// Variadic template function
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first;
    if (sizeof...(rest) > 0) {
        cout << ", ";
    }
    print(rest...);  // Recursive call with remaining arguments
}

// Variadic template sum function
template <typename T>
T sum(T value) {
    return value;
}

template <typename T, typename... Args>
T sum(T first, Args... rest) {
    return first + sum(rest...);
}

int main() {
    // Call print with different arguments
    print("Hello", 42, 3.14, 'X', "World");
    
    // Call sum with integers
    int sumInt = sum(1, 2, 3, 4, 5);
    cout << "Sum of integers: " << sumInt << endl;
    
    // Call sum with doubles
    double sumDouble = sum(1.1, 2.2, 3.3, 4.4);
    cout << "Sum of doubles: " << sumDouble << endl;
    
    return 0;
}
```

Output:
```
Hello, 42, 3.14, X, World
Sum of integers: 15
Sum of doubles: 11
```

### Best Practices for Templates

1. **Use templates for generic algorithms and data structures** that work with multiple types.
2. **Minimize dependencies on the template parameters** - only use operations that are required.
3. **Add constraints to template parameters** using SFINAE (C++11) or concepts (C++20).
4. **Provide clear error messages** when template instantiation fails.
5. **Keep the template code in header files**, as template instantiation occurs at compile time.
6. **Consider template specializations** for better efficiency with specific types.
7. **Comment thoroughly**, as template code can be complex and hard to understand.

### Common Template Mistakes

1. **Assuming too much about template parameters** - specify requirements clearly.
2. **Neglecting to check if operations are valid** for the provided types.
3. **Complex template errors** - start simple and incrementally add complexity.
4. **Forgetting that templates are instantiated at compile time** - all required code must be available.
5. **Overuse of templates** - don't use them when simple overloading would suffice.

## 7.2 Exception Handling (try, catch, throw)

Exception handling in C++ provides a structured way to detect and handle runtime errors. It separates error-handling code from normal code, making programs more robust and readable.

### Basic Exception Handling

The try-catch-throw mechanism is the foundation of C++ exception handling:

```cpp
#include <iostream>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw "Division by zero!";  // Throw an exception
    }
    return a / b;
}

int main() {
    try {
        // Code that might throw exceptions
        cout << "5 / 2 = " << divide(5, 2) << endl;
        cout << "5 / 0 = " << divide(5, 0) << endl;  // This will throw
        cout << "This line is never executed" << endl;
    }
    catch (const char* message) {
        // Handle the exception
        cout << "Error caught: " << message << endl;
    }
    
    cout << "Program continues after exception handling" << endl;
    
    return 0;
}
```

Output:
```
5 / 2 = 2.5
Error caught: Division by zero!
Program continues after exception handling
```

### Multiple catch Blocks

You can have multiple catch blocks to handle different types of exceptions:

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

// Function that throws different types of exceptions
void testExceptions(int type) {
    switch (type) {
        case 1:
            throw 100;  // Throw an integer
        case 2:
            throw 2.5;  // Throw a double
        case 3:
            throw "C string exception";  // Throw a C-string
        case 4:
            throw string("std::string exception");  // Throw an std::string
        case 5:
            throw runtime_error("Runtime error occurred");  // Throw a standard exception
    }
}

int main() {
    for (int i = 1; i <= 6; i++) {
        cout << "\nTest case " << i << ":" << endl;
        try {
            testExceptions(i);
            cout << "No exception thrown" << endl;
        } 
        catch (int e) {
            cout << "Integer exception caught: " << e << endl;
        } 
        catch (double e) {
            cout << "Double exception caught: " << e << endl;
        } 
        catch (const char* e) {
            cout << "C-string exception caught: " << e << endl;
        } 
        catch (const string& e) {
            cout << "String exception caught: " << e << endl;
        } 
        catch (const runtime_error& e) {
            cout << "Runtime error caught: " << e.what() << endl;
        } 
        catch (...) {
            cout << "Unknown exception caught" << endl;
        }
    }
    
    return 0;
}
```

Output:
```
Test case 1:
Integer exception caught: 100

Test case 2:
Double exception caught: 2.5

Test case 3:
C-string exception caught: C string exception

Test case 4:
String exception caught: std::string exception

Test case 5:
Runtime error caught: Runtime error occurred

Test case 6:
No exception thrown
```

### Standard Exception Classes

C++ provides a hierarchy of standard exception classes in the `<stdexcept>` header:

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void demoStandardExceptions() {
    try {
        vector<int> vec(5);
        // Accessing element out of bounds
        cout << vec.at(10) << endl;  // This will throw std::out_of_range
    } 
    catch (const out_of_range& e) {
        cout << "out_of_range exception: " << e.what() << endl;
    }
    
    try {
        // Invalid argument
        throw invalid_argument("The argument is invalid");
    } 
    catch (const invalid_argument& e) {
        cout << "invalid_argument exception: " << e.what() << endl;
    }
    
    try {
        // Length error
        throw length_error("Length exceeded maximum allowed");
    } 
    catch (const length_error& e) {
        cout << "length_error exception: " << e.what() << endl;
    }
    
    try {
        // Runtime error
        throw runtime_error("A runtime error occurred");
    } 
    catch (const runtime_error& e) {
        cout << "runtime_error exception: " << e.what() << endl;
    }
}

int main() {
    demoStandardExceptions();
    return 0;
}
```

Output:
```
out_of_range exception: vector::_M_range_check: __n (which is 10) >= this->size() (which is 5)
invalid_argument exception: The argument is invalid
length_error exception: Length exceeded maximum allowed
runtime_error exception: A runtime error occurred
```

### Common Standard Exceptions

1. **`std::exception`**: Base class for all standard exceptions
2. **`std::logic_error`**: Errors that could be detected at compile time
   - `std::invalid_argument`
   - `std::domain_error`
   - `std::length_error`
   - `std::out_of_range`
3. **`std::runtime_error`**: Errors that can only be detected at runtime
   - `std::range_error`
   - `std::overflow_error`
   - `std::underflow_error`

### Creating Custom Exception Classes

You can define your own exception classes by inheriting from std::exception or its derived classes:

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

// Custom exception class
class DatabaseException : public runtime_error {
private:
    int errorCode;
    
public:
    DatabaseException(const string& message, int code) 
        : runtime_error(message), errorCode(code) {}
    
    int getErrorCode() const {
        return errorCode;
    }
};

// Function that throws a custom exception
void connectToDatabase(const string& connectionString) {
    if (connectionString.empty()) {
        throw DatabaseException("Connection string cannot be empty", 1001);
    }
    
    if (connectionString.find("password") == string::npos) {
        throw DatabaseException("Missing password in connection string", 1002);
    }
    
    cout << "Connected to database successfully" << endl;
}

int main() {
    try {
        // Test with empty connection string
        cout << "Test case 1:" << endl;
        connectToDatabase("");
    } 
    catch (const DatabaseException& e) {
        cout << "Database error: " << e.what() << endl;
        cout << "Error code: " << e.getErrorCode() << endl;
    }
    
    try {
        // Test with invalid connection string
        cout << "\nTest case 2:" << endl;
        connectToDatabase("server=localhost;database=testdb;user=admin");
    } 
    catch (const DatabaseException& e) {
        cout << "Database error: " << e.what() << endl;
        cout << "Error code: " << e.getErrorCode() << endl;
    }
    
    try {
        // Test with valid connection string
        cout << "\nTest case 3:" << endl;
        connectToDatabase("server=localhost;database=testdb;user=admin;password=secret");
    } 
    catch (const DatabaseException& e) {
        cout << "Database error: " << e.what() << endl;
        cout << "Error code: " << e.getErrorCode() << endl;
    }
    
    return 0;
}
```

Output:
```
Test case 1:
Database error: Connection string cannot be empty
Error code: 1001

Test case 2:
Database error: Missing password in connection string
Error code: 1002

Test case 3:
Connected to database successfully
```

### Exception Specifications and noexcept

In modern C++, you can use `noexcept` to specify that a function doesn't throw exceptions:

```cpp
#include <iostream>
using namespace std;

// Function with noexcept specification
void safeFunction() noexcept {
    // This function promises not to throw exceptions
    cout << "Safe function executing" << endl;
}

// Function without noexcept specification
void unsafeFunction(bool throwException) {
    cout << "Unsafe function executing" << endl;
    if (throwException) {
        throw runtime_error("Exception from unsafeFunction");
    }
}

int main() {
    // Testing noexcept functions
    try {
        safeFunction();
    } 
    catch (...) {
        cout << "Exception from safeFunction caught (should never happen)" << endl;
    }
    
    // Testing functions that might throw
    try {
        unsafeFunction(false);  // No exception
        unsafeFunction(true);   // Will throw
    } 
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    // Using noexcept operator
    cout << "\nIs safeFunction() noexcept? " << (noexcept(safeFunction()) ? "Yes" : "No") << endl;
    cout << "Is unsafeFunction() noexcept? " << (noexcept(unsafeFunction(false)) ? "Yes" : "No") << endl;
    
    return 0;
}
```

Output:
```
Safe function executing
Unsafe function executing
Unsafe function executing
Exception caught: Exception from unsafeFunction

Is safeFunction() noexcept? Yes
Is unsafeFunction() noexcept? No
```

### Stack Unwinding

When an exception is thrown, C++ performs "stack unwinding," which involves destroying all local objects in reverse order of their creation:

```cpp
#include <iostream>
using namespace std;

class Resource {
private:
    string name;
    
public:
    Resource(const string& n) : name(n) {
        cout << "Resource acquired: " << name << endl;
    }
    
    ~Resource() {
        cout << "Resource released: " << name << endl;
    }
};

void function3() {
    Resource r3("Function3 Resource");
    cout << "function3() throwing exception..." << endl;
    throw runtime_error("Exception from function3()");
    cout << "This line will never execute" << endl;
}

void function2() {
    Resource r2("Function2 Resource");
    cout << "function2() calling function3()..." << endl;
    function3();
    cout << "This line will never execute" << endl;
}

void function1() {
    Resource r1("Function1 Resource");
    cout << "function1() calling function2()..." << endl;
    function2();
    cout << "This line will never execute" << endl;
}

int main() {
    try {
        cout << "main() calling function1()..." << endl;
        function1();
        cout << "This line will never execute" << endl;
    } 
    catch (const exception& e) {
        cout << "Exception caught in main(): " << e.what() << endl;
    }
    
    cout << "Program continues after exception handling" << endl;
    
    return 0;
}
```

Output:
```
main() calling function1()...
Resource acquired: Function1 Resource
function1() calling function2()...
Resource acquired: Function2 Resource
function2() calling function3()...
Resource acquired: Function3 Resource
function3() throwing exception...
Resource released: Function3 Resource
Resource released: Function2 Resource
Resource released: Function1 Resource
Exception caught in main(): Exception from function3()
Program continues after exception handling
```

### Exception Safety Guarantees

Exception safety refers to how well a program preserves its invariants and prevents resource leaks when exceptions occur:

1. **No-throw guarantee**: The operation will not throw exceptions
2. **Strong guarantee**: If an exception occurs, the program state remains unchanged (as if the operation hadn't been called)
3. **Basic guarantee**: If an exception occurs, the program is in a valid but unspecified state
4. **No guarantee**: If an exception occurs, the program might be in an invalid state

Example demonstrating exception safety:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Resource {
private:
    string name;
    
public:
    Resource(const string& n) : name(n) {
        cout << "Resource created: " << name << endl;
        if (name == "BadResource") {
            throw runtime_error("Failed to create BadResource");
        }
    }
    
    ~Resource() {
        cout << "Resource destroyed: " << name << endl;
    }
    
    void use() {
        cout << "Using resource: " << name << endl;
    }
};

// Demonstrates basic guarantee (no leaks but state might change)
class BasicGuarantee {
private:
    vector<Resource*> resources;
    
public:
    // This might leak if an exception occurs midway
    void unsafe_add(const string& name1, const string& name2) {
        Resource* r1 = new Resource(name1);
        resources.push_back(r1);
        
        // If this throws, r1 won't be deleted
        Resource* r2 = new Resource(name2);
        resources.push_back(r2);
    }
    
    // This provides basic guarantee (no leaks)
    void basic_add(const string& name1, const string& name2) {
        Resource* r1 = nullptr;
        Resource* r2 = nullptr;
        
        try {
            r1 = new Resource(name1);
            resources.push_back(r1);
            
            r2 = new Resource(name2);
            resources.push_back(r2);
        } 
        catch (...) {
            // Clean up if exception occurs
            delete r2;  // Safe even if nullptr
            
            // r1 is already in the vector, so we don't delete it
            throw;  // Rethrow the exception
        }
    }
    
    ~BasicGuarantee() {
        for (auto resource : resources) {
            delete resource;
        }
    }
};

// Demonstrates strong guarantee (all-or-nothing)
class StrongGuarantee {
private:
    vector<unique_ptr<Resource>> resources;
    
public:
    // This provides strong guarantee (state unchanged if exception occurs)
    void strong_add(const string& name1, const string& name2) {
        // Temporary vector to hold new resources
        vector<unique_ptr<Resource>> temp;
        
        temp.push_back(make_unique<Resource>(name1));
        temp.push_back(make_unique<Resource>(name2));
        
        // If we get here, both resources were created successfully
        // Now we can modify our actual state
        for (auto& resource : temp) {
            resources.push_back(move(resource));
        }
    }
    
    void use_all() {
        for (const auto& resource : resources) {
            resource->use();
        }
    }
};

int main() {
    // Test basic guarantee
    cout << "Testing basic guarantee:" << endl;
    try {
        BasicGuarantee basic;
        basic.basic_add("Resource1", "Resource2");  // Should succeed
        cout << "First add succeeded" << endl;
        
        basic.basic_add("Resource3", "BadResource");  // Should throw
        cout << "Second add succeeded (shouldn't see this)" << endl;
    } 
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    cout << "\nTesting strong guarantee:" << endl;
    try {
        StrongGuarantee strong;
        strong.strong_add("Resource4", "Resource5");  // Should succeed
        cout << "First add succeeded" << endl;
        strong.use_all();
        
        strong.strong_add("Resource6", "BadResource");  // Should throw
        cout << "Second add succeeded (shouldn't see this)" << endl;
    } 
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    return 0;
}
```

### Best Practices for Exception Handling

1. **Use exceptions for exceptional conditions**, not normal flow control.
2. **Catch exceptions by reference** to avoid object slicing and unnecessary copying.
3. **Order catch blocks from most specific to most general** to ensure proper handling.
4. **Clean up resources** using RAII (Resource Acquisition Is Initialization) to prevent leaks.
5. **Keep exception specifications up-to-date** if you use them.
6. **Be specific about which exceptions your code might throw** in documentation.
7. **Don't let destructors throw** exceptions, as this can lead to program termination.
8. **Use smart pointers and containers** to automate resource management.
9. **Consider exception safety** when designing and implementing functions.

## 7.3 Namespaces

Namespaces provide a way to organize code into logical groups and prevent name conflicts. They allow you to create scope where identifiers (variables, functions, classes) can be placed, ensuring they don't collide with identifiers in other parts of your code.

### Basic Namespace Syntax

```cpp
#include <iostream>
using namespace std;

// Define a namespace
namespace MyNamespace {
    // Variables in namespace
    int value = 100;
    
    // Functions in namespace
    void display() {
        cout << "Value from MyNamespace: " << value << endl;
    }
    
    // Classes in namespace
    class MyClass {
    public:
        void show() {
            cout << "Hello from MyNamespace::MyClass" << endl;
        }
    };
}

int main() {
    // Accessing namespace members using scope resolution operator ::
    cout << "Value: " << MyNamespace::value << endl;
    MyNamespace::display();
    
    MyNamespace::MyClass obj;
    obj.show();
    
    return 0;
}
```

Output:
```
Value: 100
Value from MyNamespace: 100
Hello from MyNamespace::MyClass
```

### The `using` Directive

The `using` directive brings all names from a namespace into the current scope:

```cpp
#include <iostream>

// Define a namespace
namespace Math {
    const double PI = 3.14159265358979;
    
    double square(double x) {
        return x * x;
    }
    
    double cube(double x) {
        return x * x * x;
    }
}

int main() {
    // Without using
    std::cout << "PI: " << Math::PI << std::endl;
    std::cout << "Square of 5: " << Math::square(5) << std::endl;
    
    // With using directive
    using namespace Math;
    std::cout << "Cube of 3: " << cube(3) << std::endl;
    std::cout << "PI squared: " << square(PI) << std::endl;
    
    return 0;
}
```

Output:
```
PI: 3.14159
Square of 5: 25
Cube of 3: 27
PI squared: 9.86961
```

### The `using` Declaration

The `using` declaration brings specific names from a namespace into the current scope:

```cpp
#include <iostream>

namespace Math {
    const double PI = 3.14159265358979;
    
    double square(double x) {
        return x * x;
    }
    
    double cube(double x) {
        return x * x * x;
    }
}

namespace Physics {
    const double G = 9.81; // Gravitational acceleration
    
    double calculateEnergy(double mass, double height) {
        return mass * G * height;
    }
}

int main() {
    // Using specific names from namespaces
    using Math::PI;
    using Math::square;
    using Physics::G;
    
    std::cout << "PI: " << PI << std::endl;
    std::cout << "Square of 4: " << square(4) << std::endl;
    std::cout << "Gravity: " << G << " m/s²" << std::endl;
    
    // Need to use full qualification for names not explicitly imported
    std::cout << "Cube of 3: " << Math::cube(3) << std::endl;
    std::cout << "Energy: " << Physics::calculateEnergy(10, 5) << " joules" << std::endl;
    
    return 0;
}
```

Output:
```
PI: 3.14159
Square of 4: 16
Gravity: 9.81 m/s²
Cube of 3: 27
Energy: 490.5 joules
```

### Namespace Aliases

Namespace aliases allow you to create shorter names for namespaces:

```cpp
#include <iostream>
using namespace std;

namespace VeryLongNamespaceName {
    void display() {
        cout << "This is a function in a very long namespace name" << endl;
    }
    
    namespace NestedNamespace {
        void show() {
            cout << "This is a nested function" << endl;
        }
    }
}

int main() {
    // Without alias - verbose
    VeryLongNamespaceName::display();
    VeryLongNamespaceName::NestedNamespace::show();
    
    // With alias - more concise
    namespace Short = VeryLongNamespaceName;
    Short::display();
    
    namespace ShortNested = VeryLongNamespaceName::NestedNamespace;
    ShortNested::show();
    
    return 0;
}
```

Output:
```
This is a function in a very long namespace name
This is a nested function
This is a function in a very long namespace name
This is a nested function
```

### Nested Namespaces

Namespaces can be nested inside other namespaces:

```cpp
#include <iostream>
using namespace std;

// Parent namespace
namespace Organization {
    void info() {
        cout << "Organization namespace" << endl;
    }
    
    // Nested namespace
    namespace Department {
        void info() {
            cout << "Department namespace" << endl;
        }
        
        // Further nested namespace
        namespace Team {
            void info() {
                cout << "Team namespace" << endl;
            }
        }
    }
}

// C++17 nested namespace syntax
namespace Project::Module::Component {
    void info() {
        cout << "Component namespace using C++17 syntax" << endl;
    }
}

int main() {
    // Accessing nested namespaces
    Organization::info();
    Organization::Department::info();
    Organization::Department::Team::info();
    
    // Using C++17 syntax
    Project::Module::Component::info();
    
    // Using aliases for nested namespaces
    namespace OrgTeam = Organization::Department::Team;
    OrgTeam::info();
    
    return 0;
}
```

Output:
```
Organization namespace
Department namespace
Team namespace
Component namespace using C++17 syntax
Team namespace
```

### Unnamed/Anonymous Namespaces

Unnamed namespaces provide internal linkage, similar to using the `static` keyword for global variables and functions:

```cpp
#include <iostream>
using namespace std;

// Unnamed namespace - contents have internal linkage
namespace {
    int hiddenValue = 100;
    
    void privateFunction() {
        cout << "This function is only visible in this file" << endl;
    }
}

// Global function that can access unnamed namespace contents
void accessHiddenValue() {
    cout << "Hidden value: " << hiddenValue << endl;
    privateFunction();
}

int main() {
    // Can access members of unnamed namespace directly
    cout << "Hidden value from main: " << hiddenValue << endl;
    privateFunction();
    
    accessHiddenValue();
    
    return 0;
}
```

Output:
```
Hidden value from main: 100
This function is only visible in this file
Hidden value: 100
This function is only visible in this file
```

### Inline Namespaces (C++11)

Inline namespaces automatically expose their members to the enclosing namespace:

```cpp
#include <iostream>
using namespace std;

namespace Library {
    // Original version
    namespace v1 {
        void process() {
            cout << "Using v1 process function" << endl;
        }
    }
    
    // New version - marked inline to be the default
    inline namespace v2 {
        void process() {
            cout << "Using v2 process function (newer)" << endl;
        }
        
        void newFeature() {
            cout << "This feature is only available in v2" << endl;
        }
    }
}

int main() {
    // Call v1 explicitly
    Library::v1::process();
    
    // Call v2 explicitly
    Library::v2::process();
    
    // Call default version (v2, because it's inline)
    Library::process();
    
    // Use new feature available only in v2
    Library::newFeature();
    
    return 0;
}
```

Output:
```
Using v1 process function
Using v2 process function (newer)
Using v2 process function (newer)
This feature is only available in v2
```

### Resolving Name Conflicts

Namespaces are primarily used to avoid name conflicts between different libraries or modules:

```cpp
#include <iostream>
using namespace std;

// First library
namespace Graphics {
    struct Point {
        int x, y;
        
        Point(int a, int b) : x(a), y(b) {}
        
        void display() const {
            cout << "Graphics::Point(" << x << ", " << y << ")" << endl;
        }
    };
    
    void drawLine(Point start, Point end) {
        cout << "Drawing line from ";
        start.display();
        cout << " to ";
        end.display();
    }
}

// Second library with conflicting names
namespace Math {
    struct Point {
        double x, y;
        
        Point(double a, double b) : x(a), y(b) {}
        
        void display() const {
            cout << "Math::Point(" << x << ", " << y << ")" << endl;
        }
    };
    
    double distance(Point a, Point b) {
        double dx = b.x - a.x;
        double dy = b.y - a.y;
        return sqrt(dx*dx + dy*dy);
    }
}

int main() {
    // Using fully qualified names to avoid confusion
    Graphics::Point p1(10, 20);
    Graphics::Point p2(50, 60);
    
    Math::Point mp1(1.5, 2.5);
    Math::Point mp2(4.5, 5.5);
    
    // Use functions from different namespaces
    p1.display();
    mp1.display();
    
    Graphics::drawLine(p1, p2);
    cout << "Distance between points: " << Math::distance(mp1, mp2) << endl;
    
    return 0;
}
```

Output:
```
Graphics::Point(10, 20)
Math::Point(1.5, 2.5)
Drawing line from Graphics::Point(10, 20) to Graphics::Point(50, 60)
Distance between points: 4.24264
```

### Argument-Dependent Lookup (ADL)

ADL, also known as Koenig lookup, allows unqualified functions to be found in the namespaces of their arguments:

```cpp
#include <iostream>
#include <string>
using namespace std;

namespace MyLibrary {
    struct User {
        string name;
        int id;
        
        User(const string& n, int i) : name(n), id(i) {}
    };
    
    // Function in the same namespace as the User type
    void display(const User& user) {
        cout << "User ID: " << user.id << ", Name: " << user.name << endl;
    }
}

int main() {
    MyLibrary::User user("Alice", 12345);
    
    // No need for MyLibrary:: prefix due to ADL
    display(user);  // Calls MyLibrary::display
    
    // Explicit qualification also works
    MyLibrary::display(user);
    
    return 0;
}
```

Output:
```
User ID: 12345, Name: Alice
User ID: 12345, Name: Alice
```

### Best Practices for Namespaces

1. **Use namespaces to organize related code** and prevent name collisions.
2. **Avoid `using namespace std;` in header files** as it can lead to name conflicts.
3. **Prefer `using` declarations over `using` directives** for better control.
4. **Use meaningful namespace names** that reflect the purpose or project.
5. **Use unnamed namespaces** for internal linkage instead of the `static` keyword.
6. **Keep namespace hierarchies relatively flat** to avoid overly complex qualification.
7. **Consider using namespace aliases** for long namespace names.
8. **Be aware of argument-dependent lookup** when designing libraries.
9. **Use inline namespaces for versioning** your library APIs.
10. **Document namespace contents** clearly, especially in public APIs.

### Common Namespace Pitfalls

1. **Global using directives** bringing in too many names
2. **Deeply nested namespaces** making code hard to read
3. **Confusing ADL behavior** leading to unexpected function calls
4. **Namespace pollution** from unnecessary `using` directives
5. **Forgetting to close namespace blocks** properly

### Example of a Well-Structured Namespace System

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Main library namespace
namespace MyApp {
    // Common utilities
    namespace Utils {
        string formatDate(int day, int month, int year) {
            return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        }
        
        string toUpper(string text) {
            for (char& c : text) {
                c = toupper(c);
            }
            return text;
        }
    }
    
    // Database functionality
    namespace DB {
        struct Record {
            int id;
            string name;
            string date;
        };
        
        vector<Record> getRecords() {
            // Simulated database query
            return {
                {1, "Alice", Utils::formatDate(15, 3, 2023)},
                {2, "Bob", Utils::formatDate(20, 4, 2023)}
            };
        }
        
        void displayRecord(const Record& record) {
            cout << "Record ID: " << record.id << endl;
            cout << "Name: " << record.name << endl;
            cout << "Date: " << record.date << endl;
        }
    }
    
    // User interface
    namespace UI {
        void showWelcome() {
            cout << Utils::toUpper("Welcome to MyApp") << endl;
        }
        
        void displayRecords() {
            cout << "Database Records:" << endl;
            cout << "----------------" << endl;
            
            auto records = DB::getRecords();
            for (const auto& record : records) {
                DB::displayRecord(record);
                cout << endl;
            }
        }
    }
}

int main() {
    // Using namespace aliases for convenience
    namespace UI = MyApp::UI;
    
    UI::showWelcome();
    UI::displayRecords();
    
    return 0;
}
```

Output:
```
WELCOME TO MYAPP
Database Records:
----------------
Record ID: 1
Name: Alice
Date: 15/3/2023

Record ID: 2
Name: Bob
Date: 20/4/2023
```
