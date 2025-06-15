# Chapter 10: Templates in C++ (Part 1)

## Introduction to Templates

Templates are one of C++'s most powerful features, allowing you to write generic code that works with any data type while maintaining type safety. They are the foundation of C++'s Standard Template Library (STL) and modern C++ programming. Templates enable you to create flexible, reusable code without sacrificing performance or type safety.

In essence, templates provide a way to write a single function or class that can operate on different data types without rewriting the same logic for each type. The compiler generates the appropriate code for each specific type at compile time.

## 10.1 Function Templates

Function templates allow you to write a single function that can operate on different types. Instead of writing multiple overloaded functions with identical logic but different parameter types, you can write a single function template.

### 10.1.1 Basic Function Template Syntax

The basic syntax for a function template is:

```cpp
template <typename T>
return_type function_name(parameters) {
    // Function body
}
```

Here, `T` is a template parameter that will be replaced with an actual type when the template is instantiated. The keyword `typename` can be replaced with the equivalent keyword `class`.

Let's look at a simple example:

```cpp
#include <iostream>
using namespace std;

// Function template to find maximum of two values
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // Using the template with integers
    cout << "Max of 10 and 20: " << maximum<int>(10, 20) << endl;
    
    // Using the template with doubles
    cout << "Max of 10.5 and 20.7: " << maximum<double>(10.5, 20.7) << endl;
    
    // Using the template with characters
    cout << "Max of 'a' and 'z': " << maximum<char>('a', 'z') << endl;
    
    // Type deduction (compiler determines the type)
    cout << "Max of 100 and 200: " << maximum(100, 200) << endl;
    
    return 0;
}
```

When you call the template function with `maximum<int>(10, 20)`, the compiler generates a specific version of the function for integers. The `<int>` part explicitly specifies the type, but in many cases, the compiler can deduce the type from the arguments, so you can just write `maximum(10, 20)`.

### 10.1.2 Template Type Deduction

C++ compilers can often deduce the template parameter types based on the function arguments. This makes template code cleaner and more readable:

```cpp
// Template instantiations with explicit type specification
int max_int = maximum<int>(10, 20);
double max_double = maximum<double>(10.5, 20.7);

// Same effect with type deduction
int max_int2 = maximum(10, 20);           // T is deduced as int
double max_double2 = maximum(10.5, 20.7); // T is deduced as double
```

However, there are cases where explicit specification is necessary:

```cpp
// Explicit specification when deduction might be ambiguous
double result = maximum<double>(10, 20.5); // Force T to be double
```

Without the explicit `<double>` here, the compiler would encounter ambiguity since the arguments are of different types.

### 10.1.3 Multiple Template Parameters

A function template can have multiple template parameters:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Template with two different types
template <typename T, typename U>
T convert_and_multiply(T a, U b) {
    return a * static_cast<T>(b);
}

int main() {
    // Using the template with different type combinations
    int result1 = convert_and_multiply<int, double>(10, 2.5);     // 10 * 2 = 20
    double result2 = convert_and_multiply<double, int>(10.5, 2);  // 10.5 * 2 = 21.0
    
    cout << "Result 1: " << result1 << endl;  // Output: 20
    cout << "Result 2: " << result2 << endl;  // Output: 21
    
    return 0;
}
```

### 10.1.4 Template Specialization

Sometimes, you want to provide a special implementation of a template for a specific type. This is called template specialization:

```cpp
#include <iostream>
#include <string>
using namespace std;

// General template
template <typename T>
T add(T a, T b) {
    cout << "General template called" << endl;
    return a + b;
}

// Specialization for char*
template <>
const char* add<const char*>(const char* a, const char* b) {
    cout << "Specialized template for const char* called" << endl;
    string result = string(a) + string(b);
    // Warning: Returning a pointer to a temporary - for demonstration only
    // In real code, you would need to handle memory properly
    return strdup(result.c_str());
}

int main() {
    int int_result = add(5, 3);                // Uses general template
    double double_result = add(5.7, 3.2);      // Uses general template
    
    const char* s1 = "Hello, ";
    const char* s2 = "world!";
    const char* str_result = add(s1, s2);      // Uses specialized template
    
    cout << "Int result: " << int_result << endl;
    cout << "Double result: " << double_result << endl;
    cout << "String result: " << str_result << endl;
    
    // Clean up (since we used strdup)
    free((void*)str_result);
    
    return 0;
}
```

In this example, the specialized version for `const char*` provides a custom implementation to handle string concatenation.

### 10.1.5 Non-Type Template Parameters

Templates can also have non-type parameters, such as integers, pointers, or references:

```cpp
#include <iostream>
#include <array>
using namespace std;

