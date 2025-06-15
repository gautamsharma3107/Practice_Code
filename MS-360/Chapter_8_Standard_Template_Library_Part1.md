# Chapter 8: Standard Template Library (STL) (Part 1)

## 8.1 STL Overview

The Standard Template Library (STL) is a powerful set of C++ template classes and functions that provide general-purpose classes and functions with templates that implement many popular and commonly used algorithms and data structures like vectors, lists, queues, and stacks.

### Core Components of the STL

The STL consists of three primary components:

1. **Containers**: Objects that store data
2. **Algorithms**: Functions that operate on containers
3. **Iterators**: Objects that connect algorithms to containers

### Benefits of Using the STL

1. **Reliability**: The STL is extensively tested and optimized
2. **Efficiency**: Implementations are highly optimized for performance
3. **Productivity**: Reduces development time significantly
4. **Reusability**: Promotes code reuse through generic programming
5. **Standardization**: Part of the C++ standard library

### Overview of STL Components

```cpp
#include <iostream>
#include <vector>      // Container
#include <algorithm>   // Algorithms
#include <string>
using namespace std;

int main() {
    // Create a vector container
    vector<int> numbers = {5, 2, 8, 1, 9};
    
    // Use an algorithm with iterators
    sort(numbers.begin(), numbers.end());  // Sort in ascending order
    
    // Iterate through the container using an iterator
    cout << "Sorted numbers: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Find an element using an algorithm and iterators
    auto it = find(numbers.begin(), numbers.end(), 8);
    if (it != numbers.end()) {
        cout << "Found: " << *it << " at position: " 
             << (it - numbers.begin()) << endl;
    }
    
    return 0;
}
```

### Headers for STL Components

| Component | Headers |
|-----------|---------|
| **Containers** | `<vector>`, `<list>`, `<deque>`, `<queue>`, `<stack>`, `<map>`, `<set>`, `<unordered_map>`, `<unordered_set>` |
| **Algorithms** | `<algorithm>`, `<numeric>` |
| **Iterators** | Built into containers |
| **Function Objects** | `<functional>` |
| **Adaptors** | Built into their respective headers |

### STL Design Philosophy

The STL was designed based on the concept of generic programming, with these key principles:

1. **Separation of data and algorithms**: Algorithms are not part of containers
2. **Extension through composition**: Components can be combined flexibly
3. **Type safety**: Compile-time type checking provides safety without runtime overhead
4. **Efficiency**: Performance is a key consideration in all implementations

## 8.2 Containers

STL containers are objects that store collections of other objects. They are implemented as class templates, allowing them to hold elements of any type that meets certain requirements.

### Types of STL Containers

1. **Sequence containers**: Store elements in a linear sequence
   - `vector`
   - `list`
   - `deque`
   - `array` (C++11)
   - `forward_list` (C++11)

2. **Associative containers**: Store elements in ordered structures
   - `set`
   - `multiset`
   - `map`
   - `multimap`

3. **Unordered associative containers** (C++11): Store elements in unordered structures
   - `unordered_set`
   - `unordered_multiset`
   - `unordered_map`
   - `unordered_multimap`

4. **Container adaptors**: Provide a different interface for specific sequence containers
   - `stack`
   - `queue`
   - `priority_queue`

### Common Container Operations

Most STL containers provide these operations:

- **Constructors**: Default, copy, move (C++11), and initializer list (C++11)
- **Assignment operators**: Copy, move (C++11), and initializer list (C++11)
- **Size operations**: `size()`, `empty()`, `max_size()`
- **Element access**: Depends on container type
- **Iterators**: `begin()`, `end()`, `rbegin()`, `rend()`
- **Modifiers**: `insert()`, `erase()`, `clear()`

Here's a basic comparison of some common containers:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
using namespace std;

