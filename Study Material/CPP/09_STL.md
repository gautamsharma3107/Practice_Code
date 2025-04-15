# Standard Template Library (STL) in C++

## Introduction
The Standard Template Library (STL) is a powerful set of C++ template classes that provides generic programming capabilities and reusable components. STL is organized into three fundamental components: containers, algorithms, and iterators.

## 1. Containers
Containers are data structures that store collections of objects in memory.

### 1.1 Sequence Containers

#### Vector
- Dynamic array with automatic resizing
- Random access, efficient insertion/deletion at the end
- Continuous memory allocation

```cpp
#include <iostream>
#include <vector>

int main() {
    // Declaration
    std::vector<int> vec;
    
    // Adding elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    // Accessing elements
    std::cout << "Element at index 1: " << vec[1] << std::endl;
    
    // Size and capacity
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    
    // Iterating through vector
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Insert at specific position
    vec.insert(vec.begin() + 1, 15);
    
    // Erase element
    vec.erase(vec.begin() + 2);
    
    return 0;
}
```

#### List
- Doubly-linked list implementation
- Efficient insertion and deletion anywhere in the container
- Non-contiguous memory allocation

```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> myList = {10, 20, 30, 40};
    
    // Insert at front and back
    myList.push_front(5);
    myList.push_back(50);
    
    // Traverse the list
    std::cout << "List elements: ";
    for (const auto& element : myList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Insert at specific position
    auto it = myList.begin();
    std::advance(it, 2); // Move iterator to 3rd position
    myList.insert(it, 25);
    
    // Remove element with specific value
    myList.remove(40);
    
    // Sort the list
    myList.sort();
    
    return 0;
}
```

#### Deque
- Double-ended queue
- Efficient insertion/deletion at both ends
- Random access to elements

```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq = {10, 20, 30};
    
    // Insert at both ends
    dq.push_front(5);
    dq.push_back(35);
    
    // Access elements
    std::cout << "Front element: " << dq.front() << std::endl;
    std::cout << "Back element: " << dq.back() << std::endl;
    std::cout << "Element at index 2: " << dq[2] << std::endl;
    
    // Remove from both ends
    dq.pop_front();
    dq.pop_back();
    
    return 0;
}
```

### 1.2 Associative Containers

#### Set
- Collection of unique keys, sorted by keys
- Fast search operations: O(log n) complexity
- Implemented as balanced binary search trees (typically red-black trees)

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> mySet = {50, 20, 60, 10, 30};
    
    // Insertion
    mySet.insert(40);
    
    // Attempting to add duplicate
    auto result = mySet.insert(30);
    if (!result.second) {
        std::cout << "Element 30 already exists!" << std::endl;
    }
    
    // Check if element exists
    if (mySet.find(20) != mySet.end()) {
        std::cout << "Found 20 in set" << std::endl;
    }
    
    // Traversing the set (notice sorted order)
    std::cout << "Set elements: ";
    for (const auto& element : mySet) {
        std::cout << element << " "; // Will print: 10 20 30 40 50 60
    }
    std::cout << std::endl;
    
    // Erase an element
    mySet.erase(30);
    
    return 0;
}
```

#### Map
- Collection of key-value pairs, sorted by keys
- Fast lookup by key with O(log n) complexity
- Each key must be unique

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> ages;
    
    // Insert elements
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages.insert({"Charlie", 35});
    
    // Access elements
    std::cout << "Bob's age: " << ages["Bob"] << std::endl;
    
    // Check if key exists before accessing
    if (ages.find("David") == ages.end()) {
        std::cout << "David not found in map" << std::endl;
    }
    
    // Iterate through map
    std::cout << "Name-Age pairs:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Check size
    std::cout << "Map size: " << ages.size() << std::endl;
    
    // Remove element
    ages.erase("Bob");
    
    return 0;
}
```

#### Multiset and Multimap
- Similar to set and map but allow duplicate keys

