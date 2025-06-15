# Chapter 5: Pointers and Memory Management (Part 2)

## 5.5 Dynamic Memory Allocation (new, delete)

Dynamic memory allocation allows you to request and release memory during program execution rather than at compile time. This flexibility is essential when you need to create data structures whose size is determined at runtime.

### The Stack vs. The Heap

Before diving into dynamic memory allocation, it's important to understand the two main memory regions in C++:

1. **Stack**:
   - Automatically managed memory
   - Fast allocation and deallocation (simple pointer increment/decrement)
   - Limited in size (typically a few MB)
   - Stores local variables, function parameters, and return addresses
   - Memory is freed automatically when variables go out of scope
   - LIFO (Last In, First Out) structure

2. **Heap** (Free Store):
   - Manually managed memory in traditional C++
   - Slower allocation/deallocation compared to stack
   - Limited only by available virtual memory
   - Stores dynamically allocated objects
   - Must be explicitly freed to prevent memory leaks
   - No inherent structure (allocations/deallocations can happen in any order)

### Basic Dynamic Memory Allocation

In C++, you use the `new` operator to allocate memory on the heap and the `delete` operator to free that memory:

```cpp
#include <iostream>
using namespace std;

int main() {
    // Allocating a single integer
    int* ptr = new int;  // Allocates memory for an int and returns its address
    
    // Initializing the allocated memory
    *ptr = 42;
    cout << "Value: " << *ptr << endl;
    
    // Freeing the memory when done
    delete ptr;  // Returns memory to the system
    
    // After deletion, ptr is a dangling pointer
    // Best practice: set to nullptr
    ptr = nullptr;
    
    return 0;
}
```

### Allocation with Initialization

You can initialize memory as you allocate it:

```cpp
#include <iostream>
using namespace std;

int main() {
    // Allocate and initialize an integer
    int* p1 = new int(42);  // Direct initialization
    cout << "p1 value: " << *p1 << endl;
    
    // C++11 uniform initialization
    double* p2 = new double{3.14159};
    cout << "p2 value: " << *p2 << endl;
    
    // Clean up
    delete p1;
    delete p2;
    
    return 0;
}
```

### Dynamic Arrays

To allocate arrays dynamically, use the array form of `new` and `delete`:

```cpp
#include <iostream>
using namespace std;

int main() {
    // Get size at runtime
    int size;
    cout << "Enter array size: ";
    cin >> size;
    
    // Allocate an array of the specified size
    int* array = new int[size];
    
    // Initialize the array
    for (int i = 0; i < size; i++) {
        array[i] = i * 10;
    }
    
    // Display the array
    cout << "Array values: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    
    // Free the array memory with array delete
    delete[] array;  // IMPORTANT: Use delete[] for arrays, not delete
    
    return 0;
}
```

### Allocation Failure Handling

By default, `new` throws a `std::bad_alloc` exception if memory allocation fails. You can use the `nothrow` version to get a null pointer instead:

```cpp
#include <iostream>
#include <new>  // For std::nothrow
using namespace std;

int main() {
    // Default behavior: throws exception on failure
    try {
        int* ptr = new int[1000000000000];  // Very large allocation likely to fail
        // If we get here, allocation succeeded
        delete[] ptr;
    } catch (const bad_alloc& e) {
        cout << "Memory allocation failed: " << e.what() << endl;
    }
    
    // Alternative: nothrow version
    int* ptr = new (nothrow) int[1000000000000];
    
    if (ptr == nullptr) {
        cout << "Memory allocation failed with nothrow" << endl;
    } else {
        cout << "Allocation succeeded" << endl;
        delete[] ptr;
    }
    
    return 0;
}
```

### Dynamic Allocation of Objects

When you use `new` with classes, the constructor is automatically called, and `delete` calls the destructor:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    Person(const string& n, int a) : name(n), age(a) {
        cout << "Constructing " << name << endl;
    }
    
    ~Person() {
        cout << "Destructing " << name << endl;
    }
    
    void display() {
        cout << name << " is " << age << " years old" << endl;
    }
};

int main() {
    // Allocate a single object
    Person* p1 = new Person("Alice", 30);
    p1->display();
    
    // Allocate an array of objects
    Person* group = new Person[3] {
        {"Bob", 25},
        {"Charlie", 32},
        {"Diana", 28}
    };
    
    // Access array objects
    for (int i = 0; i < 3; i++) {
        group[i].display();
    }
    
    // Clean up
    delete p1;           // Calls destructor for a single object
    delete[] group;      // Calls destructor for each array element
    
    return 0;
}
```

### Placement new

Placement new allows you to construct an object at a specific, pre-allocated memory address:

```cpp
#include <iostream>
#include <new>  // For placement new
using namespace std;

class Complex {
public:
    double real;
    double imag;
    
    Complex(double r, double i) : real(r), imag(i) {
        cout << "Complex constructed at " << this << endl;
    }
    
    ~Complex() {
        cout << "Complex destructed at " << this << endl;
    }
};

