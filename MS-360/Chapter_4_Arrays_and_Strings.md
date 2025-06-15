# Chapter 4: Arrays and Strings

## 4.1 Arrays: 1D, 2D, and Multi-dimensional

Arrays are collections of elements of the same data type stored in contiguous memory locations. They provide a way to group related data under a single name, allowing for efficient data organization and access.

### One-Dimensional Arrays

A one-dimensional array is the simplest form of array, representing a linear collection of elements.

#### Declaration and Initialization

```cpp
// Declaration syntax
data_type array_name[size];

// Examples
int numbers[5];           // Declares an array of 5 integers (uninitialized)
double prices[3] = {10.5, 20.75, 30.0};  // Declares and initializes
char grades[] = {'A', 'B', 'C', 'D', 'F'};  // Size determined automatically
```

#### Accessing Array Elements

Array elements are accessed using zero-based indexing:

```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[5] = {95, 88, 76, 92, 85};
    
    // Accessing individual elements
    cout << "First score: " << scores[0] << endl;  // 95
    cout << "Third score: " << scores[2] << endl;  // 76
    
    // Modifying an element
    scores[1] = 90;
    cout << "Updated second score: " << scores[1] << endl;  // 90
    
    return 0;
}
```

#### Common Pitfalls with 1D Arrays

1. **Array Index Out of Bounds**
   ```cpp
   int arr[5] = {1, 2, 3, 4, 5};
   cout << arr[5];  // ERROR: Valid indices are 0-4
   ```
   This is undefined behavior and can cause crashes or unexpected results.

2. **Uninitialized Arrays**
   ```cpp
   int values[5];  // Elements contain garbage values
   ```

3. **Array Size Must Be a Compile-Time Constant**
   ```cpp
   int size = 10;
   int arr[size];  // Error in standard C++ (though some compilers allow it)
   ```

### Two-Dimensional Arrays

Two-dimensional arrays can be visualized as tables with rows and columns.

#### Declaration and Initialization

```cpp
// Declaration syntax
data_type array_name[rows][columns];

// Examples
int matrix[3][4];  // 3 rows, 4 columns (uninitialized)

// Initialization
int grid[2][3] = {
    {1, 2, 3},     // First row
    {4, 5, 6}      // Second row
};

// Alternative initialization syntax
int grid2[2][3] = {1, 2, 3, 4, 5, 6};  // Filled row by row

// Partial initialization
int grid3[2][3] = {{1, 2}};  // Rest filled with zeros
```

#### Accessing 2D Array Elements

```cpp
#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Accessing individual elements
    cout << "Element at (1,2): " << matrix[1][2] << endl;  // 6
    
    // Modifying an element
    matrix[0][0] = 10;
    cout << "Updated element at (0,0): " << matrix[0][0] << endl;  // 10
    
    // Iterating through a 2D array
    cout << "All matrix elements:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

#### Memory Layout of 2D Arrays

In C++, 2D arrays are stored in row-major order, meaning all elements of the first row are stored first, then the second row, and so on.

```
For int arr[3][4], the memory layout is:
arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[1][0], arr[1][1], ...
```

This is important to understand for performance reasons, especially when working with large arrays.

### Multi-dimensional Arrays

C++ supports arrays with more than two dimensions. The principles are the same as for 2D arrays, but with additional indexes.

```cpp
// 3D array (cube)
int cube[2][3][4];  // 2 layers, 3 rows, 4 columns

// Initialization
int cube[2][2][2] = {
    {  // First layer
        {1, 2},
        {3, 4}
    },
    {  // Second layer
        {5, 6},
        {7, 8}
    }
};

// Accessing elements
cube[0][1][1] = 10;  // First layer, second row, second column
```

#### Iterating Through Multi-dimensional Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    int cube[2][2][3] = {
        {{1, 2, 3}, {4, 5, 6}},
        {{7, 8, 9}, {10, 11, 12}}
    };
    
    // Iterating through a 3D array
    for (int i = 0; i < 2; i++) {
        cout << "Layer " << i << ":" << endl;
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                cout << cube[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}
```

### Arrays in Functions

When passing arrays to functions, C++ actually passes a pointer to the first element, not a copy of the array.

