# Modern C++ Features

This document covers various modern features introduced in C++11 and later versions, enhancing the language's usability, performance, and safety.

## 1. Auto Keyword and Type Inference

The `auto` keyword allows the compiler to automatically deduce the type of a variable from its initializer, reducing verbosity and improving code maintainability.

### Basic Usage
```cpp
auto x = 5;                     // x is of type int
auto y = 3.14;                  // y is of type double
auto str = "Hello";             // str is of type const char*
auto vec = std::vector<int>{};  // vec is of type std::vector<int>
```

### With Functions
```cpp
auto add(int a, int b) -> int { // Trailing return type syntax
    return a + b;
}

// C++14 allows auto return type deduction
auto multiply(int a, int b) {
    return a * b;  // Return type is deduced as int
}
```

### Common Pitfalls
- `auto` drops const and references unless explicitly specified
```cpp
const std::vector<int> getVector();
auto v1 = getVector();       // v1 is std::vector<int>, not const
const auto v2 = getVector(); // v2 is const std::vector<int>
auto& v3 = getVector();      // v3 is const std::vector<int>&
```

## 2. Range-Based For Loops

Range-based for loops provide a cleaner syntax for iterating through collections without needing explicit iterators or indices.

### Basic Syntax
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// By value (creates copy)
for (auto element : vec) {
    std::cout << element << " ";
}

// By reference (no copying, can modify elements)
for (auto& element : vec) {
    element *= 2;  // Doubles each element
}

// By const reference (no copying, read-only)
for (const auto& element : vec) {
    std::cout << element << " ";
}
```

### Works With Various Collection Types
```cpp
// Arrays
int arr[] = {1, 2, 3, 4, 5};
for (auto elem : arr) { std::cout << elem << " "; }

// STL containers
std::map<std::string, int> map = {{"one", 1}, {"two", 2}};
for (const auto& [key, value] : map) { // C++17 structured binding
    std::cout << key << ": " << value << std::endl;
}

// Custom containers (requires begin() and end() functions)
```

### Performance Considerations
- Use references to avoid unnecessary copying
- Use const references for read-only operations

## 3. Lambda Expressions

Lambda expressions allow the creation of anonymous functions, enabling more concise code for operations that would otherwise require separate function definitions.

### Basic Syntax
```cpp
// [capture-clause](parameters) -> return_type { body }
auto add = [](int a, int b) -> int { return a + b; };
std::cout << add(5, 3); // Outputs 8

// Return type can often be deduced
auto multiply = [](int a, int b) { return a * b; };
```

### Capturing Variables
```cpp
int multiplier = 5;

// Capture by value
auto times_val = [multiplier](int x) { return x * multiplier; };

// Capture by reference
auto times_ref = [&multiplier](int x) { return x * multiplier; };

// Capture all local variables by value
auto lambda_all_val = [=]() { /* ... */ };

// Capture all local variables by reference
auto lambda_all_ref = [&]() { /* ... */ };

// Mixed captures
auto lambda_mixed = [=, &multiplier]() { /* ... */ };

// Capture with initialization (C++14)
auto init_capture = [value = 42]() { return value; };
```

### Mutable Lambdas
```cpp
auto counter = [count = 0]() mutable {
    return ++count;
};

std::cout << counter() << std::endl; // 1
std::cout << counter() << std::endl; // 2
```

### Generic Lambdas (C++14)
```cpp
auto print = [](const auto& value) {
    std::cout << value << std::endl;
};

print(42);        // Works with int
print("Hello");   // Works with const char*
print(3.14159);   // Works with double
```

### Common Use Cases
```cpp
// With algorithms
std::vector<int> numbers = {1, 5, 4, 2, 3};
std::sort(numbers.begin(), numbers.end(), 
          [](int a, int b) { return a > b; }); // Sort descending

// As callbacks
button.setOnClickListener([](ClickEvent e) {
    std::cout << "Button clicked at: " << e.getX() << "," << e.getY() << std::endl;
});
```

## 4. nullptr

`nullptr` is a type-safe null pointer constant that replaces the use of `NULL` or `0` for pointer values.

### Basic Usage
```cpp
int* ptr = nullptr;  // Better than int* ptr = NULL or int* ptr = 0
```

### Advantages
```cpp
// Resolves function overload ambiguity
void foo(int);
void foo(char*);

foo(0);      // Calls foo(int)
foo(nullptr); // Calls foo(char*)

// Type safety
int x = nullptr; // Error: cannot convert nullptr to int
```

### With Templates and Auto
```cpp
template <typename T>
void processPointer(T ptr) {
    if (ptr == nullptr) {
        // Handle null case
    }
    // Handle non-null case
}

