# Chapter 5: Pointers and Memory Management

## 5.1 Introduction to Pointers

Pointers are among the most powerful and challenging features in C++. At their core, pointers are variables that store memory addresses of other variables or objects, enabling direct memory manipulation.

### What is a Pointer?

A pointer is a variable that stores the memory address of another variable. Just as a regular variable gives a name to a value, a pointer gives a name to a memory location.

### Declaring Pointers

To declare a pointer, use the `*` symbol after the data type:

```cpp
data_type* pointer_name;
// or
data_type *pointer_name;  // Both styles are correct
```

Examples:

```cpp
int* p_integer;      // Pointer to an integer
double* p_double;    // Pointer to a double
char* p_character;   // Pointer to a character
```

### Address-of Operator (&)

The address-of operator `&` returns the memory address of a variable:

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 42;
    int* ptr = &num;  // ptr now holds the address of num
    
    cout << "Value of num: " << num << endl;
    cout << "Address of num: " << &num << endl;
    cout << "Value stored in ptr: " << ptr << endl;
    
    return 0;
}
```

Output:
```
Value of num: 42
Address of num: 0x7ffcb53e9d0c (this will differ on your system)
Value stored in ptr: 0x7ffcb53e9d0c
```

### Dereferencing Operator (*)

The dereferencing operator `*` accesses the value at the memory address stored in a pointer:

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 42;
    int* ptr = &num;
    
    cout << "Value of num: " << num << endl;
    cout << "Value pointed to by ptr: " << *ptr << endl;
    
    // Modify the value through the pointer
    *ptr = 100;
    cout << "New value of num: " << num << endl;
    
    return 0;
}
```

Output:
```
Value of num: 42
Value pointed to by ptr: 42
New value of num: 100
```

### Null Pointers

A null pointer doesn't point to any valid memory location. Always initialize pointers to `nullptr` if you're not immediately assigning a valid address:

```cpp
#include <iostream>
using namespace std;

int main() {
    // Modern C++ (C++11 and later)
    int* modern_ptr = nullptr;
    
    // Pre-C++11 style (avoid in modern code)
    int* old_style_ptr = NULL;
    int* c_style_ptr = 0;  // Also works but less clear
    
    // Check before dereferencing
    if (modern_ptr != nullptr) {
        cout << "Value: " << *modern_ptr << endl;
    } else {
        cout << "Pointer is null, cannot dereference" << endl;
    }
    
    return 0;
}
```

### Pointer Memory Requirements

Regardless of the data type they point to, pointers have a fixed size determined by the architecture:
- 4 bytes on 32-bit systems
- 8 bytes on 64-bit systems

```cpp
#include <iostream>
using namespace std;

int main() {
    int* p_int;
    double* p_double;
    char* p_char;
    void* p_void;
    
    cout << "Size of int pointer: " << sizeof(p_int) << " bytes" << endl;
    cout << "Size of double pointer: " << sizeof(p_double) << " bytes" << endl;
    cout << "Size of char pointer: " << sizeof(p_char) << " bytes" << endl;
    cout << "Size of void pointer: " << sizeof(p_void) << " bytes" << endl;
    
    return 0;
}
```

Output on a 64-bit system:
```
Size of int pointer: 8 bytes
Size of double pointer: 8 bytes
Size of char pointer: 8 bytes
Size of void pointer: 8 bytes
```

### Void Pointers

Void pointers can point to data of any type but must be cast before dereferencing:

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 42;
    void* generic_ptr = &num;  // Store address as void pointer
    
    // Must cast before dereferencing
    int* int_ptr = static_cast<int*>(generic_ptr);
    cout << "Value: " << *int_ptr << endl;
    
    // Direct dereferencing of void pointer is not allowed
    // cout << *generic_ptr << endl;  // Error!
    
    return 0;
}
```

### Pointers to Pointers

You can create pointers to pointers, which are especially useful for dynamic multi-dimensional arrays:

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;      // Pointer to int
    int** ptr_to_ptr = &ptr;  // Pointer to pointer to int
    
    cout << "value: " << value << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << "**ptr_to_ptr: " << **ptr_to_ptr << endl;
    
    **ptr_to_ptr = 100;  // Change value through double pointer
    cout << "After modification, value: " << value << endl;
    
    return 0;
}
```