```cpp
#include <iostream>
#include <set>
#include <map>
#include <string>

int main() {
    // Multiset example
    std::multiset<int> ms = {10, 20, 10, 30, 20};
    std::cout << "Multiset elements: ";
    for (const auto& elem : ms) {
        std::cout << elem << " "; // Will print: 10 10 20 20 30
    }
    std::cout << std::endl;
    
    // Count occurrences
    std::cout << "Count of 20: " << ms.count(20) << std::endl; // Should print 2
    
    // Multimap example
    std::multimap<std::string, int> grades;
    grades.insert({"Alice", 85});
    grades.insert({"Bob", 90});
    grades.insert({"Alice", 92}); // Same key, different value
    
    std::cout << "Student grades:" << std::endl;
    for (const auto& grade : grades) {
        std::cout << grade.first << ": " << grade.second << std::endl;
    }
    
    return 0;
}
```

### 1.3 Unordered Containers
Introduced in C++11, these are hash table implementations with average O(1) lookup.

#### Unordered Set and Unordered Map

```cpp
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

int main() {
    // Unordered set
    std::unordered_set<int> uset = {10, 15, 5, 20};
    
    // Insert and check
    uset.insert(25);
    if (uset.find(15) != uset.end()) {
        std::cout << "15 is in the set" << std::endl;
    }
    
    // Unordered map
    std::unordered_map<std::string, std::string> capitals;
    capitals["USA"] = "Washington D.C.";
    capitals["France"] = "Paris";
    capitals["Japan"] = "Tokyo";
    
    // Access with error checking
    auto it = capitals.find("Germany");
    if (it != capitals.end()) {
        std::cout << "Capital of Germany: " << it->second << std::endl;
    } else {
        std::cout << "Germany not found in map" << std::endl;
    }
    
    // Display all capitals (order not guaranteed)
    std::cout << "Country capitals:" << std::endl;
    for (const auto& pair : capitals) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    return 0;
}
```

### 1.4 Container Adapters

#### Stack

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> s;
    
    // Push elements
    s.push(10);
    s.push(20);
    s.push(30);
    
    // Check top and size
    std::cout << "Top element: " << s.top() << std::endl;
    std::cout << "Stack size: " << s.size() << std::endl;
    
    // Pop and print elements
    std::cout << "Stack elements (top to bottom): ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    
    return 0;
}
```

#### Queue

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    
    // Add elements
    q.push(10);
    q.push(20);
    q.push(30);
    
    // Check front, back and size
    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Back element: " << q.back() << std::endl;
    std::cout << "Queue size: " << q.size() << std::endl;
    
    // Remove and print elements
    std::cout << "Queue elements (front to back): ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
    
    return 0;
}
```

#### Priority Queue