auto ptr = nullptr; // Type is std::nullptr_t, not int
```

## 5. Smart Pointers

Smart pointers automate memory management, helping to prevent memory leaks and other memory-related issues.

### std::unique_ptr
Exclusive ownership model - exactly one owner of the pointer.

```cpp
// Creation
std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2 = std::make_unique<int>(10); // C++14, preferred

// Cannot be copied
// std::unique_ptr<int> ptr3 = ptr1; // Error

// Can be moved
std::unique_ptr<int> ptr3 = std::move(ptr1); // ptr1 is now empty

// Access
std::cout << *ptr2 << std::endl; // 10

// Custom deleters
auto customDeleter = [](int* p) {
    std::cout << "Deleting at " << p << std::endl;
    delete p;
};
std::unique_ptr<int, decltype(customDeleter)> ptr4(new int(20), customDeleter);

// Array support
std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);
arr[0] = 1;
```

### std::shared_ptr
Shared ownership model - multiple pointers can own the same object.

```cpp
// Creation
std::shared_ptr<int> ptr1(new int(5));
std::shared_ptr<int> ptr2 = std::make_shared<int>(10); // Preferred (single allocation)

// Can be copied
std::shared_ptr<int> ptr3 = ptr2; // Both ptr2 and ptr3 point to the same int(10)

// Reference counting
std::cout << ptr2.use_count() << std::endl; // 2

// Custom deleters
std::shared_ptr<int> ptr4(new int(20), [](int* p) {
    std::cout << "Custom deleter called" << std::endl;
    delete p;
});
```

### std::weak_ptr
A non-owning "weak" reference to an object managed by std::shared_ptr.

```cpp
// Helps break reference cycles
std::shared_ptr<int> shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;

// Check if the object still exists and access it
if (auto ptr = weak.lock()) {
    std::cout << "Value: " << *ptr << std::endl;
} else {
    std::cout << "Object no longer exists" << std::endl;
}
```

### Example: Avoiding Circular References
```cpp
struct Node {
    int value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Prevents circular reference
};

void createNodes() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    
    node1->next = node2;
    node2->prev = node1;  // If this were shared_ptr, we'd have a memory leak
}
```

## 6. Move Semantics and Rvalue References

Move semantics allows the efficient transfer of resources from temporary objects, avoiding unnecessary copies.

### Rvalue References
```cpp
void process(int& x) { std::cout << "lvalue reference: " << x << std::endl; }
void process(int&& x) { std::cout << "rvalue reference: " << x << std::endl; }

int main() {
    int a = 5;
    process(a);      // Calls lvalue version
    process(10);     // Calls rvalue version
    process(std::move(a)); // Calls rvalue version, a is now in a valid but unspecified state
}
```

### Move Constructor and Assignment
```cpp
class ResourceOwner {
private:
    int* resource;
    
public:
    // Constructor
    ResourceOwner(int value) : resource(new int(value)) {
        std::cout << "Constructor called" << std::endl;
    }
    
    // Destructor
    ~ResourceOwner() {
        std::cout << "Destructor called" << std::endl;
        delete resource;
    }
    
    // Copy constructor
    ResourceOwner(const ResourceOwner& other) : resource(new int(*other.resource)) {
        std::cout << "Copy constructor called" << std::endl;
    }
    
    // Move constructor
    ResourceOwner(ResourceOwner&& other) noexcept : resource(other.resource) {
        std::cout << "Move constructor called" << std::endl;
        other.resource = nullptr; // Important: prevent double deletion
    }
    
    // Copy assignment
    ResourceOwner& operator=(const ResourceOwner& other) {
        std::cout << "Copy assignment called" << std::endl;
        if (this != &other) {
            delete resource;
            resource = new int(*other.resource);
        }
        return *this;
    }
    