Output:
```
value: 42
*ptr: 42
**ptr_to_ptr: 42
After modification, value: 100
```

### Common Pointer Mistakes and Their Solutions

1. **Dereferencing Uninitialized Pointers**
   ```cpp
   int* ptr;  // Uninitialized - contains garbage address
   *ptr = 10;  // DANGER! Undefined behavior
   
   // Solution:
   int* ptr = nullptr;  // Initialize to nullptr
   if (ptr) *ptr = 10;  // Check before dereferencing
   ```

2. **Dereferencing Null Pointers**
   ```cpp
   int* ptr = nullptr;
   *ptr = 10;  // CRASH! Cannot dereference nullptr
   
   // Solution:
   if (ptr != nullptr) {
       *ptr = 10;  // Safe - only deference if not null
   }
   ```

3. **Dangling Pointers** (pointer to released memory)
   ```cpp
   int* createAndReturn() {
       int local = 10;
       return &local;  // DANGER! Returns address of local variable
   }
   
   // Solution:
   int* createAndReturn() {
       static int persistent = 10;  // Static variable persists beyond function call
       return &persistent;  // Safe - memory still exists
   }
   ```

4. **Memory Leaks**
   ```cpp
   void leakMemory() {
       int* ptr = new int(42);
       // Function ends without delete
       // Memory leak!
   }
   
   // Solution:
   void noLeak() {
       int* ptr = new int(42);
       // Use ptr...
       delete ptr;  // Always clean up allocated memory
   }
   ```

### Best Practices for Pointers

1. **Always initialize pointers**
   ```cpp
   int* ptr = nullptr;  // Good practice
   ```

2. **Check for null before dereferencing**
   ```cpp
   if (ptr != nullptr) {
       *ptr = 100;  // Safe
   }
   ```

3. **Delete dynamically allocated memory**
   ```cpp
   int* ptr = new int(42);
   // Use ptr...
   delete ptr;  // Free memory
   ptr = nullptr;  // Prevent use after free
   ```

4. **Use smart pointers for automatic memory management** (covered later in this chapter)
   ```cpp
   #include <memory>
   std::unique_ptr<int> ptr = std::make_unique<int>(42);
   // Memory automatically freed when ptr goes out of scope
   ```

5. **Prefer references over pointers when possible**
   ```cpp
   void modify(int& num) {  // Reference parameter
       num *= 2;
   }
   ```

6. **Use const for pointers to read-only data**
   ```cpp
   const int* ptr;  // Pointer to constant int (data cannot be modified)
   int* const ptr;  // Constant pointer to int (pointer cannot be reassigned)
   const int* const ptr;  // Constant pointer to constant int (neither can change)
   ```

## 5.2 Pointer Arithmetic

Pointer arithmetic allows you to navigate through memory by performing mathematical operations on pointers. This is particularly useful for array manipulation and memory management.

### Basic Arithmetic Operations

#### Incrementing and Decrementing

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* ptr = numbers;  // Points to first element
    
    cout << "Initial value: " << *ptr << endl;  // 10
    
    ptr++;  // Move to next element
    cout << "After increment: " << *ptr << endl;  // 20
    
    ptr--;  // Move back to previous element
    cout << "After decrement: " << *ptr << endl;  // 10
    
    return 0;
}
```

#### Adding and Subtracting Integers

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* ptr = numbers;
    
    cout << "Value at index 0: " << *ptr << endl;         // 10
    cout << "Value at index 2: " << *(ptr + 2) << endl;   // 30
    cout << "Value at index 4: " << *(ptr + 4) << endl;   // 50
    
    // Pointer arithmetic with array indexing
    cout << "Using array notation: " << ptr[3] << endl;   // 40
    
    return 0;
}
```

### How Pointer Arithmetic Works

