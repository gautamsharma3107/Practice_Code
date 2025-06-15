# Chapter 7: Advanced C++ Features (Part 3)

## 7.7 Move Semantics & Rvalue References

Move semantics, introduced in C++11, revolutionized the way resources are managed and transferred between objects. This feature significantly improves performance when working with objects that manage resources (like memory, file handles, or network connections).

### Understanding L-values and R-values

To understand move semantics, we first need to understand the concepts of l-values and r-values:

- **L-value**: An expression that refers to a memory location and can appear on the left side of an assignment.
- **R-value**: An expression that isn't an l-value; typically a temporary value or literal that cannot appear on the left side of an assignment.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;  // x is an l-value, 10 is an r-value
    
    int y = x;   // y is an l-value, x is an l-value but used as an r-value
    
    // int& ref1 = 42;      // Error: cannot bind non-const lvalue reference to an rvalue
    const int& ref2 = 42;  // OK: can bind const lvalue reference to an rvalue
    
    // These are all r-values:
    // 10
    // x + y
    // x++  (the value produced, not x itself)
    
    // These are all l-values:
    // x
    // ++x (both the value produced and x itself)
    // ref2
    
    return 0;
}
```

### Rvalue References

C++11 introduced a new reference type called an **rvalue reference**, denoted by `&&`. This allows us to bind specifically to r-values:

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    // lvalue reference - binds to lvalues
    int& lref = x;
    // int& invalid_lref = 10;  // Error: can't bind lvalue reference to rvalue
    
    // rvalue reference - binds to rvalues
    int&& rref = 20;  // OK: 20 is an rvalue
    // int&& invalid_rref = x;  // Error: can't bind rvalue reference to lvalue
    
    // But we can force it with std::move
    int&& forced_rref = move(x);  // OK: move(x) creates an rvalue
    
    cout << "x: " << x << endl;
    cout << "lref: " << lref << endl;
    cout << "rref: " << rref << endl;
    cout << "forced_rref: " << forced_rref << endl;
    
    // Changing through references affects the original
    lref = 100;
    cout << "After lref = 100, x: " << x << endl;
    
    forced_rref = 200;
    cout << "After forced_rref = 200, x: " << x << endl;
    
    return 0;
}
```

### Understanding std::move

`std::move` doesn't actually move anything - it's just a cast that produces an rvalue reference to its argument:

```cpp
#include <iostream>
#include <utility>  // For std::move
#include <string>
using namespace std;

int main() {
    // Example with a fundamental type
    int a = 10;
    int b = move(a);  // Same as: int b = a;
    cout << "a: " << a << ", b: " << b << endl;  // a is still 10
    
    // Example with a string
    string str1 = "Hello, World!";
    string str2 = move(str1);  // str1's contents are moved to str2
    
    cout << "str1: '" << str1 << "'" << endl;  // str1 might be empty or in a valid but unspecified state
    cout << "str2: '" << str2 << "'" << endl;  // str2 now has "Hello, World!"
    
    return 0;
}
```

### Move Constructor and Move Assignment

Move semantics are implemented through two special member functions:

1. **Move Constructor**: `ClassName(ClassName&& other)`
2. **Move Assignment Operator**: `ClassName& operator=(ClassName&& other)`

Here's an example of a class with both move and copy operations:

```cpp
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Resource {
private:
    int* data;
    size_t size;
    
    void logOperation(const string& op) const {
        cout << op << " [this=" << this << ", data=" << data << ", size=" << size << "]" << endl;
    }
    
public:
    // Constructor
    Resource(size_t sz) : size(sz) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
        logOperation("Constructor");
    }
    
    // Destructor
    ~Resource() {
        logOperation("Destructor");
        delete[] data;
    }
    
    // Copy constructor
    Resource(const Resource& other) : size(other.size) {
        data = new int[size];
        copy(other.data, other.data + size, data);
        logOperation("Copy constructor");
    }
    
    // Copy assignment operator
    Resource& operator=(const Resource& other) {
        logOperation("Copy assignment operator");
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // Move constructor
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        logOperation("Move constructor");
        // Important: leave the source in a valid state
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        logOperation("Move assignment operator");
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            
            // Important: leave the source in a valid state
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // Utility method
    void print() const {
        cout << "Resource [data=" << data << ", size=" << size << "]: ";
        for (size_t i = 0; i < size && i < 10; ++i) {
            cout << data[i] << " ";
        }
        if (size > 10) cout << "...";
        cout << endl;
    }
    
    // Add some data for testing
    void update(int value) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = value + i;
        }
    }
};

int main() {
    cout << "Creating r1" << endl;
    Resource r1(5);
    r1.update(10);
    r1.print();
    
    cout << "\nCopy construction:" << endl;
    Resource r2 = r1;  // Copy constructor
    r2.print();
    
    cout << "\nMove construction:" << endl;
    Resource r3 = move(r1);  // Move constructor
    r3.print();
    
    // r1 has been moved from, should be in a valid but unspecified state
    cout << "\nr1 after move:" << endl;
    r1.print();  // Should be empty or in a valid state
    
    cout << "\nCopy assignment:" << endl;
    Resource r4(3);
    r4 = r2;  // Copy assignment
    r4.print();
    
    cout << "\nMove assignment:" << endl;
    Resource r5(2);
    r5 = move(r2);  // Move assignment
    r5.print();
    
    cout << "\nr2 after move:" << endl;
    r2.print();  // Should be empty or in a valid state
    
    return 0;
}
```

### Perfect Forwarding

Perfect forwarding allows a function template to preserve the value category and cv-qualifiers of its arguments when passing them to another function:

```cpp
#include <iostream>
#include <utility>
#include <string>
using namespace std;

// A function that takes both lvalue and rvalue arguments
void process(string& s) {
    cout << "Process lvalue: " << s << endl;
}

void process(string&& s) {
    cout << "Process rvalue: " << s << endl;
}

// A forwarding function template
template<typename T>
void perfectForward(T&& arg) {
    // Forward keeps the value category (lvalue or rvalue) of the argument
    cout << "Forwarding to: ";
    process(forward<T>(arg));
}

int main() {
    string hello = "Hello";
    
    // Direct calls
    cout << "Direct calls:" << endl;
    process(hello);            // Calls lvalue version
    process(move(hello));      // Calls rvalue version
    process("temporary");      // Calls rvalue version
    
    // With perfect forwarding
    cout << "\nWith forwarding:" << endl;
    perfectForward(hello);              // Calls lvalue version
    perfectForward(move(hello));        // Calls rvalue version
    perfectForward("another temp");     // Calls rvalue version
    
    return 0;
}
```

### Universal References

The term "universal reference" (coined by Scott Meyers) refers to a special case of rvalue references:

```cpp
#include <iostream>
#include <utility>
#include <string>
using namespace std;

// T&& here is a universal reference, not an rvalue reference
template<typename T>
void universalRef(T&& param) {
    // Type deduction happens with T&&
    cout << "T&& param: " << param << endl;
    
    // We can check if it's an lvalue or rvalue reference
    if (is_lvalue_reference<T>::value) {
        cout << "Parameter is an lvalue reference" << endl;
    } else {
        cout << "Parameter is an rvalue reference" << endl;
    }
}

int main() {
    string hello = "Hello";
    
    universalRef(hello);    // T deduced as string&, param is string&
    universalRef("World");  // T deduced as const char[6], param is const char(&&)[6]
    universalRef(move(hello));  // T deduced as string, param is string&&
    
    return 0;
}
```

### Move Semantics with Standard Library

