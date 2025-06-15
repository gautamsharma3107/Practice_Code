# Chapter 2: Variables, Data Types & Operators

## 2.1 Variable Declaration & Initialization

Variables are named storage locations in memory that hold values that can be modified during program execution. In C++, every variable must be declared before it can be used.

### Declaration Syntax
```cpp
data_type variable_name;  // Declaration
data_type variable_name = initial_value;  // Declaration with initialization
```

### Examples
```cpp
int count;          // Declaration
int score = 100;    // Declaration with initialization
double price = 45.60, tax = 5.5;  // Multiple declarations
char grade = 'A';   // Character initialization
bool isActive = true;  // Boolean initialization
```

### Variable Naming Rules
- Must begin with a letter or underscore (_)
- Can consist of letters, digits, and underscores
- Cannot use C++ keywords (like int, class, return, etc.)
- C++ is case-sensitive (count and Count are different variables)

### Best Practices
- Use meaningful names that indicate the variable's purpose
- Follow a consistent naming convention (e.g., camelCase or snake_case)
- Initialize variables when declared to avoid undefined behavior
- Keep variables scoped as tightly as possible

### Memory Sizes
Memory allocated depends on the data type and platform:
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " byte" << endl;
    cout << "Size of bool: " << sizeof(bool) << " byte" << endl;
    return 0;
}
```

### Variable Scope and Lifetime
- **Local variables**: Declared within a function or block, exist only within that scope
- **Global variables**: Declared outside any function, accessible throughout the program
- **Static variables**: Retain value between function calls

```cpp
#include <iostream>
using namespace std;

int globalVar = 10;  // Global variable

void demoFunction() {
    static int staticVar = 0;  // Static variable
    int localVar = 5;          // Local variable
    
    staticVar++;
    localVar++;
    
    cout << "Global: " << globalVar << ", Static: " << staticVar << ", Local: " << localVar << endl;
}

int main() {
    demoFunction();  // Output: Global: 10, Static: 1, Local: 6
    demoFunction();  // Output: Global: 10, Static: 2, Local: 6
    demoFunction();  // Output: Global: 10, Static: 3, Local: 6
    return 0;
}
```

## 2.2 Data Types: Primitive & Derived

C++ offers various data types that can be broadly categorized as primitive (built-in) and derived (user-defined).

### Primitive Data Types

#### Integer Types
- **int**: Standard integer type (-2,147,483,648 to 2,147,483,647)
- **short**: Small integer (-32,768 to 32,767)
- **long**: Large integer (at least 32 bits)
- **long long**: Very large integer (at least 64 bits)
- **unsigned** variants: Store only positive numbers, doubling the positive range

```cpp
int regular = 42;
short small = 32767;
long large = 2147483647L;  // Note the 'L' suffix
long long veryLarge = 9223372036854775807LL;  // Note the 'LL' suffix
unsigned int positiveOnly = 4294967295U;  // Note the 'U' suffix
```

#### Floating Point Types
- **float**: Single precision (7 digits precision), ~1.2E-38 to ~3.4E+38
- **double**: Double precision (15 digits precision), ~2.3E-308 to ~1.7E+308
- **long double**: Extended precision (platform dependent)

```cpp
float price = 19.99f;  // Note the 'f' suffix
double pi = 3.14159265359;
long double veryPrecise = 3.14159265359L;  // Note the 'L' suffix
```

#### Character Types
- **char**: Single character (1 byte)
- **wchar_t**: Wide character (typically 2 or 4 bytes)
- **char16_t**: UTF-16 character (C++11)
- **char32_t**: UTF-32 character (C++11)

```cpp
char letter = 'A';
wchar_t wideLetter = L'Ω';  // Note the 'L' prefix
char16_t utf16Char = u'π';  // Note the 'u' prefix
char32_t utf32Char = U'😊';  // Note the 'U' prefix
```

#### Boolean Type
- **bool**: Represents true or false values

```cpp
bool isValid = true;
bool isEmpty = false;
```

#### Void Type
- **void**: Represents absence of type, used primarily for functions that don't return a value

### Modified Data Types
C++ provides modifiers to alter the range and memory usage of basic types:

- **signed**: Can represent both positive and negative numbers (default for int)
- **unsigned**: Can only represent positive numbers
- **short**: Reduces size
- **long**: Increases size

```cpp
signed int canBeNegative = -42;  // Same as just "int"
unsigned int onlyPositive = 42;
short int smallRange = 100;
long int largeRange = 1000000L;
```

### Derived Data Types

#### Arrays
Collection of elements of the same type.
```cpp
int numbers[5] = {1, 2, 3, 4, 5};
char name[10] = "C++";
```

#### Pointers
Store memory addresses of variables.
```cpp
int* ptr;
int value = 42;
ptr = &value;  // ptr now holds the address of value
```

#### References
An alias for an existing variable.
```cpp
int original = 10;
int& ref = original;  // ref is a reference to original
ref = 20;  // Changes original to 20 as well
```

#### User-Defined Types

- **struct**: Collection of variables of different types
```cpp
struct Person {
    string name;
    int age;
    double height;
};