template <typename Container>
void displayContainer(const Container& c, const string& name) {
    cout << name << ": ";
    for (const auto& item : c) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    // Creating different containers
    vector<int> vec = {1, 2, 3, 4, 5};
    list<int> lst = {1, 2, 3, 4, 5};
    deque<int> deq = {1, 2, 3, 4, 5};
    
    // Display initial state
    displayContainer(vec, "vector");
    displayContainer(lst, "list");
    displayContainer(deq, "deque");
    
    // Adding elements to the front
    // vec.insert(vec.begin(), 0);  // Potentially expensive for vector
    lst.push_front(0);            // Efficient for list
    deq.push_front(0);            // Efficient for deque
    
    // Adding elements to the back
    vec.push_back(6);             // Efficient for vector
    lst.push_back(6);             // Efficient for list
    deq.push_back(6);             // Efficient for deque
    
    // Display after modifications
    cout << "\nAfter modifications:" << endl;
    displayContainer(vec, "vector");
    displayContainer(lst, "list");
    displayContainer(deq, "deque");
    
    // Create a stack using deque as the underlying container
    stack<int> stk(deq);
    
    cout << "\nStack (top->bottom): ";
    while (!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
    
    return 0;
}
```

### 8.2.1 Vector

`std::vector` is a sequence container that represents a dynamic array, capable of growing or shrinking in size. It provides random access to elements and is the most commonly used STL container.

#### Key Features

- **Dynamic size**: Can grow or shrink automatically
- **Random access**: Constant-time access to elements by index
- **Contiguous storage**: Elements are stored in contiguous memory
- **Efficient insertion/deletion at the end**: Amortized constant time
- **Inefficient insertion/deletion elsewhere**: Linear time

#### Basic Vector Operations

```cpp
#include <iostream>
#include <vector>
#include <algorithm>  // For algorithms like sort, find
using namespace std;

int main() {
    // Different ways to create a vector
    vector<int> vec1;                     // Empty vector
    vector<int> vec2(5, 0);               // Vector with 5 elements, all 0
    vector<int> vec3 = {10, 20, 30, 40};  // Initializer list (C++11)
    vector<int> vec4(vec3);               // Copy constructor
    
    // Size operations
    cout << "vec1 size: " << vec1.size() << endl;
    cout << "vec2 size: " << vec2.size() << endl;
    cout << "vec3 size: " << vec3.size() << endl;
    cout << "vec3 capacity: " << vec3.capacity() << endl;  // Number of elements it can hold
    
    // Adding elements
    vec1.push_back(100);
    vec1.push_back(200);
    vec1.push_back(300);
    
    // Accessing elements
    cout << "vec1[0]: " << vec1[0] << endl;        // No bounds checking
    cout << "vec1.at(1): " << vec1.at(1) << endl;  // With bounds checking
    cout << "vec1.front(): " << vec1.front() << endl;
    cout << "vec1.back(): " << vec1.back() << endl;
    
    // Iteration
    cout << "vec3 elements: ";
    for (const auto& item : vec3) {  // Range-based for loop (C++11)
        cout << item << " ";
    }
    cout << endl;
    
    // Insert and erase
    vec3.insert(vec3.begin() + 2, 25);  // Insert 25 at position 2
    
    cout << "vec3 after insert: ";
    for (size_t i = 0; i < vec3.size(); ++i) {  // Traditional iteration
        cout << vec3[i] << " ";
    }
    cout << endl;
    
    vec3.erase(vec3.begin() + 1);  // Erase element at position 1
    
    cout << "vec3 after erase: ";
    for (auto it = vec3.begin(); it != vec3.end(); ++it) {  // Iterator-based loop
        cout << *it << " ";
    }
    cout << endl;
    
    // Using algorithms
    sort(vec3.begin(), vec3.end());  // Sort in ascending order
    
    cout << "vec3 after sorting: ";
    for (const auto& item : vec3) {
        cout << item << " ";
    }
    cout << endl;
    
    // Finding elements
    auto findIt = find(vec3.begin(), vec3.end(), 30);
    if (findIt != vec3.end()) {
        cout << "Found element: " << *findIt << endl;
    }
    
    // Clearing the vector
    vec3.clear();
    cout << "vec3 size after clearing: " << vec3.size() << endl;
    
    return 0;
}
```

#### Vector Performance Considerations

- **Memory reallocation**: When a vector grows beyond its capacity, it reallocates memory
- **Reserve**: Use `reserve()` to prevent multiple reallocations
- **Shrink to fit**: Use `shrink_to_fit()` to reduce capacity to fit size

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Demonstrating vector capacity and reallocation
    vector<int> numbers;
    
    cout << "Initial capacity: " << numbers.capacity() << endl;
    
    // Add elements and observe capacity changes
    for (int i = 0; i < 100; ++i) {
        numbers.push_back(i);
        
        // Print capacity every time it changes
        if (numbers.size() == numbers.capacity()) {
            cout << "Size: " << numbers.size() 
                 << ", Capacity: " << numbers.capacity() << endl;
        }
    }
    
    // Using reserve to pre-allocate memory
    vector<int> efficientVec;
    efficientVec.reserve(1000);  // Pre-allocate space for 1000 elements
    
    cout << "\nefficient vector - Initial capacity after reserve: " 
         << efficientVec.capacity() << endl;
    
    for (int i = 0; i < 100; ++i) {
        efficientVec.push_back(i);
    }
    
    cout << "efficient vector - Size: " << efficientVec.size() 
         << ", Capacity: " << efficientVec.capacity() << endl;
    
    // Using shrink_to_fit to reduce capacity
    efficientVec.shrink_to_fit();
    cout << "After shrink_to_fit - Size: " << efficientVec.size() 
         << ", Capacity: " << efficientVec.capacity() << endl;
    
    return 0;
}
```

#### Vector of Custom Objects

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Custom class
class Person {
private:
    string name;
    int age;
    
public:
    Person(const string& n, int a) : name(n), age(a) {}
    
    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    
    // For sorting and comparison
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

// For displaying Person objects
ostream& operator<<(ostream& os, const Person& person) {
    return os << person.getName() << " (" << person.getAge() << ")";
}

int main() {
    // Create a vector of Person objects
    vector<Person> people;
    
    // Add elements
    people.push_back(Person("Alice", 25));
    people.push_back(Person("Bob", 30));
    people.push_back(Person("Charlie", 22));
    people.emplace_back("David", 35);  // Construct in place (more efficient)
    
    // Display people
    cout << "People:" << endl;
    for (const auto& person : people) {
        cout << person << endl;
    }
    
    // Sort by age (using Person::operator<)
    sort(people.begin(), people.end());
    
    cout << "\nPeople sorted by age:" << endl;
    for (const auto& person : people) {
        cout << person << endl;
    }
    
    // Sort by name using a lambda function
    sort(people.begin(), people.end(), 
         [](const Person& a, const Person& b) {
             return a.getName() < b.getName();
         });
    
    cout << "\nPeople sorted by name:" << endl;
    for (const auto& person : people) {
        cout << person << endl;
    }
    
    return 0;
}
```

### 8.2.2 List

`std::list` is a sequence container that implements a doubly-linked list. It allows efficient insertion and removal of elements anywhere within the sequence.

#### Key Features

- **Non-contiguous memory**: Elements are not stored in contiguous memory
- **Bidirectional iterators**: Can move forward and backward
- **Efficient insertion/deletion anywhere**: Constant time
- **No random access**: Cannot use `[]` or `at()`
- **Slow element search**: Linear time complexity

#### Basic List Operations

```cpp
#include <iostream>
#include <list>
#include <string>
#include <algorithm>  // for find
using namespace std;

int main() {
    // Create a list
    list<int> numbers = {10, 20, 30, 40, 50};
    
    // Display the list
    cout << "List contents: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Add elements
    numbers.push_back(60);    // Add to the end
    numbers.push_front(5);    // Add to the beginning
    
    // Display after adding
    cout << "After adding elements: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Insert in the middle
    auto it = find(numbers.begin(), numbers.end(), 30);
    if (it != numbers.end()) {
        numbers.insert(it, 25);  // Insert before the found element
    }
    
    // Display after inserting
    cout << "After inserting 25: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Remove elements
    numbers.remove(20);  // Remove all occurrences of 20
    
    numbers.pop_front();  // Remove the first element
    numbers.pop_back();   // Remove the last element
    
    // Display after removing
    cout << "After removing elements: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Size operations
    cout << "List size: " << numbers.size() << endl;
    cout << "Is empty? " << (numbers.empty() ? "Yes" : "No") << endl;
    
    // Sort the list
    numbers.sort();  // Lists have their own sort method!
    
    cout << "After sorting: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Reverse the list
    numbers.reverse();  // Lists have their own reverse method!
    
    cout << "After reversing: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Clear the list
    numbers.clear();
    cout << "Size after clearing: " << numbers.size() << endl;
    
    return 0;
}
```

#### Unique List Operations

Lists have specialized member functions that other containers don't have:

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    // Create two lists
    list<int> list1 = {10, 20, 30, 20, 40, 30, 30, 50};
    list<int> list2 = {5, 15, 25, 35, 45};
    
    cout << "Original list1: ";
    for (const auto& item : list1) {
        cout << item << " ";
    }
    cout << endl;
    
    // Remove duplicate elements
    list1.unique();
    
    cout << "After unique(): ";
    for (const auto& item : list1) {
        cout << item << " ";
    }
    cout << endl;
    
    // Sort both lists
    list1.sort();
    list2.sort();
    
    cout << "list1 sorted: ";
    for (const auto& item : list1) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "list2 sorted: ";
    for (const auto& item : list2) {
        cout << item << " ";
    }
    cout << endl;
    
    // Merge two sorted lists
    list1.merge(list2);  // list2 will be empty after merging
    
    cout << "After merge: ";
    for (const auto& item : list1) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "list2 size after merge: " << list2.size() << endl;
    
    // Splice (insert elements from another list)
    list<int> source = {100, 200, 300};
    auto it = list1.begin();
    advance(it, 3);  // Move iterator to the 4th position
    
    list1.splice(it, source);  // Insert all elements from source at position it
    
    cout << "After splice: ";
    for (const auto& item : list1) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "source size after splice: " << source.size() << endl;
    
    return 0;
}
```

#### When to Use List

- When you need frequent insertions and deletions at arbitrary positions
- When elements should not be relocated (pointers/references remain valid)
- When you don't need random access to elements
- When the specific operations (splice, unique, etc.) are needed

#### List vs Vector Performance

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

template<typename Container>
void performanceTest(const string& containerName) {
    const int NUM_ELEMENTS = 100000;
    
    Container container;
    
    // Test insertion at the end
    auto startTime = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        container.push_back(i);
    }
    auto endTime = high_resolution_clock::now();
    auto durationPushBack = duration_cast<milliseconds>(endTime - startTime).count();
    
    cout << containerName << " - Push back time: " << durationPushBack << "ms" << endl;
    
    // Test insertion at the beginning
    Container container2;
    startTime = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS / 10; ++i) {  // Using fewer elements for vector
        container2.insert(container2.begin(), i);
    }
    endTime = high_resolution_clock::now();
    auto durationInsertFront = duration_cast<milliseconds>(endTime - startTime).count();
    
    cout << containerName << " - Insert at front time: " << durationInsertFront << "ms" << endl;
    
    // Test iteration (if not empty)
    if (!container.empty()) {
        startTime = high_resolution_clock::now();
        typename Container::value_type sum = 0;
        for (const auto& item : container) {
            sum += item;
        }
        endTime = high_resolution_clock::now();
        auto durationIteration = duration_cast<milliseconds>(endTime - startTime).count();
        
        cout << containerName << " - Iteration time: " << durationIteration << "ms" << endl;
    }
    
    cout << endl;
}

