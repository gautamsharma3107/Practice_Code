# Chapter 8: Standard Template Library (STL) (Part 3)

## 8.3 Iterators

Iterators are one of the most important concepts in the STL. They act as the "glue" between containers and algorithms, providing a uniform way to access elements in containers regardless of their internal structure.

### What Are Iterators?

Iterators are objects that behave like pointers, providing a way to traverse through the elements in a container. They abstract the specifics of how a container stores its elements, allowing algorithms to work with any container that provides the required iterators.

### Iterator Categories

STL defines several categories of iterators, each with different capabilities:

1. **Input Iterators**: Read-only, single-pass traversal (e.g., `istream_iterator`)
2. **Output Iterators**: Write-only, single-pass traversal (e.g., `ostream_iterator`)
3. **Forward Iterators**: Read/write, single-direction traversal, multi-pass (e.g., `forward_list` iterators)
4. **Bidirectional Iterators**: Read/write, bidirectional traversal (e.g., `list`, `set` iterators)
5. **Random Access Iterators**: Read/write, arbitrary access (e.g., `vector`, `deque` iterators)
6. **Contiguous Iterators** (C++17): Random access with contiguous memory guarantee (e.g., `vector` iterators)

Each category is a superset of the capabilities of the previous categories.

Here's a table showing which containers provide which types of iterators:

| Container          | Iterator Type      |
|--------------------|-------------------|
| `vector`           | Random Access (Contiguous) |
| `array`            | Random Access (Contiguous) |
| `deque`            | Random Access     |
| `list`             | Bidirectional     |
| `forward_list`     | Forward           |
| `set`/`multiset`   | Bidirectional     |
| `map`/`multimap`   | Bidirectional     |
| `unordered_*`      | Forward           |

### Basic Iterator Operations

All iterators support these basic operations:

- Dereferencing: `*iter` (access element)
- Increment: `++iter` (move to next element)
- Copy/assignment: `iter1 = iter2`
- Comparison: `iter1 == iter2`, `iter1 != iter2`

More advanced iterators support additional operations:

- Bidirectional: `--iter` (move to previous element)
- Random Access: `iter + n`, `iter - n`, `iter[n]`, `iter1 - iter2`, `iter1 < iter2`

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;

int main() {
    // Using iterators with vector (random access)
    vector<int> nums = {10, 20, 30, 40, 50};
    
    cout << "Vector using iterators:" << endl;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " ";  // Dereferencing to get value
    }
    cout << endl;
    
    // Random access operations (only for random access iterators)
    auto it = nums.begin();
    cout << "Vector - Third element using random access: " << *(it + 2) << endl;
    cout << "Vector - Second element using subscript: " << it[1] << endl;
    
    // Using iterators with list (bidirectional)
    list<int> myList = {5, 15, 25, 35, 45};
    
    cout << "\nList using iterators:" << endl;
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Bidirectional iteration - going backwards
    cout << "List in reverse:" << endl;
    auto listEnd = myList.end();
    auto listIt = myList.end();
    do {
        --listIt;
        cout << *listIt << " ";
    } while (listIt != myList.begin());
    cout << endl;
    
    // Set with bidirectional iterators
    set<char> chars = {'a', 'b', 'c', 'd', 'e'};
    
    cout << "\nSet using iterators:" << endl;
    for (auto it = chars.begin(); it != chars.end(); ++it) {
        cout << *it << " ";
        // *it = 'z';  // Error - set iterators are const
    }
    cout << endl;
    
    return 0;
}
```

### Iterator Functions and Utilities

STL provides several utility functions for working with iterators:

```cpp
#include <iostream>
#include <vector>
#include <iterator>  // For iterator utilities
using namespace std;

int main() {
    vector<int> nums = {10, 20, 30, 40, 50, 60, 70};
    
    // advance() - moves iterator forward or backward
    auto it1 = nums.begin();
    advance(it1, 3);  // Move forward 3 positions
    cout << "After advance(3): " << *it1 << endl;  // 40
    
    // next(), prev() - returns iterator to next/previous positions
    auto it2 = next(it1, 2);  // Iterator 2 positions after it1
    cout << "next(it1, 2): " << *it2 << endl;  // 60
    
    auto it3 = prev(it1, 1);  // Iterator 1 position before it1
    cout << "prev(it1, 1): " << *it3 << endl;  // 30
    
    // distance() - returns distance between iterators
    cout << "Distance from begin to it1: " 
         << distance(nums.begin(), it1) << endl;  // 3
    
    // Iterate with specific step
    cout << "Iterating with step 2: ";
    for (auto it = nums.begin(); it != nums.end(); advance(it, 2)) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Special Iterator Types

STL provides several special iterator types for specific purposes:

#### Reverse Iterators

Reverse iterators traverse a container in reverse order. They're created using `rbegin()` and `rend()` container methods:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {10, 20, 30, 40, 50};
    
    cout << "Forward iteration: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "Reverse iteration with reverse_iterator: ";
    for (auto rit = nums.rbegin(); rit != nums.rend(); ++rit) {
        cout << *rit << " ";  // 50 40 30 20 10
    }
    cout << endl;
    
    // Converting between normal and reverse iterators
    auto it = nums.begin() + 2;  // Points to 30
    vector<int>::reverse_iterator rit(it);
    cout << "it points to: " << *it << endl;          // 30
    cout << "rit points to: " << *rit << endl;        // 20 (previous element)
    cout << "rit.base() points to: " << *rit.base() << endl;  // 30
    
    return 0;
}
```

#### Const Iterators

Const iterators prevent modification of the elements they point to:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {10, 20, 30, 40, 50};
    
    // Non-const iterator - can modify elements
    auto it = nums.begin();
    *it = 100;  // OK - modifies the first element
    
    // Const iterator - can't modify elements
    auto cit = nums.cbegin();  // or const_iterator cit = nums.begin();
    // *cit = 200;  // Error: assignment of read-only location
    
    cout << "Vector after modification: ";
    for (const auto& num : nums) {
        cout << num << " ";  // 100 20 30 40 50
    }
    cout << endl;
    
    return 0;
}
```