// Template with a non-type parameter
template <typename T, int Size>
class Buffer {
private:
    T data[Size];
    
public:
    Buffer() : data{} {}
    
    T& operator[](int index) {
        if (index < 0 || index >= Size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int size() const {
        return Size;
    }
};

int main() {
    // Create buffers of different types and sizes
    Buffer<int, 10> int_buffer;
    Buffer<double, 5> double_buffer;
    
    // Populate buffers
    for (int i = 0; i < int_buffer.size(); ++i) {
        int_buffer[i] = i * 10;
    }
    
    for (int i = 0; i < double_buffer.size(); ++i) {
        double_buffer[i] = i * 1.5;
    }
    
    // Display buffer contents
    cout << "Int buffer: ";
    for (int i = 0; i < int_buffer.size(); ++i) {
        cout << int_buffer[i] << " ";
    }
    cout << endl;
    
    cout << "Double buffer: ";
    for (int i = 0; i < double_buffer.size(); ++i) {
        cout << double_buffer[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

In this example, `Size` is a non-type template parameter that determines the size of the array at compile time.

### 10.1.6 Default Template Arguments

Template parameters can have default arguments:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Template with default parameter
template <typename T = int>
T identity(T value) {
    return value;
}

int main() {
    // Using the template with explicit type
    double d = identity<double>(3.14);
    string s = identity<string>("Hello");
    
    // Using default argument (T = int)
    int i = identity(42);
    
    cout << "Double: " << d << endl;
    cout << "String: " << s << endl;
    cout << "Int: " << i << endl;
    
    return 0;
}
```

### 10.1.7 Using Concepts (C++20)

In C++20, you can use concepts to constrain template parameters:

```cpp
#include <iostream>
#include <concepts>
using namespace std;

// Define a concept for types that support addition
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

// Function that only works with Addable types
template <Addable T>
T add(T a, T b) {
    return a + b;
}

// Another way to constrain a template
template <typename T>
requires Addable<T>
T multiply_and_add(T a, T b, T c) {
    return a * b + c;
}

int main() {
    cout << "Add integers: " << add(5, 3) << endl;
    cout << "Add doubles: " << add(2.5, 3.7) << endl;
    cout << "Multiply and add: " << multiply_and_add(2, 3, 4) << endl;
    
    // This would cause a compilation error if uncommented:
    // struct NonAddable {};
    // add(NonAddable{}, NonAddable{});
    
    return 0;
}
```

Concepts provide a way to express requirements on template arguments, making template error messages more readable and allowing more precise control over which types can be used with a template.

### 10.1.8 Function Template Best Practices

1. **Prefer type deduction** when possible to make code cleaner.
2. **Use constraints** (C++20 concepts or SFINAE in earlier versions) to restrict which types can be used with your templates.
3. **Be mindful of implicit conversions** that might happen during type deduction.
4. **Specialize templates** only when you need different behavior for specific types.
5. **Consider using forwarding references** (`T&&`) with `std::forward` for perfect forwarding.
6. **Document template requirements** clearly, especially what operations the types need to support.
7. **Write clear error messages** for when requirements aren't met.

## 10.2 Class Templates

Class templates extend the template concept to classes, allowing you to create a blueprint for a class where some types are left as parameters to be specified later.

### 10.2.1 Basic Class Template Syntax

The basic syntax for a class template is:

```cpp
template <typename T>
class ClassName {
    // Class members
};
```

Let's look at a simple example of a generic container:

```cpp
#include <iostream>
using namespace std;

// Class template
template <typename T>
class Container {
private:
    T element;
    
public:
    Container(T arg) : element(arg) {}
    
    T getElement() const {
        return element;
    }
    
    void setElement(T arg) {
        element = arg;
    }
};

int main() {
    // Create containers of different types
    Container<int> int_container(42);
    Container<double> double_container(3.14);
    Container<string> string_container("Hello, templates!");
    
    // Access and modify container contents
    cout << "Int container: " << int_container.getElement() << endl;
    cout << "Double container: " << double_container.getElement() << endl;
    cout << "String container: " << string_container.getElement() << endl;
    
    int_container.setElement(100);
    cout << "Modified int container: " << int_container.getElement() << endl;
    
    return 0;
}
```

Unlike function templates, the template arguments for class templates usually cannot be deduced from the constructor arguments (prior to C++17), so you must specify them explicitly.

### 10.2.2 Member Functions in Class Templates

Member functions of a class template can be defined either inside or outside the class definition:

```cpp
// Inside the class definition
template <typename T>
class Container {
    T element;
public:
    Container(T arg) : element(arg) {}
    
    T getElement() const { return element; }
    void setElement(T arg) { element = arg; }
};

// Outside the class definition
template <typename T>
class Box {
    T content;
public:
    Box(T arg);
    T getContent() const;
    void setContent(T arg);
};

// Implementation of member functions
template <typename T>
Box<T>::Box(T arg) : content(arg) {}

template <typename T>
T Box<T>::getContent() const {
    return content;
}

template <typename T>
void Box<T>::setContent(T arg) {
    content = arg;
}
```

When defining member functions outside the class, you need to repeat the template declaration and use the full qualified name (`Box<T>::methodName`).

### 10.2.3 Multiple Template Parameters

Like function templates, class templates can have multiple template parameters:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Class with multiple template parameters
template <typename KeyType, typename ValueType>
class Pair {
private:
    KeyType key;
    ValueType value;
    
public:
    Pair(KeyType k, ValueType v) : key(k), value(v) {}
    
    KeyType getKey() const { return key; }
    ValueType getValue() const { return value; }
    
    void setKey(KeyType k) { key = k; }
    void setValue(ValueType v) { value = v; }
    
    void display() const {
        cout << "Key: " << key << ", Value: " << value << endl;
    }
};

int main() {
    // Create pairs with different type combinations
    Pair<int, string> student(101, "John Doe");
    Pair<string, double> temperature("Celsius", 25.5);
    Pair<char, int> ascii('A', 65);
    
    // Display pairs
    student.display();
    temperature.display();
    ascii.display();
    
    return 0;
}
```

### 10.2.4 Template Specialization for Classes

Like function templates, class templates can be specialized for specific types:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Primary template
template <typename T>
class Storage {
private:
    T data;
    
public:
    Storage(T d) : data(d) {}
    
    void print() const {
        cout << "Generic storage contains: " << data << endl;
    }
};

// Full specialization for bool
template <>
class Storage<bool> {
private:
    bool data;
    
public:
    Storage(bool d) : data(d) {}
    
    void print() const {
        cout << "Boolean storage contains: " << (data ? "true" : "false") << endl;
    }
};

// Partial specialization for pointer types
template <typename T>
class Storage<T*> {
private:
    T* data;
    
public:
    Storage(T* d) : data(d) {}
    
    void print() const {
        cout << "Pointer storage contains address: " << data;
        if (data) {
            cout << " with value: " << *data;
        } else {
            cout << " (nullptr)";
        }
        cout << endl;
    }
    
    ~Storage() {
        // Specialized cleanup for pointer type
        // Note: This assumes ownership of the pointer, which may not be appropriate
        // in all cases.
        delete data;
    }
};

int main() {
    // Using generic template
    Storage<int> int_storage(42);
    Storage<string> string_storage("Hello, world!");
    
    // Using specialized template for bool
    Storage<bool> bool_storage(true);
    
    // Using specialized template for pointer type
    int* value = new int(100);
    Storage<int*> ptr_storage(value);
    
    // Print all storages
    int_storage.print();
    string_storage.print();
    bool_storage.print();
    ptr_storage.print();
    
    return 0;
}
```

There are two types of class template specialization:
- **Full Specialization**: The entire template is specialized for a specific type.
- **Partial Specialization**: Only some template parameters are specialized, or a pattern of types (like pointers) is specialized.

### 10.2.5 Default Template Arguments for Classes

Like function templates, class templates can have default template arguments:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Class with default template argument
template <typename T, typename Container = vector<T>>
class Stack {
private:
    Container elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    T pop() {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

int main() {
    // Using default container (vector)
    Stack<int> int_stack;
    
    // Push elements
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    cout << "Stack size: " << int_stack.size() << endl;
    
    // Pop elements
    while (!int_stack.empty()) {
        cout << "Popped: " << int_stack.pop() << endl;
    }
    
    return 0;
}
```

In this example, the `Stack` template has a default container type of `vector<T>`, but you could provide a different container type if needed.

### 10.2.6 Template Parameters as Template Template Parameters

You can have template parameters that are themselves templates:

```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <list>
using namespace std;

// Template template parameter
template <
    typename T,
    template <typename, typename> class Container = vector,
    typename Allocator = allocator<T>
>
class Stack {
private:
    Container<T, Allocator> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    T pop() {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

int main() {
    // Using different container types
    Stack<int> vector_stack;                   // Default: vector
    Stack<int, deque> deque_stack;
    Stack<int, list> list_stack;
    
    // Push elements to all stacks
    for (int i = 1; i <= 5; ++i) {
        vector_stack.push(i * 10);
        deque_stack.push(i * 100);
        list_stack.push(i * 1000);
    }
    
    // Pop from vector stack
    cout << "Vector stack contents: ";
    while (!vector_stack.empty()) {
        cout << vector_stack.pop() << " ";
    }
    cout << endl;
    
    // Pop from deque stack
    cout << "Deque stack contents: ";
    while (!deque_stack.empty()) {
        cout << deque_stack.pop() << " ";
    }
    cout << endl;
    
    // Pop from list stack
    cout << "List stack contents: ";
    while (!list_stack.empty()) {
        cout << list_stack.pop() << " ";
    }
    cout << endl;
    
    return 0;
}
```

This advanced feature allows you to parameterize your class on different container implementations that share a common interface.

### 10.2.7 Nested Class Templates

You can nest class templates within class templates:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Outer template class
template <typename T>
class Outer {
private:
    T outerValue;
    
public:
    Outer(T value) : outerValue(value) {}
    
    // Nested template class
    template <typename U>
    class Inner {
    private:
        U innerValue;
        T* outerPtr;  // Can reference the outer class's type
        
    public:
        Inner(U value, Outer<T>* outer) : 
            innerValue(value), outerPtr(outer) {}
        
        void display() const {
            cout << "Inner value: " << innerValue << endl;
            cout << "Outer value: " << outerPtr->getOuterValue() << endl;
        }
    };
    
    T getOuterValue() const {
        return outerValue;
    }
    
    // Factory method to create Inner objects
    template <typename U>
    Inner<U> createInner(U value) {
        return Inner<U>(value, this);
    }
};

int main() {
    // Create an outer object
    Outer<string> outer("Hello from outer");
    
    // Create inner objects
    auto inner1 = outer.createInner(42);
    auto inner2 = outer.createInner(3.14);
    
    // Alternative direct creation
    typename Outer<string>::Inner<char> inner3('A', &outer);
    
    // Display inner objects
    inner1.display();
    inner2.display();
    inner3.display();
    
    return 0;
}
```

Note the use of `typename` when referring to the nested class template from outside the class.

### 10.2.8 Friend Functions and Templates

Template classes can have friend functions and friend classes:

```cpp
#include <iostream>
using namespace std;

// Forward declaration
template <typename T>
class Container;

// Friend function declaration
template <typename T>
void display(const Container<T>& c);

// Class template with friend
template <typename T>
class Container {
private:
    T value;
    
public:
    Container(T v) : value(v) {}
    
    // Friend function declaration
    friend void display<T>(const Container<T>& c);
    
    // Non-template friend function
    friend void reset(Container<T>& c) {
        cout << "Resetting container value from " << c.value << " to default" << endl;
        c.value = T();
    }
    
    // Friend class template
    template <typename U>
    friend class Inspector;
};

// Friend function definition
template <typename T>
void display(const Container<T>& c) {
    cout << "Container value: " << c.value << endl;
}

// Friend class template
template <typename T>
class Inspector {
public:
    static void inspect(const Container<T>& c) {
        cout << "Inspector accessing private value: " << c.value << endl;
    }
};

int main() {
    Container<int> ic(42);
    Container<string> sc("Hello");
    
    // Use friend function
    display(ic);
    display(sc);
    
    // Use non-template friend function
    reset(ic);
    display(ic);
    
    // Use friend class
    Inspector<int>::inspect(ic);
    Inspector<string>::inspect(sc);
    
    return 0;
}
```

Friend declarations in templates can be complex because they involve both the template mechanism and the friendship relationship.

### 10.2.9 Class Template Best Practices

1. **Make template parameters meaningful** with descriptive names like `ValueType` instead of just `T`.
2. **Use default template arguments** when sensible defaults exist.
3. **Consider providing type aliases** for common instantiations of your templates.
4. **Be careful with specializations** as they can lead to code duplication.
5. **Document template requirements** clearly, especially what operations the types need to support.
6. **Consider using concepts (C++20)** to constrain template parameters.
7. **Keep implementation details in the .cpp file when possible** by using explicit instantiation.
8. **Design for minimal dependencies** between template parameters.
9. **Use static assertions** to verify template requirements at compile time.
10. **Be mindful of code bloat** from excessive template instantiations.

By following these best practices, you can create effective, maintainable, and reusable template classes.
