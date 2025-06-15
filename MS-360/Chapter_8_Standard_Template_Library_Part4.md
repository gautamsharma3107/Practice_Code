# Chapter 8: Standard Template Library (STL) (Part 4)

## 8.5 Function Objects (Functors)

Function objects, often called functors, are objects that can be called like a function. They are implemented as classes that overload the function call operator `operator()`.

### 8.5.1 Basic Concept of Functors

Functors are essentially objects that behave like functions. They're created by defining classes that implement the function call operator `()`.

```cpp
#include <iostream>
using namespace std;

// Simple functor that adds a specified value
class Adder {
private:
    int addValue;
    
public:
    // Constructor that initializes the value to add
    Adder(int val) : addValue(val) {}
    
    // Function call operator
    int operator()(int x) const {
        return x + addValue;
    }
};

int main() {
    // Create functor objects
    Adder add5(5);
    Adder add10(10);
    
    // Use the functors like functions
    cout << "add5(10) = " << add5(10) << endl;      // Outputs: 15
    cout << "add10(10) = " << add10(10) << endl;    // Outputs: 20
    
    // Can be used on multiple values
    cout << "add5(20) = " << add5(20) << endl;      // Outputs: 25
    cout << "add5(25) = " << add5(25) << endl;      // Outputs: 30
    
    return 0;
}
```

### 8.5.2 Advantages of Functors

Functors have several advantages over regular functions:

1. **State Preservation**: They can maintain state between calls
2. **Type Safety**: They are objects with defined types
3. **Inline Optimization**: Compilers can often inline functor calls
4. **Parameterization**: They can be customized at instantiation
5. **STL Integration**: They integrate seamlessly with STL algorithms

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Counter functor that tracks how many times it's called
class Counter {
private:
    int count = 0;
    int threshold;
    
public:
    Counter(int t = 0) : threshold(t) {}
    
    // Function call operator that counts calls and checks threshold
    bool operator()(int x) {
        ++count;
        return x > threshold;
    }
    
    // Method to get current count
    int getCount() const {
        return count;
    }
};