```cpp
#include <iostream>
using namespace std;

// Function that takes a 1D array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Modifying the array affects the original
    arr[0] = 100;
}

// Function that takes a 2D array
// Column size must be specified
void print2DArray(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    printArray(numbers, 5);
    cout << "After function call, numbers[0] = " << numbers[0] << endl;  // 100
    
    print2DArray(matrix, 2);
    
    return 0;
}
```

#### Alternative Ways to Pass Arrays

Using templates and references can make array handling safer and more flexible:

```cpp
#include <iostream>
using namespace std;

// Using a template parameter for the array size
template <size_t N>
void printArray(int (&arr)[N]) {
    for (size_t i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// For 2D arrays
template <size_t Rows, size_t Cols>
void print2DArray(int (&arr)[Rows][Cols]) {
    for (size_t i = 0; i < Rows; i++) {
        for (size_t j = 0; j < Cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    printArray(numbers);  // Size deduced automatically
    print2DArray(matrix);  // Dimensions deduced automatically
    
    return 0;
}
```

### Modern Array Alternatives

While traditional C-style arrays are important to understand, modern C++ provides safer alternatives:

1. **std::array** (fixed-size array, C++11)
```cpp
#include <array>
#include <iostream>
using namespace std;

int main() {
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    
    cout << "Size: " << numbers.size() << endl;
    cout << "Element at index 2: " << numbers[2] << endl;
    cout << "Element at index 2 (with bounds checking): " << numbers.at(2) << endl;
    
    return 0;
}
```

2. **std::vector** (dynamic-size array)
```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Adding elements
    numbers.push_back(6);
    
    // Accessing elements
    cout << "Size: " << numbers.size() << endl;
    cout << "Element at index 2: " << numbers[2] << endl;
    
    return 0;
}
```

## 4.2 Operations on Arrays (Insert, Delete, Search, Traverse)

Arrays support various operations, including traversal, insertion, deletion, and searching. However, unlike higher-level data structures, C-style arrays don't provide built-in methods for these operations, so we need to implement them manually.

### Array Traversal

Traversal means visiting each element in the array.

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Traversing using indexing
    cout << "Using index-based loop:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Traversing using range-based for loop (C++11)
    cout << "Using range-based for loop:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Array Insertion

Adding elements to an array requires shifting existing elements to make space.

```cpp
#include <iostream>
using namespace std;

// Function to insert an element at a specific position
bool insertElement(int arr[], int& size, int maxSize, int element, int position) {
    // Check if array is full or position is invalid
    if (size >= maxSize || position < 0 || position > size) {
        return false;
    }
    
    // Shift elements to the right
    for (int i = size; i > position; i--) {
        arr[i] = arr[i-1];
    }
    
    // Insert the element
    arr[position] = element;
    size++;
    
    return true;
}

int main() {
    const int maxSize = 10;
    int numbers[maxSize] = {10, 20, 30, 40, 50};
    int size = 5;
    
    cout << "Before insertion: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Insert 25 at position 2
    if (insertElement(numbers, size, maxSize, 25, 2)) {
        cout << "After insertion: ";
        for (int i = 0; i < size; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Insertion failed" << endl;
    }
    
    return 0;
}
```

Output:
```
Before insertion: 10 20 30 40 50
After insertion: 10 20 25 30 40 50
```

### Array Deletion

Removing elements requires shifting subsequent elements to fill the gap.

```cpp
#include <iostream>
using namespace std;

// Function to delete an element at a specific position
bool deleteElement(int arr[], int& size, int position) {
    // Check if array is empty or position is invalid
    if (size <= 0 || position < 0 || position >= size) {
        return false;
    }
    
    // Shift elements to the left
    for (int i = position; i < size - 1; i++) {
        arr[i] = arr[i+1];
    }
    
    // Decrease size
    size--;
    
    return true;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    cout << "Before deletion: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Delete element at position 2 (value 30)
    if (deleteElement(numbers, size, 2)) {
        cout << "After deletion: ";
        for (int i = 0; i < size; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Deletion failed" << endl;
    }
    
    return 0;
}
```

Output:
```
Before deletion: 10 20 30 40 50
After deletion: 10 20 40 50
```

