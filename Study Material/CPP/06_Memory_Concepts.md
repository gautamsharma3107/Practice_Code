# Memory Concepts in C++

## Stack vs Heap Memory

### Stack Memory
- **Definition**: Region of memory that stores temporary variables created by functions
- **Characteristics**:
  - Automatically managed (allocation/deallocation) by the compiler
  - LIFO (Last In First Out) data structure
  - Fixed size (OS-dependent, typically 1-8 MB)
  - Very fast allocation/deallocation (simple pointer adjustment)
  - Local variables and function parameters are stored here
  - Memory is automatically reclaimed when variables go out of scope

```cpp
void stackExample() {
    int a = 5;        // Stored on stack
    double b = 10.5;  // Stored on stack
    char c = 'A';     // Stored on stack
    
    // When this function returns, a, b, and c are automatically deallocated
}
```

**Memory Layout Visualization**:
```
     Stack Growth
         ↓
     +------------+
     | Function B | ← Stack Pointer
     +------------+
     | Function A |
     +------------+
     |    main    |
     +------------+
         ↑
  High Addresses
```

### Heap Memory
- **Definition**: Region of memory used for dynamic allocation
- **Characteristics**:
  - Manually managed by the programmer
  - No specific pattern of allocation/deallocation
  - Limited only by virtual memory size
  - Slower than stack allocation
  - Subject to fragmentation over time
  - Requires explicit deallocation to prevent memory leaks

```cpp
void heapExample() {
    int* dynamicInt = new int;      // Allocates an integer on the heap
    *dynamicInt = 10;               // Sets the value
    
    // Must explicitly deallocate the memory
    delete dynamicInt;              // Prevents memory leak
    dynamicInt = nullptr;           // Good practice to avoid dangling pointers
}
```

**Memory Layout Visualization**:
```
  Low Addresses
         ↓
     +------------+
     |    Code    |
     +------------+
     | Static Data|
     +------------+
     |    Heap    | ← Heap grows upward
     |            |
     +------------+
     |            |
     |  Free Mem  |
     |            |
     +------------+
     |    Stack   | ← Stack grows downward
     +------------+
         ↑
  High Addresses
```

### Key Differences

| Feature | Stack | Heap |
|---------|-------|------|
| Size | Limited (MB range) | Large (GB range) |
| Speed | Very fast | Relatively slower |
| Management | Automatic | Manual (with `new`/`delete`) |
| Fragmentation | No fragmentation | Can be fragmented |
| Allocation | Compile-time | Runtime |
| Deallocation | Automatic | Manual |
| Main use | Local variables | Dynamic data structures |

## Pointers

### Basic Pointer Concepts
- **Definition**: Variables that store memory addresses
- **Declaration**: `type* pointer_name;` or `type *pointer_name;`
- **Operations**:
  - **&** (address-of): Gets the memory address of a variable
  - **\*** (dereference): Accesses the value at a memory address

```cpp
#include <iostream>

int main() {
    int number = 42;        // Regular integer variable
    int* pointer = &number; // Pointer storing the address of 'number'
    
    std::cout << "Value of number: " << number << std::endl;         // 42
    std::cout << "Address of number: " << &number << std::endl;      // e.g., 0x7ffeefbff8ac
    std::cout << "Value of pointer: " << pointer << std::endl;       // e.g., 0x7ffeefbff8ac
    std::cout << "Value pointed by pointer: " << *pointer << std::endl; // 42
    
    // Modifying the value through pointer
    *pointer = 100;
    std::cout << "New value of number: " << number << std::endl;     // 100
    
    return 0;
}
```

### Null Pointers
- Used to indicate that a pointer doesn't point to a valid memory location
- Modern C++ uses `nullptr` (preferred over older NULL or 0)

```cpp
int* ptr = nullptr;  // Modern C++ null pointer
if (ptr == nullptr) {
    std::cout << "Pointer is null" << std::endl;
}
```

### Void Pointers
- Generic pointers that can point to any data type
- Cannot be dereferenced directly (must be cast first)