Standard library containers take advantage of move semantics when available:

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ExpensiveObject {
private:
    string* data;
    
public:
    ExpensiveObject() : data(new string("Default")) {
        cout << "Default constructor [" << *data << "]" << endl;
    }
    
    ExpensiveObject(const string& str) : data(new string(str)) {
        cout << "String constructor [" << *data << "]" << endl;
    }
    
    ~ExpensiveObject() {
        if (data) cout << "Destructor [" << *data << "]" << endl;
        delete data;
    }
    
    // Copy operations
    ExpensiveObject(const ExpensiveObject& other) : data(new string(*other.data)) {
        cout << "Copy constructor [" << *data << "]" << endl;
    }
    
    ExpensiveObject& operator=(const ExpensiveObject& other) {
        cout << "Copy assignment [" << *data << " = " << *other.data << "]" << endl;
        if (this != &other) {
            *data = *other.data;
        }
        return *this;
    }
    
    // Move operations
    ExpensiveObject(ExpensiveObject&& other) noexcept : data(other.data) {
        cout << "Move constructor [" << *data << "]" << endl;
        other.data = nullptr;  // Prevent double deletion
    }
    
    ExpensiveObject& operator=(ExpensiveObject&& other) noexcept {
        cout << "Move assignment [" << *data << " = " << *other.data << "]" << endl;
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;  // Prevent double deletion
        }
        return *this;
    }
    
    // For displaying
    void display() const {
        cout << "ExpensiveObject: " << (data ? *data : "null") << endl;
    }
};

int main() {
    // Using vector's emplace_back (constructs in-place)
    cout << "--- Vector with emplace_back ---" << endl;
    vector<ExpensiveObject> v1;
    v1.emplace_back("First");  // Constructs directly in the vector
    v1.emplace_back("Second");
    
    // Using push_back with move
    cout << "\n--- Vector with push_back and move ---" << endl;
    vector<ExpensiveObject> v2;
    ExpensiveObject obj("Third");
    v2.push_back(move(obj));  // Moves obj into the vector
    
    // obj was moved from, should be in a valid but unspecified state
    cout << "\nAfter move, obj is: ";
    obj.display();
    
    // Using temporary objects
    cout << "\n--- Vector with temporary objects ---" << endl;
    vector<ExpensiveObject> v3;
    v3.push_back(ExpensiveObject("Fourth"));  // Temporary is moved, not copied
    
    return 0;
}
```

### Best Practices for Move Semantics

1. **Always mark move operations with `noexcept`**
   - This allows standard library containers to optimize certain operations

2. **Leave moved-from objects in a valid (albeit unspecified) state**
   - Typically this means nulling out pointers
   - Setting primitive types to safe defaults

3. **Consider move operations for classes that manage resources**
   - Memory, file handles, network connections, etc.

4. **Use `std::move` with caution**
   - Don't use it when you still need the object's value
   - Be especially careful with forwarded parameters

5. **Don't inhibit compiler optimizations**
   - Return local objects by value - copy elision will optimize away the copy

## 7.8 Rule of 3 / 5 / 0

The "Rule of Three/Five/Zero" is a guideline for class design regarding special member functions in C++.

### Rule of Three

The Rule of Three states that if a class requires any of these three special member functions, it probably needs all three:

1. Destructor
2. Copy constructor
3. Copy assignment operator

This is because these functions are usually needed together when a class manages a resource (like memory or file handles).

```cpp
#include <iostream>
#include <cstring>  // For strlen, strcpy
using namespace std;

// Class that follows the Rule of Three
class Buffer {
private:
    char* data;
    size_t size;
    
public:
    // Constructor
    Buffer(const char* str) {
        size = strlen(str) + 1;
        data = new char[size];
        strcpy(data, str);
        cout << "Constructor: " << data << endl;
    }
    
    // Destructor (1/3)
    ~Buffer() {
        cout << "Destructor: " << (data ? data : "nullptr") << endl;
        delete[] data;
    }
    
    // Copy constructor (2/3)
    Buffer(const Buffer& other) : size(other.size) {
        data = new char[size];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Copy assignment operator (3/3)
    Buffer& operator=(const Buffer& other) {
        cout << "Copy assignment operator" << endl;
        if (this != &other) {
            delete[] data;  // Free old resource
            
            size = other.size;
            data = new char[size];
            strcpy(data, other.data);
        }
        return *this;
    }
    
    // Display the buffer
    void display() const {
        cout << "Buffer: " << data << " (size: " << size << ")" << endl;
    }
};

void showRuleOfThree() {
    Buffer b1("Hello");
    b1.display();
    
    // Copy construction
    Buffer b2 = b1;  // or Buffer b2(b1);
    b2.display();
    
    // Copy assignment
    Buffer b3("Temporary");
    b3 = b1;
    b3.display();
}

int main() {
    cout << "Demonstrating Rule of Three:" << endl;
    showRuleOfThree();
    
    return 0;
}
```

### Rule of Five

With the introduction of move semantics in C++11, the Rule of Three became the Rule of Five. If a class needs custom versions of any of these five special member functions, it probably needs all five:

1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

```cpp
#include <iostream>
#include <cstring>  // For strlen, strcpy
using namespace std;

// Class that follows the Rule of Five
class DynamicArray {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    DynamicArray(size_t sz) : size(sz) {
        data = new int[size];
        fill(data, data + size, 0);
        cout << "Constructor: size " << size << endl;
    }
    