#### Insert Iterators

Insert iterators convert assignment operations into insertions:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>  // For copy
#include <iterator>   // For insert iterators
using namespace std;

int main() {
    vector<int> source = {10, 20, 30, 40, 50};
    
    // back_inserter - inserts at the end using push_back
    vector<int> dest1;
    copy(source.begin(), source.end(), back_inserter(dest1));
    
    // front_inserter - inserts at the beginning using push_front (not available for vector)
    list<int> dest2;
    copy(source.begin(), source.end(), front_inserter(dest2));
    
    // inserter - inserts at a specific position
    vector<int> dest3 = {1, 2, 3};
    copy(source.begin(), source.end(), inserter(dest3, dest3.begin() + 1));
    
    // Display results
    cout << "Source: ";
    for (int n : source) cout << n << " ";
    cout << endl;
    
    cout << "dest1 (back_inserter): ";
    for (int n : dest1) cout << n << " ";
    cout << endl;
    
    cout << "dest2 (front_inserter): ";
    for (int n : dest2) cout << n << " ";
    cout << endl;
    
    cout << "dest3 (inserter): ";
    for (int n : dest3) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

#### Stream Iterators

Stream iterators allow STL algorithms to work directly with input/output streams:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>   // For stream iterators
using namespace std;

int main() {
    // Writing to output stream
    vector<int> nums = {10, 20, 30, 40, 50};
    
    cout << "Vector contents: ";
    copy(nums.begin(), nums.end(), 
         ostream_iterator<int>(cout, " "));
    cout << endl;
    
    // Reading from input stream
    cout << "Enter integers (Ctrl+Z or Ctrl+D to end): ";
    vector<int> input;
    copy(istream_iterator<int>(cin), istream_iterator<int>(),
         back_inserter(input));
    
    cout << "You entered: ";
    copy(input.begin(), input.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
    
    // Using stream iterators for calculations
    cout << "Sum: " << accumulate(input.begin(), input.end(), 0) << endl;
    
    return 0;
}
```

### Iterator Invalidation

Iterator invalidation occurs when a container operation makes existing iterators invalid. Understanding when this happens is crucial for safe code:

```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    // Vector iterator invalidation
    vector<int> vec = {10, 20, 30, 40, 50};
    auto vecIt = vec.begin() + 2;  // Points to 30
    
    cout << "Before insertion: *vecIt = " << *vecIt << endl;
    
    // This insertion might invalidate all iterators if reallocation occurs
    vec.insert(vec.begin(), 5);
    
    // Using vecIt after insertion could cause undefined behavior
    // cout << "After insertion: *vecIt = " << *vecIt << endl;  // Dangerous!
    
    // Instead, get a new iterator
    vecIt = vec.begin() + 3;  // Points to 30 again
    cout << "After reacquiring iterator: *vecIt = " << *vecIt << endl;
    
    // List iterators are more stable - only invalidated when their actual element is removed
    list<int> lst = {10, 20, 30, 40, 50};
    auto lstIt = next(lst.begin(), 2);  // Points to 30
    
    cout << "\nList before insertion: *lstIt = " << *lstIt << endl;
    
    // This doesn't invalidate lstIt since the element it points to isn't affected
    lst.insert(lst.begin(), 5);
    
    cout << "List after insertion: *lstIt = " << *lstIt << endl;  // Still valid!
    
    // Removing the element pointed to by lstIt would invalidate it
    auto toRemove = lstIt;
    ++lstIt;  // Move to next element before removing
    lst.erase(toRemove);
    
    cout << "List after erasing 30, lstIt now points to: " << *lstIt << endl;
    
    return 0;
}
```

### Writing Iterator-Safe Code

To write iterator-safe code, follow these guidelines:

1. **Refresh iterators after container modifications**:
   ```cpp
   auto it = container.begin();
   container.insert(/* ... */);
   it = container.begin();  // Refresh iterator
   ```

2. **Store indices instead of iterators** when heavy modification is expected:
   ```cpp
   size_t index = 3;
   container.insert(/* ... */);
   auto it = container.begin() + index;  // Recalculate iterator
   ```

3. **Use returned iterators** from modifying operations:
   ```cpp
   // erase() returns iterator to element after the erased one
   it = container.erase(it);  // No need to increment
   ```

4. **Be aware of container-specific behaviors**:
   - `vector`/`deque`: Insertions/removals invalidate iterators to elements after the modification point
   - `list`/`forward_list`: Insertions/removals only invalidate iterators pointing to affected elements
   - Associative containers: Insertions/removals don't invalidate iterators except to the erased elements

### Custom Iterator Implementation

Understanding how iterators work internally can be valuable. Here's a simple example of implementing your own iterator:

```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Simple container with custom iterator
class IntArray {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    IntArray(size_t n) : size(n) {
        data = new int[size]();  // Initialize with zeros
    }
    
    // Destructor
    ~IntArray() {
        delete[] data;
    }
    
    // Get value at index
    int& at(size_t index) {
        if (index >= size) throw out_of_range("Index out of bounds");
        return data[index];
    }
    
    // Get size
    size_t getSize() const {
        return size;
    }
    
    // Custom iterator class
    class Iterator {
    private:
        int* ptr;
        
    public:
        // Iterator traits
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = ptrdiff_t;
        using pointer = int*;
        using reference = int&;
        
        // Constructor
        Iterator(int* p) : ptr(p) {}
        
        // Dereference
        int& operator*() const {
            return *ptr;
        }
        
        // Increment (prefix)
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        // Increment (postfix)
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        // Decrement (prefix)
        Iterator& operator--() {
            --ptr;
            return *this;
        }
        
        // Decrement (postfix)
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        
        // Addition
        Iterator operator+(difference_type n) const {
            return Iterator(ptr + n);
        }
        
        // Subtraction
        Iterator operator-(difference_type n) const {
            return Iterator(ptr - n);
        }
        
        // Distance between iterators
        difference_type operator-(const Iterator& other) const {
            return ptr - other.ptr;
        }
        
        // Equality comparison
        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }
        
        // Inequality comparison
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };
    
    // Iterator factory methods
    Iterator begin() {
        return Iterator(data);
    }
    
    Iterator end() {
        return Iterator(data + size);
    }
};