```cpp
void* generic_ptr;
int num = 10;
generic_ptr = &num;  // Can store address of any type

// Must cast before dereferencing
int* int_ptr = static_cast<int*>(generic_ptr);
std::cout << *int_ptr << std::endl;  // 10
```

## Pointer Arithmetic

Pointers can be manipulated using arithmetic operations, which is particularly useful when working with arrays and data structures.

### Increment and Decrement
- When you increment a pointer, it moves to the next element of its type
- The actual memory address increases by `sizeof(type)`

```cpp
#include <iostream>

int main() {
    int array[5] = {10, 20, 30, 40, 50};
    int* ptr = array;  // Points to the first element
    
    std::cout << "Address of array[0]: " << ptr << ", Value: " << *ptr << std::endl;
    
    ptr++;  // Move to next integer (adds sizeof(int) bytes to address)
    std::cout << "Address of array[1]: " << ptr << ", Value: " << *ptr << std::endl;
    
    ptr += 2;  // Skip ahead by 2 elements
    std::cout << "Address of array[3]: " << ptr << ", Value: " << *ptr << std::endl;
    
    ptr--;  // Move back one element
    std::cout << "Address of array[2]: " << ptr << ", Value: " << *ptr << std::endl;
    
    return 0;
}
```

### Array Traversal with Pointers
```cpp
void printArray(int* arr, int size) {
    for (int* p = arr; p < arr + size; p++) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
}

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    printArray(numbers, 5);  // Output: 10 20 30 40 50
    return 0;
}
```

### Pointer Arithmetic with Different Types
```cpp
char charArray[5] = {'a', 'b', 'c', 'd', 'e'};
char* charPtr = charArray;
charPtr++; // Moves 1 byte forward

double doubleArray[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
double* doublePtr = doubleArray;
doublePtr++; // Moves 8 bytes forward (typically, sizeof(double))
```

## References

### Basic References
- An alias (alternative name) for an existing variable
- Must be initialized when declared
- Cannot be reassigned to refer to another variable
- Cannot have null references (always refers to a valid object)

```cpp
#include <iostream>

int main() {
    int original = 42;
    int& ref = original;  // Reference to original
    
    std::cout << "Original: " << original << std::endl;  // 42
    std::cout << "Reference: " << ref << std::endl;      // 42
    
    // Modifying through reference
    ref = 100;
    std::cout << "Original after modification: " << original << std::endl;  // 100
    
    // Modifying original
    original = 200;
    std::cout << "Reference after modifying original: " << ref << std::endl;  // 200
    
    return 0;
}
```

### References vs Pointers
```cpp
void incrementByPointer(int* ptr) {
    (*ptr)++;  // Need to dereference
}

void incrementByReference(int& ref) {
    ref++;     // Direct access, no dereferencing needed
}

int main() {
    int num = 10;
    
    incrementByPointer(&num);  // Pass address
    std::cout << num << std::endl;  // 11
    
    incrementByReference(num);  // Pass variable directly
    std::cout << num << std::endl;  // 12
    
    return 0;
}
```

### Reference Best Practices
- Use references for function parameters when:
  - The function needs to modify the original variable
  - You want to avoid copying large objects
- Use const references for read-only access to avoid unnecessary copies:
  ```cpp
  void printString(const std::string& str) {  // Efficient, no copying
      std::cout << str << std::endl;
  }
  ```

## Dynamic Memory Allocation

### Basic Allocation and Deallocation
```cpp
#include <iostream>

int main() {
    // Single object allocation
    int* singleInt = new int;  // Allocate memory for single integer
    *singleInt = 42;
    std::cout << "Value: " << *singleInt << std::endl;
    delete singleInt;  // Free memory
    
    // Array allocation
    int* intArray = new int[5];  // Allocate memory for 5 integers
    for (int i = 0; i < 5; i++) {
        intArray[i] = i * 10;
    }
    
    for (int i = 0; i < 5; i++) {
        std::cout << intArray[i] << " ";  // 0 10 20 30 40
    }
    std::cout << std::endl;
    
    delete[] intArray;  // Free array memory (note the [])
    
    return 0;
}
```