int main() {
    // Allocate raw memory (no constructor called)
    char* memory = new char[sizeof(Complex)];
    
    // Construct object at the allocated memory
    Complex* obj = new (memory) Complex(3.0, 4.0);
    
    cout << "Real: " << obj->real << ", Imaginary: " << obj->imag << endl;
    
    // Must explicitly call destructor (placement new doesn't register with delete)
    obj->~Complex();
    
    // Free the raw memory
    delete[] memory;
    
    return 0;
}
```

### Common Mistakes and Pitfalls

1. **Memory Leaks**: Forgetting to `delete` what you `new`

```cpp
void leakMemory() {
    int* ptr = new int(42);
    // No delete before function returns - memory leaked!
}
```

2. **Double Deletion**: Deleting the same memory twice

```cpp
int* ptr = new int(42);
delete ptr;
// ... some code ...
delete ptr;  // ERROR: Double free, undefined behavior
```

3. **Using Deleted Memory**: Accessing memory after it's been freed

```cpp
int* ptr = new int(42);
delete ptr;
*ptr = 100;  // ERROR: Accessing freed memory
```

4. **Mismatched new/delete**: Using wrong form of delete

```cpp
int* single = new int;
int* array = new int[10];

delete[] single;  // ERROR: Using array delete for single object
delete array;     // ERROR: Using single delete for array
```

### Advanced: Custom Memory Allocators

For performance-critical applications, you can create custom allocators:

```cpp
#include <iostream>
using namespace std;

class PoolAllocator {
private:
    char* memory_pool;
    size_t used;
    size_t capacity;

public:
    PoolAllocator(size_t size) : capacity(size), used(0) {
        memory_pool = new char[size];
    }
    
    ~PoolAllocator() {
        delete[] memory_pool;
    }
    
    void* allocate(size_t size) {
        if (used + size > capacity) {
            return nullptr;  // Not enough space
        }
        
        void* result = memory_pool + used;
        used += size;
        return result;
    }
    
    // Simple allocator doesn't support individual deallocation
};

int main() {
    // Create a 1KB memory pool
    PoolAllocator pool(1024);
    
    // Allocate some integers from the pool
    int* a = static_cast<int*>(pool.allocate(sizeof(int)));
    int* b = static_cast<int*>(pool.allocate(sizeof(int)));
    
    *a = 42;
    *b = 100;
    
    cout << "a: " << *a << endl;
    cout << "b: " << *b << endl;
    
    // No need to delete individual allocations
    // Pool is freed when it goes out of scope
    
    return 0;
}
```

### Best Practices

1. **Always match `new` with `delete`, and `new[]` with `delete[]`**

2. **Set pointers to `nullptr` after deleting them**
   ```cpp
   delete ptr;
   ptr = nullptr;  // Prevents accidental use after delete
   ```

3. **Check for allocation failure with `nothrow`**
   ```cpp
   int* ptr = new(nothrow) int[1000000];
   if (!ptr) {
       // Handle allocation failure
   }
   ```

4. **Prefer stack allocation when possible**
   ```cpp
   // Better (stack allocation)
   int values[10];
   
   // Worse (heap allocation, manual management)
   int* values = new int[10];
   // ... use values ...
   delete[] values;
   ```

5. **Use containers and smart pointers for dynamic memory management** (covered later)
   ```cpp
   #include <vector>
   vector<int> values(10);  // Dynamic array with automatic memory management
   ```

## 5.6 Dangling Pointers and Memory Leaks

Memory management errors are among the most common and problematic bugs in C++. Two particularly significant issues are dangling pointers and memory leaks.

### Dangling Pointers

A dangling pointer is a pointer that references a memory location that is no longer valid, typically because the memory has been freed or gone out of scope.

#### Common Causes of Dangling Pointers

1. **Using a Pointer After Deletion**

```cpp
#include <iostream>
using namespace std;

int main() {
    int* ptr = new int(42);
    delete ptr;
    
    // Danger! ptr is now dangling
    *ptr = 100;  // Undefined behavior
    cout << *ptr << endl;  // Undefined behavior
    
    return 0;
}
```

2. **Returning Address of Local Variables**

```cpp
#include <iostream>
using namespace std;

int* createDanglingPointer() {
    int local = 42;  // Local variable on stack
    return &local;   // DANGER: Returns address of local variable
}

int main() {
    int* ptr = createDanglingPointer();
    // ptr is dangling - points to memory that was on the stack
    // and is no longer valid
    cout << *ptr << endl;  // Undefined behavior
    
    return 0;
}
```

3. **Pointers to Freed Memory in Data Structures**

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int d) : data(d), next(nullptr) {}
};

int main() {
    Node* head = new Node(1);
    Node* second = new Node(2);
    head->next = second;
    
    // Delete the second node
    delete second;
    
    // head->next is now dangling
    cout << head->next->data << endl;  // DANGER: Undefined behavior
    
    delete head;
    return 0;
}
```

### Detecting and Preventing Dangling Pointers

1. **Set Pointers to nullptr After Deletion**

```cpp
#include <iostream>
using namespace std;

int main() {
    int* ptr = new int(42);
    
    // Use the pointer
    cout << "Value: " << *ptr << endl;
    
    // Clean up and nullify
    delete ptr;
    ptr = nullptr;
    
    // Safe check before use
    if (ptr != nullptr) {
        cout << *ptr << endl;
    } else {
        cout << "Pointer is null" << endl;
    }
    
    return 0;
}
```

2. **Handle Owner Responsibility Clearly**