### Linear Search

Linear search checks each element sequentially until the target is found or the end is reached.

```cpp
#include <iostream>
using namespace std;

// Function to perform linear search
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    int target = 30;
    
    int result = linearSearch(numbers, size, target);
    
    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found" << endl;
    }
    
    return 0;
}
```

### Binary Search

Binary search is more efficient for sorted arrays. It repeatedly divides the search space in half.

```cpp
#include <iostream>
using namespace std;

// Function to perform binary search on a sorted array
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if target is at mid
        if (arr[mid] == target) {
            return mid;
        }
        
        // If target is greater, ignore left half
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Target not found
    return -1;
}

int main() {
    int sortedNumbers[] = {10, 20, 30, 40, 50, 60, 70};
    int size = 7;
    int target = 40;
    
    int result = binarySearch(sortedNumbers, 0, size - 1, target);
    
    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found" << endl;
    }
    
    return 0;
}
```

### Sorting Arrays

Sorting is a fundamental operation. Here's a simple implementation of bubble sort:

```cpp
#include <iostream>
using namespace std;

// Function to perform bubble sort
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Before sorting: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    bubbleSort(numbers, size);
    
    cout << "After sorting: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

Output:
```
Before sorting: 64 34 25 12 22 11 90
After sorting: 11 12 22 25 34 64 90
```

#### Using Standard Library Algorithms

The C++ standard library provides efficient implementations of many common array operations:

```cpp
#include <iostream>
#include <algorithm>  // for sort(), find(), etc.
using namespace std;

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Sort
    sort(numbers, numbers + size);
    
    cout << "After sorting: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Binary search (array must be sorted)
    bool found = binary_search(numbers, numbers + size, 25);
    cout << "Is 25 in the array? " << (found ? "Yes" : "No") << endl;
    
    // Find element
    int* position = find(numbers, numbers + size, 22);
    if (position != numbers + size) {
        cout << "Found 22 at index: " << (position - numbers) << endl;
    }
    
    // Count occurrences
    int count = std::count(numbers, numbers + size, 11);
    cout << "Number of occurrences of 11: " << count << endl;
    
    return 0;
}
```

## 4.3 Strings in C++

Strings represent sequences of characters. C++ provides two main ways to work with strings:
1. C-style strings (character arrays)
2. The `std::string` class from the standard library

### 4.3.1 Character Arrays vs std::string

#### C-style Strings

C-style strings are character arrays terminated by a null character `'\0'`.

```cpp
#include <iostream>
#include <cstring>  // For C-string functions
using namespace std;

int main() {
    // Declaration and initialization
    char greeting1[] = "Hello";  // Compiler adds null terminator
    char greeting2[] = {'H', 'e', 'l', 'l', 'o', '\0'};  // Explicit null terminator
    
    // Size calculations
    cout << "Size of greeting1: " << sizeof(greeting1) << endl;  // 6 (includes '\0')
    cout << "Length of greeting1: " << strlen(greeting1) << endl;  // 5 (excludes '\0')
    
    return 0;
}
```

**Limitations of C-style strings**:
- Fixed size determined at declaration
- No bounds checking
- Manual memory management required for dynamic strings
- Limited built-in operations

#### std::string

The `std::string` class provides a safer, more flexible, and feature-rich alternative.

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declaration and initialization
    string str1 = "Hello";
    string str2("World");
    string str3 = str1 + " " + str2;  // String concatenation
    
    // Size and capacity
    cout << "str3: " << str3 << endl;
    cout << "Length: " << str3.length() << endl;
    cout << "Size: " << str3.size() << endl;  // Same as length()
    cout << "Capacity: " << str3.capacity() << endl;  // Space allocated
    
    return 0;
}
```

**Advantages of std::string**:
- Dynamically resizes as needed
- Provides bounds checking with `.at()` method
- Handles memory management automatically
- Rich set of member functions for string manipulation

#### Comparison Between C-style Strings and std::string