### Dynamic Object Allocation
```cpp
class Rectangle {
private:
    int width;
    int height;
public:
    Rectangle(int w, int h) : width(w), height(h) {
        std::cout << "Rectangle created" << std::endl;
    }
    
    ~Rectangle() {
        std::cout << "Rectangle destroyed" << std::endl;
    }
    
    int area() { return width * height; }
};

int main() {
    // Dynamic allocation of object
    Rectangle* rect = new Rectangle(5, 3);
    std::cout << "Area: " << rect->area() << std::endl;  // 15
    
    // Must explicitly delete to call destructor
    delete rect;
    
    // Dynamic array of objects
    Rectangle* rectArray = new Rectangle[3] { {1,2}, {3,4}, {5,6} };
    for (int i = 0; i < 3; i++) {
        std::cout << "Rectangle " << i << " area: " << rectArray[i].area() << std::endl;
    }
    
    delete[] rectArray;  // Calls destructor for each object in the array
    
    return 0;
}
```

### Placement new
- Allows constructing an object at a specific memory address

```cpp
#include <iostream>
#include <new>  // Required for placement new

class Sample {
public:
    int value;
    Sample(int v) : value(v) {
        std::cout << "Constructor called with value " << value << std::endl;
    }
    ~Sample() {
        std::cout << "Destructor called for value " << value << std::endl;
    }
};

int main() {
    // Allocate memory without constructing an object
    void* memory = operator new(sizeof(Sample));
    
    // Construct object at pre-allocated memory
    Sample* obj = new (memory) Sample(42);
    
    std::cout << "Object value: " << obj->value << std::endl;
    
    // Manually call destructor
    obj->~Sample();
    
    // Free raw memory
    operator delete(memory);
    
    return 0;
}
```

## Memory Management and Leaks

### Common Memory Leak Scenarios
```cpp
// Leak #1: Forgetting to delete
void leak1() {
    int* ptr = new int[100];  // Allocated memory
    // Missing delete[] ptr;   // Memory leak: never freed
}

// Leak #2: Overwriting pointer before deleting
void leak2() {
    int* ptr = new int;
    *ptr = 10;
    ptr = new int;  // Original allocation lost (leaked)
    *ptr = 20;
    delete ptr;     // Only second allocation freed
}

// Leak #3: Exception causing function to exit before deallocation
void leak3() {
    int* ptr = new int[100];
    // Some code that might throw an exception
    // If exception occurs, delete[] ptr; is never reached
    delete[] ptr;
}
```

### Proper Memory Management
```cpp
// Technique #1: Ensuring deletion with proper control flow
void proper1() {
    int* ptr = nullptr;
    try {
        ptr = new int[100];
        // Use the memory
    } catch (...) {
        delete[] ptr;  // Clean up in case of exception
        throw;         // Re-throw the exception
    }
    delete[] ptr;      // Normal clean up
}

// Technique #2: RAII (Resource Acquisition Is Initialization)
class ArrayWrapper {
private:
    int* data;
public:
    ArrayWrapper(size_t size) : data(new int[size]) {}
    ~ArrayWrapper() { delete[] data; }
    int& operator[](size_t index) { return data[index]; }
};

void proper2() {
    ArrayWrapper array(100);  // Memory allocated
    // Use array
    // No need for explicit delete - destructor handles it
}  // Memory automatically freed when array goes out of scope
```

### Memory Leak Detection Tools
- **Valgrind**: Comprehensive memory error detector
  ```bash
  valgrind --leak-check=full ./your_program
  ```
- **AddressSanitizer**: Compile-time instrumentation
  ```bash
  g++ -fsanitize=address -g yourcode.cpp -o your_program
  ```
- **Dr. Memory**: Memory monitoring for Windows

## Smart Pointers

Smart pointers are wrapper classes that manage the lifetime of dynamically allocated objects automatically.

### std::unique_ptr
- Exclusively owns and manages the object it points to
- Automatically deletes the object when the unique_ptr goes out of scope
- Cannot be copied, only moved (exclusive ownership)