int main() {
    IntArray arr(5);
    
    // Initialize with values
    for (size_t i = 0; i < arr.getSize(); ++i) {
        arr.at(i) = i * 10;
    }
    
    // Use our custom iterator
    cout << "Array elements: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Test random access
    auto it = arr.begin();
    it = it + 3;
    cout << "Element at position 3: " << *it << endl;
    
    // Test range-based for loop (requires begin/end)
    cout << "Using range-based for loop: ";
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Best Practices for Using Iterators

1. **Prefer high-level iteration** when possible:
   ```cpp
   // Modern, safer approach
   for (const auto& item : container) { /* ... */ }
   
   // Traditional, more explicit approach
   for (auto it = container.begin(); it != container.end(); ++it) { /* ... */ }
   ```

2. **Use appropriate iterator types**:
   - Use `const_iterator`/`cbegin()` when you don't need to modify elements
   - Use reverse iterators (`rbegin()`/`rend()`) for backwards traversal

3. **Check validity before dereferencing**:
   ```cpp
   auto it = container.find(value);
   if (it != container.end()) {
       // Only dereference valid iterators
       process(*it);
   }
   ```

4. **Update iterators after container modifications**

5. **Understand the iterator requirements of algorithms**:
   - Some algorithms require only input/forward iterators
   - Others need bidirectional or random access

6. **Use iterator utilities** like `advance()`, `next()`, `prev()`, and `distance()`

7. **Be mindful of iterator invalidation rules** for each container

## 8.4 Algorithms (sort, find, count, etc.)

The STL algorithms library provides a large collection of functions that operate on ranges of elements defined by iterators. These algorithms are both efficient and generic, working with any container type that provides the required iterators.

### Algorithm Categories

STL algorithms can be broadly categorized as:

1. **Non-modifying sequence operations**: Don't change the elements or their order
2. **Modifying sequence operations**: Change elements or their order
3. **Sorting and related operations**: Sort, merge, partition, etc.
4. **Binary search operations**: Search in sorted sequences
5. **Set operations**: Operations on sorted ranges
6. **Numeric operations**: Mathematical operations

### Non-Modifying Algorithms

These algorithms don't modify the elements in the container:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // find - returns iterator to first occurrence of value
    auto it = find(nums.begin(), nums.end(), 5);
    if (it != nums.end()) {
        cout << "Found 5 at index: " << distance(nums.begin(), it) << endl;
    }
    
    // find_if - finds element satisfying predicate
    auto even = find_if(nums.begin(), nums.end(), 
                       [](int n){ return n % 2 == 0; });
    if (even != nums.end()) {
        cout << "First even number: " << *even << endl;
    }
    
    // count - counts occurrences of value
    int count_5 = count(nums.begin(), nums.end(), 5);
    cout << "Number 5 appears " << count_5 << " times" << endl;
    
    // count_if - counts elements satisfying predicate
    int num_even = count_if(nums.begin(), nums.end(), 
                          [](int n){ return n % 2 == 0; });
    cout << "Number of even values: " << num_even << endl;
    
    // all_of, any_of, none_of - check conditions
    bool all_positive = all_of(nums.begin(), nums.end(), 
                            [](int n){ return n > 0; });
    cout << "All positive: " << boolalpha << all_positive << endl;
    
    bool any_greater_than_5 = any_of(nums.begin(), nums.end(),
                                 [](int n){ return n > 5; });
    cout << "Any greater than 5: " << any_greater_than_5 << endl;
    
    bool none_negative = none_of(nums.begin(), nums.end(), 
                              [](int n){ return n < 0; });
    cout << "None negative: " << none_negative << endl;
    
    // for_each - applies function to each element
    cout << "Elements: ";
    for_each(nums.begin(), nums.end(), 
            [](int n){ cout << n << " "; });
    cout << endl;
    
    // min_element, max_element - finds min/max element
    auto min_it = min_element(nums.begin(), nums.end());
    auto max_it = max_element(nums.begin(), nums.end());
    cout << "Min: " << *min_it << ", Max: " << *max_it << endl;
    
    // minmax_element - finds both min and max
    auto [min_it2, max_it2] = minmax_element(nums.begin(), nums.end());
    cout << "Min: " << *min_it2 << ", Max: " << *max_it2 << endl;
    
    // accumulate - computes sum or applies binary operation
    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum: " << sum << endl;
    
    int product = accumulate(nums.begin(), nums.end(), 1, 
                          [](int a, int b){ return a * b; });
    cout << "Product: " << product << endl;
    
    // adjacent_find - finds equal adjacent elements
    auto adjacent = adjacent_find(nums.begin(), nums.end());
    if (adjacent != nums.end()) {
        cout << "First adjacent equal elements: " << *adjacent 
             << " and " << *(adjacent + 1) << endl;
    }
    
    return 0;
}
```

### Modifying Algorithms

These algorithms modify container elements or their order:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void print_vector(const vector<T>& v, const string& label) {
    cout << label << ": ";
    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    print_vector(nums, "Original");
    
    // copy - copies elements to another container
    vector<int> copy_dest(nums.size());
    copy(nums.begin(), nums.end(), copy_dest.begin());
    print_vector(copy_dest, "Copy");
    
    // copy_if - copies elements satisfying predicate
    vector<int> even_numbers;
    copy_if(nums.begin(), nums.end(), back_inserter(even_numbers),
           [](int n){ return n % 2 == 0; });
    print_vector(even_numbers, "Even numbers");
    
    // transform - applies function to each element
    vector<int> transformed(nums.size());
    transform(nums.begin(), nums.end(), transformed.begin(),
             [](int n){ return n * n; });
    print_vector(transformed, "Squared");
    
    // transform with two input sequences
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2 = {10, 20, 30, 40, 50};
    vector<int> sum_vec(vec1.size());
    
    transform(vec1.begin(), vec1.end(), vec2.begin(), 
              sum_vec.begin(), plus<int>());
    print_vector(sum_vec, "vec1 + vec2");
    
    // fill - fills range with value
    vector<int> filled(5);
    fill(filled.begin(), filled.end(), 42);
    print_vector(filled, "Filled with 42");
    
    // fill_n - fills n elements with value
    vector<int> partial_fill(10);
    fill_n(partial_fill.begin(), 5, 99);
    print_vector(partial_fill, "First 5 elements filled with 99");
    
    // generate - fills range with values from generator function
    vector<int> generated(5);
    int value = 1;
    generate(generated.begin(), generated.end(), 
            [&value]() { return value *= 2; });
    print_vector(generated, "Generated powers of 2");
    
    // replace - replaces values
    vector<int> replaced = nums;
    replace(replaced.begin(), replaced.end(), 1, 99);
    print_vector(replaced, "Replaced 1 with 99");
    
    // replace_if - replaces values satisfying predicate
    vector<int> replaced_if = nums;
    replace_if(replaced_if.begin(), replaced_if.end(),
              [](int n){ return n % 2 == 0; }, 0);
    print_vector(replaced_if, "Replaced even numbers with 0");
    
    // remove and erase-remove idiom
    vector<int> to_remove = nums;
    print_vector(to_remove, "Before remove");
    
    // Remove doesn't change vector size, it moves unwanted elements to end
    auto new_end = remove(to_remove.begin(), to_remove.end(), 1);
    to_remove.erase(new_end, to_remove.end());  // Actually remove
    print_vector(to_remove, "After removing 1");
    
    // remove_if - removes elements satisfying predicate
    vector<int> remove_if_vec = nums;
    remove_if_vec.erase(
        remove_if(remove_if_vec.begin(), remove_if_vec.end(),
                 [](int n){ return n < 3; }),
        remove_if_vec.end()
    );
    print_vector(remove_if_vec, "After removing elements < 3");
    
    // unique - removes consecutive duplicates
    vector<int> with_dups = {1, 1, 2, 2, 2, 3, 3, 1, 1, 4};
    print_vector(with_dups, "With duplicates");
    
    with_dups.erase(unique(with_dups.begin(), with_dups.end()),
                   with_dups.end());
    print_vector(with_dups, "After removing consecutive duplicates");
    
    // reverse - reverses element order
    vector<int> to_reverse = {1, 2, 3, 4, 5};
    reverse(to_reverse.begin(), to_reverse.end());
    print_vector(to_reverse, "Reversed");
    
    // rotate - rotates elements
    vector<int> to_rotate = {1, 2, 3, 4, 5, 6, 7};
    rotate(to_rotate.begin(), to_rotate.begin() + 3, to_rotate.end());
    print_vector(to_rotate, "Rotated (moved first 3 elements to end)");
    
    // shuffle - randomly shuffles elements
    vector<int> to_shuffle = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    random_device rd;
    mt19937 g(rd());  // Random generator
    shuffle(to_shuffle.begin(), to_shuffle.end(), g);
    print_vector(to_shuffle, "Shuffled");
    
    // swap_ranges - swaps elements between ranges
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {6, 7, 8, 9, 10};
    swap_ranges(v1.begin(), v1.end(), v2.begin());
    print_vector(v1, "v1 after swap");
    print_vector(v2, "v2 after swap");
    
    return 0;
}
```