int main() {
    cout << "Performance comparison between vector and list:" << endl;
    cout << "-------------------------------------------" << endl;
    
    performanceTest<vector<int>>("vector");
    performanceTest<list<int>>("list");
    
    return 0;
}
```

### 8.2.3 Deque

`std::deque` (double-ended queue) is a sequence container that allows fast insertion and deletion at both its beginning and end. Unlike vector, deque elements are not stored in contiguous memory.

#### Key Features

- **Random access**: Constant-time access to elements by index
- **Efficient insertion/deletion at both ends**: Constant time
- **Inefficient insertion/deletion in the middle**: Linear time
- **Non-contiguous memory**: Elements are stored in multiple chunks
- **No reallocation**: No need to reserve capacity

#### Basic Deque Operations

```cpp
#include <iostream>
#include <deque>
#include <string>
using namespace std;

int main() {
    // Create a deque
    deque<int> numbers;
    
    // Add elements to both ends
    numbers.push_back(30);   // Add to the end
    numbers.push_back(40);
    numbers.push_front(20);  // Add to the beginning
    numbers.push_front(10);
    
    // Display contents
    cout << "Deque contents: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Access elements
    cout << "First element: " << numbers.front() << endl;
    cout << "Last element: " << numbers.back() << endl;
    cout << "Element at position 2: " << numbers[2] << endl;
    cout << "Element at position 1: " << numbers.at(1) << endl;
    
    // Insert in the middle
    auto it = numbers.begin() + 2;
    numbers.insert(it, 25);
    
    cout << "After inserting 25: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Remove elements from both ends
    numbers.pop_front();  // Remove from the beginning
    numbers.pop_back();   // Remove from the end
    
    cout << "After removing from both ends: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Size operations
    cout << "Size: " << numbers.size() << endl;
    cout << "Is empty: " << (numbers.empty() ? "Yes" : "No") << endl;
    
    // Resize the deque
    numbers.resize(6, 0);  // Resize to 6 elements, fill new positions with 0
    
    cout << "After resizing: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Clear the deque
    numbers.clear();
    cout << "Size after clearing: " << numbers.size() << endl;
    
    return 0;
}
```

#### Using a Deque as a Double-Ended Queue

This is the natural use case for a deque:

```cpp
#include <iostream>
#include <deque>
#include <string>
using namespace std;