```cpp
#include <iostream>
using namespace std;

class ResourceManager {
private:
    int* resource;

public:
    ResourceManager() : resource(new int(42)) {}
    
    ~ResourceManager() {
        delete resource;
        resource = nullptr;
    }
    
    // Prevent copying to avoid multiple owners
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    int getValue() const { return *resource; }
};

int main() {
    ResourceManager manager;
    cout << "Value: " << manager.getValue() << endl;
    
    // Resource automatically freed when manager goes out of scope
    return 0;
}
```

3. **Use Defensive Programming with External APIs**

```cpp
#include <iostream>
using namespace std;

// Simulated external API function that might free a pointer
void externalFunction(int* ptr) {
    // Might delete ptr internally
    delete ptr;
}

int main() {
    int* ptr = new int(42);
    
    // Call to external function that might delete ptr
    externalFunction(ptr);
    
    // Defensive check (imperfect but better than nothing)
    // Note: This doesn't guarantee safety, as ptr might point to reallocated memory
    if (ptr != nullptr) {
        cout << "Assuming pointer is still valid: " << *ptr << endl;
    }
    
    // Better approach: Don't use ptr after the external call
    ptr = nullptr;  // Explicitly indicate we no longer own it
    
    return 0;
}
```

### Memory Leaks

A memory leak occurs when dynamically allocated memory is not freed, causing the program to gradually consume more and more memory, potentially leading to degraded performance or crashes.

#### Common Causes of Memory Leaks

1. **Forgetting to Delete Allocated Memory**

```cpp
#include <iostream>
using namespace std;

void leakMemory() {
    int* ptr = new int(42);
    // Function ends without deleting ptr
    // The memory at ptr is now leaked
}

int main() {
    for (int i = 0; i < 1000; i++) {
        leakMemory();  // Leaks 1000 integers worth of memory
    }
    
    cout << "Program continues with leaked memory" << endl;
    
    return 0;
}
```

2. **Losing the Pointer Before Deletion**

```cpp
#include <iostream>
using namespace std;

int main() {
    int* ptr = new int(42);
    ptr = new int(100);  // Original memory is leaked
    
    delete ptr;  // Only frees the second allocation
    
    return 0;
}
```

3. **Memory Leaks in Exception Scenarios**

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

void processData() {
    int* data = new int[1000];
    
    // If this throws, data won't be deleted
    if (rand() % 2 == 0) {
        throw runtime_error("Random error occurred");
    }
    
    // Normal cleanup path
    delete[] data;
}

int main() {
    try {
        processData();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
        // Memory is leaked here
    }
    
    return 0;
}
```

4. **Circular References in Data Structures**

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int d) : data(d), next(nullptr) {}
};

void createCycle() {
    Node* first = new Node(1);
    Node* second = new Node(2);
    
    first->next = second;
    second->next = first;  // Creates a cycle
    
    // No way to delete all nodes from here
    // Both nodes are leaked
}

int main() {
    createCycle();
    
    cout << "Program continues with leaked memory" << endl;
    
    return 0;
}
```

### Detecting and Preventing Memory Leaks

1. **Always Delete What You Allocate**

```cpp
#include <iostream>
using namespace std;

int main() {
    // Proper memory management
    int* ptr = new int(42);
    
    // Use the pointer...
    cout << "Value: " << *ptr << endl;
    
    // Clean up
    delete ptr;
    ptr = nullptr;
    
    return 0;
}
```

2. **Use RAII (Resource Acquisition Is Initialization)**

```cpp
#include <iostream>
#include <fstream>
using namespace std;

class IntArray {
private:
    int* data;
    size_t size;
    
public:
    IntArray(size_t s) : size(s) {
        data = new int[size];
        cout << "Allocated array of size " << size << endl;
    }
    
    ~IntArray() {
        delete[] data;
        cout << "Freed array of size " << size << endl;
        data = nullptr;
    }
    
    // Disable copying to prevent double deletion
    IntArray(const IntArray&) = delete;
    IntArray& operator=(const IntArray&) = delete;
    
    int& operator[](size_t index) {
        return data[index];
    }
};

void processData() {
    IntArray arr(10);  // Resource acquisition
    
    // Use the array
    arr[0] = 42;
    
    // No need to manually free memory
    // arr's destructor will be called automatically when it goes out of scope
}

int main() {
    processData();
    cout << "Function completed with no leaks" << endl;
    
    return 0;
}
```

3. **Exception-Safe Resource Management**

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class DataProcessor {
private:
    int* buffer;

public:
    DataProcessor(size_t size) : buffer(new int[size]) {
        cout << "Buffer allocated" << endl;
    }
    
    ~DataProcessor() {
        cout << "Buffer deallocated" << endl;
        delete[] buffer;
    }
    
    void process() {
        // Potentially throws an exception
        if (rand() % 2 == 0) {
            throw runtime_error("Processing error");
        }
        
        cout << "Processing completed successfully" << endl;
    }
};