When we add an integer `n` to a pointer, it actually advances the pointer by `n * sizeof(data_type)` bytes, not just by `n` bytes. This ensures we advance to the correct memory location based on the type's size.

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    
    char char_array[5] = {'A', 'B', 'C', 'D', 'E'};
    int int_array[5] = {10, 20, 30, 40, 50};
    double double_array[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    char* char_ptr = char_array;
    int* int_ptr = int_array;
    double* double_ptr = double_array;
    
    // Print initial and incremented addresses
    cout << "\nChar pointer:" << endl;
    cout << "Initial address: " << static_cast<void*>(char_ptr) << endl;
    char_ptr += 1;  // Advances by 1 byte
    cout << "After ptr += 1: " << static_cast<void*>(char_ptr) << endl;
    
    cout << "\nInt pointer:" << endl;
    cout << "Initial address: " << int_ptr << endl;
    int_ptr += 1;  // Advances by sizeof(int) bytes (typically 4)
    cout << "After ptr += 1: " << int_ptr << endl;
    
    cout << "\nDouble pointer:" << endl;
    cout << "Initial address: " << double_ptr << endl;
    double_ptr += 1;  // Advances by sizeof(double) bytes (typically 8)
    cout << "After ptr += 1: " << double_ptr << endl;
    
    return 0;
}
```

Note: We use `static_cast<void*>` for the char pointer because `cout` would interpret a `char*` as a C-string and try to print the characters it points to.

### Pointer Subtraction

You can subtract pointers of the same type to find the number of elements between them:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* start = numbers;        // Points to first element
    int* end = &numbers[4];      // Points to last element
    
    ptrdiff_t elements = end - start;
    cout << "Elements between pointers: " << elements << endl;  // 4
    
    return 0;
}
```

### Pointer Comparison

Pointers can be compared using relational operators:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* p1 = &numbers[1];  // Points to 20
    int* p2 = &numbers[3];  // Points to 40
    
    if (p1 < p2) {
        cout << "p1 points to an element before p2" << endl;
    } else {
        cout << "p1 points to an element after or equal to p2" << endl;
    }
    
    cout << "Elements between p1 and p2: " << (p2 - p1) << endl;
    
    return 0;
}
```

### Traversing Arrays with Pointers

Pointers provide an efficient way to traverse arrays:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* end = numbers + 5;  // Points past the last element
    
    cout << "Method 1: Using pointer arithmetic in a for loop" << endl;
    for (int* ptr = numbers; ptr < end; ptr++) {
        cout << *ptr << " ";
    }
    cout << endl;
    
    cout << "Method 2: Using array indexing with pointer arithmetic" << endl;
    int* base = numbers;
    for (int i = 0; i < 5; i++) {
        cout << *(base + i) << " ";  // Equivalent to base[i]
    }
    cout << endl;
    
    cout << "Method 3: Using a while loop" << endl;
    int* ptr = numbers;
    while (ptr < end) {
        cout << *ptr++ << " ";  // Print current value, then increment pointer
    }
    cout << endl;
    
    return 0;
}
```

### Limitations and Safety Concerns

1. **Going Beyond Bounds**

If you increment or decrement a pointer beyond the bounds of the array it initially pointed to, you'll be accessing invalid memory locations:

```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr;
ptr += 10;  // Points far beyond the array
*ptr = 100;  // DANGER: Undefined behavior, potential crash
```

2. **Invalid Operations**

You cannot:
- Add two pointers
- Multiply or divide pointers
- Perform bitwise operations on pointers

```cpp
int* p1 = &x;
int* p2 = &y;
int* sum = p1 + p2;  // Error: Cannot add two pointers
```

3. **Arithmetic on void Pointers**

Pointer arithmetic on void pointers isn't allowed without casting:

```cpp
void* ptr = &x;
ptr++;  // Error: Cannot increment void pointer
void* next = static_cast<char*>(ptr) + 1;  // Cast first
```

### Real-World Applications

1. **Implementing Custom String Functions**

```cpp
#include <iostream>
using namespace std;

// Custom strlen function
size_t custom_strlen(const char* str) {
    const char* start = str;
    // Increment until null terminator is found
    while (*str != '\0') {
        str++;
    }
    return str - start;  // Distance is the length
}

int main() {
    const char* message = "Hello, World!";
    cout << "Length of string: " << custom_strlen(message) << endl;
    return 0;
}
```