Person person1 = {"John Doe", 30, 5.9};
```

- **class**: Foundation of object-oriented programming
```cpp
class BankAccount {
private:
    double balance;
public:
    BankAccount(double initialBalance) : balance(initialBalance) {}
    void deposit(double amount) { balance += amount; }
    double getBalance() { return balance; }
};
```

- **union**: Stores different data types in the same memory location
```cpp
union Data {
    int i;
    float f;
    char str[20];
};

Data data;
data.i = 10;  // Now data.i is active
data.f = 3.14f;  // data.i is no longer valid, data.f is active
```

- **enum**: User-defined type consisting of named constants
```cpp
enum Color {RED, GREEN, BLUE};
Color myColor = RED;
```

### Type Aliases
C++ allows creating aliases for types:

```cpp
// Using typedef (traditional approach)
typedef unsigned long ulong;
ulong counter = 0;

// Using using (modern approach, C++11)
using Integer = int;
Integer value = 42;
```

## 2.3 Type Conversion & Typecasting

Type conversion refers to converting one data type to another. It can happen implicitly (automatically) or explicitly (through casting).

### Implicit Type Conversion (Automatic)

C++ automatically converts between types when an operation involves different data types:

```cpp
int i = 10;
double d = i;  // Implicit conversion from int to double (d = 10.0)

char c = 'A';
int ascii = c;  // Implicit conversion from char to int (ascii = 65)

bool b = 42;  // Implicit conversion from int to bool (b = true)
```

#### Conversion Rules
1. During an expression evaluation, smaller data types are converted to larger data types
2. Integral types (int, char, etc.) are converted to floating-point types when mixed
3. The result of an operation has the type of the most "capacious" operand

#### Promotion
Implicit conversion of smaller types to larger types:
```cpp
short s = 10;
int i = s;  // Short to int
float f = i;  // Int to float
double d = f;  // Float to double
```

#### Demotion
Implicit conversion of larger types to smaller types (may result in data loss):
```cpp
double d = 9.99;
int i = d;  // i becomes 9, fractional part is truncated
```

### Explicit Type Conversion (Typecasting)

C++ provides several ways to explicitly convert data types:

#### C-style Cast
```cpp
double d = 3.14159;
int i = (int)d;  // i becomes 3
```

#### Function-style Cast
```cpp
float f = 3.14f;
int i = int(f);  // i becomes 3
```

#### C++ Style Cast Operators

1. **static_cast**: For "well-behaved" conversions
```cpp
double d = 3.14159;
int i = static_cast<int>(d);  // i becomes 3
```

2. **dynamic_cast**: For safe downcasting in inheritance hierarchies
```cpp
Base* basePtr = new Derived();
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);  // Safe conversion, checks at runtime
```

3. **const_cast**: To add or remove const qualifier
```cpp
const int value = 10;
int* ptr = const_cast<int*>(&value);  // Removes const
```

4. **reinterpret_cast**: For low-level reinterpreting of bit patterns
```cpp
int* p = new int(65);
char* ch = reinterpret_cast<char*>(p);  // Dangerous, reinterprets memory
```

### Potential Issues with Type Conversion

#### Overflow
```cpp
int largeValue = 2147483647;  // Maximum int value
largeValue++;  // Overflow: largeValue becomes -2147483648
```

#### Precision Loss
```cpp
double precise = 3.14159265359;
float lessPrecise = precise;  // Precision is lost
```

#### Sign Issues
```cpp
unsigned int positive = 10;
int value = -5;
if (positive < value) {
    cout << "This will execute unexpectedly!";  // This executes because -5 converts to a large unsigned value
}
```

### Best Practices

1. Avoid mixing signed and unsigned types in expressions
2. Prefer C++ style casts over C-style casts
3. Be aware of potential data loss when converting between types
4. Use explicit casting when the conversion may not be intuitive
5. Use numeric_limits<T> to check value ranges before conversion

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    double d = 123456789.0;
    if (d <= numeric_limits<int>::max() && d >= numeric_limits<int>::min()) {
        int i = static_cast<int>(d);
        cout << "Safe conversion: " << i << endl;
    } else {
        cout << "Unsafe conversion: value out of range" << endl;
    }
    return 0;
}
```

