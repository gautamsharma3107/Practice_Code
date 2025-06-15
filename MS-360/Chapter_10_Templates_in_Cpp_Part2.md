# Chapter 10: Templates in C++ (Part 2)

## 10.3 Template Specialization

Template specialization allows you to provide custom implementations for specific template arguments. This powerful mechanism enables you to optimize for particular types or handle edge cases that don't fit with your generic implementation.

### 10.3.1 Full Template Specialization

Full specialization completely overrides the primary template for a specific type:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Primary template
template <typename T>
class DataHandler {
public:
    void process(T data) {
        cout << "Generic processing of data: " << data << endl;
    }
};

// Full specialization for int
template <>
class DataHandler<int> {
public:
    void process(int data) {
        cout << "Specialized processing for int: " << data * 2 << endl;
    }
};

// Full specialization for string
template <>
class DataHandler<string> {
public:
    void process(string data) {
        cout << "Specialized processing for string: " << data.length() 
             << " characters" << endl;
    }
};

int main() {
    // Using primary template
    DataHandler<double> dh_double;
    dh_double.process(3.14);  // Generic processing
    
    // Using specialized templates
    DataHandler<int> dh_int;
    dh_int.process(42);  // Specialized processing for int
    
    DataHandler<string> dh_string;
    dh_string.process("Hello, template specialization!");  // Specialized for string
    
    return 0;
}
```

In this example, when `DataHandler` is instantiated with `int` or `string`, the specialized implementations are used instead of the primary template.

### 10.3.2 Function Template Specialization

Function templates can also be specialized:

```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Primary template function
template <typename T>
T max_value(T a, T b) {
    cout << "Using generic max_value" << endl;
    return (a > b) ? a : b;
}

// Specialization for C-style strings (const char*)
template <>
const char* max_value<const char*>(const char* a, const char* b) {
    cout << "Using specialized max_value for const char*" << endl;
    return (strcmp(a, b) > 0) ? a : b;
}

int main() {
    int i1 = 42, i2 = 73;
    cout << "Max int: " << max_value(i1, i2) << endl;
    
    const char* s1 = "apple";
    const char* s2 = "banana";
    cout << "Max string: " << max_value(s1, s2) << endl;
    
    // Using with auto type deduction
    auto result = max_value<double>(3.14, 2.71);
    cout << "Max double: " << result << endl;
    
    return 0;
}
```

Function specializations are particularly useful when the generic algorithm doesn't work for a specific type, like comparing C-strings which requires `strcmp()` instead of the `>` operator.

### 10.3.3 Partial Template Specialization

Partial specialization allows you to specialize a template for a subset of possible template arguments. This is only available for class templates, not function templates:

```cpp
#include <iostream>
#include <type_traits>
using namespace std;

// Primary template
template <typename T, typename U>
class Pair {
public:
    Pair(T first, U second) : first_(first), second_(second) {
        cout << "Primary template used" << endl;
    }
    
    void display() const {
        cout << "Pair: " << first_ << ", " << second_ << endl;
    }
    
private:
    T first_;
    U second_;
};

// Partial specialization for when both types are the same
template <typename T>
class Pair<T, T> {
public:
    Pair(T first, T second) : first_(first), second_(second) {
        cout << "Partial specialization for same types used" << endl;
    }
    
    void display() const {
        cout << "Same-type pair: " << first_ << ", " << second_ << endl;
    }
    
    T max() const {
        return first_ > second_ ? first_ : second_;
    }
    
private:
    T first_;
    T second_;
};

// Partial specialization for pointer types
template <typename T, typename U>
class Pair<T*, U*> {
public:
    Pair(T* first, U* second) : first_(first), second_(second) {
        cout << "Partial specialization for pointers used" << endl;
    }
    
    void display() const {
        cout << "Pointer pair: " << *first_ << ", " << *second_ << endl;
    }
    
private:
    T* first_;
    U* second_;
};