2. **Efficient Array Processing**

```cpp
#include <iostream>
using namespace std;

// Sum array elements using pointer arithmetic
int sum_array(const int* arr, int size) {
    const int* end = arr + size;
    int total = 0;
    
    while (arr < end) {
        total += *arr++;
    }
    
    return total;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    cout << "Sum of array: " << sum_array(numbers, 5) << endl;
    return 0;
}
```

### Best Practices for Pointer Arithmetic

1. **Always check bounds**
   ```cpp
   if (ptr >= array && ptr < array + size) {
       // Safe to dereference
   }
   ```

2. **Use modern C++ containers when possible**
   ```cpp
   #include <vector>
   vector<int> numbers = {10, 20, 30, 40, 50};
   // No manual pointer manipulation needed
   ```

3. **Consider using iterators instead**
   ```cpp
   for (auto it = numbers.begin(); it != numbers.end(); ++it) {
       cout << *it << " ";
   }
   ```

4. **Prefer array indexing for better readability**
   ```cpp
   int arr[5] = {10, 20, 30, 40, 50};
   // Instead of *(arr + i), prefer arr[i]
   ```

## 5.3 Pointers and Arrays

In C++, arrays and pointers are closely related. Understanding this relationship is fundamental to mastering C++ memory management.

### The Relationship Between Arrays and Pointers

When you use an array name in most expressions, it "decays" (is implicitly converted) into a pointer to its first element:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    int* ptr = numbers;  // Same as &numbers[0]
    
    cout << "Array name: " << numbers << endl;
    cout << "Address of first element: " << &numbers[0] << endl;
    cout << "Pointer value: " << ptr << endl;
    
    // All three point to the same memory location
    
    return 0;
}
```

### Key Differences Between Arrays and Pointers

Despite this close relationship, arrays and pointers are not identical:

1. **Size Information**
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    int* ptr = numbers;
    
    cout << "sizeof(numbers): " << sizeof(numbers) << " bytes" << endl;  // 5 * sizeof(int)
    cout << "sizeof(ptr): " << sizeof(ptr) << " bytes" << endl;  // Size of pointer only
    
    return 0;
}
```

The array name holds the size information, while a pointer doesn't.

2. **Reassignment**
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr;

ptr = nullptr;  // OK - pointer can be reassigned
// arr = nullptr;  // ERROR - array name cannot be reassigned
```

3. **Behavior in sizeof**
```cpp
int arr[5];
int* ptr = arr;

sizeof(arr);  // Returns 5 * sizeof(int)
sizeof(ptr);  // Returns sizeof(pointer), typically 4 or 8 bytes
```

4. **Array Decay When Passing to Functions**
```cpp
#include <iostream>
using namespace std;

void printSize(int arr[]) {
    // arr is a pointer here, not an array
    cout << "Size inside function: " << sizeof(arr) << " bytes" << endl;  // Size of pointer
}

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    cout << "Size in main: " << sizeof(numbers) << " bytes" << endl;  // 5 * sizeof(int)
    
    printSize(numbers);
    
    return 0;
}
```

### Accessing Array Elements with Pointers

You can access array elements using pointers in several ways:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    int* ptr = numbers;
    
    // Method 1: Array notation with array name
    cout << "numbers[2]: " << numbers[2] << endl;
    
    // Method 2: Pointer arithmetic with array name
    cout << "*(numbers + 2): " << *(numbers + 2) << endl;
    
    // Method 3: Array notation with pointer
    cout << "ptr[2]: " << ptr[2] << endl;
    
    // Method 4: Pointer arithmetic with pointer
    cout << "*(ptr + 2): " << *(ptr + 2) << endl;
    
    return 0;
}
```

All four methods access the same element (the third element, value 30).

### Multi-dimensional Arrays and Pointers

Working with multi-dimensional arrays using pointers is more complex:

```cpp
#include <iostream>
using namespace std;

int main() {
    int matrix[3][4] = {
        {11, 12, 13, 14},
        {21, 22, 23, 24},
        {31, 32, 33, 34}
    };
    
    // Pointer to the first row
    int (*rowPtr)[4] = matrix;
    cout << "First element via row pointer: " << (*rowPtr)[0] << endl;  // 11
    
    // Pointer to the first element
    int* elemPtr = &matrix[0][0];
    cout << "First element via element pointer: " << *elemPtr << endl;  // 11
    
    // Access elements
    cout << "Element at row 1, col 2: " << *(*(rowPtr + 1) + 2) << endl;  // 23
    cout << "Same element using direct access: " << matrix[1][2] << endl;  // 23
    
    // Accessing matrix elements with a single pointer
    cout << "Using linear indexing with element pointer:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << *(elemPtr + i*4 + j) << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

### Dynamic Arrays with Pointers

Pointers are essential for creating dynamically-sized arrays:

```cpp
#include <iostream>
using namespace std;

int main() {
    int size;
    cout << "Enter size for dynamic array: ";
    cin >> size;
    
    // Allocate memory
    int* dynamicArray = new int[size];
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 10;
    }
    
    // Print values
    cout << "Array values:" << endl;
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // Free memory
    delete[] dynamicArray;
    
    return 0;
}
```

### Creating Dynamic 2D Arrays

There are several approaches to creating dynamic 2D arrays:

```cpp
#include <iostream>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    
    // Method 1: Array of pointers
    int** array1 = new int*[rows];
    for (int i = 0; i < rows; i++) {
        array1[i] = new int[cols];
        // Initialize
        for (int j = 0; j < cols; j++) {
            array1[i][j] = i * cols + j;
        }
    }
    
    // Method 2: Single block with manual indexing
    int* array2 = new int[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array2[i * cols + j] = i * cols + j;
        }
    }
    
    // Clean up Method 1
    for (int i = 0; i < rows; i++) {
        delete[] array1[i];
    }
    delete[] array1;
    
    // Clean up Method 2
    delete[] array2;
    
    return 0;
}
```

### Arrays of Pointers vs. Pointers to Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    // Array of pointers
    int* ptr_array[3];  // Array of 3 int pointers
    
    // Initialize with pointers to different variables
    int a = 10, b = 20, c = 30;
    ptr_array[0] = &a;
    ptr_array[1] = &b;
    ptr_array[2] = &c;
    
    cout << "Array of pointers values: ";
    for (int i = 0; i < 3; i++) {
        cout << *ptr_array[i] << " ";
    }
    cout << endl;
    
    // Pointer to an array
    int numbers[5] = {1, 2, 3, 4, 5};
    int (*array_ptr)[5] = &numbers;  // Pointer to an array of 5 ints
    
    cout << "Values through array pointer: ";
    for (int i = 0; i < 5; i++) {
        cout << (*array_ptr)[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Best Practices for Arrays and Pointers

1. **Prefer Modern Alternatives**
   ```cpp
   #include <vector>
   #include <array>
   
   // Instead of raw dynamic arrays
   vector<int> dynamicArray(size);
   
   // Instead of fixed-size arrays
   array<int, 5> fixedArray = {1, 2, 3, 4, 5};
   ```

2. **Pass Array Size**
   ```cpp
   void processArray(int* arr, int size) {
       // Always include size information
   }
   ```

3. **Use Range-based For Loops When Possible**
   ```cpp
   for (int value : fixedArray) {
       cout << value << " ";
   }
   ```

4. **Consider Templates for Size Safety**
   ```cpp
   template<size_t N>
   void processArray(int (&arr)[N]) {
       // Size is known at compile time
       for (size_t i = 0; i < N; i++) {
           // Process arr[i]
       }
   }
   ```

5. **Avoid Pointer Arithmetic When Better Alternatives Exist**
   ```cpp
   // Prefer this
   for (int i = 0; i < size; i++) {
       cout << arr[i];
   }
   
   // Over this
   for (int* p = arr; p < arr + size; p++) {
       cout << *p;
   }
   ```

## 5.4 Pointers to Functions

Function pointers allow you to store and invoke functions dynamically. They're essential for callbacks, plugins, and implementing function dispatch tables.

### Basic Function Pointer Syntax

The syntax for declaring a function pointer is:

```cpp
return_type (*pointer_name)(parameter_types);
```

Example:

```cpp
#include <iostream>
using namespace std;