int main() {
    try {
        DataProcessor processor(1000);
        processor.process();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    cout << "Program continues with no memory leaks" << endl;
    
    return 0;
}
```

### Tools for Detecting Memory Issues

1. **Valgrind** - A powerful tool for memory debugging, detecting leaks, and profiling
   ```bash
   # Compile with debugging information
   g++ -g program.cpp -o program
   
   # Run with Valgrind
   valgrind --leak-check=full ./program
   ```

2. **Address Sanitizer** - Part of Clang/GCC compilers
   ```bash
   # Compile with AddressSanitizer
   g++ -fsanitize=address -g program.cpp -o program
   
   # Run normally, leaks will be reported
   ./program
   ```

3. **Static Analysis Tools**
   - CppCheck
   - Clang Static Analyzer
   - PVS-Studio

4. **Custom Leak Detection** - For specific scenarios

```cpp
#include <iostream>
#include <map>
using namespace std;

// Simple memory leak detector
class LeakDetector {
private:
    static map<void*, size_t> allocations;
    
public:
    static void* allocate(size_t size) {
        void* ptr = malloc(size);
        allocations[ptr] = size;
        return ptr;
    }
    
    static void deallocate(void* ptr) {
        auto it = allocations.find(ptr);
        if (it != allocations.end()) {
            allocations.erase(it);
            free(ptr);
        }
    }
    
    static void reportLeaks() {
        if (allocations.empty()) {
            cout << "No memory leaks detected" << endl;
            return;
        }
        
        cout << "Memory leaks detected:" << endl;
        size_t total = 0;
        for (const auto& pair : allocations) {
            cout << "  Address " << pair.first << ": " << pair.second << " bytes" << endl;
            total += pair.second;
        }
        cout << "Total leaked: " << total << " bytes" << endl;
    }
};

map<void*, size_t> LeakDetector::allocations;

// Override global new/delete
void* operator new(size_t size) {
    return LeakDetector::allocate(size);
}

void operator delete(void* ptr) noexcept {
    LeakDetector::deallocate(ptr);
}

int main() {
    int* p1 = new int(42);
    int* p2 = new int(100);
    
    // Deliberately leak p1
    delete p2;
    
    LeakDetector::reportLeaks();
    
    return 0;
}
```

## 5.7 Smart Pointers (unique_ptr, shared_ptr, weak_ptr)

Smart pointers are class templates that provide automatic memory management for dynamically allocated objects. They ensure proper deletion of objects when they are no longer needed, helping to prevent memory leaks and other memory-related problems.

### Types of Smart Pointers

Modern C++ provides three main types of smart pointers in the `<memory>` header:

1. **`std::unique_ptr`** - Exclusive ownership model
2. **`std::shared_ptr`** - Shared ownership model
3. **`std::weak_ptr`** - Non-owning reference to a `shared_ptr`

### std::unique_ptr

`std::unique_ptr` implements exclusive ownership of a dynamically allocated object. Only one `unique_ptr` can own the object at any time, and when that `unique_ptr` is destroyed or reassigned, the object is automatically deleted.

#### Basic Usage

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource(int id) : id_(id) {
        cout << "Resource " << id_ << " constructed" << endl;
    }
    
    ~Resource() {
        cout << "Resource " << id_ << " destroyed" << endl;
    }
    
    void use() {
        cout << "Using resource " << id_ << endl;
    }
    
private:
    int id_;
};

int main() {
    // Create a unique_ptr
    unique_ptr<Resource> res1(new Resource(1));
    
    // Use the resource
    res1->use();
    
    // Automatic cleanup when res1 goes out of scope
    
    return 0;
}
```

#### Creating with make_unique (C++14)

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // C++14 way: Preferred for exception safety and efficiency
    unique_ptr<Resource> res = make_unique<Resource>(1);
    
    // Pre-C++14 way
    unique_ptr<Resource> res2(new Resource(2));
    
    return 0;
}
```

#### Moving Ownership

`unique_ptr` can't be copied, but ownership can be transferred using `std::move`:

```cpp
#include <iostream>
#include <memory>
#include <utility>  // For std::move
using namespace std;

int main() {
    unique_ptr<Resource> res1 = make_unique<Resource>(1);
    
    // Transfer ownership
    unique_ptr<Resource> res2 = move(res1);
    
    // res1 is now empty (null)
    if (res1 == nullptr) {
        cout << "res1 is null after move" << endl;
    }
    
    // res2 now owns the resource
    res2->use();
    
    return 0;
}
```

#### Array Support

`unique_ptr` supports arrays with a specialized version:

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // Array of integers
    unique_ptr<int[]> numbers = make_unique<int[]>(5);
    
    // Initialize array
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }
    
    // Access elements
    for (int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    // Automatically deletes the array when numbers goes out of scope
    
    return 0;
}
```

#### Custom Deleters

You can specify custom cleanup operations:

```cpp
#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

int main() {
    // Custom deleter for FILE*
    auto fileDeleter = [](FILE* file) {
        cout << "Closing file..." << endl;
        if (file) {
            fclose(file);
        }
    };
    
    // Open a file
    FILE* rawFile = fopen("example.txt", "w");
    if (!rawFile) {
        cerr << "Could not open file" << endl;
        return 1;
    }
    
    // Create unique_ptr with custom deleter
    unique_ptr<FILE, decltype(fileDeleter)> file(rawFile, fileDeleter);
    
    // Use the file
    fprintf(file.get(), "Hello, Smart Pointers!");
    
    // File automatically closed when file goes out of scope
    
    return 0;
}
```

### std::shared_ptr

`std::shared_ptr` implements shared ownership of a dynamically allocated object. Multiple `shared_ptr` instances can own the same object, and the object is deleted only when the last owning `shared_ptr` is destroyed or reassigned.