int main() {
    vector<int> nums = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Count how many elements are greater than 5
    Counter counter(5);
    int greaterThan5 = count_if(nums.begin(), nums.end(), counter);
    
    cout << "Numbers greater than 5: " << greaterThan5 << endl;
    cout << "Function was called " << counter.getCount() << " times" << endl;
    
    return 0;
}
```

### 8.5.3 Standard Library Functors

The C++ Standard Library provides many built-in functors in the `<functional>` header:

#### Arithmetic Functors

```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Using arithmetic functors
    plus<int> add;
    minus<int> subtract;
    multiplies<int> multiply;
    divides<double> divide;
    modulus<int> mod;
    negate<int> negate;
    
    cout << "plus: 5 + 3 = " << add(5, 3) << endl;
    cout << "minus: 5 - 3 = " << subtract(5, 3) << endl;
    cout << "multiplies: 5 * 3 = " << multiply(5, 3) << endl;
    cout << "divides: 5 / 3 = " << divide(5, 3) << endl;
    cout << "modulus: 5 % 3 = " << mod(5, 3) << endl;
    cout << "negate: -5 = " << negate(5) << endl;
    
    // Using functors with algorithms
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> result(nums.size());
    
    // Transform each element by multiplying it by 2
    transform(nums.begin(), nums.end(), result.begin(), 
             bind(multiply, placeholders::_1, 2));
    
    cout << "After multiplying each element by 2: ";
    for (int n : result) {
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}
```

#### Comparison Functors

```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Using comparison functors
    equal_to<int> eq;
    not_equal_to<int> neq;
    greater<int> gt;
    less<int> lt;
    greater_equal<int> ge;
    less_equal<int> le;
    
    cout << "equal_to: 5 == 3 is " << boolalpha << eq(5, 3) << endl;
    cout << "not_equal_to: 5 != 3 is " << neq(5, 3) << endl;
    cout << "greater: 5 > 3 is " << gt(5, 3) << endl;
    cout << "less: 5 < 3 is " << lt(5, 3) << endl;
    cout << "greater_equal: 5 >= 5 is " << ge(5, 5) << endl;
    cout << "less_equal: 3 <= 5 is " << le(3, 5) << endl;
    
    // Sorting with comparison functors
    vector<int> nums = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Sort in descending order
    sort(nums.begin(), nums.end(), greater<int>());
    
    cout << "Sorted in descending order: ";
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}
```

#### Logical Functors

```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Using logical functors
    logical_and<bool> land;
    logical_or<bool> lor;
    logical_not<bool> lnot;
    
    cout << "logical_and: true && false is " << boolalpha << land(true, false) << endl;
    cout << "logical_or: true || false is " << lor(true, false) << endl;
    cout << "logical_not: !true is " << lnot(true) << endl;
    
    // Using with algorithms
    vector<bool> b1 = {true, false, true};
    vector<bool> b2 = {false, true, true};
    vector<bool> result(b1.size());
    
    // Element-wise AND operation
    transform(b1.begin(), b1.end(), b2.begin(), result.begin(), logical_and<bool>());
    
    cout << "Result of element-wise AND: ";
    for (bool b : result) {
        cout << b << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 8.5.4 Functors with STL Algorithms

Functors integrate seamlessly with STL algorithms, making code more readable and flexible:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Custom functor that checks if a number is divisible by another
class DivisibleBy {
private:
    int divisor;
    
public:
    DivisibleBy(int d) : divisor(d) {}
    
    bool operator()(int value) const {
        return value % divisor == 0;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    // Count numbers divisible by 3
    int count3 = count_if(nums.begin(), nums.end(), DivisibleBy(3));
    cout << "Numbers divisible by 3: " << count3 << endl;
    
    // Count numbers divisible by 2
    int count2 = count_if(nums.begin(), nums.end(), DivisibleBy(2));
    cout << "Numbers divisible by 2: " << count2 << endl;
    
    // Find first number divisible by both 2 and 3 (i.e., 6)
    auto it = find_if(nums.begin(), nums.end(), 
                     [](int n) { return n % 2 == 0 && n % 3 == 0; });
    
    if (it != nums.end()) {
        cout << "First number divisible by both 2 and 3: " << *it << endl;
    }
    
    // Remove all numbers divisible by 4
    nums.erase(
        remove_if(nums.begin(), nums.end(), DivisibleBy(4)), 
        nums.end()
    );
    
    cout << "After removing numbers divisible by 4: ";
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 8.5.5 Function Adapters

Function adapters modify the behavior of existing functors:

```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Using not1 to negate a functor
    auto notDivisible3 = not1(bind(modulus<int>(), placeholders::_1, 3));
    
    cout << "Numbers not divisible by 3: ";
    for_each(nums.begin(), nums.end(), 
            [&notDivisible3](int n) {
                if (notDivisible3(n)) {
                    cout << n << " ";
                }
            });
    cout << endl;
    
    // Using negators
    auto isOdd = not1(ptr_fun(isEven));  // Negate isEven function
    
    cout << "Odd numbers: ";
    for_each(nums.begin(), nums.end(),
            [&isOdd](int n) {
                if (isOdd(n)) {
                    cout << n << " ";
                }
            });
    cout << endl;
    
    // Using bind (C++11) to create new functors from existing ones
    auto isMultipleOf3 = bind(modulus<int>(), placeholders::_1, 3);
    auto isNotMultipleOf3 = bind(not_equal_to<int>(), 
                               bind(modulus<int>(), placeholders::_1, 3), 0);
    
    cout << "Is 9 multiple of 3? " << boolalpha << isMultipleOf3(9) << endl;
    cout << "Is 10 not multiple of 3? " << isNotMultipleOf3(10) << endl;
    
    return 0;
}
```

### 8.5.6 Creating Complex Functors

More complex functors can contain multiple functions and store state:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Statistical functor that computes mean, min, max and count
class Statistics {
private:
    int count = 0;
    double sum = 0.0;
    double min = numeric_limits<double>::max();
    double max = numeric_limits<double>::lowest();
    
public:
    // Function call operator to process each value
    void operator()(double value) {
        ++count;
        sum += value;
        
        if (value < min) min = value;
        if (value > max) max = value;
    }
    
    // Functions to retrieve statistics
    int getCount() const { return count; }
    double getSum() const { return sum; }
    double getMean() const { return count > 0 ? sum / count : 0; }
    double getMin() const { return min; }
    double getMax() const { return max; }
    double getRange() const { return max - min; }
};

// Functor that applies multiple operations based on rules
class NumberClassifier {
private:
    vector<int> primes;
    vector<int> evens;
    vector<int> odds;
    
public:
    void operator()(int value) {
        // Check if even or odd
        if (value % 2 == 0) {
            evens.push_back(value);
        } else {
            odds.push_back(value);
        }
        
        // Check if prime
        if (value <= 1) return;
        bool isPrime = true;
        for (int i = 2; i * i <= value; ++i) {
            if (value % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push_back(value);
        }
    }
    
    const vector<int>& getPrimes() const { return primes; }
    const vector<int>& getEvens() const { return evens; }
    const vector<int>& getOdds() const { return odds; }
};

int main() {
    vector<double> values = {1.5, 3.7, 2.8, 9.2, 4.3, 5.1, 2.9, 8.4};
    
    // Using the Statistics functor
    Statistics stats = for_each(values.begin(), values.end(), Statistics());
    
    cout << "Number of values: " << stats.getCount() << endl;
    cout << "Sum: " << stats.getSum() << endl;
    cout << "Mean: " << stats.getMean() << endl;
    cout << "Minimum: " << stats.getMin() << endl;
    cout << "Maximum: " << stats.getMax() << endl;
    cout << "Range: " << stats.getRange() << endl;
    
    // Using the NumberClassifier functor
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    NumberClassifier classifier = for_each(numbers.begin(), numbers.end(), NumberClassifier());
    
    cout << "\nPrime numbers: ";
    for (int prime : classifier.getPrimes()) {
        cout << prime << " ";
    }
    cout << endl;
    
    cout << "Even numbers: ";
    for (int even : classifier.getEvens()) {
        cout << even << " ";
    }
    cout << endl;
    
    cout << "Odd numbers: ";
    for (int odd : classifier.getOdds()) {
        cout << odd << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 8.5.7 Functors vs Lambdas

Modern C++ provides lambdas as a simpler alternative to functors in many cases:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Traditional functor approach
class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int value) const {
        return value * factor;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> result1(nums.size());
    vector<int> result2(nums.size());
    vector<int> result3(nums.size());
    
    // Approach 1: Using functor
    transform(nums.begin(), nums.end(), result1.begin(), Multiplier(3));
    
    // Approach 2: Using lambda
    transform(nums.begin(), nums.end(), result2.begin(), 
             [factor = 3](int value) { return value * factor; });
    
    // Approach 3: Using std::bind
    transform(nums.begin(), nums.end(), result3.begin(),
             bind(multiplies<int>(), placeholders::_1, 3));
    
    // Output results
    cout << "Using functor: ";
    for (int n : result1) cout << n << " ";
    cout << endl;
    
    cout << "Using lambda: ";
    for (int n : result2) cout << n << " ";
    cout << endl;
    
    cout << "Using bind: ";
    for (int n : result3) cout << n << " ";
    cout << endl;
    
    // When to use functors over lambdas:
    // 1. When you need a reusable function object
    // 2. When you need complex state management
    // 3. When your functor is used in multiple places
    // 4. When you need custom template parameters
    
    return 0;
}
```

### 8.5.8 Best Practices for Functors

1. **Keep functors simple and focused** - Each functor should have a single responsibility
2. **Use meaningful names** - Names should reflect what the functor does
3. **Make functors const-correct** - Mark the function call operator as `const` when it doesn't modify the functor's state
4. **Consider lambdas for simple cases** - Use lambdas for short, one-off operations
5. **Consider std::function for polymorphic function wrappers** - When you need to store different callable objects
6. **Use STL functors when possible** - Leverage existing functors before creating your own

## 8.6 Custom Comparators

Custom comparators allow you to define custom ordering rules for containers and algorithms. They're essential when working with complex data types or when you need specific ordering behaviors.

### 8.6.1 Basic Concept of Comparators

A comparator is a function or function object that takes two arguments and returns a boolean indicating whether the first argument should be considered "less than" the second.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Custom comparator function
bool descending(int a, int b) {
    return a > b;  // Sort in descending order
}

int main() {
    vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Sort using custom comparator function
    sort(numbers.begin(), numbers.end(), descending);
    
    cout << "Sorted in descending order: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Sort using lambda comparator (ascending)
    sort(numbers.begin(), numbers.end(), 
         [](int a, int b) { return a < b; });
    
    cout << "Sorted in ascending order: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 8.6.2 Comparator Classes

Comparators can also be implemented as classes, which is useful when they need to maintain state or be parameterized:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Custom comparator class
class CustomCompare {
private:
    bool ascending;
    
public:
    CustomCompare(bool asc = true) : ascending(asc) {}
    
    bool operator()(int a, int b) const {
        return ascending ? (a < b) : (a > b);
    }
};

int main() {
    vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Sort using comparator object (descending)
    sort(numbers.begin(), numbers.end(), CustomCompare(false));
    
    cout << "Sorted in descending order: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Sort using same comparator class but ascending
    sort(numbers.begin(), numbers.end(), CustomCompare(true));
    
    cout << "Sorted in ascending order: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### 8.6.3 Comparators for Custom Types

Custom comparators are particularly useful for custom types:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Student class
class Student {
public:
    string name;
    double gpa;
    int id;
    
    Student(string n, double g, int i) : name(n), gpa(g), id(i) {}
    
    // For easy output
    friend ostream& operator<<(ostream& os, const Student& s) {
        return os << s.name << " (ID: " << s.id << ", GPA: " << s.gpa << ")";
    }
};

// Comparator by name
struct CompareByName {
    bool operator()(const Student& a, const Student& b) const {
        return a.name < b.name;
    }
};

// Comparator by GPA
struct CompareByGPA {
    bool operator()(const Student& a, const Student& b) const {
        return a.gpa > b.gpa;  // Note: Higher GPA first (descending)
    }
};

// Comparator by ID
struct CompareByID {
    bool operator()(const Student& a, const Student& b) const {
        return a.id < b.id;
    }
};

int main() {
    vector<Student> students = {
        {"Alice", 3.8, 103},
        {"Bob", 3.6, 101},
        {"Charlie", 4.0, 105},
        {"David", 3.9, 102},
        {"Eva", 3.7, 104}
    };
    
    // Sort by name
    sort(students.begin(), students.end(), CompareByName());
    
    cout << "Sorted by name:\n";
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    // Sort by GPA (descending)
    sort(students.begin(), students.end(), CompareByGPA());
    
    cout << "\nSorted by GPA (highest first):\n";
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    // Sort by ID
    sort(students.begin(), students.end(), CompareByID());
    
    cout << "\nSorted by ID:\n";
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    // Using lambda for multi-criteria sort (GPA then name)
    sort(students.begin(), students.end(), 
         [](const Student& a, const Student& b) {
             if (a.gpa != b.gpa) {
                 return a.gpa > b.gpa;  // First by GPA (descending)
             }
             return a.name < b.name;    // Then by name (ascending)
         });
    
    cout << "\nSorted by GPA (then by name for ties):\n";
    for (const auto& student : students) {
        cout << student << endl;
    }
    
    return 0;
}
```

### 8.6.4 Comparators with Associative Containers

Custom comparators are essential for associative containers like `set` and `map`, where they define the ordering of elements:

```cpp
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

// Case-insensitive string comparator
struct CaseInsensitiveCompare {
    bool operator()(const string& a, const string& b) const {
        // Convert both strings to lowercase for comparison
        string a_lower = a;
        string b_lower = b;
        
        transform(a_lower.begin(), a_lower.end(), a_lower.begin(), ::tolower);
        transform(b_lower.begin(), b_lower.end(), b_lower.begin(), ::tolower);
        
        return a_lower < b_lower;
    }
};

int main() {
    // Set with custom comparator
    set<string, CaseInsensitiveCompare> names;
    
    // Inserting names
    names.insert("John");
    names.insert("alice");
    names.insert("Bob");
    names.insert("CHARLIE");
    names.insert("Alice");  // Will not be inserted since "alice" is already present
    
    cout << "Case-insensitive set of names:" << endl;
    for (const auto& name : names) {
        cout << name << endl;
    }
    
    // Map with custom comparator
    map<string, int, CaseInsensitiveCompare> nameCounts;
    
    // Counting names regardless of case
    vector<string> words = {"Apple", "banana", "APPLE", "orange", "Banana", "ORANGE"};
    
    for (const auto& word : words) {
        ++nameCounts[word];
    }
    
    cout << "\nCase-insensitive word counts:" << endl;
    for (const auto& [word, count] : nameCounts) {
        cout << word << ": " << count << endl;
    }
    
    return 0;
}
```

### 8.6.5 Comparators with STL Algorithms

Custom comparators can be used with many STL algorithms:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Person structure
struct Person {
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
    
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.name << " (age: " << p.age << ")";
    }
};

int main() {
    vector<Person> people = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 22},
        {"David", 35},
        {"Eva", 28}
    };
    
    // Find the oldest person
    auto oldest = max_element(people.begin(), people.end(),
                            [](const Person& a, const Person& b) {
                                return a.age < b.age;
                            });
    
    cout << "Oldest person: " << *oldest << endl;
    
    // Find the youngest person
    auto youngest = min_element(people.begin(), people.end(),
                              [](const Person& a, const Person& b) {
                                  return a.age < b.age;
                              });
    
    cout << "Youngest person: " << *youngest << endl;
    
    // Sort by name
    sort(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.name < b.name;
        });
    
    cout << "\nPeople sorted by name:" << endl;
    for (const auto& person : people) {
        cout << person << endl;
    }
    
    // Partial sort - get 3 youngest people
    partial_sort(people.begin(), people.begin() + 3, people.end(),
               [](const Person& a, const Person& b) {
                   return a.age < b.age;
               });
    
    cout << "\n3 youngest people:" << endl;
    for (auto it = people.begin(); it != people.begin() + 3; ++it) {
        cout << *it << endl;
    }
    
    // Binary search with custom comparator
    vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    
    // Find element closest to 45
    auto closest = lower_bound(numbers.begin(), numbers.end(), 45);
    
    if (closest != numbers.end()) {
        cout << "\nClosest number to 45 is: " << *closest << endl;
    }
    
    return 0;
}
```

### 8.6.6 Complex Custom Comparators

More complex sorting scenarios often require sophisticated comparators:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

// Product class
class Product {
public:
    string name;
    double price;
    int stock;
    string category;
    
    Product(string n, double p, int s, string c)
        : name(n), price(p), stock(s), category(c) {}
    
    friend ostream& operator<<(ostream& os, const Product& p) {
        return os << p.name << " - $" << p.price
                  << " (Stock: " << p.stock
                  << ", Category: " << p.category << ")";
    }
};

// Multi-criteria comparator class
class ProductComparator {
private:
    enum class SortCriterion { Name, Price, Stock, Category };
    enum class SortDirection { Ascending, Descending };
    
    vector<pair<SortCriterion, SortDirection>> criteria;
    
public:
    // Add a sorting criterion
    void addCriterion(SortCriterion crit, SortDirection dir = SortDirection::Ascending) {
        criteria.push_back({crit, dir});
    }
    
    // Clear all criteria
    void clearCriteria() {
        criteria.clear();
    }
    
    // Comparison operator
    bool operator()(const Product& a, const Product& b) const {
        for (const auto& [criterion, direction] : criteria) {
            bool result;
            
            switch (criterion) {
                case SortCriterion::Name:
                    if (a.name != b.name) {
                        result = a.name < b.name;
                        break;
                    }
                    continue;  // Move to next criterion
                    
                case SortCriterion::Price:
                    if (a.price != b.price) {
                        result = a.price < b.price;
                        break;
                    }
                    continue;  // Move to next criterion
                    
                case SortCriterion::Stock:
                    if (a.stock != b.stock) {
                        result = a.stock < b.stock;
                        break;
                    }
                    continue;  // Move to next criterion
                    
                case SortCriterion::Category:
                    if (a.category != b.category) {
                        result = a.category < b.category;
                        break;
                    }
                    continue;  // Move to next criterion
            }
            
            // Apply sort direction
            return direction == SortDirection::Ascending ? result : !result;
        }
        
        // If all criteria match, maintain stable sort
        return false;
    }
    
    // Factory methods for common comparators
    static ProductComparator byNameAsc() {
        ProductComparator comp;
        comp.addCriterion(SortCriterion::Name, SortDirection::Ascending);
        return comp;
    }
    
    static ProductComparator byPriceDesc() {
        ProductComparator comp;
        comp.addCriterion(SortCriterion::Price, SortDirection::Descending);
        return comp;
    }
    
    static ProductComparator byCategoryThenPrice() {
        ProductComparator comp;
        comp.addCriterion(SortCriterion::Category, SortDirection::Ascending);
        comp.addCriterion(SortCriterion::Price, SortDirection::Ascending);
        return comp;
    }
};

int main() {
    vector<Product> products = {
        {"Laptop", 999.99, 15, "Electronics"},
        {"Smartphone", 699.99, 25, "Electronics"},
        {"Desk", 249.99, 5, "Furniture"},
        {"Chair", 149.99, 12, "Furniture"},
        {"Mouse", 29.99, 50, "Electronics"},
        {"Keyboard", 89.99, 30, "Electronics"},
        {"Bookshelf", 199.99, 8, "Furniture"},
        {"Monitor", 249.99, 20, "Electronics"}
    };
    
    // Sort by name (ascending)
    sort(products.begin(), products.end(), ProductComparator::byNameAsc());
    
    cout << "Products sorted by name (ascending):\n";
    for (const auto& product : products) {
        cout << product << endl;
    }
    
    // Sort by price (descending)
    sort(products.begin(), products.end(), ProductComparator::byPriceDesc());
    
    cout << "\nProducts sorted by price (descending):\n";
    for (const auto& product : products) {
        cout << product << endl;
    }
    
    // Sort by category, then by price
    sort(products.begin(), products.end(), ProductComparator::byCategoryThenPrice());
    
    cout << "\nProducts sorted by category, then by price:\n";
    for (const auto& product : products) {
        cout << product << endl;
    }
    
    // Custom multi-level sorting using a configurable comparator
    ProductComparator customComp;
    customComp.addCriterion(ProductComparator::SortCriterion::Stock, 
                           ProductComparator::SortDirection::Ascending);
    customComp.addCriterion(ProductComparator::SortCriterion::Name, 
                           ProductComparator::SortDirection::Descending);
    
    sort(products.begin(), products.end(), customComp);
    
    cout << "\nProducts sorted by stock (ascending), then by name (descending):\n";
    for (const auto& product : products) {
        cout << product << endl;
    }
    
    return 0;
}
```

### 8.6.7 Using Comparators with priority_queue

The `priority_queue` container adapter requires a special form of comparator:

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Task class
class Task {
public:
    string description;
    int priority;  // Higher number means higher priority
    
    Task(string desc, int prio) : description(desc), priority(prio) {}
    
    // For easy output
    friend ostream& operator<<(ostream& os, const Task& task) {
        return os << task.description << " (Priority: " << task.priority << ")";
    }
};

// Comparator for Task priority queue
struct TaskCompare {
    // Note: priority_queue uses this to determine if a is "less" priority than b
    // For a max-heap (highest priority first), we return true if a should come after b
    bool operator()(const Task& a, const Task& b) const {
        return a.priority < b.priority;  // This creates a max-heap
    }
};

int main() {
    // Create a priority queue of tasks
    priority_queue<Task, vector<Task>, TaskCompare> taskQueue;
    
    // Add tasks
    taskQueue.push(Task("Check emails", 2));
    taskQueue.push(Task("Fix critical bug", 5));
    taskQueue.push(Task("Write documentation", 1));
    taskQueue.push(Task("Code review", 3));
    taskQueue.push(Task("Client meeting", 4));
    
    cout << "Tasks in priority order:\n";
    while (!taskQueue.top()) {
        cout << taskQueue.top() << endl;
        taskQueue.pop();
    }
    
    // Using a min-heap with lambda (lowest priority first)
    auto minCompare = [](const Task& a, const Task& b) {
        return a.priority > b.priority;  // Return true if a should come after b
    };
    
    priority_queue<Task, vector<Task>, decltype(minCompare)> minTaskQueue(minCompare);
    
    // Add tasks to min-heap
    minTaskQueue.push(Task("Check emails", 2));
    minTaskQueue.push(Task("Fix critical bug", 5));
    minTaskQueue.push(Task("Write documentation", 1));
    minTaskQueue.push(Task("Code review", 3));
    minTaskQueue.push(Task("Client meeting", 4));
    
    cout << "\nTasks in reverse priority order:\n";
    while (!minTaskQueue.empty()) {
        cout << minTaskQueue.top() << endl;
        minTaskQueue.pop();
    }
    
    return 0;
}
```

### 8.6.8 Stable and Unstable Sorting

Using comparators with stable and unstable sorting algorithms:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
    
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.name << " (age: " << p.age << ")";
    }
};

int main() {
    vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 30},
        {"David", 25}, {"Eva", 30}, {"Frank", 25}
    };
    
    // Make a copy for stable_sort
    vector<Person> stablePeople = people;
    
    // Unstable sort by age (may reorder people of the same age)
    sort(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.age < b.age;
        });
    
    cout << "After regular sort by age (unstable):\n";
    for (const auto& person : people) {
        cout << person << endl;
    }
    
    // Stable sort by age (preserves original order of people with same age)
    stable_sort(stablePeople.begin(), stablePeople.end(),
               [](const Person& a, const Person& b) {
                   return a.age < b.age;
               });
    
    cout << "\nAfter stable sort by age:\n";
    for (const auto& person : stablePeople) {
        cout << person << endl;
    }
    
    // Custom multi-criteria comparator preserving stability
    cout << "\nMulti-criteria stable sort (age then name):\n";
    
    // Sort by name first
    stable_sort(stablePeople.begin(), stablePeople.end(),
               [](const Person& a, const Person& b) {
                   return a.name < b.name;
               });
    
    // Then sort by age (will preserve name order for same age)
    stable_sort(stablePeople.begin(), stablePeople.end(),
               [](const Person& a, const Person& b) {
                   return a.age < b.age;
               });
    
    for (const auto& person : stablePeople) {
        cout << person << endl;
    }
    
    return 0;
}
```

### 8.6.9 Best Practices for Custom Comparators

1. **Follow the strict weak ordering requirements**:
   - If a < b is true, then b < a must be false
   - If a < b is false and b < a is false, then a and b are equivalent
   - If a < b and b < c, then a < c (transitivity)

2. **Make your comparators const-correct**:
   ```cpp
   bool operator()(const Type& a, const Type& b) const { ... }
   ```

3. **Keep comparators simple and focused**:
   - Each comparator should have a clear sorting criterion
   - Use multiple comparators for complex sorting scenarios

4. **Use lambdas for simple, one-off comparisons**:
   ```cpp
   sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.value < b.value; });
   ```

5. **Use function objects for reusable or stateful comparators**:
   ```cpp
   struct MyComparator {
       bool operator()(const Type& a, const Type& b) const { ... }
   };
   ```

6. **Be consistent with the meaning of the comparison**:
   - Convention: return `true` if `a` should come before `b`
   - Exception: `priority_queue` interprets the comparison differently

7. **Be mindful of stability when needed**:
   - Use `stable_sort` when the original order matters for equivalent elements
   - Use multi-pass sorting for complex criteria while preserving order

8. **Avoid expensive operations in comparators**:
   - Comparison functions are called many times during sorting
   - Cache results or precompute values when appropriate

9. **Test edge cases**:
   - Empty strings, zero/negative values, duplicate elements
   - Very large or very small values
   - Make sure your comparator behaves correctly in all situations