// Function to be pointed to
int add(int x, int y) {
    return x + y;
}

int main() {
    // Declare function pointer
    int (*operation)(int, int);
    
    // Assign function address to the pointer
    operation = add;  // No & needed, function name decays to address
    
    // Call the function via pointer
    int result = operation(5, 3);
    cout << "Result: " << result << endl;  // 8
    
    return 0;
}
```

### Using typedef and using for Function Pointers

To simplify complicated function pointer syntax, use `typedef` or `using`:

```cpp
#include <iostream>
using namespace std;

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
int divide(int x, int y) { return y != 0 ? x / y : 0; }

// Old style with typedef
typedef int (*MathFunction)(int, int);

// Modern style with using (C++11)
using Operation = int (*)(int, int);

int main() {
    MathFunction op1 = add;
    Operation op2 = multiply;
    
    cout << "5 + 3 = " << op1(5, 3) << endl;  // 8
    cout << "5 * 3 = " << op2(5, 3) << endl;  // 15
    
    return 0;
}
```

### Arrays of Function Pointers

Function pointers can be organized into arrays to create function tables:

```cpp
#include <iostream>
using namespace std;

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
int divide(int x, int y) { return y != 0 ? x / y : 0; }

int main() {
    // Array of function pointers
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};
    string op_names[4] = {"+", "-", "*", "/"};
    
    int a = 10, b = 5;
    
    // Use each function in the array
    for (int i = 0; i < 4; i++) {
        cout << a << " " << op_names[i] << " " << b << " = ";
        cout << operations[i](a, b) << endl;
    }
    
    return 0;
}
```

### Function Pointers as Arguments

Function pointers allow you to pass behavior to other functions:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Takes a function pointer as parameter
void transform(vector<int>& values, int (*func)(int)) {
    for (size_t i = 0; i < values.size(); i++) {
        values[i] = func(values[i]);
    }
}

// Functions to be passed
int square(int x) { return x * x; }
int triple(int x) { return x * 3; }

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    cout << "Original values: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    // Apply square function
    transform(numbers, square);
    cout << "After square: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    // Apply triple function
    transform(numbers, triple);
    cout << "After triple: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    return 0;
}
```

### Member Function Pointers

Member function pointers are used to point to class methods:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    int add(int x, int y) { return x + y; }
    int subtract(int x, int y) { return x - y; }
    int multiply(int x, int y) { return x * y; }
    int divide(int x, int y) { return y != 0 ? x / y : 0; }
};

int main() {
    // Declare a member function pointer
    int (Calculator::*operation)(int, int) = &Calculator::add;
    
    // Create an object
    Calculator calc;
    
    // Call the member function through the pointer
    cout << "5 + 3 = " << (calc.*operation)(5, 3) << endl;
    
    // Change the function pointer
    operation = &Calculator::multiply;
    cout << "5 * 3 = " << (calc.*operation)(5, 3) << endl;
    
    return 0;
}
```

### Function Pointers vs. std::function (C++11)

Modern C++ provides `std::function` for more flexibility:

```cpp
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// Traditional function
int add(int x, int y) { return x + y; }

// Function object (functor)
struct Multiplier {
    int operator()(int x, int y) const { return x * y; }
};

int main() {
    // Different ways to create std::function objects
    function<int(int,int)> f1 = add;
    function<int(int,int)> f2 = [](int x, int y) { return x - y; };  // Lambda
    function<int(int,int)> f3 = Multiplier();  // Function object
    
    cout << "10 + 5 = " << f1(10, 5) << endl;
    cout << "10 - 5 = " << f2(10, 5) << endl;
    cout << "10 * 5 = " << f3(10, 5) << endl;
    
    // Store in a container
    vector<function<int(int,int)>> operations = {f1, f2, f3};
    
    int x = 20, y = 4;
    for (auto& op : operations) {
        cout << "Result: " << op(x, y) << endl;
    }
    
    return 0;
}
```

### Practical Applications

1. **Callbacks**

```cpp
#include <iostream>
#include <functional>
using namespace std;