## 2.4 Operators in C++

Operators allow you to perform various operations on variables and values. C++ provides a rich set of operators.

### 2.4.1 Arithmetic Operators

Arithmetic operators perform mathematical calculations.

| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `a + b` |
| `-` | Subtraction | `a - b` |
| `*` | Multiplication | `a * b` |
| `/` | Division | `a / b` |
| `%` | Modulus (remainder) | `a % b` |
| `++` | Increment | `a++` or `++a` |
| `--` | Decrement | `a--` or `--a` |

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;
    
    cout << "a + b = " << (a + b) << endl;  // 13
    cout << "a - b = " << (a - b) << endl;  // 7
    cout << "a * b = " << (a * b) << endl;  // 30
    cout << "a / b = " << (a / b) << endl;  // 3 (integer division)
    cout << "a % b = " << (a % b) << endl;  // 1 (remainder)
    
    int c = a++;  // c = 10, then a becomes 11 (post-increment)
    int d = ++b;  // b becomes 4, then d = 4 (pre-increment)
    
    cout << "a after post-increment: " << a << endl;  // 11
    cout << "b after pre-increment: " << b << endl;   // 4
    cout << "c after assigning a++: " << c << endl;   // 10
    cout << "d after assigning ++b: " << d << endl;   // 4
    
    return 0;
}
```

#### Important Notes
- Integer division truncates decimal part: `5 / 2` gives `2`, not `2.5`
- Modulus works only with integers and gives the remainder: `5 % 2` gives `1`
- Pre-increment (`++a`) increments first, then uses the value
- Post-increment (`a++`) uses the current value, then increments
- Division by zero causes runtime errors

### 2.4.2 Relational Operators

Relational operators compare two values and return a boolean result.

| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal to | `a == b` |
| `!=` | Not equal to | `a != b` |
| `>` | Greater than | `a > b` |
| `<` | Less than | `a < b` |
| `>=` | Greater than or equal to | `a >= b` |
| `<=` | Less than or equal to | `a <= b` |

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    
    cout << "a == b: " << (a == b) << endl;  // 0 (false)
    cout << "a != b: " << (a != b) << endl;  // 1 (true)
    cout << "a > b: " << (a > b) << endl;    // 0 (false)
    cout << "a < b: " << (a < b) << endl;    // 1 (true)
    cout << "a >= b: " << (a >= b) << endl;  // 0 (false)
    cout << "a <= b: " << (a <= b) << endl;  // 1 (true)
    
    return 0;
}
```

#### Best Practices
- Use `==` for equality comparison, not `=` (which is assignment)
- Be careful when comparing floating-point numbers due to precision issues
- Use appropriate epsilon values for floating-point comparisons
- Avoid comparing unsigned with signed integers

```cpp
// Proper floating-point comparison
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    double a = 0.1 + 0.2;
    double b = 0.3;
    
    // Direct comparison may fail due to precision
    cout << "a == b: " << (a == b) << endl;  // May print 0 (false)
    
    // Better approach with epsilon
    const double epsilon = 1e-9;
    cout << "Proper comparison: " << (abs(a - b) < epsilon) << endl;  // 1 (true)
    
    return 0;
}
```

### 2.4.3 Logical Operators

Logical operators combine boolean expressions.