```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    // Max priority queue (default)
    std::priority_queue<int> pq;
    pq.push(10);
    pq.push(30);
    pq.push(20);
    
    std::cout << "Max priority queue elements: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " "; // Will print: 30 20 10
        pq.pop();
    }
    std::cout << std::endl;
    
    // Min priority queue (using comparison function)
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    min_pq.push(10);
    min_pq.push(30);
    min_pq.push(20);
    
    std::cout << "Min priority queue elements: ";
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << " "; // Will print: 10 20 30
        min_pq.pop();
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 2. Iterators
Iterators provide a way to access the elements of a container sequentially without exposing the underlying implementation.

### 2.1 Iterator Types
- **Input Iterators**: Can be dereferenced to read elements (single-pass reading)
- **Output Iterators**: Can be dereferenced to write elements (single-pass writing)
- **Forward Iterators**: Can be read and written to, and can be incremented (multi-pass reading)
- **Bidirectional Iterators**: Like forward iterators but can also be decremented
- **Random Access Iterators**: Can be moved to any element in constant time

### 2.2 Common Iterator Operations

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <set>

int main() {
    // Vector iterators (Random Access)
    std::vector<int> vec = {10, 20, 30, 40, 50};
    
    // Basic iteration
    std::cout << "Vector elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Random access
    auto vecIt = vec.begin();
    vecIt += 2; // Move to the third element
    std::cout << "Third element: " << *vecIt << std::endl;
    
    // List iterators (Bidirectional)
    std::list<int> lst = {10, 20, 30, 40, 50};
    auto lstIt = lst.begin();
    std::advance(lstIt, 2); // Advance 2 positions
    std::cout << "Third element in list: " << *lstIt << std::endl;
    
    // Bidirectional movement
    ++lstIt; // Move forward
    std::cout << "Fourth element: " << *lstIt << std::endl;
    --lstIt; // Move backward
    std::cout << "Back to third: " << *lstIt << std::endl;
    
    // Const iterators
    std::vector<int> numbers = {1, 2, 3};
    for (auto cit = numbers.cbegin(); cit != numbers.cend(); ++cit) {
        // *cit = 10; // Error: cannot modify through const_iterator
        std::cout << *cit << " ";
    }
    std::cout << std::endl;
    
    // Reverse iterators
    std::cout << "Reverse order: ";
    for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 3. Algorithms
STL provides a rich set of algorithms that work on ranges of elements.

### 3.1 Non-modifying Sequence Operations

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50, 30, 20};
    
    // Count
    int count = std::count(vec.begin(), vec.end(), 30);
    std::cout << "Count of 30: " << count << std::endl;
    
    // Count_if (count even numbers)
    int evenCount = std::count_if(vec.begin(), vec.end(), 
                                 [](int x) { return x % 2 == 0; });
    std::cout << "Count of even numbers: " << evenCount << std::endl;
    
    // Find
    auto it = std::find(vec.begin(), vec.end(), 40);
    if (it != vec.end()) {
        std::cout << "Found 40 at position: " << (it - vec.begin()) << std::endl;
    }
    
    // Find_if (find first number > 35)
    auto it2 = std::find_if(vec.begin(), vec.end(),
                           [](int x) { return x > 35; });
    if (it2 != vec.end()) {
        std::cout << "First number > 35: " << *it2 << std::endl;
    }
    
    // For_each (print each element)
    std::cout << "All elements: ";
    std::for_each(vec.begin(), vec.end(), 
                 [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
    
    return 0;
}
```

### 3.2 Modifying Sequence Operations

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void print_vector(const std::vector<int>& v, const std::string& label) {
    std::cout << label << ": ";
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    print_vector(vec, "Original");
    
    // Transform (multiply each element by 2)
    std::transform(vec.begin(), vec.end(), vec.begin(),
                  [](int x) { return x * 2; });
    print_vector(vec, "After transform (x2)");
    
    // Replace
    std::replace(vec.begin(), vec.end(), 60, 99);
    print_vector(vec, "After replace (60->99)");
    
    // Replace_if (replace elements > 70 with 70)
    std::replace_if(vec.begin(), vec.end(),
                   [](int x) { return x > 70; },
                   70);
    print_vector(vec, "After replace_if (>70 -> 70)");
    
    // Fill
    std::fill(vec.begin() + 2, vec.begin() + 4, 33);
    print_vector(vec, "After fill (pos 2-3 with 33)");
    
    // Generate
    std::vector<int> gen(5);
    int value = 1;
    std::generate(gen.begin(), gen.end(), [&value]() { return value *= 2; });
    print_vector(gen, "After generate (powers of 2)");
    
    // Remove and erase (remove-erase idiom)
    std::vector<int> vec2 = {10, 20, 30, 20, 40, 20, 50};
    print_vector(vec2, "Before removal");
    
    // Remove doesn't change container size, just moves elements
    auto newEnd = std::remove(vec2.begin(), vec2.end(), 20);
    // Erase the "removed" elements
    vec2.erase(newEnd, vec2.end());
    print_vector(vec2, "After remove-erase (20)");
    
    return 0;
}
```

### 3.3 Sorting and Related Operations

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void print_vec(const std::vector<int>& v) {
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {30, 10, 50, 20, 40};
    
    // Sort ascending
    std::sort(vec.begin(), vec.end());
    std::cout << "Sorted (ascending): ";
    print_vec(vec);
    
    // Sort descending
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "Sorted (descending): ";
    print_vec(vec);
    
    // Custom sort
    std::vector<std::string> names = {"Alice", "Bob", "charlie", "David"};
    std::sort(names.begin(), names.end(), 
             [](const std::string& a, const std::string& b) {
                 // Case-insensitive comparison
                 return std::lexicographical_compare(
                     a.begin(), a.end(),
                     b.begin(), b.end(),
                     [](char x, char y) {
                         return std::tolower(x) < std::tolower(y);
                     }
                 );
             });
    
    std::cout << "Names sorted case-insensitive: ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    // Partial sort
    std::vector<int> vec2 = {30, 10, 50, 20, 40, 15, 25};
    std::partial_sort(vec2.begin(), vec2.begin() + 3, vec2.end());
    std::cout << "Partial sorted (first 3): ";
    print_vec(vec2);
    
    // Binary search (requires sorted range)
    std::vector<int> vec3 = {10, 20, 30, 40, 50};
    bool found = std::binary_search(vec3.begin(), vec3.end(), 30);
    std::cout << "Binary search for 30: " << (found ? "Found" : "Not found") << std::endl;
    
    // Lower bound and upper bound
    auto lower = std::lower_bound(vec3.begin(), vec3.end(), 25);
    auto upper = std::upper_bound(vec3.begin(), vec3.end(), 30);
    
    std::cout << "Lower bound of 25: " << *lower << std::endl;
    std::cout << "Upper bound of 30: " << *upper << std::endl;
    
    return 0;
}
```