#### Basic Usage

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource(int id) : id_(id) {
        cout << "Resource " << id_ << " constructed" << endl;
    }
    
    ~Resource() {
        cout << "Resource " << id_ << " destroyed" << endl;
    }
    
    void use() {
        cout << "Using resource " << id_ << endl;
    }
    
private:
    int id_;
};

int main() {
    // Create a shared_ptr
    shared_ptr<Resource> res1 = make_shared<Resource>(1);
    
    // Create another shared_ptr pointing to the same resource
    shared_ptr<Resource> res2 = res1;
    
    cout << "Resource count: " << res1.use_count() << endl;  // 2
    
    // Both can use the resource
    res1->use();
    res2->use();
    
    // Resource deleted when both res1 and res2 go out of scope
    
    return 0;
}
```

#### Creating with make_shared

`make_shared` is more efficient than using the constructor with `new` because it allocates memory for both the object and the control block in a single operation:

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // Efficient way: One allocation for object and control block
    shared_ptr<Resource> res1 = make_shared<Resource>(1);
    
    // Less efficient way: Separate allocations
    shared_ptr<Resource> res2(new Resource(2));
    
    return 0;
}
```

#### Sharing and Use Count

Each `shared_ptr` internally maintains a reference count:

```cpp
#include <iostream>
#include <memory>
using namespace std;

void useResource(shared_ptr<Resource> res) {
    cout << "In function, count: " << res.use_count() << endl;
    res->use();
    // res is destroyed when function exits, decreasing count
}

int main() {
    shared_ptr<Resource> res = make_shared<Resource>(1);
    cout << "Initial count: " << res.use_count() << endl;  // 1
    
    {
        shared_ptr<Resource> res2 = res;
        cout << "Block scope count: " << res.use_count() << endl;  // 2
    }
    
    cout << "After block scope: " << res.use_count() << endl;  // 1
    
    useResource(res);  // Temporarily increases count
    
    cout << "After function: " << res.use_count() << endl;  // 1
    
    return 0;
}
```

#### Custom Deleters

Similar to `unique_ptr`, `shared_ptr` supports custom deleters:

```cpp
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

class Socket {
public:
    Socket(int handle) : handle_(handle) {
        cout << "Socket " << handle_ << " opened" << endl;
    }
    
    int getHandle() const { return handle_; }
    
private:
    int handle_;
};

void closeSocket(Socket* socket) {
    cout << "Socket " << socket->getHandle() << " closed" << endl;
    delete socket;
}

int main() {
    // Socket with custom deleter
    shared_ptr<Socket> socket(new Socket(12345), closeSocket);
    
    cout << "Using socket " << socket->getHandle() << endl;
    
    // Socket automatically closed when socket ptr goes out of scope
    
    return 0;
}
```

### std::weak_ptr

`std::weak_ptr` provides a non-owning reference to an object managed by a `shared_ptr`. It doesn't affect the reference count, and it can't access the object directly without being converted to a `shared_ptr` first.

#### Breaking Circular References

The primary use of `weak_ptr` is to break circular references that would otherwise cause memory leaks with `shared_ptr`:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Node;
using NodePtr = shared_ptr<Node>;
using WeakNodePtr = weak_ptr<Node>;

class Node {
public:
    NodePtr next;
    WeakNodePtr prev;  // Using weak_ptr to avoid circular reference
    
    int data;
    
    Node(int d) : data(d) {
        cout << "Node " << d << " created" << endl;
    }
    
    ~Node() {
        cout << "Node " << data << " destroyed" << endl;
    }
};

int main() {
    // Create nodes
    NodePtr node1 = make_shared<Node>(1);
    NodePtr node2 = make_shared<Node>(2);
    
    // Create circular reference
    node1->next = node2;
    node2->prev = node1;  // Weak reference doesn't increase count
    
    cout << "Node1 use count: " << node1.use_count() << endl;  // 1
    cout << "Node2 use count: " << node2.use_count() << endl;  // 2 (node1->next and node2)
    
    // Check if weak_ptr is still valid
    if (auto p = node2->prev.lock()) {
        cout << "Node2->prev points to node with data: " << p->data << endl;
    }
    
    // When we go out of scope, all nodes are properly deleted
    // If we had used shared_ptr for prev, nodes would never be deleted
    
    return 0;
}
```

#### Using weak_ptr

`weak_ptr` can't be directly dereferenced; you must first convert it to a `shared_ptr` using the `lock()` method:

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // Create a shared_ptr
    shared_ptr<int> shared = make_shared<int>(42);
    
    // Create a weak_ptr from it
    weak_ptr<int> weak = shared;
    
    cout << "shared count: " << shared.use_count() << endl;  // 1
    
    // Convert weak_ptr to shared_ptr to use it
    if (auto locked = weak.lock()) {
        cout << "Value: " << *locked << endl;
        cout << "shared count during access: " << shared.use_count() << endl;  // 2
    } else {
        cout << "Original object no longer exists" << endl;
    }
    
    // Reset the original shared_ptr
    shared.reset();
    
    // Try to access again
    if (auto locked = weak.lock()) {
        cout << "Value is still available" << endl;
    } else {
        cout << "Original object has been deleted" << endl;
    }
    
    return 0;
}
```

#### Checking Expiration