| Operator | Description | Example |
|----------|-------------|---------|
| `&&` | Logical AND | `a && b` |
| `\|\|` | Logical OR | `a \|\| b` |
| `!` | Logical NOT | `!a` |

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;
    
    cout << "a && b: " << (a && b) << endl;  // 0 (false)
    cout << "a || b: " << (a || b) << endl;  // 1 (true)
    cout << "!a: " << (!a) << endl;          // 0 (false)
    cout << "!b: " << (!b) << endl;          // 1 (true)
    
    // Compound expressions
    cout << "(a || b) && (!b): " << ((a || b) && (!b)) << endl;  // 1 (true)
    
    // Short-circuit evaluation
    int x = 5, y = 0;
    if (y != 0 && x / y > 2) {  // y != 0 is false, so x / y is not evaluated (prevents division by zero)
        cout << "This won't execute" << endl;
    }
    
    return 0;
}
```

#### Short-Circuit Evaluation
- In `expr1 && expr2`, if `expr1` is false, `expr2` is not evaluated
- In `expr1 || expr2`, if `expr1` is true, `expr2` is not evaluated
- This prevents potential errors like division by zero or null pointer access

#### Truth Table

| A | B | A && B | A \|\| B | !A |
|---|---|--------|---------|-----|
| T | T | T      | T       | F   |
| T | F | F      | T       | F   |
| F | T | F      | T       | T   |
| F | F | F      | F       | T   |

### 2.4.4 Bitwise Operators

Bitwise operators perform operations at the binary (bit) level.

| Operator | Description | Example |
|----------|-------------|---------|
| `&` | Bitwise AND | `a & b` |
| `\|` | Bitwise OR | `a \| b` |
| `^` | Bitwise XOR | `a ^ b` |
| `~` | Bitwise NOT | `~a` |
| `<<` | Left shift | `a << n` |
| `>>` | Right shift | `a >> n` |

#### Examples

```cpp
#include <iostream>
#include <bitset>  // For binary representation
using namespace std;

int main() {
    int a = 5;  // 0101 in binary
    int b = 3;  // 0011 in binary
    
    cout << "Binary a: " << bitset<8>(a) << endl;
    cout << "Binary b: " << bitset<8>(b) << endl;
    
    cout << "a & b: " << (a & b) << " (" << bitset<8>(a & b) << ")" << endl;       // 1 (0001)
    cout << "a | b: " << (a | b) << " (" << bitset<8>(a | b) << ")" << endl;       // 7 (0111)
    cout << "a ^ b: " << (a ^ b) << " (" << bitset<8>(a ^ b) << ")" << endl;       // 6 (0110)
    cout << "~a: " << (~a) << " (" << bitset<8>(~a) << ")" << endl;                // -6
    cout << "a << 1: " << (a << 1) << " (" << bitset<8>(a << 1) << ")" << endl;    // 10 (1010)
    cout << "a >> 1: " << (a >> 1) << " (" << bitset<8>(a >> 1) << ")" << endl;    // 2 (0010)
    
    return 0;
}
```

#### Common Bitwise Applications

1. **Setting a bit**: `number |= (1 << position)`
2. **Clearing a bit**: `number &= ~(1 << position)`
3. **Toggling a bit**: `number ^= (1 << position)`
4. **Checking a bit**: `(number & (1 << position)) != 0`
5. **Power of 2 multiplication**: `number << n` (multiplies by 2ⁿ)
6. **Power of 2 division**: `number >> n` (divides by 2ⁿ)

```cpp
int num = 42;  // 00101010 in binary
int position = 3;

// Set bit at position 3
num |= (1 << position);  // num becomes 50 (00110010)

// Clear bit at position 3
num &= ~(1 << position);  // num becomes 42 again (00101010)

// Toggle bit at position 3
num ^= (1 << position);  // num becomes 50 (00110010)