### Sorting and Related Algorithms

Sorting algorithms arrange elements in a specific order:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>  // For greater<>
using namespace std;

template<typename T>
void print_vector(const vector<T>& v, const string& label) {
    cout << label << ": ";
    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    print_vector(nums, "Original");
    
    // sort - sorts elements (quicksort-like algorithm)
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());
    print_vector(sorted, "Sorted ascending");
    
    // sort in descending order
    vector<int> sorted_desc = nums;
    sort(sorted_desc.begin(), sorted_desc.end(), greater<int>());
    print_vector(sorted_desc, "Sorted descending");
    
    // Custom sort comparator
    vector<int> custom_sort = nums;
    sort(custom_sort.begin(), custom_sort.end(),
        [](int a, int b) { return abs(a - 5) < abs(b - 5); });
    print_vector(custom_sort, "Sorted by distance from 5");
    
    // stable_sort - preserves relative order of equal elements
    vector<pair<int, char>> pairs = {
        {2, 'a'}, {1, 'b'}, {2, 'c'}, {1, 'd'}, {3, 'e'}
    };
    
    stable_sort(pairs.begin(), pairs.end(),
               [](auto& p1, auto& p2) { return p1.first < p2.first; });
    
    cout << "Stable sorted pairs: ";
    for (const auto& p : pairs) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    
    // partial_sort - sorts part of range
    vector<int> partial = nums;
    partial_sort(partial.begin(), partial.begin() + 4, partial.end());
    print_vector(partial, "First 4 elements sorted");
    
    // nth_element - partially sorts so that nth element is in correct position
    vector<int> nth = nums;
    auto middle = nth.begin() + nth.size() / 2;
    nth_element(nth.begin(), middle, nth.end());
    print_vector(nth, "After nth_element (median)");
    cout << "Median: " << *middle << endl;
    
    // partition - separates elements that satisfy predicate
    vector<int> to_partition = nums;
    auto partition_point = partition(to_partition.begin(), to_partition.end(),
                                   [](int n) { return n % 2 == 0; });
    
    cout << "Even elements: ";
    for (auto it = to_partition.begin(); it != partition_point; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "Odd elements: ";
    for (auto it = partition_point; it != to_partition.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // is_sorted - checks if range is sorted
    bool sorted_check = is_sorted(sorted.begin(), sorted.end());
    cout << "Is 'sorted' sorted? " << boolalpha << sorted_check << endl;
    
    // merge - merges two sorted ranges
    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2 = {2, 4, 6, 8, 10};
    vector<int> merged(v1.size() + v2.size());
    
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), merged.begin());
    print_vector(merged, "Merged sorted ranges");
    
    // inplace_merge - merges two consecutive sorted ranges in-place
    vector<int> to_inplace_merge = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    auto middle_point = to_inplace_merge.begin() + 5;
    inplace_merge(to_inplace_merge.begin(), middle_point, to_inplace_merge.end());
    print_vector(to_inplace_merge, "After inplace_merge");
    
    return 0;
}
```

### Binary Search Algorithms

These algorithms work efficiently on sorted ranges:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Create a sorted vector
    vector<int> sorted = {10, 20, 30, 30, 30, 40, 50, 60, 70};
    
    // binary_search - checks if element exists (returns bool)
    bool has30 = binary_search(sorted.begin(), sorted.end(), 30);
    bool has35 = binary_search(sorted.begin(), sorted.end(), 35);
    
    cout << "Contains 30: " << boolalpha << has30 << endl;
    cout << "Contains 35: " << has35 << endl;
    
    // lower_bound - returns iterator to first element >= value
    auto lb = lower_bound(sorted.begin(), sorted.end(), 30);
    cout << "Lower bound of 30 is at index: " 
         << distance(sorted.begin(), lb) << endl;
    
    // upper_bound - returns iterator to first element > value
    auto ub = upper_bound(sorted.begin(), sorted.end(), 30);
    cout << "Upper bound of 30 is at index: " 
         << distance(sorted.begin(), ub) << endl;
    
    // equal_range - returns pair of iterators defining the range of equal elements
    auto [first, last] = equal_range(sorted.begin(), sorted.end(), 30);
    cout << "Range of 30s is from index " 
         << distance(sorted.begin(), first) << " to " 
         << distance(sorted.begin(), last) << endl;
    
    cout << "Count of 30s: " << distance(first, last) << endl;
    
    // Binary search with custom comparison
    vector<pair<string, int>> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 95}, {"David", 80}
    };
    
    // Sort by score descending, then by name ascending
    sort(scores.begin(), scores.end(), 
        [](const auto& a, const auto& b) {
            if (a.second != b.second) {
                return a.second > b.second;  // Higher score first
            }
            return a.first < b.first;  // Same score, alphabetical by name
        });
    
    cout << "\nScores (sorted):" << endl;
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    // Search for score >= 90
    auto it = lower_bound(scores.begin(), scores.end(), 90,
                       [](const auto& a, int value) {
                           return a.second > value;  // Reversed comparison
                       });
    
    cout << "\nStudents with score >= 90:" << endl;
    while (it != scores.end() && it->second >= 90) {
        cout << it->first << ": " << it->second << endl;
        ++it;
    }
    
    return 0;
}
```