You can check if a `weak_ptr` refers to an object that still exists without converting it to a `shared_ptr`:

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    weak_ptr<int> weak;
    
    {
        shared_ptr<int> shared = make_shared<int>(42);
        weak = shared;
        
        cout << "weak.expired(): " << weak.expired() << endl;  // 0 (false)
    }
    
    // After the shared_ptr is destroyed
    cout << "weak.expired(): " << weak.expired() << endl;  // 1 (true)
    
    return 0;
}
```

### Choosing the Right Smart Pointer

1. **Use `unique_ptr` when:**
   - You need exclusive ownership (only one owner)
   - You want to transfer ownership (via `std::move`)
   - You need custom deleters but don't want reference counting overhead
   - For resource management within a single scope or class

2. **Use `shared_ptr` when:**
   - Ownership is shared among multiple objects
   - You don't know which owner will last longest
   - You need shared resources to be cleaned up only when all users are done

3. **Use `weak_ptr` when:**
   - You need a non-owning reference to a resource managed by `shared_ptr`
   - To break circular references between `shared_ptr`s
   - When you need to track if an object still exists without affecting its lifetime

4. **Don't use smart pointers when:**
   - Managing non-heap resources (use RAII wrappers instead)
   - Working with C-style APIs that expect raw pointers (use `.get()` method)
   - The overhead would be unacceptable (very rare in practice)

### Smart Pointer Best Practices

1. **Prefer `make_unique` and `make_shared` over direct constructor use**
   ```cpp
   // Good
   auto ptr = make_unique<Resource>(args);
   
   // Less optimal
   unique_ptr<Resource> ptr(new Resource(args));
   ```

2. **Don't mix raw and smart pointers for ownership**
   ```cpp
   Resource* raw = new Resource();
   shared_ptr<Resource> smart(raw);
   delete raw;  // DANGER: Double deletion
   ```

3. **Use appropriate access patterns**
   ```cpp
   // For unique_ptr or shared_ptr
   resource->method();
   
   // For weak_ptr
   if (auto locked = weak.lock()) {
       locked->method();
   }
   ```

4. **Pass by reference when you don't want to transfer or share ownership**
   ```cpp
   void useResource(const Resource& resource) {
       // Function doesn't participate in ownership
   }
   ```

5. **Consider `const` smart pointers for read-only access**
   ```cpp
   const shared_ptr<Resource> ptr = make_shared<Resource>();
   // ptr.reset() is not allowed
   ```

## 5.8 RAII and Scope-Based Resource Management

RAII (Resource Acquisition Is Initialization) is a programming idiom that ensures proper management of resources by tying their lifetimes to the lifetime of objects. It's one of the most important idioms in C++ and forms the basis for many C++ standard library components.

### The RAII Principle

The core idea of RAII is:

1. Encapsulate each resource in a class
2. Acquire the resource in the constructor
3. Release the resource in the destructor
4. Use instances of the class to manage the resource

This ensures that resources are automatically cleaned up when objects go out of scope, even in the presence of exceptions or early returns.

### Basic RAII Example

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler {
private:
    ofstream file;
    string filename;

public:
    FileHandler(const string& fname) : filename(fname) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }
        cout << "File opened: " << filename << endl;
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
            cout << "File closed: " << filename << endl;
        }
    }
    
    void write(const string& data) {
        if (!file.is_open()) {
            throw runtime_error("File not open");
        }
        file << data << endl;
    }
};

void processFile(const string& filename) {
    try {
        FileHandler handler(filename);
        handler.write("Line 1");
        handler.write("Line 2");
        
        // File is automatically closed when handler goes out of scope,
        // even if an exception is thrown
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    processFile("example.txt");
    return 0;
}
```

### Benefits of RAII

1. **Automatic Resource Management**
   - No need to manually track resource cleanup
   - Resources are released in the reverse order of acquisition

2. **Exception Safety**
   - Resources are properly cleaned up even if exceptions occur
   - No resource leaks in error paths

3. **Clear Ownership Semantics**
   - The object that owns a resource is responsible for its cleanup
   - Avoids ambiguity about who should clean up

### RAII for Different Resource Types

#### Memory Management

Smart pointers are the primary RAII mechanism for memory:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource() { cout << "Resource acquired" << endl; }
    ~Resource() { cout << "Resource released" << endl; }
    void use() { cout << "Resource used" << endl; }
};

void useResource() {
    unique_ptr<Resource> res = make_unique<Resource>();
    res->use();
    
    // Memory automatically freed when res goes out of scope
}

int main() {
    cout << "Entering function" << endl;
    useResource();
    cout << "Function complete" << endl;
    
    return 0;
}
```

#### File Handling

The standard library's file streams implement RAII:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

void writeToFile(const string& filename, const string& data) {
    ofstream file(filename);  // Opens file
    
    if (file.is_open()) {
        file << data << endl;
    }
    
    // File automatically closed when file goes out of scope
}

int main() {
    writeToFile("example.txt", "Hello, RAII!");
    cout << "File operation complete" << endl;
    
    return 0;
}
```

#### Mutex Locking

RAII for thread synchronization with `std::lock_guard`:

```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

class ThreadSafeCounter {
private:
    mutex mtx;
    int counter = 0;

public:
    void increment() {
        lock_guard<mutex> lock(mtx);  // RAII lock
        counter++;
        // lock automatically released when lock_guard goes out of scope
    }
    
    int getValue() {
        lock_guard<mutex> lock(mtx);  // RAII lock
        return counter;
    }
};

void incrementTask(ThreadSafeCounter& counter, int times) {
    for (int i = 0; i < times; i++) {
        counter.increment();
    }
}

int main() {
    ThreadSafeCounter counter;
    
    vector<thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(thread(incrementTask, ref(counter), 1000));
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "Final counter value: " << counter.getValue() << endl;
    
    return 0;
}
```

#### Database Connections

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

// Mock database connection
class DBConnection {
public:
    DBConnection(const string& connString) {
        cout << "Opening database connection to " << connString << endl;
        // Imagine real connection logic here
        if (connString.empty()) {
            throw runtime_error("Invalid connection string");
        }
    }
    
    ~DBConnection() {
        cout << "Closing database connection" << endl;
    }
    
    void executeQuery(const string& query) {
        cout << "Executing query: " << query << endl;
    }
};

// RAII wrapper
class DBTransaction {
private:
    DBConnection& conn;
    bool committed = false;

public:
    DBTransaction(DBConnection& connection) : conn(connection) {
        cout << "Beginning transaction" << endl;
    }
    
    void commit() {
        cout << "Committing transaction" << endl;
        committed = true;
    }
    
    ~DBTransaction() {
        if (!committed) {
            cout << "Rolling back uncomitted transaction" << endl;
        }
    }
};

void performDatabaseOperation(const string& connString) {
    DBConnection connection(connString);
    
    try {
        DBTransaction transaction(connection);
        
        connection.executeQuery("SELECT * FROM users");
        connection.executeQuery("UPDATE users SET active = true");
        
        transaction.commit();
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        // Transaction automatically rolled back
        // Connection automatically closed
    }
    
    // Connection automatically closed when it goes out of scope
}

int main() {
    try {
        performDatabaseOperation("server=localhost;db=test");
    } catch (const exception& e) {
        cerr << "Database operation failed: " << e.what() << endl;
    }
    
    return 0;
}
```

### Creating Custom RAII Classes

To create your own RAII wrappers:

```cpp
#include <iostream>
using namespace std;

// Example of a custom resource
struct RawResource {
    void* data;
    
    static RawResource* create() {
        cout << "Creating raw resource" << endl;
        return new RawResource{malloc(1024)};
    }
    
    static void destroy(RawResource* res) {
        cout << "Destroying raw resource" << endl;
        free(res->data);
        delete res;
    }
};

// RAII wrapper
class ManagedResource {
private:
    RawResource* resource;

public:
    ManagedResource() : resource(RawResource::create()) {}
    
    ~ManagedResource() {
        RawResource::destroy(resource);
    }
    
    // Disable copying
    ManagedResource(const ManagedResource&) = delete;
    ManagedResource& operator=(const ManagedResource&) = delete;
    
    // Enable moving
    ManagedResource(ManagedResource&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
    }
    