int main() {
    // Uses primary template
    Pair<int, string> p1(42, "hello");
    p1.display();
    
    // Uses partial specialization for same types
    Pair<double, double> p2(3.14, 2.71);
    p2.display();
    cout << "Max value: " << p2.max() << endl;  // Additional method available
    
    // Uses partial specialization for pointers
    int x = 10, y = 20;
    Pair<int, int> p3(&x, &y);
    p3.display();
    
    return 0;
}
```

Partial specialization patterns can include:
- Same template parameters (`Pair<T,T>`)
- Pointer types (`Pair<T*,U*>`)
- Reference types (`Pair<T&,U&>`)
- Const qualifiers (`Pair<const T, U>`)
- Nested templates (`Pair<vector<T>, U>`)

### 10.3.4 Specialization for Array Types

Templates can be specialized for array types, which is particularly useful for creating safe array wrappers:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

// Primary template
template <typename T>
class Array {
public:
    explicit Array(size_t size) : size_(size) {
        data_ = new T[size];
        cout << "Generic Array constructor" << endl;
    }
    
    ~Array() {
        delete[] data_;
    }
    
    T& operator[](size_t index) {
        return data_[index];
    }
    
    size_t size() const {
        return size_;
    }
    
private:
    T* data_;
    size_t size_;
};

// Specialization for char arrays (strings)
template <>
class Array<char> {
public:
    explicit Array(size_t size) : size_(size) {
        data_ = new char[size + 1];  // Extra space for null terminator
        data_[0] = '\0';  // Initialize as empty string
        cout << "Specialized Array<char> constructor" << endl;
    }
    
    ~Array() {
        delete[] data_;
    }
    
    char& operator[](size_t index) {
        return data_[index];
    }
    
    size_t size() const {
        return size_;
    }
    
    // String-specific methods
    size_t length() const {
        return strlen(data_);
    }
    
    void assign(const char* str) {
        size_t len = strlen(str);
        if (len > size_) {
            len = size_;  // Truncate if too long
        }
        strncpy(data_, str, len);
        data_[len] = '\0';  // Ensure null termination
    }
    
private:
    char* data_;
    size_t size_;  // Size excluding null terminator
};

int main() {
    // Generic array of integers
    Array<int> intArray(5);
    for (size_t i = 0; i < intArray.size(); ++i) {
        intArray[i] = i * 10;
    }
    
    cout << "Int array contents: ";
    for (size_t i = 0; i < intArray.size(); ++i) {
        cout << intArray[i] << " ";
    }
    cout << endl;
    
    // Specialized array for characters (string)
    Array<char> charArray(20);  // Space for 20 chars + null terminator
    charArray.assign("Hello, specialization!");
    
    cout << "Char array contents: " << &charArray[0] << endl;
    cout << "Char array length: " << charArray.length() << endl;
    
    return 0;
}
```

This approach makes working with character arrays safer and more intuitive by providing string-specific functionality.

### 10.3.5 Specialization Based on Type Traits

Modern C++ provides type traits that can be used with SFINAE (Substitution Failure Is Not An Error) to create more sophisticated specializations:

```cpp
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
using namespace std;

// Primary template handles non-container types
template <typename T, typename = void>
class ElementPrinter {
public:
    static void print(const T& value) {
        cout << value << endl;
    }
};

// Specialization for container types (using SFINAE with std::void_t and decltype)
template <typename T>
class ElementPrinter<T, 
    std::void_t<decltype(std::declval<T>().begin()),  // Check for begin() method
               decltype(std::declval<T>().end())>>    // Check for end() method
{
public:
    static void print(const T& container) {
        cout << "Container elements: ";
        for (const auto& elem : container) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// Another example with std::enable_if
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
square(T value) {
    return value * value;
}

template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, void>::type
square(T value) {
    cout << "Cannot square non-arithmetic type" << endl;
}

int main() {
    // Test ElementPrinter
    int num = 42;
    string str = "Hello";
    vector<int> vec = {1, 2, 3, 4, 5};
    
    ElementPrinter<int>::print(num);           // Uses primary template
    ElementPrinter<string>::print(str);        // Uses primary template
    ElementPrinter<vector<int>>::print(vec);   // Uses container specialization
    
    // Test square function
    cout << "Square of 5: " << square(5) << endl;
    cout << "Square of 3.14: " << square(3.14) << endl;
    square("Cannot square me");  // Uses non-arithmetic version
    
    return 0;
}
```

In C++17 and later, you can use `if constexpr` for compile-time decisions that are more readable than SFINAE:

```cpp
#include <iostream>
#include <type_traits>
using namespace std;

// Single template function with compile-time branching
template <typename T>
auto process(T value) {
    if constexpr (is_integral_v<T>) {
        cout << "Processing integral type" << endl;
        return value * 2;
    } else if constexpr (is_floating_point_v<T>) {
        cout << "Processing floating-point type" << endl;
        return value * 3.14;
    } else {
        cout << "Processing other type" << endl;
        return value;
    }
}

int main() {
    int i = 10;
    double d = 2.5;
    string s = "test";
    
    auto result1 = process(i);  // int version
    auto result2 = process(d);  // double version
    auto result3 = process(s);  // other version
    
    cout << "Results: " << result1 << ", " << result2 << ", " << result3 << endl;
    
    return 0;
}
```

### 10.3.6 When to Use Template Specialization

Template specialization is powerful but should be used judiciously:

1. **Type-specific optimizations**: When you can provide a more efficient implementation for certain types
2. **Edge cases**: When the generic algorithm doesn't work for a specific type
3. **Different behaviors**: When you need fundamentally different behavior for certain types
4. **Adding functionality**: When you want to provide additional methods for specific types

Watch out for these pitfalls:
1. **Code bloat**: Excessive specializations can lead to code maintenance issues
2. **Surprising behavior**: Users might be surprised when their code behaves differently for different types
3. **Overspecialization**: Don't specialize when simple overloading would work

## 10.4 Variadic Templates

Variadic templates allow you to write templates that accept an arbitrary number of arguments of arbitrary types. This feature, introduced in C++11, enables powerful metaprogramming and perfect forwarding.

### 10.4.1 Basic Variadic Templates