    // Move assignment
    ResourceOwner& operator=(ResourceOwner&& other) noexcept {
        std::cout << "Move assignment called" << std::endl;
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
    
    int getValue() const { return resource ? *resource : 0; }
};
```

### Example Usage
```cpp
void demonstrateMoveSemantics() {
    std::vector<ResourceOwner> vec;
    
    std::cout << "Creating and pushing object:" << std::endl;
    ResourceOwner obj(42);
    vec.push_back(obj);  // Copy constructor called
    
    std::cout << "\nPushing temporary object:" << std::endl;
    vec.push_back(ResourceOwner(100));  // Move constructor called
    
    std::cout << "\nPushing with std::move:" << std::endl;
    vec.push_back(std::move(obj));  // Move constructor called
}
```

### Perfect Forwarding
```cpp
template<typename T, typename... Args>
std::unique_ptr<T> create_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```

## 7. std::tuple and std::pair

These utilities allow grouping multiple values of different types.

### std::pair
```cpp
// Creating pairs
std::pair<int, std::string> p1 = {1, "example"};
auto p2 = std::make_pair(2, "another example");

// Accessing elements
std::cout << p1.first << ": " << p1.second << std::endl;

// Structured binding (C++17)
auto [id, name] = p2;
std::cout << id << ": " << name << std::endl;
```

### std::tuple
```cpp
// Creating tuples
std::tuple<int, double, std::string> t1 = {1, 3.14, "tuple"};
auto t2 = std::make_tuple(2, 2.71, "another tuple");

// Accessing elements
std::cout << std::get<0>(t1) << std::endl;  // 1
std::cout << std::get<1>(t1) << std::endl;  // 3.14
std::cout << std::get<2>(t1) << std::endl;  // "tuple"

// Getting element by type (must be unique types)
std::cout << std::get<int>(t1) << std::endl;     // 1
std::cout << std::get<double>(t1) << std::endl;  // 3.14

// Structured binding (C++17)
auto [id, value, description] = t2;
std::cout << id << ", " << value << ", " << description << std::endl;

// std::tie for unpacking
int x;
double y;
std::string z;
std::tie(x, y, z) = t1;

// Concatenating tuples
auto combined = std::tuple_cat(t1, t2);
```

## 8. std::optional and std::variant

These types provide safer alternatives to represent values that might be absent or that could be one of several types.

### std::optional (C++17)
```cpp
#include <optional>

// Creating optionals
std::optional<int> o1 = 42;
std::optional<int> o2; // empty

// Checking and accessing value
if (o1.has_value()) {
    std::cout << *o1 << std::endl;
}

// Default value if not present
int value = o2.value_or(0); // value = 0

// Assignment
o2 = 24;
o1 = std::nullopt; // Make empty

// Use in functions
std::optional<std::string> findUserName(int id) {
    if (userExists(id)) {
        return getUserName(id);
    }
    return std::nullopt;
}
```

### std::variant (C++17)
```cpp
#include <variant>

// Creating variants
std::variant<int, double, std::string> v1 = 42;
std::variant<int, double, std::string> v2 = 3.14;
std::variant<int, double, std::string> v3 = "hello";

// Checking type
if (std::holds_alternative<int>(v1)) {
    std::cout << "v1 holds an int" << std::endl;
}

// Getting value
std::cout << std::get<int>(v1) << std::endl;
// std::cout << std::get<double>(v1) << std::endl; // Would throw std::bad_variant_access

// Safe access with std::get_if
if (auto pval = std::get_if<double>(&v2)) {
    std::cout << "v2 holds double: " << *pval << std::endl;
}

// Visitor pattern
std::variant<int, float, std::string> v4 = "hello";

auto visitor = [](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>)
        std::cout << "int: " << arg << std::endl;
    else if constexpr (std::is_same_v<T, float>)
        std::cout << "float: " << arg << std::endl;
    else if constexpr (std::is_same_v<T, std::string>)
        std::cout << "string: " << arg << std::endl;
};

std::visit(visitor, v4);
```

## 9. Concurrency and Multithreading

C++11 introduced a standard threading library, eliminating the need for platform-specific APIs.

### std::thread
```cpp
#include <thread>
#include <iostream>

void func(int x) {
    std::cout << "Thread ID: " << std::this_thread::get_id() 
              << " Value: " << x << std::endl;
}

int main() {
    // Create and start thread
    std::thread t1(func, 42);
    
    // Lambda with thread
    std::thread t2([](int x) {
        std::cout << "Lambda thread: " << x << std::endl;
    }, 100);
    
    // Wait for threads to finish
    t1.join();
    t2.join();
    
    // Detaching threads (careful!)
    std::thread t3(func, 200);
    t3.detach();
    
    return 0; // t3 may still be running
}
```

### Synchronization
```cpp
#include <mutex>
#include <shared_mutex> // C++17

std::mutex mtx;
int shared_data = 0;

void incrementSafe() {
    std::lock_guard<std::mutex> lock(mtx); // RAII lock
    shared_data++;
}

void complexOperation() {
    std::unique_lock<std::mutex> lock(mtx); // More flexible than lock_guard
    // Can unlock/lock multiple times
    lock.unlock();
    // Do something without the lock
    lock.lock();
    shared_data += 2;
}

// Reader-writer locks (C++17)
std::shared_mutex rwmtx;

void reader() {
    std::shared_lock lock(rwmtx); // Multiple threads can read
    // Read shared data
}

void writer() {
    std::unique_lock lock(rwmtx); // Exclusive access
    // Modify shared data
}
```

### Condition Variables
```cpp
std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