// Check bit at position 3
bool isBitSet = (num & (1 << position)) != 0;  // true
```

#### Bit Manipulation Techniques

- **Swapping without temp variable**:
```cpp
a ^= b;
b ^= a;
a ^= b;
```

- **Finding the rightmost set bit**:
```cpp
int rightmostSetBit = num & -num;
```

- **Counting set bits (Brian Kernighan's Algorithm)**:
```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Clear the rightmost set bit
        count++;
    }
    return count;
}
```

### 2.4.5 Assignment Operators

Assignment operators assign values to variables.

| Operator | Description | Example | Equivalent |
|----------|-------------|---------|------------|
| `=` | Simple assignment | `a = b` | `a = b` |
| `+=` | Add and assign | `a += b` | `a = a + b` |
| `-=` | Subtract and assign | `a -= b` | `a = a - b` |
| `*=` | Multiply and assign | `a *= b` | `a = a * b` |
| `/=` | Divide and assign | `a /= b` | `a = a / b` |
| `%=` | Modulus and assign | `a %= b` | `a = a % b` |
| `&=` | Bitwise AND and assign | `a &= b` | `a = a & b` |
| `\|=` | Bitwise OR and assign | `a \|= b` | `a = a \| b` |
| `^=` | Bitwise XOR and assign | `a ^= b` | `a = a ^ b` |
| `<<=` | Left shift and assign | `a <<= b` | `a = a << b` |
| `>>=` | Right shift and assign | `a >>= b` | `a = a >> b` |

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    
    a += 5;  // a becomes 15
    cout << "After a += 5: a = " << a << endl;
    
    a -= 3;  // a becomes 12
    cout << "After a -= 3: a = " << a << endl;
    
    a *= 2;  // a becomes 24
    cout << "After a *= 2: a = " << a << endl;
    
    a /= 4;  // a becomes 6
    cout << "After a /= 4: a = " << a << endl;
    
    a %= 4;  // a becomes 2
    cout << "After a %= 4: a = " << a << endl;
    
    a <<= 3;  // a becomes 16
    cout << "After a <<= 3: a = " << a << endl;
    
    a >>= 2;  // a becomes 4
    cout << "After a >>= 2: a = " << a << endl;
    
    return 0;
}
```

#### Chained Assignments
```cpp
int x, y, z;
x = y = z = 10;  // All three variables get value 10
```

#### Compound Assignment Benefits
1. More concise code
2. Potentially more efficient (the expression is evaluated once)
3. Less prone to typing errors

### 2.4.6 Ternary Operator

The ternary conditional operator `?:` is the only operator in C++ that takes three operands.

**Syntax**: `condition ? expression1 : expression2`

- If `condition` is true, `expression1` is evaluated
- If `condition` is false, `expression2` is evaluated

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    // Simple usage
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    cout << "Maximum: " << max << endl;  // 20
    
    // Using with cout
    cout << "a is " << ((a % 2 == 0) ? "even" : "odd") << endl;  // a is even
    
    // Nested ternary
    int x = 5;
    string result = (x > 10) ? "Greater than 10" : 
                   (x > 5) ? "Between 6 and 10" :
                   (x == 5) ? "Equal to 5" : "Less than 5";
    cout << result << endl;  // Equal to 5
    
    // Assignment with ternary
    int score = 85;
    char grade = (score >= 90) ? 'A' : 
                (score >= 80) ? 'B' :
                (score >= 70) ? 'C' :
                (score >= 60) ? 'D' : 'F';
    cout << "Grade: " << grade << endl;  // B
    
    return 0;
}
```

#### Benefits Over if-else
- More concise for simple conditions
- Can be used in expressions where if-else can't (like initializations)
- Often allows assigning a value in a single line

#### Best Practices
- Use for simple conditions where readability isn't compromised
- Avoid deeply nested ternary operations as they can be hard to read
- Use parentheses to make the intent clear
- Consider if-else for complex conditions for better readability

```cpp
// Less readable
string status = age < 13 ? "child" : age < 20 ? "teenager" : age < 65 ? "adult" : "senior";