// Simple double-ended queue demonstration
class ProcessQueue {
private:
    deque<string> processes;
    
public:
    // Add high-priority process to the front
    void addHighPriority(const string& process) {
        processes.push_front(process);
        cout << "Added high-priority process: " << process << endl;
    }
    
    // Add normal process to the back
    void addNormal(const string& process) {
        processes.push_back(process);
        cout << "Added normal process: " << process << endl;
    }
    
    // Process next (from the front)
    void processNext() {
        if (!processes.empty()) {
            cout << "Processing: " << processes.front() << endl;
            processes.pop_front();
        } else {
            cout << "No processes to handle." << endl;
        }
    }
    
    // Display queue
    void displayQueue() const {
        if (processes.empty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        
        cout << "Current process queue (front->back): ";
        for (const auto& proc : processes) {
            cout << proc << " ";
        }
        cout << endl;
    }
    
    // Queue size
    size_t size() const {
        return processes.size();
    }
};

int main() {
    ProcessQueue queue;
    
    queue.addNormal("Background task");
    queue.addNormal("File indexing");
    queue.addHighPriority("User input");
    queue.addNormal("Cleanup");
    queue.addHighPriority("System alert");
    
    queue.displayQueue();
    
    cout << "\nProcessing queue:" << endl;
    while (queue.size() > 0) {
        queue.processNext();
    }
    
    queue.displayQueue();
    
    return 0;
}
```

#### When to Use Deque

- When you need frequent insertions and deletions at both ends
- When you need random access to elements
- When memory efficiency is important (no overallocation like vector)
- When relocating elements is undesirable

#### Comparison: Vector vs List vs Deque

| Operation | Vector | List | Deque |
|-----------|--------|------|-------|
| Random Access | O(1) | O(n) | O(1) |
| Insert/Delete at beginning | O(n) | O(1) | O(1) |
| Insert/Delete at end | Amortized O(1) | O(1) | O(1) |
| Insert/Delete in middle | O(n) | O(1) + search time | O(n) |
| Memory Layout | Contiguous | Non-contiguous | Chunked blocks |
| Iterator Invalidation on Insert/Delete | Yes (at/after insertion point) | No | Possibly |

### 8.2.4 Stack

`std::stack` is a container adapter that provides a LIFO (Last-In, First-Out) data structure. It is implemented as an adapter over other containers, typically `deque` by default.

#### Key Features

- **LIFO (Last-In, First-Out)**: Elements are inserted and removed from the same end
- **Container Adapter**: Built on top of other containers
- **Limited Interface**: Only allows operations appropriate for stacks
- **No iterators**: Can't traverse all elements

#### Basic Stack Operations

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    // Create a stack with default container (deque)
    stack<int> numbers;
    
    // Push elements onto the stack
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);
    
    cout << "Stack size: " << numbers.size() << endl;
    cout << "Top element: " << numbers.top() << endl;
    
    // Pop elements from the stack
    cout << "Popping elements: ";
    while (!numbers.empty()) {
        cout << numbers.top() << " ";
        numbers.pop();
    }
    cout << endl;
    
    cout << "Stack empty? " << (numbers.empty() ? "Yes" : "No") << endl;
    
    // Creating a stack with a different underlying container
    stack<string, vector<string>> strStack;
    
    strStack.push("First");
    strStack.push("Second");
    strStack.push("Third");
    
    cout << "String stack top: " << strStack.top() << endl;
    
    return 0;
}
```

#### Real-World Stack Applications

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <cctype>  // for isdigit
using namespace std;

// Example 1: Check for balanced parentheses
bool areParenthesesBalanced(const string& expr) {
    stack<char> s;
    
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            // Push opening bracket to stack
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            // Check for matching opening bracket
            if (s.empty()) {
                return false;  // Unmatched closing bracket
            }
            
            char top = s.top();
            if ((c == ')' && top == '(') ||
                (c == ']' && top == '[') ||
                (c == '}' && top == '{')) {
                s.pop();  // Matched, remove the opening bracket
            } else {
                return false;  // Mismatched brackets
            }
        }
    }
    
    // If stack is empty, all brackets are matched
    return s.empty();
}