### 3.4 Numeric Operations

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Accumulate (sum)
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    // Product
    int product = std::accumulate(vec.begin(), vec.end(), 1, 
                                 std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;
    
    // Inner product
    std::vector<int> vec2 = {10, 20, 30, 40, 50};
    int inner_product = std::inner_product(vec.begin(), vec.end(),
                                          vec2.begin(), 0);
    std::cout << "Inner product: " << inner_product << std::endl;
    
    // Partial sum
    std::vector<int> partial_sums(vec.size());
    std::partial_sum(vec.begin(), vec.end(), partial_sums.begin());
    
    std::cout << "Partial sums: ";
    for (int i : partial_sums) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Adjacent difference
    std::vector<int> adj_diff(vec.size());
    std::adjacent_difference(vec.begin(), vec.end(), adj_diff.begin());
    
    std::cout << "Adjacent differences: ";
    for (int i : adj_diff) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 4. Function Objects (Functors)
Function objects are instances of classes that overload the function call operator `()`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Custom functor
class Multiplier {
private:
    int factor;
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> result(vec.size());
    
    // Using the custom functor
    Multiplier mult(3);
    std::transform(vec.begin(), vec.end(), result.begin(), mult);
    
    std::cout << "After multiplication by 3: ";
    for (int i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Using built-in functors
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    
    std::cout << "Sorted in descending order: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 5. Lambda Expressions
Lambda expressions allow you to define anonymous function objects inline.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Basic lambda: filter even numbers
    std::cout << "Even numbers: ";
    std::for_each(vec.begin(), vec.end(), [](int x) {
        if (x % 2 == 0) {
            std::cout << x << " ";
        }
    });
    std::cout << std::endl;
    
    // Lambda with capture
    int threshold = 5;
    auto count = std::count_if(vec.begin(), vec.end(),
                             [threshold](int x) { return x > threshold; });
    std::cout << "Numbers greater than " << threshold << ": " << count << std::endl;
    
    // Lambda with mutable capture
    int sum = 0;
    std::for_each(vec.begin(), vec.end(),
                 [&sum](int x) { sum += x; });
    std::cout << "Sum of all elements: " << sum << std::endl;
    
    // Lambda that captures all variables by reference
    int product = 1;
    std::for_each(vec.begin(), vec.end(),
                 [&](int x) { product *= x; });
    std::cout << "Product of all elements: " << product << std::endl;
    
    // Lambda with return type
    auto transformer = [](int x) -> double { return x * 1.5; };
    std::cout << "5 transformed: " << transformer(5) << std::endl;
    
    return 0;
}
```

## 6. Practice Problems

### Problem 1: Word Frequency Counter

```cpp
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

void count_word_frequency(const std::string& text) {
    std::map<std::string, int> frequency;
    std::istringstream iss(text);
    std::string word;
    
    while (iss >> word) {
        // Convert to lowercase and remove punctuation
        std::transform(word.begin(), word.end(), word.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        word.erase(std::remove_if(word.begin(), word.end(),
                                 [](unsigned char c) { return std::ispunct(c); }),
                  word.end());
        
        if (!word.empty()) {
            ++frequency[word];
        }
    }
    
    // Print results
    std::cout << "Word frequencies:" << std::endl;
    for (const auto& pair : frequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    const std::string text = "The quick brown fox jumps over the lazy dog. "
                            "The fox was quick and brown.";
    count_word_frequency(text);
    return 0;
}
```

### Problem 2: Custom Sort for Student Records

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Student {
    std::string name;
    int age;
    double gpa;
    
    Student(const std::string& n, int a, double g)
        : name(n), age(a), gpa(g) {}
};

void print_students(const std::vector<Student>& students) {
    std::cout << "Student List:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Name\t\tAge\tGPA" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    for (const auto& student : students) {
        std::cout << student.name << "\t";
        if (student.name.length() < 8) std::cout << "\t";
        std::cout << student.age << "\t" << student.gpa << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

int main() {
    std::vector<Student> students = {
        {"Alice", 20, 3.75},
        {"Bob", 22, 3.25},
        {"Charlie", 21, 3.8},
        {"David", 20, 3.5},
        {"Eve", 23, 3.9}
    };
    
    // Sort by name
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.name < b.name;
              });
    
    std::cout << "Sorted by name:" << std::endl;
    print_students(students);
    
    // Sort by age
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.age < b.age;
              });
    
    std::cout << "\nSorted by age:" << std::endl;
    print_students(students);
    
    // Sort by GPA (descending)
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.gpa > b.gpa;
              });
    
    std::cout << "\nSorted by GPA (highest first):" << std::endl;
    print_students(students);
    
    return 0;
}
```

## 7. Tips and Best Practices

1. **Choose the Right Container:**
   - Use `vector` for dynamic arrays with fast random access
   - Use `list` for frequent insertions/deletions in the middle
   - Use `map`/`set` for key-based lookup with ordering
   - Use `unordered_map`/`unordered_set` for faster key-based lookup without ordering

2. **Prefer STL Algorithms:**
   - Use STL algorithms instead of writing your own loops
   - They are optimized, tested, and express intent clearly

3. **Use Iterator Invalidation Awareness:**
   - Operations like insertion or erasure can invalidate iterators
   - Always update your iterators after container-modifying operations

4. **Range-based for Loops:**
   - Use modern range-based for loops when iterating through containers
   ```cpp
   for (const auto& element : container) {
       // Process element
   }
   ```

5. **Use Auto When Appropriate:**
   - Use `auto` for complex iterator types to improve code readability
   - But don't overuse it to the point where types become unclear

6. **Prefer Algorithm Composition:**
   - Combine algorithms rather than writing complex loops
   - Use lambdas to customize algorithm behavior

7. **Consider Memory Management:**
   - Be aware of copy operations with large containers
   - Consider using references and move semantics to avoid unnecessary copies

## 8. Further Resources

1. [C++ Reference](https://en.cppreference.com/w/cpp/container)
2. [C++ STL Tutorials](https://www.cplusplus.com/reference/stl/)
3. [Effective STL by Scott Meyers](https://www.amazon.com/Effective-STL-Specific-Standard-Template/dp/0201749629)
4. [LeetCode STL Practice](https://leetcode.com/)