// More readable
string status;
if (age < 13) status = "child";
else if (age < 20) status = "teenager";
else if (age < 65) status = "adult";
else status = "senior";
```

### 2.4.7 Operator Precedence & Associativity

Operator precedence determines the order in which operations are performed when an expression has multiple operators. Associativity determines the order of operations with the same precedence level.

#### Common Precedence Levels (from highest to lowest)

| Precedence | Operator | Description | Associativity |
|------------|----------|-------------|---------------|
| 1 | `::` | Scope resolution | Left to right |
| 2 | `++` `--` (postfix) | Postfix increment/decrement | Left to right |
| 2 | `()` | Function call | Left to right |
| 2 | `[]` | Array subscript | Left to right |
| 2 | `.` `->` | Member access | Left to right |
| 3 | `++` `--` (prefix) | Prefix increment/decrement | Right to left |
| 3 | `+` `-` (unary) | Unary plus/minus | Right to left |
| 3 | `!` `~` | Logical NOT, Bitwise NOT | Right to left |
| 3 | `(type)` | Type cast | Right to left |
| 3 | `*` | Dereference | Right to left |
| 3 | `&` | Address-of | Right to left |
| 3 | `sizeof` | Size-of | Right to left |
| 3 | `new` `delete` | Dynamic memory allocation | Right to left |
| 4 | `*` `/` `%` | Multiplication, Division, Modulus | Left to right |
| 5 | `+` `-` | Addition, Subtraction | Left to right |
| 6 | `<<` `>>` | Bitwise shift | Left to right |
| 7 | `<` `<=` `>` `>=` | Relational operators | Left to right |
| 8 | `==` `!=` | Equality operators | Left to right |
| 9 | `&` | Bitwise AND | Left to right |
| 10 | `^` | Bitwise XOR | Left to right |
| 11 | `\|` | Bitwise OR | Left to right |
| 12 | `&&` | Logical AND | Left to right |
| 13 | `\|\|` | Logical OR | Left to right |
| 14 | `?:` | Ternary conditional | Right to left |
| 15 | `=` `+=` `-=` etc. | Assignment operators | Right to left |
| 16 | `,` | Comma | Left to right |

#### Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    // Example 1: Arithmetic precedence
    int result1 = 10 + 5 * 2;  // * has higher precedence than +
    cout << "10 + 5 * 2 = " << result1 << endl;  // 20, not 30
    
    // Example 2: Using parentheses to override precedence
    int result2 = (10 + 5) * 2;
    cout << "(10 + 5) * 2 = " << result2 << endl;  // 30
    
    // Example 3: Assignment vs equality
    int x = 5;
    if (x = 10) {  // Assignment, not comparison! Sets x to 10, then evaluates to 10 (true)
        cout << "This will execute because x = 10 is an assignment that returns 10" << endl;
    }
    
    // Example 4: Associativity
    int a = 10, b = 5, c = 2;
    int result3 = a - b - c;  // Left-to-right: (a - b) - c
    cout << "10 - 5 - 2 = " << result3 << endl;  // 3, not 7
    
    // Example 5: Mixed operators
    int result4 = 10 * 5 + 3 * 2;  // (10 * 5) + (3 * 2)
    cout << "10 * 5 + 3 * 2 = " << result4 << endl;  // 56
    
    // Example 6: Complex expression
    int result5 = 5 + 3 * 8 / 4 - 2;  // 5 + ((3 * 8) / 4) - 2
    cout << "5 + 3 * 8 / 4 - 2 = " << result5 << endl;  // 9
    
    // Example 7: Assignment associativity (right to left)
    int d, e, f;
    d = e = f = 42;  // f = 42, then e = 42, then d = 42
    cout << "d = " << d << ", e = " << e << ", f = " << f << endl;
    
    return 0;
}
```

#### Common Precedence Mistakes

1. **Assignment vs. Equality**
```cpp
// Wrong
if (x = 5) { ... }  // Assigns 5 to x, then evaluates to true

// Correct
if (x == 5) { ... }  // Compares x with 5
```

2. **Boolean Logic Order**
```cpp
// This condition might not work as expected
if (a > 0 && b > 0 || c > 0 && d > 0) { ... }

// Better with explicit parentheses
if ((a > 0 && b > 0) || (c > 0 && d > 0)) { ... }
```

3. **Increment/Decrement with Other Operations**
```cpp
int i = 5;
int j = i++ + ++i;  // Undefined behavior due to multiple modifications

// Better approach: separate the operations
int i = 5;
int temp = i++;  // temp = 5, i = 6
int j = temp + ++i;  // j = 5 + 7 = 12, i = 7
```

#### Best Practices

1. Use parentheses to make your intentions clear and avoid relying on operator precedence rules
2. Break complex expressions into simpler ones using intermediate variables
3. Be particularly careful with:
   - Assignment in conditions
   - Bitwise operators vs logical operators
   - Increment/decrement operators in complex expressions
4. When in doubt, add parentheses to clarify the order of operations

```cpp
// Unclear
if (a == b && c == d || e == f && g == h) { ... }

// Clear
if (((a == b) && (c == d)) || ((e == f) && (g == h))) { ... }

// Or even better: break into smaller pieces
bool condition1 = (a == b) && (c == d);
bool condition2 = (e == f) && (g == h);
if (condition1 || condition2) { ... }
```

By understanding operator precedence and associativity, you can write more reliable and bug-free code, while also making your intentions clearer to others who read your code.