    // Destructor (1/5)
    ~DynamicArray() {
        cout << "Destructor: size " << size << endl;
        delete[] data;
    }
    
    // Copy constructor (2/5)
    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "Copy constructor: size " << size << endl;
    }
    
    // Copy assignment operator (3/5)
    DynamicArray& operator=(const DynamicArray& other) {
        cout << "Copy assignment operator" << endl;
        if (this != &other) {
            delete[] data;  // Free old resource
            
            size = other.size;
            data = new int[size];
            copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // Move constructor (4/5)
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size(other.size) {
        cout << "Move constructor: size " << size << endl;
        // Leave source in valid, empty state
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment operator (5/5)
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        cout << "Move assignment operator" << endl;
        if (this != &other) {
            delete[] data;  // Free old resource
            
            // Take ownership of other's resources
            data = other.data;
            size = other.size;
            
            // Leave source in valid, empty state
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // Utility methods
    void setValue(size_t index, int value) {
        if (index < size && data != nullptr) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        if (index < size && data != nullptr) {
            return data[index];
        }
        return -1;
    }
    
    void display() const {
        cout << "DynamicArray [size=" << size << ", data=" << data << "]: ";
        if (data != nullptr) {
            for (size_t i = 0; i < size && i < 10; ++i) {
                cout << data[i] << " ";
            }
            if (size > 10) cout << "...";
        } else {
            cout << "nullptr";
        }
        cout << endl;
    }
};

void showRuleOfFive() {
    DynamicArray a1(5);
    for (int i = 0; i < 5; ++i) {
        a1.setValue(i, i * 10);
    }
    a1.display();
    
    cout << "\n--- Copy operations ---" << endl;
    DynamicArray a2 = a1;  // Copy construction
    a2.display();
    
    DynamicArray a3(3);
    a3 = a1;  // Copy assignment
    a3.display();
    
    cout << "\n--- Move operations ---" << endl;
    DynamicArray a4 = move(a1);  // Move construction
    a4.display();
    
    cout << "a1 after move: ";
    a1.display();  // Should be in a valid but empty state
    
    DynamicArray a5(2);
    a5 = move(a2);  // Move assignment
    a5.display();
    
    cout << "a2 after move: ";
    a2.display();  // Should be in a valid but empty state
}

int main() {
    cout << "Demonstrating Rule of Five:" << endl;
    showRuleOfFive();
    
    return 0;
}
```

### Rule of Zero

The Rule of Zero states that if a class can avoid defining any special member functions, it should. Instead, it should rely on the compiler-generated defaults or compose from classes that already handle their resources properly.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// Class that follows the Rule of Zero
class Document {
private:
    string title;               // string already manages its memory
    vector<string> paragraphs;  // vector already manages its memory
    shared_ptr<string> metadata;  // shared_ptr already manages its resource
    
public:
    // Regular constructor - no special handling needed for resources
    Document(const string& t) : title(t), metadata(make_shared<string>("Created: 2023")) {
        cout << "Document created: " << title << endl;
    }
    
    // No need for destructor, copy/move operations - they're generated correctly
    
    void addParagraph(const string& text) {
        paragraphs.push_back(text);
    }
    
    void display() const {
        cout << "Document: " << title << endl;
        cout << "Metadata: " << *metadata << endl;
        cout << "Contents:" << endl;
        for (size_t i = 0; i < paragraphs.size(); ++i) {
            cout << "  " << (i + 1) << ". " << paragraphs[i] << endl;
        }
    }
};

void showRuleOfZero() {
    Document doc1("Rule of Zero Example");
    doc1.addParagraph("Paragraph 1: Introduction to the Rule of Zero");
    doc1.addParagraph("Paragraph 2: Let standard components handle resources");
    
    // Copy construction works correctly without custom implementation
    Document doc2 = doc1;
    doc2.addParagraph("Paragraph 3: This was added only to doc2");
    
    cout << "\n--- Original document ---" << endl;
    doc1.display();
    
    cout << "\n--- Copied document with extra paragraph ---" << endl;
    doc2.display();
    
    // Move operations also work correctly
    Document doc3 = move(doc1);
    
    cout << "\n--- Moved document ---" << endl;
    doc3.display();
    
    // doc1 is in a valid but unspecified state after the move
    // Depending on the implementation, doc1.title might be empty now
}

int main() {
    cout << "Demonstrating Rule of Zero:" << endl;
    showRuleOfZero();
    
    return 0;
}
```

### When to Apply Each Rule

1. **Rule of Zero** (preferred):
   - Apply when your class doesn't manage any resources directly
   - Use standard containers and smart pointers
   - Let the compiler generate the special member functions

2. **Rule of Five**:
   - Apply when your class directly manages a resource
   - Implement all five special member functions consistently
   - Consider if you could redesign to use the Rule of Zero instead

3. **Rule of Three** (C++98/03):
   - Apply in legacy code before C++11
   - Consider upgrading to Rule of Five when moving to C++11 or later

### Special Member Functions and `= default`, `= delete`

C++11 introduced explicit ways to control special member functions:

```cpp
#include <iostream>
using namespace std;

class ControlledCopy {
private:
    int value;
    
public:
    ControlledCopy(int v) : value(v) {
        cout << "Constructor with value " << value << endl;
    }
    
    // Default constructor explicitly defaulted
    ControlledCopy() = default;
    
    // Copy constructor explicitly defaulted
    ControlledCopy(const ControlledCopy&) = default;
    
    // Move constructor explicitly deleted
    ControlledCopy(ControlledCopy&&) = delete;
    
    // Copy assignment explicitly deleted
    ControlledCopy& operator=(const ControlledCopy&) = delete;
    
    // Move assignment explicitly defaulted (but unused since move constructor is deleted)
    ControlledCopy& operator=(ControlledCopy&&) = default;
    
    // Display the value
    void display() const {
        cout << "Value: " << value << endl;
    }
};

int main() {
    ControlledCopy a(42);
    ControlledCopy b;  // Default constructor
    
    // Copy constructor (allowed)
    ControlledCopy c = a;
    
    // Copy assignment (not allowed)
    // b = a;  // Error: copy assignment operator is deleted
    
    // Move constructor (not allowed)
    // ControlledCopy d = move(a);  // Error: move constructor is deleted
    
    return 0;
}
```

## 7.9 Copy Constructor vs Move Constructor

Copy and move constructors both create new objects from existing ones, but they do it in fundamentally different ways:

### Copy Constructor

The copy constructor creates a new object as a copy of an existing object, duplicating its resources:

- Takes a constant reference to an existing object
- Creates a duplicate of all resources
- The source object remains unchanged
- Uses the form: `ClassName(const ClassName& other)`

### Move Constructor

The move constructor creates a new object by transferring ownership of resources from an existing object:

- Takes an rvalue reference to an existing object
- Steals (moves) resources from the source
- Leaves the source object in a valid but unspecified state
- Uses the form: `ClassName(ClassName&& other) noexcept`

### Key Differences

#### 1. Parameter Types

```cpp
class MyClass {
public:
    // Copy constructor - takes const reference
    MyClass(const MyClass& other);
    
    // Move constructor - takes rvalue reference
    MyClass(MyClass&& other) noexcept;
};
```

#### 2. Resource Handling

```cpp
#include <iostream>
#include <string>
using namespace std;

class StringWrapper {
private:
    string* text;
    
public:
    // Constructor
    StringWrapper(const string& str) : text(new string(str)) {
        cout << "Constructor: " << *text << endl;
    }
    
    // Destructor
    ~StringWrapper() {
        cout << "Destructor: " << (text ? *text : "null") << endl;
        delete text;
    }
    
    // Copy constructor - duplicates the resource
    StringWrapper(const StringWrapper& other) : text(new string(*other.text)) {
        cout << "Copy constructor: " << *text << endl;
    }
    
    // Move constructor - takes ownership of the resource
    StringWrapper(StringWrapper&& other) noexcept : text(other.text) {
        cout << "Move constructor: " << *text << endl;
        other.text = nullptr;  // Prevent destruction of the moved resource
    }
    
    // Get the string value
    string getValue() const { 
        return text ? *text : "null"; 
    }
};

int main() {
    // Original object
    StringWrapper original("Hello world");
    cout << "Original: " << original.getValue() << endl;
    
    // Copy construction
    StringWrapper copy = original;
    cout << "Copy: " << copy.getValue() << endl;
    cout << "Original after copy: " << original.getValue() << endl;
    
    // Move construction
    StringWrapper moved = move(original);
    cout << "Moved: " << moved.getValue() << endl;
    cout << "Original after move: " << original.getValue() << endl;
    
    return 0;
}
```

#### 3. Performance Implications

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

class LargeObject {
private:
    vector<int> data;
    
public:
    // Constructor to create a large object
    LargeObject(size_t size) : data(size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
    }
    
    // Copy constructor - expensive, copies all data
    LargeObject(const LargeObject& other) : data(other.data) {
        // Expensive deep copy
    }
    
    // Move constructor - cheap, just transfers ownership
    LargeObject(LargeObject&& other) noexcept : data(move(other.data)) {
        // Fast ownership transfer
    }
    
    // Get data size
    size_t size() const {
        return data.size();
    }
};

// Test function for performance comparison
void testPerformance() {
    const int NUM_OBJECTS = 1000;
    const int OBJECT_SIZE = 100000;
    
    // Test copy performance
    auto copyStart = high_resolution_clock::now();
    vector<LargeObject> copyVec;
    copyVec.reserve(NUM_OBJECTS);  // Reserve to avoid reallocation
    
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        LargeObject obj(OBJECT_SIZE);
        copyVec.push_back(obj);  // Copy construction
    }
    
    auto copyEnd = high_resolution_clock::now();
    auto copyDuration = duration_cast<milliseconds>(copyEnd - copyStart).count();
    
    // Test move performance
    auto moveStart = high_resolution_clock::now();
    vector<LargeObject> moveVec;
    moveVec.reserve(NUM_OBJECTS);  // Reserve to avoid reallocation
    
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        LargeObject obj(OBJECT_SIZE);
        moveVec.push_back(move(obj));  // Move construction
    }
    
    auto moveEnd = high_resolution_clock::now();
    auto moveDuration = duration_cast<milliseconds>(moveEnd - moveStart).count();
    
    cout << "Copy performance: " << copyDuration << " ms" << endl;
    cout << "Move performance: " << moveDuration << " ms" << endl;
    cout << "Performance ratio: " << (copyDuration / (moveDuration > 0 ? moveDuration : 1)) << "x" << endl;
}

int main() {
    cout << "Performance comparison of copy vs move:" << endl;
    testPerformance();
    
    return 0;
}
```

#### 4. When Each is Called

```cpp
#include <iostream>
#include <utility>  // For std::move
#include <vector>
using namespace std;

class TraceableObject {
private:
    int id;
    
public:
    // Constructor
    TraceableObject(int i) : id(i) {
        cout << "Constructor: " << id << endl;
    }
    
    // Destructor
    ~TraceableObject() {
        cout << "Destructor: " << id << endl;
    }
    
    // Copy constructor
    TraceableObject(const TraceableObject& other) : id(other.id) {
        cout << "Copy constructor: " << id << endl;
    }
    
    // Move constructor
    TraceableObject(TraceableObject&& other) noexcept : id(other.id) {
        cout << "Move constructor: " << id << endl;
        other.id = -1;  // Mark as moved
    }
    
    // For display
    int getId() const { return id; }
};

// Function that takes by value - copy or move happens
void takeByValue(TraceableObject obj) {
    cout << "Inside takeByValue: id = " << obj.getId() << endl;
}

// Function that returns by value - might use move or RVO/NRVO
TraceableObject createObject() {
    TraceableObject obj(42);
    cout << "createObject - before return" << endl;
    return obj;  // Could use NRVO (Named Return Value Optimization)
}

TraceableObject createObjectWithMove() {
    TraceableObject obj(43);
    cout << "createObjectWithMove - before return" << endl;
    return move(obj);  // Explicitly moving, prevents NRVO
}

int main() {
    cout << "1. Local object creation:" << endl;
    TraceableObject local(1);
    
    cout << "\n2. Copy construction:" << endl;
    TraceableObject copy = local;
    
    cout << "\n3. Move construction:" << endl;
    TraceableObject moved = move(local);
    
    cout << "\n4. Passing to function by value:" << endl;
    TraceableObject arg(2);
    takeByValue(arg);  // Makes a copy
    
    cout << "\n5. Passing temporary to function:" << endl;
    takeByValue(TraceableObject(3));  // Move construction usually happens
    
    cout << "\n6. Return value optimization:" << endl;
    TraceableObject fromFunc = createObject();  // Might be constructed in place
    
    cout << "\n7. Returning with explicit move:" << endl;
    TraceableObject fromFuncMoved = createObjectWithMove();
    
    cout << "\n8. Adding to a vector (may need to reallocate):" << endl;
    vector<TraceableObject> vec;
    vec.push_back(TraceableObject(4));  // Move construction from temporary
    TraceableObject pushMe(5);
    vec.push_back(pushMe);  // Copy construction
    vec.push_back(move(pushMe));  // Move construction
    
    cout << "\n9. End of program - all objects will be destroyed" << endl;
    return 0;
}
```

### Best Practices

1. **Always mark move operations as `noexcept`**
   - Enables optimizations in standard containers

2. **Be consistent with the Rule of Three/Five/Zero**
   - If you define one special member function, consider if you need the others

3. **Avoid unnecessary copying when moving is sufficient**
   - Use `std::move` when appropriate, especially for returning large objects

4. **Remember that copy operations must not modify their source**
   - While move operations should leave the source in a valid but unspecified state

5. **Make move operations efficient**
   - They should be much faster than copying, otherwise there's no benefit

6. **Consider special cases where copy and move logic differ**
   - Reference counting, internal bookkeeping, etc.

7. **Watch out for self-assignment**
   - Both copy and move assignment operators should handle self-assignment correctly

### Example: Move vs Copy in Standard Library

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main() {
    // String examples
    string original = "This is a fairly long string that would require allocation";
    
    // Copy vs Move with strings
    cout << "--- String copy vs move ---" << endl;
    string strCopy = original;  // Copy constructor
    cout << "Original after copy: " << original << endl;
    
    string strMove = move(original);  // Move constructor
    cout << "Original after move: '" << original << "'" << endl;
    cout << "Moved-to string: " << strMove << endl;
    
    // Vector examples
    cout << "\n--- Vector copy vs move ---" << endl;
    vector<int> vecOriginal = {1, 2, 3, 4, 5};
    cout << "Original size: " << vecOriginal.size() << endl;
    
    vector<int> vecCopy = vecOriginal;  // Copy constructor
    cout << "Original size after copy: " << vecOriginal.size() << endl;
    
    vector<int> vecMove = move(vecOriginal);  // Move constructor
    cout << "Original size after move: " << vecOriginal.size() << endl;
    cout << "Moved-to vector size: " << vecMove.size() << endl;
    
    // Unique pointer (can only be moved, not copied)
    cout << "\n--- Unique pointer (move-only) ---" << endl;
    unique_ptr<int> ptrOriginal = make_unique<int>(42);
    cout << "Original pointer value: " << *ptrOriginal << endl;
    
    // unique_ptr<int> ptrCopy = ptrOriginal;  // Error: copy not allowed
    
    unique_ptr<int> ptrMove = move(ptrOriginal);
    cout << "Moved-to pointer value: " << *ptrMove << endl;
    cout << "Original pointer after move is null? " << (ptrOriginal == nullptr ? "yes" : "no") << endl;
    
    return 0;
}
```

### Example: Custom Copy and Move Operations with Complex Resources

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// A resource class that maintains a reference count
class SharedResource {
private:
    string name;
    int* refCount;
    
public:
    SharedResource(const string& n) : name(n) {
        refCount = new int(1);
        cout << "Resource created: " << name << " (refCount = " << *refCount << ")" << endl;
    }
    
    ~SharedResource() {
        (*refCount)--;
        cout << "Reference removed from: " << name << " (refCount = " << *refCount << ")" << endl;
        if (*refCount == 0) {
            cout << "Deleting resource: " << name << endl;
            delete refCount;
        }
    }
    
    // Copy constructor increases reference count
    SharedResource(const SharedResource& other)
        : name(other.name), refCount(other.refCount) {
        (*refCount)++;
        cout << "Resource copied: " << name << " (refCount = " << *refCount << ")" << endl;
    }
    
    // Copy assignment operator
    SharedResource& operator=(const SharedResource& other) {
        cout << "Copy assignment for: " << name << " = " << other.name << endl;
        if (this != &other) {
            // Decrease our current reference
            (*refCount)--;
            if (*refCount == 0) {
                cout << "Deleting old resource: " << name << endl;
                delete refCount;
            }
            
            // Point to the new resource and increase its count
            name = other.name;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }
    
    // Move constructor takes ownership without changing reference count
    SharedResource(SharedResource&& other) noexcept
        : name(move(other.name)), refCount(other.refCount) {
        other.refCount = new int(1);  // Source gets a new reference count
        cout << "Resource moved: " << name << " (refCount unchanged = " << *refCount << ")" << endl;
    }
    
    // Move assignment operator
    SharedResource& operator=(SharedResource&& other) noexcept {
        cout << "Move assignment for: " << name << " = " << other.name << endl;
        if (this != &other) {
            // Decrease our current reference
            (*refCount)--;
            if (*refCount == 0) {
                cout << "Deleting old resource: " << name << endl;
                delete refCount;
            }
            
            // Take ownership of the other's resource
            name = move(other.name);
            refCount = other.refCount;
            
            // Give other a new reference count
            other.refCount = new int(1);
        }
        return *this;
    }
    
    string getName() const { return name; }
    int getRefCount() const { return *refCount; }
};

int main() {
    cout << "Creating original resources:" << endl;
    SharedResource res1("Resource A");
    SharedResource res2("Resource B");
    
    cout << "\nCopying resources:" << endl;
    SharedResource res3 = res1;  // Copy constructor
    cout << "res1: " << res1.getName() << ", refCount = " << res1.getRefCount() << endl;
    cout << "res3: " << res3.getName() << ", refCount = " << res3.getRefCount() << endl;
    
    cout << "\nMoving resources:" << endl;
    SharedResource res4 = move(res2);  // Move constructor
    cout << "res2: " << res2.getName() << ", refCount = " << res2.getRefCount() << endl;
    cout << "res4: " << res4.getName() << ", refCount = " << res4.getRefCount() << endl;
    
    cout << "\nCopy assignment:" << endl;
    res2 = res1;  // Copy assignment
    cout << "res1: " << res1.getName() << ", refCount = " << res1.getRefCount() << endl;
    cout << "res2: " << res2.getName() << ", refCount = " << res2.getRefCount() << endl;
    
    cout << "\nMove assignment:" << endl;
    res4 = move(res3);  // Move assignment
    cout << "res3: " << res3.getName() << ", refCount = " << res3.getRefCount() << endl;
    cout << "res4: " << res4.getName() << ", refCount = " << res4.getRefCount() << endl;
    
    cout << "\nEnd of program - all resources will be cleaned up" << endl;
    return 0;
}
```

### Conclusion

Understanding the differences between copy and move operations is essential for writing efficient C++ code, especially when dealing with classes that manage resources. By implementing both types correctly and following the appropriate rules (Zero, Three, or Five), you can create classes that perform well and manage resources safely.