void producer() {
    // Prepare data
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_ready = true;
    }
    cv.notify_one(); // Notify one waiting thread
    // cv.notify_all(); // Notify all waiting threads
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return data_ready; }); // Predicate prevents spurious wakeups
    // Process data
}
```

### Futures and Promises
```cpp
#include <future>

// Using async
std::future<int> result = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
});

// Do other work while calculation runs
std::cout << "Waiting for result..." << std::endl;

// Get result (will block until ready)
std::cout << "Result: " << result.get() << std::endl;

// Manual future/promise
std::promise<std::string> promise;
std::future<std::string> future = promise.get_future();

std::thread t([&promise]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    promise.set_value("Hello from thread");
    // For exceptions: promise.set_exception(std::make_exception_ptr(std::runtime_error("Error")));
});

std::cout << future.get() << std::endl;
t.join();
```

## 10. Regular Expressions

The `<regex>` library provides support for regular expressions.

```cpp
#include <regex>
#include <iostream>
#include <string>

void regex_examples() {
    std::string text = "John Smith: 123-456-7890, Jane Doe: 987-654-3210";
    std::regex phone_pattern(R"((\d{3})-(\d{3})-(\d{4}))");
    
    // Search for a match
    std::smatch match;
    if (std::regex_search(text, match, phone_pattern)) {
        std::cout << "Found: " << match[0] << std::endl;
        std::cout << "Area code: " << match[1] << std::endl;
    }
    
    // Iterate through all matches
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), phone_pattern);
    auto words_end = std::sregex_iterator();
    
    std::cout << "Found " << std::distance(words_begin, words_end) << " phone numbers:" << std::endl;
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::cout << match.str() << std::endl;
    }
    
    // Replace
    std::string result = std::regex_replace(
        text, 
        phone_pattern, 
        "($1) $2-$3"
    );
    std::cout << "After replacement: " << result << std::endl;
    
    // Validation
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::string email = "user@example.com";
    bool is_valid = std::regex_match(email, email_pattern);
    std::cout << email << " is " << (is_valid ? "valid" : "invalid") << std::endl;
}
```

## 11. Structured Bindings (C++17)

Structured bindings allow you to destructure objects into individual variables.

```cpp
// With arrays
int arr[] = {1, 2, 3};
auto [a, b, c] = arr;

// With pairs
std::pair<int, std::string> person = {1, "Alice"};
auto [id, name] = person;

// With tuples
std::tuple<int, double, std::string> record = {1, 3.14, "Pi"};
auto [key, value, desc] = record;

// With custom structures
struct Point {
    double x;
    double y;
};
Point p = {2.5, 3.7};
auto [x, y] = p;

// In range-based for loops
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Carol", 92}};
for (const auto& [name, score] : scores) {
    std::cout << name << " scored " << score << std::endl;
}
```

## 12. if constexpr (C++17)

Allows compile-time conditional code selection.

```cpp
template <typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // This code is only instantiated when T is an integral type
        std::cout << "Integer: " << value << std::endl;
    } 
    else if constexpr (std::is_floating_point_v<T>) {
        // This code is only instantiated when T is a floating-point type
        std::cout << "Float: " << value << std::endl;
        std::cout << "Rounded: " << std::round(value) << std::endl;
    } 
    else if constexpr (std::is_same_v<T, std::string>) {
        // This code is only instantiated when T is std::string
        std::cout << "String: " << value << " (length: " << value.length() << ")" << std::endl;
    } 
    else {
        // Fallback for other types
        std::cout << "Other type" << std::endl;
    }
}
```

## Problem Exercises
1. **Auto Keyword**: Create a function that returns a vector of integers and use `auto` to iterate through it.
   - [LeetCode Problem](https://leetcode.com/problems/two-sum/)
   
2. **Range-Based For Loops**: Write a program that takes a list of numbers and prints their squares using a range-based for loop.
   - [HackerRank Problem](https://www.hackerrank.com/challenges/c-tutorial-for-loop/problem)

3. **Lambda Expressions**: Implement a sorting function using a lambda expression.
   - [Codewars Problem](https://www.codewars.com/kata/sort-the-odd/train/cpp)

4. **Smart Pointers**: Create a class that uses smart pointers to manage its resources.
   - [GeeksforGeeks Problem](https://www.geeksforgeeks.org/smart-pointers-in-c/)

5. **Concurrency**: Write a program that spawns multiple threads to perform a task concurrently.
   - [LeetCode Problem](https://leetcode.com/problems/print-in-order/)

6. **Regular Expressions**: Validate an email address using regular expressions.
   - [HackerRank Problem](https://www.hackerrank.com/challenges/validating-email-addresses-with-a-filter/problem)

These exercises will help reinforce your understanding of modern C++ features and their applications.