### Set Operations on Sorted Ranges

These algorithms perform set operations on sorted ranges:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template<typename Container>
void print_container(const Container& c, const string& label) {
    cout << label << ": ";
    for (const auto& item : c) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    // Two sorted sets
    vector<int> set1 = {1, 2, 3, 4, 5, 5, 6};
    vector<int> set2 = {4, 5, 5, 6, 7, 8};
    
    print_container(set1, "Set 1");
    print_container(set2, "Set 2");
    
    // includes - checks if one range includes another
    bool set2_in_set1 = includes(set1.begin(), set1.end(), 
                              set2.begin(), set2.end());
    bool fourToSix_in_set1 = includes(set1.begin(), set1.end(), 
                                     set2.begin(), set2.begin() + 3);
    
    cout << "Set 2 is contained in Set 1: " << boolalpha << set2_in_set1 << endl;
    cout << "Range [4,5,5] is contained in Set 1: " << fourToSix_in_set1 << endl;
    
    // set_union - elements in either set
    vector<int> set_union;
    set_union(set1.begin(), set1.end(), 
              set2.begin(), set2.end(),
              back_inserter(set_union));
    print_container(set_union, "Union");
    
    // set_intersection - elements in both sets
    vector<int> set_intersection;
    set_intersection(set1.begin(), set1.end(),
                    set2.begin(), set2.end(),
                    back_inserter(set_intersection));
    print_container(set_intersection, "Intersection");
    
    // set_difference - elements in first set but not in second
    vector<int> set_difference1;
    set_difference(set1.begin(), set1.end(),
                  set2.begin(), set2.end(),
                  back_inserter(set_difference1));
    print_container(set_difference1, "Set1 - Set2");
    
    vector<int> set_difference2;
    set_difference(set2.begin(), set2.end(),
                  set1.begin(), set1.end(),
                  back_inserter(set_difference2));
    print_container(set_difference2, "Set2 - Set1");
    
    // set_symmetric_difference - elements in either set but not in both
    vector<int> sym_diff;
    set_symmetric_difference(set1.begin(), set1.end(),
                            set2.begin(), set2.end(),
                            back_inserter(sym_diff));
    print_container(sym_diff, "Symmetric Difference");
    
    return 0;
}
```

### Numeric Algorithms

Numeric algorithms are specialized for mathematical operations:

```cpp
#include <iostream>
#include <vector>
#include <numeric>  // For numeric algorithms
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    
    // accumulate - computes sum or applies binary operation
    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum: " << sum << endl;
    
    // Accumulate with custom binary operation
    int product = accumulate(nums.begin(), nums.end(), 1, 
                          multiplies<int>());
    cout << "Product: " << product << endl;
    
    // inner_product - computes dot product or custom combination
    vector<int> weights = {2, 1, 3, 2, 1};
    int dot_product = inner_product(nums.begin(), nums.end(),
                                  weights.begin(), 0);
    cout << "Weighted sum: " << dot_product << endl;
    
    // Custom inner product (sum of absolute differences)
    int abs_diff_sum = inner_product(nums.begin(), nums.end(),
                                   weights.begin(), 0,
                                   plus<int>(),
                                   [](int a, int b) { return abs(a - b); });
    cout << "Sum of absolute differences: " << abs_diff_sum << endl;
    
    // adjacent_difference - computes difference between adjacent elements
    vector<int> diffs(nums.size());
    adjacent_difference(nums.begin(), nums.end(), diffs.begin());
    
    cout << "Adjacent differences: ";
    for (int diff : diffs) {
        cout << diff << " ";
    }
    cout << endl;
    
    // Custom adjacent difference (sum of adjacent elements)
    vector<int> adjacent_sums(nums.size());
    adjacent_difference(nums.begin(), nums.end(), adjacent_sums.begin(),
                      plus<int>());
    
    cout << "Adjacent sums: ";
    for (int sum : adjacent_sums) {
        cout << sum << " ";
    }
    cout << endl;
    
    // partial_sum - computes running sum
    vector<int> running_sum(nums.size());
    partial_sum(nums.begin(), nums.end(), running_sum.begin());
    
    cout << "Running sum: ";
    for (int sum : running_sum) {
        cout << sum << " ";
    }
    cout << endl;
    
    // Custom partial sum (running product)
    vector<int> running_product(nums.size());
    partial_sum(nums.begin(), nums.end(), running_product.begin(),
               multiplies<int>());
    
    cout << "Running product: ";
    for (int prod : running_product) {
        cout << prod << " ";
    }
    cout << endl;
    
    // iota - fills range with sequential values
    vector<int> seq(10);
    iota(seq.begin(), seq.end(), 1);  // Start from 1
    
    cout << "Sequence: ";
    for (int n : seq) {
        cout << n << " ";
    }
    cout << endl;
    
    // reduce - parallel version of accumulate (C++17)
    // int parallel_sum = reduce(execution::par, nums.begin(), nums.end(), 0);
    // cout << "Parallel sum: " << parallel_sum << endl;
    
    return 0;
}
```

### Algorithm Complexity and Performance

Understanding algorithm time complexity helps choose the right one for your task:

| Algorithm | Time Complexity | Space Complexity | Notes |
|----------|----------------|-----------------|-------|
| `find`, `count` | O(n) | O(1) | Linear search |
| `binary_search` | O(log n) | O(1) | Requires sorted input |
| `sort` | O(n log n) | O(log n) | Typically QuickSort/IntroSort |
| `stable_sort` | O(n log n) | O(n) | Typically MergeSort |
| `partial_sort` | O(n log k) | O(k) | k = position of element |
| `nth_element` | O(n) | O(1) | Linear average time |
| `min_element`/`max_element` | O(n) | O(1) | Single pass |
| `accumulate` | O(n) | O(1) | Linear traversal |

### Parallel Algorithms (C++17)

C++17 introduced parallel versions of many algorithms:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <execution>  // For parallel execution policies
using namespace std;
using namespace chrono;

int main() {
    // Create a large vector for testing
    vector<int> large_vec(10'000'000);
    iota(large_vec.begin(), large_vec.end(), 0);  // Fill with 0...n
    shuffle(large_vec.begin(), large_vec.end(), mt19937{random_device{}()});
    
    cout << "Testing sort performance with 10 million elements:" << endl;
    
    // Sequential sort
    auto seq_vec = large_vec;
    auto start = high_resolution_clock::now();
    sort(execution::seq, seq_vec.begin(), seq_vec.end());
    auto end = high_resolution_clock::now();
    auto seq_time = duration_cast<milliseconds>(end - start).count();
    cout << "Sequential sort: " << seq_time << " ms" << endl;
    
    // Parallel sort
    auto par_vec = large_vec;
    start = high_resolution_clock::now();
    sort(execution::par, par_vec.begin(), par_vec.end());
    end = high_resolution_clock::now();
    auto par_time = duration_cast<milliseconds>(end - start).count();
    cout << "Parallel sort: " << par_time << " ms" << endl;
    
    // Parallel unsequenced sort
    auto par_unseq_vec = large_vec;
    start = high_resolution_clock::now();
    sort(execution::par_unseq, par_unseq_vec.begin(), par_unseq_vec.end());
    end = high_resolution_clock::now();
    auto par_unseq_time = duration_cast<milliseconds>(end - start).count();
    cout << "Parallel unsequenced sort: " << par_unseq_time << " ms" << endl;
    
    // Verify all results are the same
    bool same_results = equal(seq_vec.begin(), seq_vec.end(), 
                             par_vec.begin()) &&
                       equal(seq_vec.begin(), seq_vec.end(), 
                             par_unseq_vec.begin());
    cout << "All sorted results match: " << boolalpha << same_results << endl;
    
    return 0;
}
```