The syntax for variadic templates uses `...` (ellipsis) in three different contexts:
1. **Parameter pack declaration**: `template <typename... Args>`
2. **Function parameter declaration**: `void func(Args... args)`
3. **Parameter pack expansion**: `func(args...)`

Here's a simple example:

```cpp
#include <iostream>
using namespace std;

// Variadic template function that prints all arguments
template <typename... Args>
void printAll(Args... args) {
    // This doesn't work directly because args is a parameter pack
    // We need a way to "unpack" it
}

// Helper function to print a single argument
template <typename T>
void print(T arg) {
    cout << arg << " ";
}

// Base case for recursion (no arguments)
void printAllHelper() {
    cout << endl;  // Just print a newline
}

// Recursive case with variadic template
template <typename First, typename... Rest>
void printAllHelper(First first, Rest... rest) {
    print(first);            // Process the first argument
    printAllHelper(rest...); // Process the rest recursively
}

// User-friendly wrapper
template <typename... Args>
void printAll(Args... args) {
    printAllHelper(args...);
}

int main() {
    // Call with different number and types of arguments
    printAll(1, 2, 3);
    printAll("Hello", "variadic", "templates", 2023);
    printAll(3.14, 'A', true, 42, "mixed types");
    
    return 0;
}
```

This example recursively processes the arguments in the parameter pack by peeling off one argument at a time.

### 10.4.2 Variadic Templates with Fold Expressions (C++17)

C++17 introduced fold expressions to simplify working with parameter packs:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Print all arguments using a fold expression
template <typename... Args>
void printAll(Args... args) {
    // Fold expression with comma operator
    ((cout << args << " "), ...);
    cout << endl;
}

// Sum all arguments
template <typename... Args>
auto sum(Args... args) {
    // Fold expression with addition operator
    return (... + args);
}

// Check if all conditions are true
template <typename... Args>
bool all(Args... args) {
    // Fold expression with AND operator
    return (... && args);
}

// Check if any condition is true
template <typename... Args>
bool any(Args... args) {
    // Fold expression with OR operator
    return (... || args);
}

int main() {
    // Test printing
    printAll(1, 2, 3, 4, 5);
    printAll("C++", "is", "awesome");
    
    // Test sum
    cout << "Sum of {1, 2, 3, 4, 5} = " << sum(1, 2, 3, 4, 5) << endl;
    cout << "Sum of {3.14, 2.71, 1.41} = " << sum(3.14, 2.71, 1.41) << endl;
    
    // Test logical operations
    cout << "all(true, true, true) = " << all(true, true, true) << endl;
    cout << "all(true, false, true) = " << all(true, false, true) << endl;
    cout << "any(false, false, true) = " << any(false, false, true) << endl;
    cout << "any(false, false, false) = " << any(false, false, false) << endl;
    
    return 0;
}
```

Fold expressions come in four forms:
1. **Unary right fold**: `(... op pack)`
2. **Unary left fold**: `(pack op ...)`
3. **Binary right fold**: `(init op ... op pack)`
4. **Binary left fold**: `(pack op ... op init)`

### 10.4.3 Perfect Forwarding with Variadic Templates

Variadic templates are often used with perfect forwarding to pass arguments to another function:

```cpp
#include <iostream>
#include <utility>  // For std::forward
#include <vector>
#include <string>
using namespace std;

class Widget {
public:
    template<typename... Args>
    explicit Widget(Args&&... args) {
        cout << "Widget constructor with " << sizeof...(args) << " arguments" << endl;
    }
};

// Factory function that forwards arguments to constructor
template<typename... Args>
Widget makeWidget(Args&&... args) {
    return Widget(std::forward<Args>(args)...);
}

// Example with container emplace
template<typename T, typename... Args>
void emplace_back_wrapper(vector<T>& v, Args&&... args) {
    cout << "Adding element with " << sizeof...(args) << " constructor arguments" << endl;
    v.emplace_back(std::forward<Args>(args)...);
}

int main() {
    // Create Widgets with different arguments
    Widget w1 = makeWidget();
    Widget w2 = makeWidget(10);
    Widget w3 = makeWidget("hello", 42, true);
    
    // Use with vector
    vector<string> strings;
    
    // Add strings with different constructors
    emplace_back_wrapper(strings, "Direct string");
    emplace_back_wrapper(strings, 10, 'a');  // string(10, 'a')
    emplace_back_wrapper(strings, "Hello"s + " world");  // string from expression
    
    cout << "Vector contains:" << endl;
    for (const auto& s : strings) {
        cout << "\"" << s << "\" (length: " << s.length() << ")" << endl;
    }
    
    return 0;
}
```

This pattern allows creating wrapper functions that preserve the perfect forwarding of arguments to the wrapped function.

### 10.4.4 Variadic Template Class

Template classes can also be variadic:

```cpp
#include <iostream>
#include <tuple>
using namespace std;

// Variadic class template
template<typename... Types>
class Tuple {
public:
    static constexpr size_t size = sizeof...(Types);
    
    Tuple() {
        cout << "Created Tuple with " << size << " types" << endl;
    }
};