// Example 2: Evaluate postfix expression
int evaluatePostfix(const string& expr) {
    stack<int> s;
    
    for (char c : expr) {
        // If character is a digit, push it to the stack
        if (isdigit(c)) {
            s.push(c - '0');  // Convert char to integer
        } 
        // If character is an operator, pop two elements and apply operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // Need at least two operands
            if (s.size() < 2) {
                cerr << "Invalid expression" << endl;
                return 0;
            }
            
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            
            switch (c) {
                case '+': s.push(operand1 + operand2); break;
                case '-': s.push(operand1 - operand2); break;
                case '*': s.push(operand1 * operand2); break;
                case '/': s.push(operand1 / operand2); break;
            }
        }
    }
    
    // Result should be the only item left in the stack
    if (s.size() != 1) {
        cerr << "Invalid expression" << endl;
        return 0;
    }
    
    return s.top();
}

// Example 3: Function call simulation
void simulateFunctionCalls() {
    stack<string> callStack;
    
    cout << "Function call simulation:" << endl;
    
    // Main calls function A
    callStack.push("main");
    cout << "Entering function: main" << endl;
    
    // Function A calls function B
    callStack.push("functionA");
    cout << "Entering function: functionA" << endl;
    
    // Function B calls function C
    callStack.push("functionB");
    cout << "Entering function: functionB" << endl;
    
    callStack.push("functionC");
    cout << "Entering function: functionC" << endl;
    
    // Functions return in reverse order
    cout << "\nFunctions returning:" << endl;
    while (!callStack.empty()) {
        cout << "Returning from function: " << callStack.top() << endl;
        callStack.pop();
    }
}