```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired" << std::endl; }
    ~Resource() { std::cout << "Resource released" << std::endl; }
    void use() { std::cout << "Resource being used" << std::endl; }
};

void uniquePtrDemo() {
    // Create a unique_ptr to a Resource
    std::unique_ptr<Resource> res1 = std::make_unique<Resource>();
    
    // Use the resource
    res1->use();
    
    // Transfer ownership
    std::unique_ptr<Resource> res2 = std::move(res1);
    
    // res1 is now nullptr
    if (res1 == nullptr) {
        std::cout << "res1 no longer owns the resource" << std::endl;
    }
    
    // Use through new owner
    res2->use();
    
    // Resource will be automatically released when res2 goes out of scope
}
```

### std::shared_ptr
- Multiple shared_ptr instances can own the same object
- Object is deleted when the last shared_ptr owning it is destroyed
- Maintains a reference count internally

```cpp
#include <iostream>
#include <memory>

void sharedPtrDemo() {
    // Create a shared_ptr
    std::shared_ptr<Resource> res1 = std::make_shared<Resource>();
    
    {
        // Create another shared_ptr that shares ownership of the same object
        std::shared_ptr<Resource> res2 = res1;
        
        std::cout << "Reference count: " << res1.use_count() << std::endl;  // 2
        
        // Both can use the resource
        res1->use();
        res2->use();
        
        // res2 will be destroyed at the end of this scope, but resource remains
    }
    
    std::cout << "Reference count: " << res1.use_count() << std::endl;  // 1
    
    // Resource is still available
    res1->use();
    
    // Resource will be released when res1 is destroyed
}
```

### std::weak_ptr
- Non-owning reference to an object managed by shared_ptr
- Doesn't increase reference count
- Must be converted to shared_ptr to access the object
- Useful for breaking circular references

```cpp
#include <iostream>
#include <memory>

class Node {
public:
    std::string name;
    std::shared_ptr<Node> next;  // Strong reference
    std::weak_ptr<Node> prev;    // Weak reference to prevent cycles
    
    Node(const std::string& n) : name(n) {
        std::cout << "Node " << name << " created" << std::endl;
    }
    
    ~Node() {
        std::cout << "Node " << name << " destroyed" << std::endl;
    }
};

void weakPtrDemo() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>("Node1");
    std::shared_ptr<Node> node2 = std::make_shared<Node>("Node2");
    
    // Create a doubly-linked list
    node1->next = node2;
    node2->prev = node1;  // Weak reference to prevent cycle
    
    // Using weak_ptr
    if (auto temp = node2->prev.lock()) {  // Convert to shared_ptr to use
        std::cout << "Node2's previous node is: " << temp->name << std::endl;
    }
    
    // Without weak_ptr, we would have a memory leak due to circular references
    // When using weak_ptr, memory is properly cleaned up
}
```

### Custom Deleters with Smart Pointers
```cpp
#include <iostream>
#include <memory>

// Custom deleter function
void customFileDeleter(FILE* file) {
    std::cout << "Custom deleter: Closing file" << std::endl;
    if (file) {
        fclose(file);
    }
}

void customDeleterDemo() {
    // Using unique_ptr with custom deleter
    {
        std::unique_ptr<FILE, decltype(&customFileDeleter)> filePtr(
            fopen("example.txt", "w"), customFileDeleter);
        
        if (filePtr) {
            fprintf(filePtr.get(), "Custom deleter example");
            // File will be automatically closed by our custom deleter
        }
    }
    
    // Using shared_ptr with custom deleter
    {
        std::shared_ptr<FILE> filePtr(
            fopen("example2.txt", "w"), customFileDeleter);
        
        if (filePtr) {
            fprintf(filePtr.get(), "Another example");
            // File will be automatically closed by our custom deleter
        }
    }
}
```

## Problem Exercises

### Exercise 1: Stack vs Heap Comparison
Write a program that compares the performance of stack allocation versus heap allocation.