// Partial specialization for an empty tuple
template<>
class Tuple<> {
public:
    static constexpr size_t size = 0;
    
    Tuple() {
        cout << "Created empty Tuple" << endl;
    }
};

// Recursive inheritance approach (common pre-C++17 technique)
template<typename Head, typename... Tail>
class RecursiveTuple {
private:
    Head head_;
    RecursiveTuple<Tail...> tail_;
    
public:
    RecursiveTuple(Head head, Tail... tail)
        : head_(head), tail_(tail...) {
        cout << "Added element of type " << typeid(Head).name() << endl;
    }
    
    Head getHead() const { return head_; }
    
    template<size_t I>
    auto get() const {
        if constexpr (I == 0)
            return head_;
        else
            return tail_.template get<I-1>();
    }
};

// Base case for recursive inheritance
template<typename T>
class RecursiveTuple<T> {
private:
    T value_;
    
public:
    RecursiveTuple(T value) : value_(value) {
        cout << "Added final element of type " << typeid(T).name() << endl;
    }
    
    T getHead() const { return value_; }
    
    template<size_t I>
    T get() const {
        static_assert(I == 0, "Index out of bounds");
        return value_;
    }
};

int main() {
    // Basic examples
    Tuple<> t0;
    Tuple<int> t1;
    Tuple<int, double, string> t3;
    
    // Recursive implementation
    RecursiveTuple<int, double, string> rt(42, 3.14, "hello");
    
    cout << "First element: " << rt.getHead() << endl;
    cout << "Elements by index:" << endl;
    cout << "  [0]: " << rt.get<0>() << endl;
    cout << "  [1]: " << rt.get<1>() << endl;
    cout << "  [2]: " << rt.get<2>() << endl;
    
    // Using standard library tuple
    tuple<int, double, string> std_tuple(42, 3.14, "hello");
    cout << "std::tuple elements:" << endl;
    cout << "  [0]: " << get<0>(std_tuple) << endl;
    cout << "  [1]: " << get<1>(std_tuple) << endl;
    cout << "  [2]: " << get<2>(std_tuple) << endl;
    
    return 0;
}
```

### 10.4.5 Expanding Parameter Packs in Different Contexts

Parameter packs can be expanded in various contexts:

```cpp
#include <iostream>
#include <array>
#include <vector>
using namespace std;

// Function call expansion
template<typename... Args>
void callFunctions(Args... funcs) {
    // Call each function with no arguments
    (funcs(), ...);  // Fold expression (C++17)
}

// Array initialization
template<typename T, typename... Args>
auto makeArray(Args... args) {
    return array<T, sizeof...(args)>{args...};
}

// Capture in lambda expressions
template<typename... Args>
auto captureAll(Args... args) {
    return [args...] {
        // Use fold expression to print
        ((cout << args << " "), ...);
        cout << endl;
    };
}

// Expansion in template arguments
template<typename... Ts>
struct TypeList {};

template<typename... Args>
auto makeTypeList() {
    return TypeList<Args...>{};
}

// Parameter pack in initializer lists
template<typename T, typename... Args>
vector<T> makeVector(Args... args) {
    return {static_cast<T>(args)...};
}