| Feature | C-style Strings | std::string |
|---------|----------------|-------------|
| Memory Management | Manual | Automatic |
| Size | Fixed at compile time | Dynamic |
| Bounds Checking | None | Available with `.at()` |
| Concatenation | Manual (strcat) | Simple with `+` operator |
| Comparison | strcmp function | `==`, `!=`, `<`, `>` operators |
| Standard Library Support | Limited (cstring) | Extensive |
| Performance | Sometimes faster for simple operations | Optimized for most use cases |

### 4.3.2 String Functions

#### C-style String Functions

The `<cstring>` header provides various functions for C-style strings:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[20] = "Hello";
    char str2[20] = "World";
    char result[40];
    
    // String length
    cout << "Length of str1: " << strlen(str1) << endl;
    
    // String copy
    strcpy(result, str1);
    cout << "strcpy result: " << result << endl;
    
    // String concatenation
    strcat(result, " ");
    strcat(result, str2);
    cout << "strcat result: " << result << endl;
    
    // String comparison
    int comparison = strcmp(str1, str2);
    cout << "strcmp result: " << comparison << endl;
    // Negative: str1 < str2, 0: str1 == str2, Positive: str1 > str2
    
    // Finding characters
    char* position = strchr(str1, 'l');
    if (position) {
        cout << "First 'l' found at position: " << (position - str1) << endl;
    }
    
    // Finding substrings
    char* subPosition = strstr(result, "World");
    if (subPosition) {
        cout << "Substring 'World' found at position: " << (subPosition - result) << endl;
    }
    
    return 0;
}
```

#### std::string Member Functions

The std::string class provides numerous member functions for string manipulation:

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello, World!";
    
    // Access operations
    cout << "First character: " << str[0] << endl;
    cout << "Safe access: " << str.at(1) << endl;
    cout << "Substring: " << str.substr(7, 5) << endl;  // "World"
    
    // Modification
    str.replace(7, 5, "C++");
    cout << "After replace: " << str << endl;  // "Hello, C++!"
    
    str.insert(7, "Amazing ");
    cout << "After insert: " << str << endl;  // "Hello, Amazing C++!"
    
    str.erase(7, 8);  // Erase "Amazing "
    cout << "After erase: " << str << endl;  // "Hello, C++!"
    
    // Finding
    size_t pos = str.find("C++");
    if (pos != string::npos) {
        cout << "Found 'C++' at position: " << pos << endl;
    }
    
    // Case conversion (C++17 or later with <algorithm>)
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    cout << "Lowercase: " << lower << endl;
    
    return 0;
}
```

### 4.3.3 Input/Output of Strings

#### Reading and Writing C-style Strings

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char name[50];
    
    // Reading a word (stops at whitespace)
    cout << "Enter your name (first name only): ";
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    
    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Reading a line (including spaces)
    cout << "Enter your full name: ";
    cin.getline(name, 50);
    cout << "Hello, " << name << "!" << endl;
    
    return 0;
}
```

#### Input/Output with std::string

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    
    // Reading a word
    cout << "Enter your name (first name only): ";
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    
    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Reading a line
    cout << "Enter your full name: ";
    getline(cin, name);
    cout << "Hello, " << name << "!" << endl;
    
    return 0;
}
```

#### Reading Multiple Lines

```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string input;
    
    cout << "Enter multiple lines of text (Ctrl+Z or Ctrl+D to end):" << endl;
    
    // Read multiple lines until EOF
    stringstream buffer;
    while (getline(cin, input)) {
        buffer << input << endl;
    }
    
    string allText = buffer.str();
    cout << "\nYou entered:" << endl;
    cout << allText;
    
    return 0;
}
```

#### String Streams

String streams provide a way to treat strings like streams, useful for parsing and formatting:

```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    // String to numbers
    string numStr = "123 45.67";
    istringstream iss(numStr);
    
    int intVal;
    double doubleVal;
    iss >> intVal >> doubleVal;
    
    cout << "Parsed values: " << intVal << " and " << doubleVal << endl;
    
    // Numbers to string
    ostringstream oss;
    oss << "Int: " << intVal << ", Double: " << doubleVal;
    string result = oss.str();
    
    cout << "Formatted string: " << result << endl;
    
    return 0;
}
```

### 4.3.4 String Conversion Functions

Converting between strings and other data types:

```cpp
#include <iostream>
#include <string>
#include <cstdlib>  // For C-style conversions
using namespace std;

int main() {
    // C-style conversions
    const char* numStr = "123.456";
    int intVal = atoi(numStr);     // String to int
    double doubleVal = atof(numStr);   // String to double
    
    cout << "C-style conversions: " << intVal << ", " << doubleVal << endl;
    
    // C++ style conversions (C++11 and later)
    string str = "42";
    int num = stoi(str);     // String to int
    double dbl = stod("3.14159"); // String to double
    
    cout << "C++ style conversions: " << num << ", " << dbl << endl;
    
    // Converting numbers to strings
    string numString = to_string(12345);
    string dblString = to_string(67.89);
    
    cout << "Numbers to strings: " << numString << ", " << dblString << endl;
    
    return 0;
}
```

## 4.4 String Manipulation Problems

Let's look at common string manipulation problems and their solutions.

### 1. Reverse a String

**Problem**: Reverse a given string.

**Solution 1**: Using std::string

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string reverseString(const string& str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

int main() {
    string input = "Hello, World!";
    string reversed = reverseString(input);
    
    cout << "Original: " << input << endl;
    cout << "Reversed: " << reversed << endl;
    
    return 0;
}
```

**Solution 2**: Manual reversal with C-style strings

```cpp
#include <iostream>
#include <cstring>
using namespace std;

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int main() {
    char str[] = "Hello, World!";
    
    cout << "Original: " << str << endl;
    reverseString(str);
    cout << "Reversed: " << str << endl;
    
    return 0;
}
```

### 2. Check if a String is a Palindrome

**Problem**: Determine if a string reads the same forward and backward.

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool isPalindrome(const string& str) {
    string cleaned;
    
    // Remove non-alphanumeric characters and convert to lowercase
    for (char c : str) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    
    // Compare with reverse
    string reversed = cleaned;
    reverse(reversed.begin(), reversed.end());
    
    return cleaned == reversed;
}

int main() {
    string testCases[] = {
        "A man, a plan, a canal: Panama",
        "race a car",
        "Was it a car or a cat I saw?",
        "No lemon, no melon"
    };
    
    for (const string& test : testCases) {
        cout << "\"" << test << "\" is " 
             << (isPalindrome(test) ? "a palindrome" : "not a palindrome") << endl;
    }
    
    return 0;
}
```

### 3. Find All Occurrences of a Substring

**Problem**: Find all occurrences of a substring within a string.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<size_t> findAllOccurrences(const string& str, const string& sub) {
    vector<size_t> positions;
    size_t pos = str.find(sub, 0);
    
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = str.find(sub, pos + 1);
    }
    
    return positions;
}

int main() {
    string text = "The rain in Spain falls mainly in the plain.";
    string pattern = "in";
    
    vector<size_t> occurrences = findAllOccurrences(text, pattern);
    
    cout << "Occurrences of \"" << pattern << "\" in:" << endl;
    cout << "\"" << text << "\":" << endl;
    
    for (size_t pos : occurrences) {
        cout << "Position " << pos << ": " << text.substr(pos, 10) << "..." << endl;
    }
    
    return 0;
}
```

### 4. Capitalize First Letter of Each Word

**Problem**: Convert a string so that the first letter of each word is capitalized.

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string capitalizeWords(string str) {
    bool newWord = true;
    
    for (char& c : str) {
        if (isspace(c)) {
            newWord = true;
        }
        else if (newWord) {
            c = toupper(c);
            newWord = false;
        }
        else {
            c = tolower(c);
        }
    }
    
    return str;
}

int main() {
    string sentence = "the quick brown fox jumps over the lazy dog";
    string capitalized = capitalizeWords(sentence);
    
    cout << "Original: " << sentence << endl;
    cout << "Capitalized: " << capitalized << endl;
    
    return 0;
}
```

### 5. Count Words in a String

**Problem**: Count the number of words in a string.

```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int countWords(const string& str) {
    stringstream ss(str);
    string word;
    int count = 0;
    
    while (ss >> word) {
        count++;
    }
    
    return count;
}

int main() {
    string text = "The quick brown fox jumps over the lazy dog";
    int wordCount = countWords(text);
    
    cout << "Text: \"" << text << "\"" << endl;
    cout << "Word count: " << wordCount << endl;
    
    return 0;
}
```