```cpp
#include <iostream>
#include <chrono>
#include <memory>

class LargeObject {
    int data[10000]; // Large array to make the difference noticeable
public:
    LargeObject() {
        for (int i = 0; i < 10000; i++) data[i] = i;
    }
    int process() {
        int sum = 0;
        for (int i = 0; i < 10000; i++) sum += data[i];
        return sum;
    }
};

int main() {
    const int iterations = 1000000;
    
    // Stack allocation timing
    auto stackStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        LargeObject obj;  // Stack-allocated
        obj.process();
    }
    auto stackEnd = std::chrono::high_resolution_clock::now();
    
    // Heap allocation timing
    auto heapStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        LargeObject* obj = new LargeObject();  // Heap-allocated
        obj->process();
        delete obj;
    }
    auto heapEnd = std::chrono::high_resolution_clock::now();
    
    // Smart pointer timing
    auto smartStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        std::unique_ptr<LargeObject> obj = 
            std::make_unique<LargeObject>();  // Heap with smart pointer
        obj->process();
    }
    auto smartEnd = std::chrono::high_resolution_clock::now();
    
    // Calculate durations
    auto stackDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        stackEnd - stackStart).count();
    auto heapDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        heapEnd - heapStart).count();
    auto smartDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        smartEnd - smartStart).count();
    
    std::cout << "Stack allocation time: " << stackDuration << " ms\n";
    std::cout << "Heap allocation time: " << heapDuration << " ms\n";
    std::cout << "Smart pointer time: " << smartDuration << " ms\n";
    
    return 0;
}
```

### Exercise 2: Custom Dynamic Array Implementation
Implement a dynamic array class that manages its own memory.

```cpp
#include <iostream>

class DynamicArray {
private:
    int* data;
    size_t capacity;
    size_t size;
    
    void resize() {
        size_t newCapacity = capacity * 2;
        int* newData = new int[newCapacity];
        
        // Copy existing elements
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        // Clean up old memory and update pointers
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    DynamicArray(size_t initialCapacity = 10) : 
        capacity(initialCapacity), size(0) {
        data = new int[capacity];
    }
    
    ~DynamicArray() {
        delete[] data;
    }
    
    // Prevent copying to avoid double-free issues (Rule of Three/Five)
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    
    // Move operations
    DynamicArray(DynamicArray&& other) noexcept : 
        data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.size = other.capacity = 0;
    }
    
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }
    
    void push_back(int value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }
    
    int& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    
    void print() const {
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Size: " << size << ", Capacity: " << capacity << std::endl;
    }
};

int main() {
    DynamicArray arr;
    
    for (int i = 0; i < 20; i++) {
        arr.push_back(i * 10);
    }
    
    arr.print();
    
    std::cout << "Element at index 5: " << arr.at(5) << std::endl;
    arr.at(5) = 999;
    std::cout << "Modified element: " << arr.at(5) << std::endl;
    
    return 0;
}
```

### Exercise 3: Memory Leak Detector
Implement a basic memory leak detector that tracks allocations and deallocations.