int main() {
    // Test parentheses balancing
    string expr1 = "((a+b)*(c-d))";
    string expr2 = "{[a+b]*(c+d)}";
    string expr3 = "((a+b)*(c-d)";
    
    cout << expr1 << " is " << (areParenthesesBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is " << (areParenthesesBalanced(expr2) ? "balanced" : "not balanced") << endl;
    cout << expr3 << " is " << (areParenthesesBalanced(expr3) ? "balanced" : "not balanced") << endl;
    
    // Test postfix evaluation
    string postfix = "534*+";  // Represents 5+(3*4) = 17
    cout << "\nEvaluating postfix expression: " << postfix << endl;
    cout << "Result: " << evaluatePostfix(postfix) << endl;
    
    // Simulate function calls
    cout << endl;
    simulateFunctionCalls();
    
    return 0;
}
```

#### When to Use Stack

- When you need LIFO (Last-In, First-Out) behavior
- When you need to track function calls, recursive algorithms
- When you need to maintain history/state for undo operations
- For parsing expressions, syntax validation, etc.

#### Custom Stack Implementation

While you typically use the STL `std::stack`, here's a basic implementation to understand how it works internally:

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T, typename Container = vector<T>>
class MyStack {
private:
    Container container;  // Underlying container

public:
    // Check if stack is empty
    bool empty() const {
        return container.empty();
    }
    
    // Get size of stack
    size_t size() const {
        return container.size();
    }
    
    // Access top element
    T& top() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return container.back();
    }
    
    const T& top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return container.back();
    }
    
    // Add element to top
    void push(const T& value) {
        container.push_back(value);
    }
    
    void push(T&& value) {
        container.push_back(move(value));
    }
    
    // Remove top element
    void pop() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        container.pop_back();
    }
    
    // Swap contents with another stack
    void swap(MyStack& other) noexcept {
        container.swap(other.container);
    }
};

int main() {
    MyStack<int> stack;
    
    // Push elements
    for (int i = 1; i <= 5; ++i) {
        stack.push(i * 10);
        cout << "Pushed: " << stack.top() << endl;
    }
    
    cout << "\nStack contents (top to bottom): ";
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    
    return 0;
}
```