### Real-World Algorithm Examples

#### Example 1: Finding Most Frequent Words

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>  // for isalpha
using namespace std;

// Function to count word frequencies and return top k most frequent
vector<pair<string, int>> top_k_frequent_words(const string& text, int k) {
    // Tokenize text into words
    vector<string> words;
    string word;
    for (char c : text) {
        if (isalpha(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    
    // Count frequencies
    map<string, int> freq;
    for (const string& w : words) {
        freq[w]++;
    }
    
    // Convert to vector of pairs for sorting
    vector<pair<string, int>> word_counts(freq.begin(), freq.end());
    
    // Sort by frequency (descending) and alphabetically for ties
    sort(word_counts.begin(), word_counts.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second || 
                  (a.second == b.second && a.first < b.first);
        });
    
    // Return top k
    if (word_counts.size() > k) {
        word_counts.resize(k);
    }
    
    return word_counts;
}

int main() {
    string text = "To be, or not to be, that is the question: "
                 "Whether 'tis nobler in the mind to suffer "
                 "The slings and arrows of outrageous fortune, "
                 "Or to take Arms against a Sea of troubles, "
                 "And by opposing end them.";
    
    int k = 5;
    auto result = top_k_frequent_words(text, k);
    
    cout << "Top " << k << " most frequent words:" << endl;
    for (const auto& [word, count] : result) {
        cout << word << ": " << count << endl;
    }
    
    return 0;
}
```

#### Example 2: Custom Sorting Algorithm

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
    string name;
    double gpa;
    int age;
    
    // For display
    friend ostream& operator<<(ostream& os, const Student& s) {
        return os << s.name << " (GPA: " << s.gpa << ", Age: " << s.age << ")";
    }
};

int main() {
    vector<Student> students = {
        {"Alice", 3.9, 22},
        {"Bob", 3.7, 21},
        {"Charlie", 3.9, 23},
        {"David", 3.5, 22},
        {"Eve", 3.7, 20},
    };
    
    // Display original order
    cout << "Original students:" << endl;
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    // Sort by GPA (descending), then by age (ascending) for ties
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            if (a.gpa != b.gpa) {
                return a.gpa > b.gpa;  // Higher GPA first
            }
            return a.age < b.age;      // Same GPA, younger first
        });
    
    // Display sorted order
    cout << "\nStudents sorted by GPA (desc) and age (asc):" << endl;
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    // Find students with GPA >= 3.8
    auto high_gpa = partition_point(students.begin(), students.end(),
                                  [](const Student& s) { return s.gpa >= 3.8; });
    
    cout << "\nStudents with GPA >= 3.8:" << endl;
    for (auto it = students.begin(); it != high_gpa; ++it) {
        cout << *it << endl;
    }
    
    // Find student with exact name
    auto it = find_if(students.begin(), students.end(),
                    [](const Student& s) { return s.name == "Bob"; });
    
    if (it != students.end()) {
        cout << "\nFound student: " << *it << endl;
    }
    
    return 0;
}
```

#### Example 3: Algorithm Composition

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

// Function to calculate mean of a vector
double mean(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// Function to calculate standard deviation
double standard_deviation(const vector<double>& v) {
    double m = mean(v);
    vector<double> diff(v.size());
    
    // Calculate differences from mean
    transform(v.begin(), v.end(), diff.begin(),
              [m](double x) { return x - m; });
    
    // Square the differences
    transform(diff.begin(), diff.end(), diff.begin(),
              [](double x) { return x * x; });
    
    // Calculate mean of squares
    double sq_sum = accumulate(diff.begin(), diff.end(), 0.0);
    
    return sqrt(sq_sum / v.size());
}

// Function to normalize data (z-score)
vector<double> normalize(const vector<double>& v) {
    double m = mean(v);
    double sd = standard_deviation(v);
    
    vector<double> result(v.size());
    transform(v.begin(), v.end(), result.begin(),
              [m, sd](double x) { return (x - m) / sd; });
    
    return result;
}

int main() {
    vector<double> data = {12.5, 19.8, 16.7, 18.2, 15.9, 21.3, 17.5};
    
    cout << "Original data:" << endl;
    for (double val : data) {
        cout << val << " ";
    }
    cout << endl;
    
    // Calculate statistics
    double m = mean(data);
    double sd = standard_deviation(data);
    
    cout << "Mean: " << m << endl;
    cout << "Standard Deviation: " << sd << endl;
    
    // Normalize data
    auto normalized = normalize(data);
    
    cout << "\nNormalized data (z-scores):" << endl;
    for (double val : normalized) {
        cout << val << " ";
    }
    cout << endl;
    
    // Verify normalization worked correctly
    cout << "Mean of normalized data: " << mean(normalized) << endl;
    cout << "SD of normalized data: " << standard_deviation(normalized) << endl;
    
    return 0;
}
```

### Best Practices for STL Algorithms

1. **Choose the Right Algorithm**:
   - Understand what each algorithm does and its requirements
   - Consider time and space complexity
   - Check if input must be sorted

2. **Use Algorithm Compositions**:
   - Chain algorithms together for complex tasks
   - Use the output of one algorithm as input to another

3. **Make Predicate Functions Clear and Focused**:
   - Keep lambda functions short and readable
   - Use named function objects for complex predicates

4. **Consider Using Execution Policies** (C++17 and later):
   - `std::execution::seq` - sequential execution
   - `std::execution::par` - parallel execution
   - `std::execution::par_unseq` - parallel and vectorized execution

5. **Be Careful with Mutating Algorithms**:
   - Some algorithms modify containers in-place
   - Others require destination iterators

6. **Understand Iterator Requirements**:
   - Some algorithms need random access iterators
   - Others work with any iterator category

7. **Use Algorithm Adapters When Appropriate**:
   - Use iterator adapters like `back_inserter` for dynamic growth
   - Consider views (C++20) for non-copying transformations

8. **Avoid Reinventing the Wheel**:
   - There's probably an STL algorithm for your task
   - Custom loops are often less efficient and more error-prone

9. **Watch for Edge Cases**:
   - Handle empty ranges properly
   - Consider what happens with elements that compare equal

10. **Leverage Range-Based Algorithms** (C++20):
    - Modern C++ provides more intuitive range-based versions of algorithms
    - Consider using ranges when available