```cpp
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <new>

class MemoryLeakDetector {
private:
    static std::map<void*, size_t> allocations;
    static size_t totalAllocated;
    static size_t totalFreed;
    static size_t allocationCount;
    
public:
    static void* allocate(size_t size, const char* file, int line) {
        void* ptr = std::malloc(size);
        if (ptr) {
            allocations[ptr] = size;
            totalAllocated += size;
            allocationCount++;
            std::cout << "Allocation: " << ptr << " size: " << size 
                      << " at " << file << ":" << line << std::endl;
        }
        return ptr;
    }
    
    static void deallocate(void* ptr, const char* file, int line) {
        if (ptr) {
            auto it = allocations.find(ptr);
            if (it != allocations.end()) {
                totalFreed += it->second;
                std::cout << "Deallocation: " << ptr 
                          << " at " << file << ":" << line << std::endl;
                allocations.erase(it);
            } else {
                std::cout << "Warning: Freeing unallocated memory at " 
                          << file << ":" << line << std::endl;
            }
            std::free(ptr);
        }
    }
    
    static void reportLeaks() {
        std::cout << "\n=== Memory Leak Report ===\n";
        std::cout << "Total allocations: " << allocationCount << std::endl;
        std::cout << "Total allocated: " << totalAllocated << " bytes" << std::endl;
        std::cout << "Total freed: " << totalFreed << " bytes" << std::endl;
        std::cout << "Unfreed: " << (totalAllocated - totalFreed) << " bytes" << std::endl;
        std::cout << "Remaining allocations: " << allocations.size() << std::endl;
        
        for (const auto& pair : allocations) {
            std::cout << "Leak: " << pair.first << " - " << pair.second << " bytes" << std::endl;
        }
    }
};

// Initialize static members
std::map<void*, size_t> MemoryLeakDetector::allocations;
size_t MemoryLeakDetector::totalAllocated = 0;
size_t MemoryLeakDetector::totalFreed = 0;
size_t MemoryLeakDetector::allocationCount = 0;

// Overload new and delete operators
void* operator new(size_t size, const char* file, int line) {
    return MemoryLeakDetector::allocate(size, file, line);
}

void* operator new[](size_t size, const char* file, int line) {
    return MemoryLeakDetector::allocate(size, file, line);
}

void operator delete(void* ptr) noexcept {
    MemoryLeakDetector::deallocate(ptr, "unknown", 0);
}

void operator delete[](void* ptr) noexcept {
    MemoryLeakDetector::deallocate(ptr, "unknown", 0);
}

// Macros to use the leak detector
#define new new(__FILE__, __LINE__)

int main() {
    int* ptr1 = new int;
    *ptr1 = 10;
    
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) arr[i] = i;
    
    // Create a leak by not deleting ptr1
    // delete ptr1; 
    
    delete[] arr;
    
    MemoryLeakDetector::reportLeaks();
    return 0;
}
```

### Exercise 4: Smart Pointer Implementation
Implement a basic unique pointer class.

```cpp
#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;
    
public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    
    // Destructor
    ~UniquePtr() {
        if (ptr) {
            delete ptr;
        }
    }
    
    // Disable copying
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    // Move assignment
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // Dereference operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    // Access the raw pointer
    T* get() const { return ptr; }
    
    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // Reset to new pointer
    void reset(T* p = nullptr) {
        T* old = ptr;
        ptr = p;
        if (old) {
            delete old;
        }
    }
    
    // Boolean conversion
    explicit operator bool() const { return ptr != nullptr; }
};

class Resource {
public:
    Resource() { std::cout << "Resource acquired" << std::endl; }
    ~Resource() { std::cout << "Resource released" << std::endl; }
    void use() { std::cout << "Resource in use" << std::endl; }
};

int main() {
    // Test our custom unique pointer
    UniquePtr<Resource> res1(new Resource());
    res1->use();
    
    // Test move
    UniquePtr<Resource> res2(std::move(res1));
    if (res1.get() == nullptr) {
        std::cout << "res1 no longer owns the resource" << std::endl;
    }
    
    res2->use();
    
    return 0;
}
```

## Additional Resources

### Books
- **"Effective Modern C++"** by Scott Meyers
- **"C++ Primer"** by Stanley Lippman, Josée Lajoie, and Barbara Moo

### Online Resources
- [CPPReference Memory Management](https://en.cppreference.com/w/cpp/memory)
- [LearnCpp's Memory Management Tutorial](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation/)
- [Microsoft's C++ Memory Management Documentation](https://docs.microsoft.com/en-us/cpp/cpp/memory-management-in-cpp)

### Tools for Memory Analysis
- [Valgrind](https://valgrind.org/)
- [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer)
- [Dr. Memory](https://drmemory.org/)
- [Visual Studio Memory Profiling Tools](https://docs.microsoft.com/en-us/visualstudio/profiling/memory-usage)

### Practice Platforms
- [LeetCode](https://leetcode.com/) - Many problems requiring efficient memory management
- [HackerRank](https://www.hackerrank.com/) - C++ challenges
- [Codewars](https://www.codewars.com/) - Kata challenges for C++