int main() {
    // Test function call expansion
    auto f1 = []{ cout << "Function 1 called" << endl; };
    auto f2 = []{ cout << "Function 2 called" << endl; };
    auto f3 = []{ cout << "Function 3 called" << endl; };
    
    callFunctions(f1, f2, f3);
    
    // Test array creation
    auto arr = makeArray<double>(1, 2, 3, 4, 5);
    cout << "Array contents: ";
    for (auto v : arr) {
        cout << v << " ";
    }
    cout << endl;
    
    // Test lambda capture
    auto printer = captureAll(10, "hello", 3.14, 'A');
    cout << "Lambda output: ";
    printer();
    
    // Test vector creation with type conversion
    auto vec = makeVector<double>(1, 2, 3, 4.5f, 5.5);
    cout << "Vector contents: ";
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 10.4.6 Variadic Templates Best Practices

1. **Use fold expressions in C++17 and later** for simpler code
2. **Use `sizeof...(args)` to get the number of arguments** in the parameter pack
3. **Always provide a base case for recursive variadic templates** (pre-C++17)
4. **Use `std::forward` for perfect forwarding** of arguments
5. **Use `decltype` and `declval` for complex type deductions**
6. **Consider readability** - variadic templates can become complex
7. **Use standard library variadic class templates** like `std::tuple` when appropriate
8. **Test with different numbers of arguments** including zero arguments

## 10.5 Template Metaprogramming

Template metaprogramming (TMP) is a technique that uses C++ templates to perform computations at compile time. It's a form of meta-programming, where the program manipulates itself during compilation.

### 10.5.1 Introduction to Template Metaprogramming

Template metaprogramming involves:
1. **Compile-time computation**: Calculations performed during compilation
2. **Type computation**: Creating and manipulating types programmatically
3. **Code generation**: Generating specialized code based on types or values

Here's a classic example - computing factorials at compile time:

```cpp
#include <iostream>
using namespace std;

// Factorial template metaprogram
template <unsigned int N>
struct Factorial {
    static constexpr unsigned int value = N * Factorial<N - 1>::value;
};

// Base case
template <>
struct Factorial<0> {
    static constexpr unsigned int value = 1;
};

int main() {
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    cout << "Factorial of 10: " << Factorial<10>::value << endl;
    
    // This value is computed at compile time!
    constexpr unsigned int fact5 = Factorial<5>::value;
    
    // Create an array with size determined at compile time
    array<int, Factorial<5>::value> data;
    cout << "Array size: " << data.size() << endl;
    
    return 0;
}
```

In C++14 and later, you can also use constexpr functions for compile-time computation:

```cpp
#include <iostream>
using namespace std;

// Constexpr factorial function (C++14 and later)
constexpr unsigned int factorial(unsigned int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    // Computed at compile time
    constexpr unsigned int fact5 = factorial(5);
    constexpr unsigned int fact10 = factorial(10);
    
    cout << "Factorial of 5: " << fact5 << endl;
    cout << "Factorial of 10: " << fact10 << endl;
    
    // Create a compile-time array
    array<int, factorial(6)> data;
    cout << "Array size: " << data.size() << endl;
    
    return 0;
}
```

### 10.5.2 Type Traits and Type Manipulation

Template metaprogramming is often used to inspect and manipulate types:

```cpp
#include <iostream>
#include <type_traits>
using namespace std;

// Custom type trait to check if a type can be incremented
template <typename T, typename = void>
struct is_incrementable : false_type {};

template <typename T>
struct is_incrementable<T, 
    void_t<decltype(++declval<T&>())>> : true_type {};

// Helper variable template (C++14)
template <typename T>
inline constexpr bool is_incrementable_v = is_incrementable<T>::value;

// Compute result type of adding two types
template <typename T, typename U>
struct addition_result {
    using type = decltype(declval<T>() + declval<U>());
};

template <typename T, typename U>
using addition_result_t = typename addition_result<T, U>::type;

int main() {
    // Check if types are incrementable
    cout << "int is incrementable: " << is_incrementable_v<int> << endl;
    cout << "float is incrementable: " << is_incrementable_v<float> << endl;
    cout << "string is incrementable: " << is_incrementable_v<string> << endl;
    cout << "vector<int> is incrementable: " << is_incrementable_v<vector<int>> << endl;
    
    // Test addition result
    using IntPlusFloat = addition_result_t<int, float>;
    cout << "Type of int + float is: " << typeid(IntPlusFloat).name() << endl;
    
    // Use standard type traits
    cout << "is_integral<int>: " << is_integral_v<int> << endl;
    cout << "is_floating_point<double>: " << is_floating_point_v<double> << endl;
    cout << "is_same<int, long>: " << is_same_v<int, long> << endl;
    cout << "is_convertible<float, int>: " << is_convertible_v<float, int> << endl;
    
    return 0;
}
```

C++ provides many built-in type traits in the `<type_traits>` header, which form a crucial foundation for template metaprogramming.

### 10.5.3 SFINAE (Substitution Failure Is Not An Error)

SFINAE is a key concept in template metaprogramming, allowing you to select function overloads based on type properties:

```cpp
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

// Print size for containers that have a size() method
template <typename T>
auto printSize(const T& container) 
    -> decltype(container.size(), void()) {
    cout << "Container size: " << container.size() << endl;
}

// Fallback for types without a size() method
template <typename T>
void printSize(...) {
    cout << "Object has no size() method" << endl;
}

// SFINAE with enable_if for more complex conditions
template <typename T>
typename enable_if<is_integral<T>::value, T>::type
twice(T value) {
    return value * 2;
}

template <typename T>
typename enable_if<!is_integral<T>::value && is_floating_point<T>::value, T>::type
twice(T value) {
    return value * 2.0;
}

// C++20: Using concepts instead of SFINAE
#ifdef __cpp_concepts
template <typename T>
requires is_integral_v<T>
T twice_concept(T value) {
    return value * 2;
}

template <typename T>
requires (!is_integral_v<T> && is_floating_point_v<T>)
T twice_concept(T value) {
    return value * 2.0;
}
#endif

int main() {
    vector<int> vec = {1, 2, 3};
    string str = "hello";
    int num = 42;
    
    printSize(vec);   // Has size() method
    printSize(str);   // Has size() method
    printSize(num);   // No size() method
    
    cout << "twice(10): " << twice(10) << endl;
    cout << "twice(3.14): " << twice(3.14) << endl;
    
#ifdef __cpp_concepts
    cout << "twice_concept(10): " << twice_concept(10) << endl;
    cout << "twice_concept(3.14): " << twice_concept(3.14) << endl;
#endif
    
    return 0;
}
```

SFINAE relies on the C++ rule that if template argument substitution leads to an invalid type or expression, the compiler simply removes that overload from consideration rather than treating it as an error.

### 10.5.4 Conditional Compilation and Tag Dispatching

Tag dispatching is a technique that allows you to select different implementations based on type properties:

```cpp
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
using namespace std;

// Tag types for dispatching
struct random_access_tag {};
struct bidirectional_tag {};
struct forward_tag {};

// Tag selection based on iterator category
template <typename Iter>
struct iterator_category_tag {
    using type = conditional_t<
        is_same_v<typename iterator_traits<Iter>::iterator_category, random_access_iterator_tag>,
        random_access_tag,
        conditional_t<
            is_same_v<typename iterator_traits<Iter>::iterator_category, bidirectional_iterator_tag>,
            bidirectional_tag,
            forward_tag
        >
    >;
};

// Implementation for random access iterators
template <typename Iter>
void advance_impl(Iter& it, int n, random_access_tag) {
    cout << "Using fast random access advance" << endl;
    it += n;  // Random access iterators can do this efficiently
}

// Implementation for bidirectional iterators
template <typename Iter>
void advance_impl(Iter& it, int n, bidirectional_tag) {
    cout << "Using bidirectional advance" << endl;
    if (n >= 0) {
        while (n--) ++it;
    } else {
        while (n++) --it;  // Can go backwards efficiently
    }
}

// Implementation for forward iterators
template <typename Iter>
void advance_impl(Iter& it, int n, forward_tag) {
    cout << "Using forward-only advance" << endl;
    if (n < 0) {
        throw runtime_error("Cannot move backward with forward iterator");
    }
    while (n--) ++it;
}

// Unified interface that dispatches to the right implementation
template <typename Iter>
void custom_advance(Iter& it, int n) {
    advance_impl(it, n, typename iterator_category_tag<Iter>::type{});
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    list<int> lst = {1, 2, 3, 4, 5};
    
    auto vecIt = vec.begin();
    auto lstIt = lst.begin();
    
    custom_advance(vecIt, 2);  // Uses random access
    custom_advance(lstIt, 2);  // Uses bidirectional
    
    cout << "Vector iterator now points to: " << *vecIt << endl;
    cout << "List iterator now points to: " << *lstIt << endl;
    
    return 0;
}
```

Tag dispatching selects the most appropriate implementation at compile time based on type characteristics, without code duplication or runtime checks.

### 10.5.5 Recursive Template Pattern Matching

Template specializations can be used for pattern matching at compile time:

```cpp
#include <iostream>
#include <tuple>
using namespace std;

// Tuple printer using recursive templates
// Primary template for empty case
template <typename Tuple, size_t N = 0>
struct TuplePrinter {
    static void print(const Tuple& t) {
        // Do nothing - we've reached the end of recursion
    }
};

// Specialization that handles each element
template <typename Tuple, size_t N>
struct TuplePrinter<Tuple, N> {
    static void print(const Tuple& t) {
        // Base case: we're at the last element
        if constexpr (N == tuple_size_v<Tuple> - 1) {
            cout << get<N>(t);
        } else {
            // Recursive case: print this element and continue
            cout << get<N>(t) << ", ";
            TuplePrinter<Tuple, N+1>::print(t);
        }
    }
};

// User-friendly wrapper
template <typename... Args>
void printTuple(const tuple<Args...>& t) {
    cout << "(";
    TuplePrinter<tuple<Args...>, 0>::print(t);
    cout << ")" << endl;
}

// Another example: compile-time list processing
template <typename... Types>
struct TypeList {};

// Get head (first type) of a TypeList
template <typename Head, typename... Tail>
struct GetHead {
    using type = Head;
};

template <typename... Types>
using Head_t = typename GetHead<Types...>::type;

// Get tail (all but first) of a TypeList
template <typename Head, typename... Tail>
struct GetTail {
    using type = TypeList<Tail...>;
};

template <typename... Types>
using Tail_t = typename GetTail<Types...>::type;

// Is the TypeList empty?
template <typename... Types>
struct IsEmpty {
    static constexpr bool value = sizeof...(Types) == 0;
};

template <typename... Types>
inline constexpr bool IsEmpty_v = IsEmpty<Types...>::value;

int main() {
    // Test tuple printer
    tuple<int, string, double, char> t(42, "hello", 3.14, 'A');
    printTuple(t);
    
    // Test TypeList operations
    using MyTypes = TypeList<int, double, string, vector<int>>;
    
    // Extract some type information at compile time
    using FirstType = Head_t<int, double, string>;
    using RemainingTypes = Tail_t<int, double, string>;
    
    cout << "IsEmpty<>: " << IsEmpty_v<> << endl;
    cout << "IsEmpty<int>: " << IsEmpty_v<int> << endl;
    
    cout << "First type is: " << typeid(FirstType).name() << endl;
    
    return 0;
}
```

This pattern is particularly useful for processing complex types at compile time.

### 10.5.6 Compile-Time if with constexpr (C++17)

C++17's `if constexpr` greatly simplifies many template metaprogramming patterns:

```cpp
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
using namespace std;

// Generic print function using if constexpr
template <typename T>
void smartPrint(const T& value) {
    if constexpr (is_same_v<T, string>) {
        cout << "String: \"" << value << "\"" << endl;
    }
    else if constexpr (is_integral_v<T>) {
        cout << "Integer: " << value << " (0x" << hex << value << dec << ")" << endl;
    }
    else if constexpr (is_floating_point_v<T>) {
        cout << "Float: " << fixed << value << endl;
    }
    else if constexpr (requires { value.size(); }) {
        cout << "Container with " << value.size() << " elements: ";
        for (const auto& elem : value) {
            cout << elem << " ";
        }
        cout << endl;
    }
    else {
        cout << "Generic value: " << value << endl;
    }
}

// Compile-time recursion with if constexpr
template <typename Tuple, size_t... I>
void printTupleImpl(const Tuple& t, index_sequence<I...>) {
    // Using fold expression with if constexpr
    cout << "(";
    ((cout << (I == 0 ? "" : ", ") << get<I>(t)), ...);
    cout << ")" << endl;
}

template <typename... Args>
void printTuple2(const tuple<Args...>& t) {
    printTupleImpl(t, make_index_sequence<sizeof...(Args)>{});
}

int main() {
    smartPrint(42);
    smartPrint(3.14159);
    smartPrint("raw c-string");
    smartPrint(string("std::string"));
    
    vector<int> vec = {1, 2, 3, 4, 5};
    smartPrint(vec);
    
    // Test improved tuple printer
    tuple<int, string, double, bool> t(42, "hello", 3.14, true);
    printTuple2(t);
    
    return 0;
}
```

`if constexpr` evaluates the condition at compile time and only instantiates the selected branch, avoiding compilation errors that would occur in unselected branches.

### 10.5.7 Compile-Time Programming with C++20 Concepts

C++20 concepts formalize template constraints and can be used in metaprogramming:

```cpp
#include <iostream>
#include <type_traits>
#include <concepts>
using namespace std;

// Define a concept for arithmetic types
template <typename T>
concept Arithmetic = is_arithmetic_v<T>;

// Define a concept for container types
template <typename T>
concept Container = requires(T container) {
    { container.begin() } -> std::input_or_output_iterator;
    { container.end() } -> std::input_or_output_iterator;
    { container.size() } -> std::convertible_to<size_t>;
};

// Define a concept for printable types
template <typename T>
concept Printable = requires(T x, ostream& os) {
    { os << x } -> same_as<ostream&>;
};

// Function that works only with arithmetic types
template <Arithmetic T>
T square(T value) {
    return value * value;
}

// Function that works with containers
template <Container T>
auto sum(const T& container) {
    using value_type = decay_t<decltype(*begin(container))>;
    value_type result{};
    for (const auto& item : container) {
        result += item;
    }
    return result;
}

// Function that prints anything printable
template <Printable T>
void print(const T& value) {
    cout << value << endl;
}

int main() {
    // Test with arithmetic types
    cout << "square(7) = " << square(7) << endl;
    cout << "square(3.14) = " << square(3.14) << endl;
    
    // Test with containers
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "sum(vec) = " << sum(vec) << endl;
    
    array<double, 3> arr = {1.1, 2.2, 3.3};
    cout << "sum(arr) = " << sum(arr) << endl;
    
    // Test with printable types
    print("Hello, concepts!");
    print(42);
    print(vector<int>{1, 2, 3});
    
    return 0;
}
```

### 10.5.8 Real-World Applications of Template Metaprogramming

TMP is used in many practical applications:

1. **Expression templates**:

```cpp
#include <iostream>
using namespace std;

// Forward declarations
template <typename T> class Expression;
template <typename L, typename R> class Addition;

// Base expression template
template <typename Derived>
class Expression {
public:
    // Cast this to the derived type
    const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
    
    // Evaluate the expression
    double evaluate() const {
        return derived().evaluate();
    }
};

// Scalar value expression
template <typename T>
class Scalar : public Expression<Scalar<T>> {
private:
    T value_;
    
public:
    explicit Scalar(T value) : value_(value) {}
    
    double evaluate() const {
        return value_;
    }
};

// Addition expression
template <typename L, typename R>
class Addition : public Expression<Addition<L, R>> {
private:
    const L& lhs_;
    const R& rhs_;
    
public:
    Addition(const L& lhs, const R& rhs) : lhs_(lhs), rhs_(rhs) {}
    
    double evaluate() const {
        return lhs_.evaluate() + rhs_.evaluate();
    }
};

// Operator overload to create expression templates
template <typename L, typename R>
Addition<L, R> operator+(const Expression<L>& lhs, const Expression<R>& rhs) {
    return Addition<L, R>(lhs.derived(), rhs.derived());
}

int main() {
    // Create expression: 2 + 3 + 4
    Scalar<int> a(2), b(3), c(4);
    auto expr = a + b + c;
    
    // Evaluate the expression
    cout << "Result of 2 + 3 + 4 = " << expr.evaluate() << endl;
    
    // More complex expression: (2 + 3) + (4 + 5)
    Scalar<int> d(5);
    auto expr2 = (a + b) + (c + d);
    cout << "Result of (2 + 3) + (4 + 5) = " << expr2.evaluate() << endl;
    
    return 0;
}
```

2. **Static reflection**:

```cpp
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

// Simple struct for demonstration
struct Person {
    string name;
    int age;
    double height;
};

// Define a reflection helper
#define REFLECT_STRUCT_BEGIN(Type) \
    template <> struct Reflector<Type> { \
        using type = Type; \
        static constexpr auto get_members() { \
            return make_tuple(

#define REFLECT_MEMBER(name) \
            Member{#name, &type::name},

#define REFLECT_STRUCT_END() \
            ); \
        } \
    };

// Member information
struct Member {
    string_view name;
    void* ptr;
    
    template <typename T, typename U>
    Member(string_view name, U T::* member_ptr) 
        : name(name), ptr(reinterpret_cast<void*>(&member_ptr)) {}
};

// Primary template
template <typename T>
struct Reflector {};

// Apply reflection to Person struct
REFLECT_STRUCT_BEGIN(Person)
    REFLECT_MEMBER(name)
    REFLECT_MEMBER(age)
    REFLECT_MEMBER(height)
REFLECT_STRUCT_END()

// Generic function to print any reflected struct
template <typename T>
void print_struct(const T& obj) {
    cout << "Struct of type " << typeid(T).name() << " {\n";
    
    const auto members = Reflector<T>::get_members();
    apply([&obj](const auto&... members) {
        ((cout << "  " << members.name << ": " << 
           get_member_value(obj, members) << "\n"), ...);
    }, members);
    
    cout << "}" << endl;
}

// Helper to get member value (simplified)
template <typename T, typename Member>
auto get_member_value(const T& obj, const Member& member) {
    // This is a simplified implementation - real reflection would be more complex
    if (member.name == "name")
        return obj.name;
    else if (member.name == "age")
        return obj.age;
    else if (member.name == "height")
        return obj.height;
    else
        return string("unknown");
}

int main() {
    Person p{"John Doe", 30, 1.75};
    print_struct(p);
    
    return 0;
}
```

Note: True C++ reflection is still evolving, with proposals being considered for standardization. The above is a simplified example.

3. **Policy-based design**:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// Sorting policies
struct QuickSortPolicy {
    template <typename Iterator>
    static void sort(Iterator begin, Iterator end) {
        cout << "Using QuickSort policy" << endl;
        std::sort(begin, end);  // std::sort uses quicksort-like algorithm
    }
};

struct BubbleSortPolicy {
    template <typename Iterator>
    static void sort(Iterator begin, Iterator end) {
        cout << "Using BubbleSort policy" << endl;
        // Simple bubble sort implementation
        auto n = distance(begin, end);
        for (auto i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (auto j = 0; j < n - i - 1; ++j) {
                auto current = begin;
                advance(current, j);
                auto next = current;
                advance(next, 1);
                if (*current > *next) {
                    iter_swap(current, next);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
};

// Storage policies
struct VectorStorage {
    template <typename T>
    using container_type = vector<T>;
    
    static constexpr const char* name() { return "Vector Storage"; }
};

struct ListStorage {
    template <typename T>
    using container_type = list<T>;
    
    static constexpr const char* name() { return "List Storage"; }
};

// Container class that uses policies
template <
    typename T,
    typename StoragePolicy = VectorStorage,
    typename SortPolicy = QuickSortPolicy
>
class SortedContainer {
public:
    using container_t = typename StoragePolicy::template container_type<T>;
    
    void add(const T& value) {
        data_.push_back(value);
    }
    
    void sort() {
        cout << "Sorting " << StoragePolicy::name() << " using ";
        SortPolicy::sort(data_.begin(), data_.end());
    }
    
    void display() const {
        cout << "Container contents: ";
        for (const auto& item : data_) {
            cout << item << " ";
        }
        cout << endl;
    }
    
private:
    container_t data_;
};

int main() {
    // Different container configurations using policies
    SortedContainer<int> default_container;
    default_container.add(3);
    default_container.add(1);
    default_container.add(4);
    default_container.add(2);
    
    cout << "Default container: " << endl;
    default_container.sort();
    default_container.display();
    
    // Container with list storage and bubble sort
    SortedContainer<int, ListStorage, BubbleSortPolicy> custom_container;
    custom_container.add(3);
    custom_container.add(1);
    custom_container.add(4);
    custom_container.add(2);
    
    cout << "\nCustom container: " << endl;
    custom_container.sort();
    custom_container.display();
    
    return 0;
}
```

### 10.5.9 Template Metaprogramming Best Practices

1. **Use modern C++ features** like `constexpr`, `if constexpr`, and concepts when available
2. **Avoid excessive complexity** - TMP can become very difficult to understand
3. **Document your metaprogramming code thoroughly** - explain the intent and techniques
4. **Use standard library type traits** rather than reinventing them
5. **Use meaningful names** for template parameters and metafunctions
6. **Provide user-friendly wrappers** around complex metaprogramming
7. **Limit compile-time recursion depth** to avoid compiler limits
8. **Consider compile time** - heavy TMP can slow down compilation significantly
9. **Use static_assert** to provide clear error messages for invalid usage
10. **Test both positive and negative cases** to ensure correct behavior