### 6. String Pattern Matching (KMP Algorithm)

**Problem**: Efficiently find a pattern in a text (Knuth-Morris-Pratt algorithm).

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Compute the Longest Prefix Suffix (LPS) array
vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    
    int len = 0;
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

// KMP search algorithm
vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0) return matches;
    
    vector<int> lps = computeLPS(pattern);
    
    int i = 0;  // For text
    int j = 0;  // For pattern
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return matches;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    vector<int> matches = KMPSearch(text, pattern);
    
    if (matches.empty()) {
        cout << "Pattern not found in text." << endl;
    } else {
        cout << "Pattern found at positions: ";
        for (int pos : matches) {
            cout << pos << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

### 7. Anagram Check

**Problem**: Determine if two strings are anagrams (contain the same characters in different order).

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool areAnagrams(string str1, string str2) {
    // Remove spaces and convert to lowercase
    str1.erase(remove_if(str1.begin(), str1.end(), ::isspace), str1.end());
    str2.erase(remove_if(str2.begin(), str2.end(), ::isspace), str2.end());
    
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    
    if (str1.length() != str2.length()) {
        return false;
    }
    
    // Sort both strings
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    // Compare sorted strings
    return str1 == str2;
}

int main() {
    string str1 = "Listen";
    string str2 = "Silent";
    
    cout << "\"" << str1 << "\" and \"" << str2 << "\" are " 
         << (areAnagrams(str1, str2) ? "anagrams" : "not anagrams") << endl;
    
    str1 = "Triangle";
    str2 = "Integral";
    
    cout << "\"" << str1 << "\" and \"" << str2 << "\" are " 
         << (areAnagrams(str1, str2) ? "anagrams" : "not anagrams") << endl;
    
    return 0;
}
```

### 8. String Compression

**Problem**: Perform basic string compression using counts of repeated characters.

```cpp
#include <iostream>
#include <string>
using namespace std;

string compressString(const string& str) {
    if (str.empty()) return "";
    
    string compressed;
    char currentChar = str[0];
    int count = 1;
    
    for (size_t i = 1; i < str.length(); i++) {
        if (str[i] == currentChar) {
            count++;
        } else {
            compressed += currentChar + to_string(count);
            currentChar = str[i];
            count = 1;
        }
    }
    
    // Add the last character group
    compressed += currentChar + to_string(count);
    
    // Return original if compression doesn't save space
    return (compressed.length() < str.length()) ? compressed : str;
}

int main() {
    string test = "aabcccccaaa";
    string compressed = compressString(test);
    
    cout << "Original: " << test << endl;
    cout << "Compressed: " << compressed << endl;
    
    return 0;
}
```

### Best Practices for Array and String Manipulation

1. **Prefer std::string over C-style strings** for most applications
   - Easier memory management
   - Rich functionality
   - Safer operations

2. **Prefer std::vector or std::array over raw arrays**
   - Dynamic sizing (vector)
   - Bounds checking
   - STL algorithm compatibility

3. **Be aware of boundary conditions**
   - Empty arrays/strings
   - Single element cases
   - Maximum possible indices

4. **Use existing algorithms when possible**
   - The `<algorithm>` header provides many optimized functions
   - Don't reinvent the wheel

5. **Check for performance bottlenecks**
   - String concatenation in loops can be expensive
   - Consider using StringStream or reserving capacity

6. **Handle special characters and localization**
   - Be careful with Unicode and multi-byte characters
   - Consider using libraries for internationalization

7. **Validate inputs**
   - Check array bounds before accessing
   - Verify string contents meet expected format

8. **Consider space and time complexity**
   - In-place algorithms save memory
   - Some algorithms trade space for speed

9. **Remember that strings are immutable in some languages**
   - In C++, string operations can modify the original string
   - This differs from languages like Java where strings are immutable

By mastering arrays and strings, you'll build a solid foundation for more complex data structures and algorithms. These fundamental concepts are essential for solving a wide range of programming problems efficiently.