class Button {
private:
    string label;
    function<void()> clickHandler;
    
public:
    Button(const string& text, function<void()> handler)
        : label(text), clickHandler(handler) {}
    
    void click() {
        cout << "Button '" << label << "' clicked!" << endl;
        if (clickHandler) {
            clickHandler();
        }
    }
};

void sayHello() {
    cout << "Hello, World!" << endl;
}

int main() {
    // Button with named function as callback
    Button btn1("Greet", sayHello);
    
    // Button with lambda as callback
    Button btn2("Exit", []() {
        cout << "Exiting application..." << endl;
    });
    
    btn1.click();  // Triggers sayHello
    btn2.click();  // Triggers lambda
    
    return 0;
}
```

2. **Strategy Pattern**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Different sorting strategies
bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

class Sorter {
private:
    function<bool(int,int)> compareStrategy;
    
public:
    Sorter(function<bool(int,int)> strategy) : compareStrategy(strategy) {}
    
    void sort(vector<int>& data) {
        std::sort(data.begin(), data.end(), compareStrategy);
    }
};

int main() {
    vector<int> numbers = {5, 2, 9, 1, 7, 3};
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Sort with ascending strategy
    Sorter ascendingSorter(ascending);
    ascendingSorter.sort(numbers);
    
    cout << "Ascending: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Sort with descending strategy
    Sorter descendingSorter(descending);
    descendingSorter.sort(numbers);
    
    cout << "Descending: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

3. **Plugin Architecture**

```cpp
#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

// Plugin interface
using PluginFunction = function<void(const string&)>;

class PluginManager {
private:
    map<string, PluginFunction> plugins;
    
public:
    void registerPlugin(const string& name, PluginFunction func) {
        plugins[name] = func;
    }
    
    void executePlugin(const string& name, const string& data) {
        auto it = plugins.find(name);
        if (it != plugins.end()) {
            it->second(data);
        } else {
            cout << "Plugin '" << name << "' not found!" << endl;
        }
    }
};

// Plugin implementations
void textPlugin(const string& data) {
    cout << "Text Plugin: Processing '" << data << "'" << endl;
}

void numberPlugin(const string& data) {
    try {
        int value = stoi(data);
        cout << "Number Plugin: Received " << value << ", square is " << (value * value) << endl;
    } catch (...) {
        cout << "Number Plugin: Invalid number format" << endl;
    }
}

int main() {
    PluginManager manager;
    
    // Register plugins
    manager.registerPlugin("text", textPlugin);
    manager.registerPlugin("number", numberPlugin);
    manager.registerPlugin("logger", [](const string& data) {
        cout << "LOG: " << data << endl;
    });
    
    // Execute plugins
    manager.executePlugin("text", "Hello, World!");
    manager.executePlugin("number", "42");
    manager.executePlugin("logger", "Application started");
    manager.executePlugin("unknown", "test");  // Not found
    
    return 0;
}
```

### Best Practices for Function Pointers

1. **Prefer std::function for complex use cases**
   ```cpp
   // Instead of:
   void (*callback)(int, const string&);
   
   // Use:
   function<void(int, const string&)> callback;
   ```

2. **Check for null before calling**
   ```cpp
   if (callback != nullptr) {
       callback(42, "test");
   }
   ```

3. **Use meaningful typedefs or using statements**
   ```cpp
   using ErrorHandler = void (*)(const string&, int);
   ```

4. **Consider alternatives**
   - Templates for compile-time polymorphism
   - Virtual functions for object-oriented polymorphism
   - Lambda expressions for simple callbacks

5. **Document expected behavior**
   ```cpp
   // Takes a comparison function that should return:
   // - Negative value if a < b
   // - Zero if a == b
   // - Positive value if a > b
   void sort(int* array, int size, int (*compare)(int a, int b));
   ```