    ManagedResource& operator=(ManagedResource&& other) noexcept {
        if (this != &other) {
            if (resource) {
                RawResource::destroy(resource);
            }
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
    
    void* getData() const {
        return resource ? resource->data : nullptr;
    }
};

void useResource() {
    ManagedResource res;  // Resource created
    
    // Use the resource
    void* data = res.getData();
    cout << "Resource address: " << data << endl;
    
    // Resource automatically cleaned up when res goes out of scope
}

int main() {
    useResource();
    cout << "Function completed" << endl;
    
    return 0;
}
```

### RAII and the Rule of Three/Five/Zero

The "Rule of Three" (expanded to "Rule of Five" in C++11, and "Rule of Zero" as a modern alternative) is closely related to RAII:

1. **Rule of Three**: If a class requires a custom destructor, copy constructor, or copy assignment operator, it probably needs all three.
2. **Rule of Five**: In C++11 and later, adds move constructor and move assignment operator to the list.
3. **Rule of Zero**: Design classes to avoid the need for custom resource management, delegating it to member objects.

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Rule of Five example
class Buffer {
private:
    size_t size;
    unsigned char* data;

public:
    // Constructor
    Buffer(size_t size) : size(size), data(new unsigned char[size]) {
        cout << "Constructing buffer of size " << size << endl;
        fill(data, data + size, 0);
    }
    
    // Destructor
    ~Buffer() {
        cout << "Destroying buffer of size " << size << endl;
        delete[] data;
    }
    
    // Copy constructor
    Buffer(const Buffer& other) : size(other.size), data(new unsigned char[other.size]) {
        cout << "Copy constructing buffer" << endl;
        memcpy(data, other.data, size);
    }
    
    // Copy assignment operator
    Buffer& operator=(const Buffer& other) {
        cout << "Copy assigning buffer" << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new unsigned char[size];
            memcpy(data, other.data, size);
        }
        return *this;
    }
    
    // Move constructor
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        cout << "Move constructing buffer" << endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment operator
    Buffer& operator=(Buffer&& other) noexcept {
        cout << "Move assigning buffer" << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // Access methods
    size_t getSize() const { return size; }
    unsigned char* getData() { return data; }
};

// Rule of Zero example
class Document {
private:
    string title;
    unique_ptr<Buffer> content;  // Uses smart pointer for RAII

public:
    Document(string title, size_t size) 
        : title(move(title)), content(make_unique<Buffer>(size)) {}
    
    // No explicit destructor, copy/move constructors or assignment operators needed
    // The default ones will handle the resources properly
};

int main() {
    // Test Rule of Five
    Buffer b1(100);
    Buffer b2 = b1;  // Copy constructor
    Buffer b3(200);
    b3 = b1;         // Copy assignment
    
    Buffer b4 = move(b2);  // Move constructor
    b3 = move(b4);         // Move assignment
    
    // Test Rule of Zero
    Document doc("Report", 1024);
    
    return 0;
}
```

### Advanced RAII Techniques

#### Scope Guards

Scope guards execute actions at scope exit, even when exceptions occur:

```cpp
#include <iostream>
#include <functional>
using namespace std;

class ScopeGuard {
private:
    function<void()> action;
    bool dismissed = false;

public:
    explicit ScopeGuard(function<void()> action) : action(move(action)) {}
    
    ~ScopeGuard() {
        if (!dismissed) {
            action();
        }
    }
    
    void dismiss() {
        dismissed = true;
    }
    
    // Prevent copying and moving
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;
};

void someFunctionWithCleanup() {
    cout << "Allocating temporary resources..." << endl;
    
    // Setup cleanup
    ScopeGuard cleanup([]() {
        cout << "Cleanup action executed!" << endl;
    });
    
    cout << "Working with resources..." << endl;
    
    // Simulate potential exit points
    int choice = rand() % 3;
    
    if (choice == 0) {
        cout << "Early return, cleanup will still happen" << endl;
        return;  // Early return
    }
    else if (choice == 1) {
        cout << "Exception thrown, cleanup will still happen" << endl;
        throw runtime_error("Something went wrong");  // Exception
    }
    
    cout << "Function completed normally" << endl;
    // Optional: dismiss the guard if you don't want the action to run
    // cleanup.dismiss();
}

int main() {
    try {
        someFunctionWithCleanup();
    } catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
    
    return 0;
}
```

#### Deferred Actions with Destructors

```cpp
#include <iostream>
#include <string>
using namespace std;

class Timer {
private:
    string name;
    clock_t start;

public:
    Timer(const string& operationName) 
        : name(operationName), start(clock()) {
        cout << "Starting operation: " << name << endl;
    }
    
    ~Timer() {
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "Operation " << name << " took " << elapsed << " seconds" << endl;
    }
};

void performSlowOperation() {
    Timer t("SlowOperation");
    
    // Simulate work
    for (int i = 0; i < 100000000; i++) {
        int x = i * i;
        (void)x;  // Prevent optimization
    }
    
    // Timer automatically reports duration on function exit
}

int main() {
    performSlowOperation();
    return 0;
}
```

### RAII and Concurrency

RAII is particularly valuable in concurrent code:

```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

class SharedResource {
private:
    mutex resourceMutex;
    vector<int> data;

public:
    void addData(int value) {
        // lock_guard is an RAII wrapper for mutex
        lock_guard<mutex> lock(resourceMutex);
        
        cout << "Thread " << this_thread::get_id() 
             << " adding value: " << value << endl;
        data.push_back(value);
        
        // mutex automatically unlocked when lock goes out of scope
    }
    
    void processData() {
        // unique_lock is more flexible than lock_guard
        unique_lock<mutex> lock(resourceMutex);
        
        if (data.empty()) {
            cout << "No data to process" << endl;
            return;  // mutex unlocked here
        }
        
        cout << "Processing " << data.size() << " values..." << endl;
        int sum = 0;
        for (int value : data) {
            sum += value;
        }
        cout << "Sum: " << sum << endl;
        data.clear();
        
        // mutex unlocked when lock goes out of scope
    }
};

void workerThread(SharedResource& resource, int startVal, int count) {
    for (int i = 0; i < count; i++) {
        resource.addData(startVal + i);
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    SharedResource resource;
    
    // Create threads
    thread t1(workerThread, ref(resource), 100, 5);
    thread t2(workerThread, ref(resource), 200, 5);
    
    // Wait for threads to complete
    t1.join();
    t2.join();
    
    // Process the collected data
    resource.processData();
    
    return 0;
}
```

### Best Practices for RAII

1. **Design resource handling classes to follow RAII principles**
   - Acquire resources in constructors
   - Release resources in destructors
   - Don't throw exceptions from destructors

2. **Use existing RAII wrappers when available**
   - Smart pointers for dynamic memory
   - Standard containers for collections
   - Stream objects for I/O
   - `lock_guard` and `unique_lock` for mutexes

3. **Follow the Rule of Zero when possible**
   - Delegate resource management to member objects
   - Use standard library containers and smart pointers

4. **Make resource ownership clear**
   - Use move semantics to transfer ownership
   - Use smart pointers to express ownership semantics

5. **Properly handle self-assignment and exceptions**
   - Implement copy-and-swap idiom for assignment operators
   - Use the "acquire resources, and then modify state" idiom

6. **Control object copying and moving**
   - Delete copy operations for exclusive ownership
   - Implement deep copying for shared resources
   - Use move semantics for transferable resources

7. **Keep destructors simple and noexcept**
   - Avoid throwing exceptions from destructors
   - Handle cleanup failures gracefully

RAII is one of the most powerful idioms in C++, enabling robust resource management with clean, exception-safe code. Mastering RAII is essential for writing reliable C++ programs.
