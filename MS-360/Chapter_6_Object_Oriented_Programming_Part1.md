# Chapter 6: Object-Oriented Programming (Part 1)

## 6.1 Introduction to OOP

Object-Oriented Programming (OOP) is a programming paradigm that organizes code around "objects" rather than functions and logic. An object is a data structure that contains both data (attributes or properties) and code (methods or functions). OOP was developed to make complex software systems more manageable, maintainable, and reusable.

### Core Concepts of Object-Oriented Programming

#### 1. Classes and Objects

A **class** is a blueprint or template that defines the characteristics and behaviors of a specific type of object. An **object** is an instance of a class, representing a concrete entity with its own unique state.

```cpp
// Class definition
class Car {
    // Attributes and methods will go here
};

// Creating objects
Car sedan;      // First object of type Car
Car suv;        // Second object of type Car
```

#### 2. Encapsulation

**Encapsulation** is the bundling of data (attributes) and the methods that operate on that data into a single unit (class), and restricting direct access to some of the object's components. This helps to:

- Hide implementation details
- Control access to data
- Protect data integrity
- Reduce system complexity

```cpp
class BankAccount {
private:
    double balance;  // Hidden from outside access
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    bool withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double getBalance() {
        return balance;
    }
};
```

#### 3. Inheritance

**Inheritance** allows a class (subclass/derived class) to inherit attributes and methods from another class (superclass/base class). This promotes code reuse and establishes an "is-a" relationship between classes.

```cpp
class Vehicle {
public:
    void startEngine() {
        // Code to start engine
    }
};

class Car : public Vehicle {  // Car inherits from Vehicle
public:
    void accelerate() {
        // Car-specific acceleration code
    }
};
```

#### 4. Polymorphism

**Polymorphism** allows objects of different classes to be treated as objects of a common superclass. It enables one interface to be used for a general class of actions, with the specific action determined by the type of data.

```cpp
class Shape {
public:
    virtual double area() = 0;  // Pure virtual function
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() override {
        return width * height;
    }
};
```

#### 5. Abstraction

**Abstraction** is the concept of exposing only the necessary features of an object while hiding the unnecessary details from the user. It helps manage complexity by hiding implementation details behind simple interfaces.

```cpp
class Television {
private:
    // Complex internal components and mechanisms
    bool powerState;
    int channel;
    int volume;
    void initializeScreen() { /* Complex initialization code */ }
    void tuneChannel() { /* Complex tuning logic */ }
    
public:
    // Simple interface
    void turnOn() { 
        powerState = true; 
        initializeScreen();
    }
    
    void turnOff() { 
        powerState = false; 
    }
    
    void setChannel(int newChannel) { 
        channel = newChannel; 
        tuneChannel();
    }
    
    void adjustVolume(int amount) { 
        volume += amount; 
        if (volume < 0) volume = 0;
        if (volume > 100) volume = 100;
    }
};
```

### Benefits of OOP

1. **Modularity**: Systems can be divided into smaller, manageable parts
2. **Reusability**: Code can be reused through inheritance
3. **Flexibility and scalability**: Systems can be adapted and extended more easily
4. **Maintainability**: Changes to one part of the system have minimal impact on others
5. **Problem-solving approach**: Models real-world entities and their interactions

### OOP vs. Procedural Programming

| Aspect | OOP | Procedural |
|--------|-----|------------|
| Focus | Objects (data + behaviors) | Procedures (algorithms) |
| Data Access | Limited through encapsulation | Often globally accessible |
| Data & Function | Combined in objects | Separate |
| Code Reuse | Through inheritance | Through functions |
| Data Structure | Complex (objects) | Simple |
| Flexibility | High | Lower |
| Complexity | Higher initial complexity | Lower initial complexity |

### Practical Example: OOP in Action

Let's see how a simple library system might be modeled using OOP principles:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool checkedOut;
    
public:
    // Constructor
    Book(string t, string a, string i)
        : title(t), author(a), isbn(i), checkedOut(false) {}
    
    // Methods
    bool isAvailable() const {
        return !checkedOut;
    }
    
    void checkOut() {
        if (!checkedOut) {
            checkedOut = true;
            cout << title << " has been checked out." << endl;
        } else {
            cout << title << " is already checked out." << endl;
        }
    }
    
    void returnBook() {
        if (checkedOut) {
            checkedOut = false;
            cout << title << " has been returned." << endl;
        } else {
            cout << title << " is already in the library." << endl;
        }
    }
    
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
};

class Library {
private:
    vector<Book> books;
    
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    
    void displayAvailableBooks() const {
        cout << "Available Books:" << endl;
        bool foundAvailable = false;
        
        for (const auto& book : books) {
            if (book.isAvailable()) {
                cout << book.getTitle() << " by " << book.getAuthor() << endl;
                foundAvailable = true;
            }
        }
        
        if (!foundAvailable) {
            cout << "No books are currently available." << endl;
        }
    }
    
    Book* findBookByTitle(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }
};

int main() {
    // Create a library and add books
    Library myLibrary;
    
    myLibrary.addBook(Book("1984", "George Orwell", "9780451524935"));
    myLibrary.addBook(Book("To Kill a Mockingbird", "Harper Lee", "9780060935467"));
    myLibrary.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565"));
    
    // Display available books
    myLibrary.displayAvailableBooks();
    
    // Check out a book
    Book* book = myLibrary.findBookByTitle("1984");
    if (book != nullptr) {
        book->checkOut();
    }
    
    // Try to check out the same book again
    if (book != nullptr) {
        book->checkOut();
    }
    
    // Display available books after checkout
    myLibrary.displayAvailableBooks();
    
    // Return the book
    if (book != nullptr) {
        book->returnBook();
    }
    
    // Display available books after return
    myLibrary.displayAvailableBooks();
    
    return 0;
}
```

This example demonstrates many OOP principles:
- **Classes and Objects**: `Book` and `Library` classes with their respective objects
- **Encapsulation**: Private data members with public methods to access/modify them
- **Abstraction**: Complex operations simplified through methods like `checkOut()` and `returnBook()`
- **Code organization**: Related data and behavior bundled together

## 6.2 Classes and Objects

Classes and objects are the fundamental building blocks of object-oriented programming in C++. Let's dive deeper into how they work.

### Defining Classes in C++

A class in C++ is defined using the `class` keyword, followed by the class name and a block containing the class members:

```cpp
class ClassName {
    // Members (data and functions)
};
```

#### Class Members

A class can contain:

1. **Data members** (attributes): Variables that hold the state of the object
2. **Member functions** (methods): Functions that define the behavior of the object
3. **Access specifiers**: Keywords that control the visibility of class members (`public`, `private`, `protected`)

```cpp
class Person {
private:
    // Data members (attributes)
    std::string name;
    int age;
    double height;
    
public:
    // Member functions (methods)
    void setName(const std::string& n);
    std::string getName() const;
    void setAge(int a);
    int getAge() const;
    void setHeight(double h);
    double getHeight() const;
    void celebrateBirthday();
};
```

#### Class vs Struct

In C++, a `struct` is essentially the same as a `class`, with one key difference: members in a `struct` are `public` by default, while members in a `class` are `private` by default.

```cpp
struct Point {
    int x;  // public by default
    int y;  // public by default
};

class Circle {
private:  // private by default
    double radius;
    Point center;
};
```

### Implementing Member Functions

Member functions can be defined:
1. Inside the class definition (implicitly inline)
2. Outside the class definition using the scope resolution operator (`::`):

```cpp
// Inside class definition
class Rectangle {
private:
    double width;
    double height;
    
public:
    // Method defined inside class
    double area() {
        return width * height;
    }
    
    void setDimensions(double w, double h);
    double perimeter();
};

// Outside class definition
void Rectangle::setDimensions(double w, double h) {
    width = w;
    height = h;
}

double Rectangle::perimeter() {
    return 2 * (width + height);
}
```

### Creating and Using Objects

Once a class is defined, objects (instances) can be created in several ways:

```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;
    double height;
    
public:
    // Constructors will be covered in section 6.3
    Rectangle() : width(0), height(0) {}
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() { return width * height; }
    double perimeter() { return 2 * (width + height); }
    void setDimensions(double w, double h) { width = w; height = h; }
    double getWidth() { return width; }
    double getHeight() { return height; }
};

int main() {
    // Method 1: Default initialization
    Rectangle rect1;
    rect1.setDimensions(5, 3);
    
    // Method 2: Parameterized constructor
    Rectangle rect2(4, 6);
    
    // Method 3: Uniform initialization (C++11)
    Rectangle rect3{7, 2};
    
    // Method 4: Dynamic allocation
    Rectangle* rect4 = new Rectangle(8, 9);
    
    // Accessing members with dot operator
    cout << "Rectangle 1 area: " << rect1.area() << endl;
    cout << "Rectangle 2 perimeter: " << rect2.perimeter() << endl;
    
    // Accessing members with arrow operator (for pointer)
    cout << "Rectangle 4 area: " << rect4->area() << endl;
    
    // Don't forget to delete dynamically allocated objects
    delete rect4;
    
    return 0;
}
```

### The `this` Pointer

Every object in C++ has access to its own address through the `this` pointer. It is an implicit parameter to all member functions and can be used to:

1. Disambiguate between member variables and parameters with the same name
2. Return the current object to enable method chaining
3. Pass the current object to another function

```cpp
class Counter {
private:
    int count;
    
public:
    Counter(int count) : count(count) {}  // Parameter has same name as member
    
    void increment() {
        count++;
    }
    
    // Using this to disambiguate
    void reset(int count) {
        this->count = count;  // this->count refers to the member variable
    }
    
    // Using this for method chaining
    Counter& add(int value) {
        count += value;
        return *this;  // Return reference to current object
    }
    
    int getCount() const {
        return count;
    }
};

int main() {
    Counter c(5);
    c.increment();
    cout << c.getCount() << endl;  // 6
    
    c.reset(10);
    cout << c.getCount() << endl;  // 10
    
    // Method chaining
    c.add(5).add(3).add(2);
    cout << c.getCount() << endl;  // 20
    
    return 0;
}
```

### Static Class Members

A class can have static members that belong to the class itself rather than any specific instance:

1. **Static data members**: Shared among all objects of the class
2. **Static member functions**: Can access only static data members and don't have a `this` pointer

```cpp
#include <iostream>
using namespace std;

class BankAccount {
private:
    static double interestRate;  // Static data member
    string accountHolder;
    double balance;
    
public:
    BankAccount(const string& name, double initialBalance)
        : accountHolder(name), balance(initialBalance) {}
    
    void addInterest() {
        balance += balance * interestRate;
    }
    
    double getBalance() const {
        return balance;
    }
    
    // Static member function
    static void setInterestRate(double rate) {
        // Can only access static members
        interestRate = rate;
        // balance = 0;  // ERROR: Can't access non-static members
    }
    
    static double getInterestRate() {
        return interestRate;
    }
};

// Static members must be defined outside the class
double BankAccount::interestRate = 0.05;  // 5% default interest rate

int main() {
    // Access static member through class name
    cout << "Current interest rate: " << BankAccount::getInterestRate() << endl;
    
    // Create bank accounts
    BankAccount acc1("Alice", 1000);
    BankAccount acc2("Bob", 2000);
    
    // Apply interest
    acc1.addInterest();
    acc2.addInterest();
    
    cout << "Alice's balance: " << acc1.getBalance() << endl;  // 1050
    cout << "Bob's balance: " << acc2.getBalance() << endl;    // 2100
    
    // Change interest rate for all accounts
    BankAccount::setInterestRate(0.06);  // 6% interest
    
    // Apply new interest rate
    acc1.addInterest();
    acc2.addInterest();
    
    cout << "Alice's new balance: " << acc1.getBalance() << endl;  // 1113
    cout << "Bob's new balance: " << acc2.getBalance() << endl;    // 2226
    
    return 0;
}
```

### Const Member Functions

Member functions that don't modify the object's state should be declared as `const`. This enables them to be called on const objects and communicates intent:

```cpp
class Circle {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    // const member function - doesn't modify the object
    double area() const {
        return 3.14159 * radius * radius;
    }
    
    // non-const member function - modifies the object
    void setRadius(double r) {
        radius = r;
    }
};

int main() {
    const Circle unitCircle(1.0);
    
    // OK: area() is a const member function
    cout << "Area: " << unitCircle.area() << endl;
    
    // ERROR: setRadius() is not a const member function
    // unitCircle.setRadius(2.0);
    
    return 0;
}
```

### Nested Classes

A class can contain the definition of another class:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class University {
public:
    // Nested class
    class Student {
    private:
        string name;
        int id;
        
    public:
        Student(const string& n, int i) : name(n), id(i) {}
        
        string getName() const { return name; }
        int getId() const { return id; }
    };
    
private:
    string name;
    vector<Student> students;
    
public:
    University(const string& n) : name(n) {}
    
    void addStudent(const Student& s) {
        students.push_back(s);
    }
    
    void printStudents() const {
        cout << "Students at " << name << ":" << endl;
        for (const auto& student : students) {
            cout << "ID: " << student.getId() 
                 << ", Name: " << student.getName() << endl;
        }
    }
};

int main() {
    University mit("MIT");
    
    // Create student objects
    University::Student s1("John", 12345);
    University::Student s2("Lisa", 67890);
    
    // Add students to university
    mit.addStudent(s1);
    mit.addStudent(s2);
    
    // Print student list
    mit.printStudents();
    
    return 0;
}
```

### Best Practices for Classes and Objects

1. **Keep classes focused**: A class should represent a single concept and have a clear responsibility
2. **Encapsulate data**: Make data members private and provide access through methods when needed
3. **Use meaningful names**: Choose descriptive names for classes, methods, and attributes
4. **Design for users**: Design the public interface with users of the class in mind
5. **Design for extension**: Consider how the class might be extended or inherited
6. **Follow the Single Responsibility Principle**: A class should have only one reason to change
7. **Minimize method size**: Keep methods small and focused on a single task
8. **Use const correctly**: Mark methods that don't modify the object as const
9. **Limit dependencies**: Minimize dependencies between classes
10. **Document public interfaces**: Use comments to explain how to use the class

## 6.3 Constructors and Destructors

Constructors and destructors are special member functions that handle object initialization and cleanup in C++. They play a crucial role in implementing RAII (Resource Acquisition Is Initialization), one of the most important idioms in C++.

### Constructors

A constructor is a special member function that is automatically called when an object is created. Its purpose is to initialize the object's data members and acquire necessary resources.

#### Types of Constructors

1. **Default Constructor**: Takes no parameters or has default values for all parameters
2. **Parameterized Constructor**: Takes one or more parameters
3. **Copy Constructor**: Creates a new object as a copy of an existing object
4. **Move Constructor (C++11)**: Creates a new object by transferring resources from a temporary object
5. **Delegating Constructor (C++11)**: Calls another constructor in the same class
6. **Converting Constructor**: Takes a single parameter and can be used for implicit type conversion

Let's examine each type:

#### Default Constructor

```cpp
class Box {
private:
    double length;
    double width;
    double height;
    
public:
    // Default constructor
    Box() {
        length = 1.0;
        width = 1.0;
        height = 1.0;
    }
    
    // Method to display dimensions
    void displayDimensions() {
        cout << "Length: " << length 
             << ", Width: " << width 
             << ", Height: " << height << endl;
    }
};

int main() {
    Box defaultBox;  // Default constructor called
    defaultBox.displayDimensions();
    
    return 0;
}
```

#### Parameterized Constructor

```cpp
class Box {
private:
    double length;
    double width;
    double height;
    
public:
    // Default constructor
    Box() {
        length = 1.0;
        width = 1.0;
        height = 1.0;
    }
    
    // Parameterized constructor
    Box(double l, double w, double h) {
        length = l;
        width = w;
        height = h;
    }
    
    // Method to display dimensions
    void displayDimensions() {
        cout << "Length: " << length 
             << ", Width: " << width 
             << ", Height: " << height << endl;
    }
};

int main() {
    Box defaultBox;  // Default constructor called
    Box customBox(3.0, 2.0, 1.5);  // Parameterized constructor called
    
    defaultBox.displayDimensions();
    customBox.displayDimensions();
    
    return 0;
}
```

#### Constructor with Default Parameters

```cpp
class Box {
private:
    double length;
    double width;
    double height;
    
public:
    // Constructor with default parameters
    Box(double l = 1.0, double w = 1.0, double h = 1.0) {
        length = l;
        width = w;
        height = h;
    }
    
    // Method to display dimensions
    void displayDimensions() {
        cout << "Length: " << length 
             << ", Width: " << width 
             << ", Height: " << height << endl;
    }
};

int main() {
    Box box1;              // Uses all default values: 1.0, 1.0, 1.0
    Box box2(2.0);         // Uses custom length, default width/height: 2.0, 1.0, 1.0
    Box box3(3.0, 4.0);    // Uses custom length/width, default height: 3.0, 4.0, 1.0
    Box box4(5.0, 6.0, 7.0); // Uses all custom values: 5.0, 6.0, 7.0
    
    box1.displayDimensions();
    box2.displayDimensions();
    box3.displayDimensions();
    box4.displayDimensions();
    
    return 0;
}
```

#### Member Initialization List

A more efficient way to initialize members is using an initialization list:

```cpp
class Person {
private:
    string name;
    int age;
    const string id;  // const member must be initialized in the init list
    
public:
    // Constructor with initialization list
    Person(const string& n, int a, const string& i)
        : name(n), age(a), id(i) {
        // Constructor body (can contain additional code)
        cout << "Person created: " << name << endl;
    }
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }
};

int main() {
    Person person("John Doe", 30, "A12345");
    person.display();
    
    return 0;
}
```

Benefits of initialization lists:
- More efficient than assigning values in the constructor body
- Required for const members and reference members
- Required for members that don't have a default constructor
- Initializes members in declaration order (not in list order)

#### Copy Constructor

A copy constructor creates a new object as a copy of an existing object:

```cpp
class Array {
private:
    int* data;
    size_t size;
    
public:
    // Regular constructor
    Array(size_t s) : size(s) {
        data = new int[size]();  // Allocate and zero-initialize
        cout << "Regular constructor called" << endl;
    }
    
    // Copy constructor
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        // Deep copy the data
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor called" << endl;
    }
    
    // Destructor
    ~Array() {
        delete[] data;
        cout << "Destructor called" << endl;
    }
    
    void setElement(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getElement(size_t index) const {
        return (index < size) ? data[index] : 0;
    }
    
    size_t getSize() const {
        return size;
    }
};

// Function that takes an Array by value (triggers copy)
void processArray(Array arr) {
    cout << "Processing array of size " << arr.getSize() << endl;
}

int main() {
    Array arr1(5);
    arr1.setElement(0, 10);
    arr1.setElement(1, 20);
    
    // Copy constructor called when creating arr2
    Array arr2 = arr1;  // Same as: Array arr2(arr1);
    
    // Modify arr2 (doesn't affect arr1)
    arr2.setElement(0, 30);
    
    cout << "arr1[0] = " << arr1.getElement(0) << endl;  // Still 10
    cout << "arr2[0] = " << arr2.getElement(0) << endl;  // 30
    
    // Copy constructor called again when passing to function
    processArray(arr1);
    
    return 0;
}
```

The copy constructor is called in these situations:
- When initializing a new object from an existing one
- When passing an object by value
- When returning an object by value from a function

If you don't provide a copy constructor, the compiler generates one that performs a member-wise copy (shallow copy), which is problematic for classes that manage resources like dynamically allocated memory.

#### Move Constructor (C++11)

A move constructor efficiently transfers resources from a temporary (rvalue) object to a newly created object:

```cpp
#include <iostream>
#include <utility>  // For std::move
using namespace std;

class Array {
private:
    int* data;
    size_t size;
    
public:
    // Regular constructor
    Array(size_t s) : size(s) {
        data = new int[size]();
        cout << "Regular constructor called" << endl;
    }
    
    // Copy constructor
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor called" << endl;
    }
    
    // Move constructor
    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        // Transfer ownership (steal resources)
        other.data = nullptr;
        other.size = 0;
        cout << "Move constructor called" << endl;
    }
    
    // Destructor
    ~Array() {
        delete[] data;
        cout << "Destructor called for array of size " << size << endl;
    }
    
    // Other methods as before...
    size_t getSize() const { return size; }
};

// Function returning an Array by value
Array createArray(size_t size) {
    Array temp(size);
    return temp;  // Return value optimization may apply
}

int main() {
    cout << "Creating arr1:" << endl;
    Array arr1(5);
    
    cout << "\nCreating arr2 from arr1:" << endl;
    Array arr2 = arr1;  // Copy constructor
    
    cout << "\nCreating arr3 from temporary:" << endl;
    Array arr3 = createArray(3);  // Move constructor may be used
    
    cout << "\nCreating arr4 with std::move:" << endl;
    Array arr4 = std::move(arr1);  // Move constructor
    
    cout << "\nProgram ending:" << endl;
    return 0;
}
```

The move constructor "steals" resources from a temporary object that's about to be destroyed, avoiding unnecessary copying of resources. This is especially useful for classes that manage expensive resources like large memory buffers.

#### Delegating Constructors (C++11)

A constructor can call another constructor in the same class:

```cpp
class Rectangle {
private:
    double width;
    double height;
    string color;
    
public:
    // Primary constructor
    Rectangle(double w, double h, const string& c)
        : width(w), height(h), color(c) {
        cout << "Primary constructor called" << endl;
    }
    
    // Delegating constructors
    Rectangle() : Rectangle(1.0, 1.0, "white") {
        cout << "Default constructor called" << endl;
    }
    
    Rectangle(double size) : Rectangle(size, size, "white") {
        cout << "Square constructor called" << endl;
    }
    
    Rectangle(double w, double h) : Rectangle(w, h, "white") {
        cout << "Two-parameter constructor called" << endl;
    }
    
    void display() const {
        cout << "Rectangle: " << width << " x " << height 
             << ", Color: " << color << endl;
    }
};

int main() {
    Rectangle r1;              // Default constructor
    Rectangle r2(5.0);         // Square constructor
    Rectangle r3(3.0, 4.0);    // Two-parameter constructor
    Rectangle r4(2.0, 3.0, "blue");  // Primary constructor
    
    r1.display();
    r2.display();
    r3.display();
    r4.display();
    
    return 0;
}
```

Delegating constructors avoid code duplication and ensure consistent initialization.

#### Explicit Constructors

By default, constructors that take a single parameter can be used for implicit type conversion. The `explicit` keyword prevents this:

```cpp
class Integer {
private:
    int value;
    
public:
    // Implicit conversion constructor
    Integer(int v) : value(v) {
        cout << "Integer constructor called with " << v << endl;
    }
    
    int getValue() const { return value; }
};

class ExplicitInteger {
private:
    int value;
    
public:
    // Explicit constructor - prevents implicit conversion
    explicit ExplicitInteger(int v) : value(v) {
        cout << "ExplicitInteger constructor called with " << v << endl;
    }
    
    int getValue() const { return value; }
};

void processInteger(Integer i) {
    cout << "Processing integer: " << i.getValue() << endl;
}

void processExplicit(ExplicitInteger e) {
    cout << "Processing explicit integer: " << e.getValue() << endl;
}

int main() {
    // Implicit conversion works
    Integer i1 = 42;  // Implicit conversion from int to Integer
    processInteger(99);  // Implicit conversion in function call
    
    // Explicit conversion required
    ExplicitInteger e1(42);  // OK - direct initialization
    
    // ExplicitInteger e2 = 42;  // ERROR - no implicit conversion
    processExplicit(ExplicitInteger(99));  // OK - explicit conversion
    
    return 0;
}
```

Using `explicit` for single-parameter constructors is generally a good practice as it prevents unintended implicit conversions.

### Destructors

A destructor is a special member function that is called when an object is destroyed. Its purpose is to release resources acquired by the object.

#### Basic Destructor Syntax

```cpp
class Resource {
private:
    string name;
    int* data;
    
public:
    Resource(const string& n, int size) : name(n) {
        cout << "Constructor: Creating " << name << endl;
        data = new int[size];
    }
    
    ~Resource() {
        cout << "Destructor: Cleaning up " << name << endl;
        delete[] data;
    }
};

void useResource() {
    Resource r1("LocalResource", 100);
    // r1 automatically destroyed when function exits
}

int main() {
    cout << "Program starting" << endl;
    
    {
        Resource r2("BlockResource", 200);
        // r2 destroyed at end of block
    }
    
    useResource();
    
    Resource* r3 = new Resource("DynamicResource", 300);
    // r3 not automatically destroyed
    
    delete r3;  // Manual destruction needed for dynamically allocated objects
    
    cout << "Program ending" << endl;
    return 0;
}
```

#### Key Points about Destructors

1. **Naming**: A destructor's name is the class name preceded by a tilde (`~`)
2. **No Parameters**: Destructors don't take parameters
3. **No Return Type**: Destructors don't return a value (not even void)
4. **No Overloading**: A class can have only one destructor
5. **Automatic Invocation**: Destructors are called automatically when objects go out of scope
6. **Order**: Destructors are called in the reverse order of constructors
7. **Virtual Destructors**: Base class destructors should be virtual when inheritance is used (covered later)

#### When You Need to Write a Destructor

You need to write a custom destructor when your class manages resources that aren't automatically cleaned up:

1. **Dynamically allocated memory** (`new`/`delete`)
2. **File handles**
3. **Network connections**
4. **Database connections**
5. **Other system resources**

If your class doesn't manage any resources directly (it only contains built-in types or objects that handle their own cleanup), you typically don't need to write a destructor.

#### The Rule of Three/Five/Zero

When you need to manage resources explicitly:

1. **Rule of Three**: If a class needs a custom destructor, copy constructor, or copy assignment operator, it likely needs all three
2. **Rule of Five (C++11)**: Adds move constructor and move assignment operator to the list
3. **Rule of Zero**: Design classes to avoid the need for custom resource management functions

Here's a class implementing the Rule of Five:

```cpp
#include <iostream>
#include <cstring>  // For strlen, strcpy
using namespace std;

class String {
private:
    char* data;
    
    // Helper to calculate string length including null terminator
    static size_t length(const char* s) {
        return s ? strlen(s) + 1 : 1;
    }
    
public:
    // Constructor
    String(const char* s = "") {
        size_t len = length(s);
        data = new char[len];
        strcpy(data, s ? s : "");
        cout << "Constructor: " << data << endl;
    }
    
    // Destructor
    ~String() {
        cout << "Destructor: " << data << endl;
        delete[] data;
    }
    
    // Copy constructor
    String(const String& other) {
        size_t len = length(other.data);
        data = new char[len];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Copy assignment operator
    String& operator=(const String& other) {
        cout << "Copy assignment operator" << endl;
        if (this != &other) {  // Prevent self-assignment
            char* newData = new char[length(other.data)];
            strcpy(newData, other.data);
            delete[] data;  // Delete old data
            data = newData;
        }
        return *this;
    }
    
    // Move constructor (C++11)
    String(String&& other) noexcept {
        cout << "Move constructor" << endl;
        data = other.data;     // Take ownership
        other.data = nullptr;  // Prevent destruction of data
    }
    
    // Move assignment operator (C++11)
    String& operator=(String&& other) noexcept {
        cout << "Move assignment operator" << endl;
        if (this != &other) {
            delete[] data;      // Delete our data
            data = other.data;  // Take ownership
            other.data = nullptr;  // Prevent destruction of data
        }
        return *this;
    }
    
    // Accessor
    const char* c_str() const {
        return data;
    }
};

int main() {
    String s1("Hello");            // Constructor
    String s2 = s1;                // Copy constructor
    String s3;                     // Constructor with default value
    s3 = s1;                       // Copy assignment operator
    
    String s4 = std::move(s1);     // Move constructor
    String s5;                     // Constructor with default value
    s5 = std::move(s2);            // Move assignment operator
    
    cout << "s3: " << s3.c_str() << endl;
    cout << "s4: " << s4.c_str() << endl;
    cout << "s5: " << s5.c_str() << endl;
    // s1 and s2 are in valid but unspecified states
    
    return 0;
}
```

### Best Practices for Constructors and Destructors

1. **Initialize all members**: Make sure all member variables are initialized in constructors
2. **Use member initialization lists**: More efficient than assignments in the constructor body
3. **Use delegating constructors**: Avoid code duplication in constructors
4. **Make single-parameter constructors explicit**: Prevent unintended implicit conversions
5. **Follow the Rule of Three/Five/Zero**: If you need one resource-managing function, you likely need all of them
6. **Make base class destructors virtual**: When using inheritance
7. **Keep destructors exception-safe**: Destructors should never throw exceptions
8. **Use RAII**: Acquire resources in constructors and release them in destructors
9. **Consider smart pointers**: Often better than manual memory management
10. **Don't call virtual functions in constructors or destructors**: The behavior can be surprising

## 6.4 Access Specifiers (Public, Private, Protected)

Access specifiers control the visibility and accessibility of class members. C++ provides three access specifiers:

1. **public**: Members are accessible from anywhere
2. **private**: Members are accessible only from within the class
3. **protected**: Members are accessible from within the class and derived classes

### Public Access Specifier

Public members form the interface of the class. They can be accessed from anywhere the class is visible:

```cpp
class Account {
public:  // Public access specifier
    string accountNumber;  // Public data member
    
    void deposit(double amount) {  // Public method
        balance += amount;
    }
    
    double getBalance() {  // Public method
        return balance;
    }
    
private:
    double balance = 0.0;  // Private data member
};

int main() {
    Account acc;
    acc.accountNumber = "123456";  // OK - public member
    acc.deposit(1000);             // OK - public method
    cout << acc.getBalance();      // OK - public method
    // acc.balance = 5000;         // ERROR - private member
    
    return 0;
}
```

### Private Access Specifier

Private members are accessible only from within the class itself. They cannot be accessed from outside the class, including derived classes:

```cpp
class BankAccount {
private:  // Private access specifier
    double balance;
    string accountNumber;
    double interestRate;
    
    // Private helper method
    bool isValidAmount(double amount) {
        return amount > 0;
    }
    
public:
    BankAccount(const string& accNum, double initialBalance) 
        : accountNumber(accNum), balance(initialBalance), interestRate(0.05) {}
    
    bool withdraw(double amount) {
        // Can access private members and methods
        if (!isValidAmount(amount) || amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }
    
    void deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
        }
    }
    
    double getBalance() const {
        return balance;
    }
    
    string getAccountNumber() const {
        return accountNumber;
    }
};

int main() {
    BankAccount acc("12345", 1000);
    
    // acc.balance = 2000;           // ERROR - private member
    // acc.interestRate = 0.1;       // ERROR - private member
    // bool valid = acc.isValidAmount(500);  // ERROR - private method
    
    acc.deposit(500);                // OK - public method
    acc.withdraw(200);               // OK - public method
    cout << acc.getBalance() << endl;  // OK - public method
    
    return 0;
}
```

### Protected Access Specifier

Protected members are accessible from within the class and from derived classes but not from outside:

```cpp
class Shape {
protected:  // Protected access specifier
    double x, y;  // Position
    string color;
    
    // Protected helper method
    void validate() {
        if (color.empty()) {
            color = "black";
        }
    }
    
public:
    Shape(double x, double y, const string& c)
        : x(x), y(y), color(c) {
        validate();
    }
    
    void move(double newX, double newY) {
        x = newX;
        y = newY;
    }
    
    string getColor() const {
        return color;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double x, double y, double r, const string& c)
        : Shape(x, y, c), radius(r) {}
    
    void setRadius(double r) {
        radius = r;
    }
    
    double area() const {
        return 3.14159 * radius * radius;
    }
    
    // Can access protected members of base class
    void changeColor(const string& newColor) {
        color = newColor;  // OK - protected member
        validate();        // OK - protected method
    }
    
    void display() const {
        cout << "Circle at (" << x << ", " << y << "), "  // OK - protected
             << "radius " << radius << ", color " << color << endl;  // OK - protected
    }
};

int main() {
    Shape shape(10, 20, "red");
    Circle circle(15, 25, 5, "blue");
    
    // shape.x = 30;         // ERROR - protected member
    // shape.color = "green"; // ERROR - protected member
    // shape.validate();     // ERROR - protected method
    
    shape.move(30, 40);     // OK - public method
    circle.setRadius(10);   // OK - public method
    circle.changeColor("green");  // OK - public method
    circle.display();       // OK - public method
    
    return 0;
}
```

### Friend Functions and Classes

C++ allows you to declare specific functions or classes as "friends," granting them access to private and protected members:

```cpp
class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    BankAccount(const string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}
    
    // Declare friends
    friend void displayAccountDetails(const BankAccount& acc);
    friend class BankSystem;
    
    // Regular public methods
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
};

// Friend function can access private members
void displayAccountDetails(const BankAccount& acc) {
    cout << "Account: " << acc.accountNumber  // OK - can access private member
         << ", Balance: $" << acc.balance << endl;  // OK - can access private member
}

// Friend class can access private members
class BankSystem {
public:
    void transferFunds(BankAccount& from, BankAccount& to, double amount) {
        if (amount > 0 && from.balance >= amount) {
            from.balance -= amount;  // OK - can access private member
            to.balance += amount;    // OK - can access private member
            cout << "Transferred $" << amount << " from " 
                 << from.accountNumber << " to " << to.accountNumber << endl;
        } else {
            cout << "Transfer failed" << endl;
        }
    }
    
    void auditAccounts(const vector<BankAccount>& accounts) {
        double totalFunds = 0;
        for (const auto& acc : accounts) {
            totalFunds += acc.balance;  // OK - can access private member
        }
        cout << "Total funds: $" << totalFunds << endl;
    }
};

int main() {
    BankAccount acc1("12345", 1000);
    BankAccount acc2("67890", 500);
    
    displayAccountDetails(acc1);  // Friend function
    
    BankSystem system;
    system.transferFunds(acc1, acc2, 300);  // Friend class
    
    vector<BankAccount> accounts = {acc1, acc2};
    system.auditAccounts(accounts);  // Friend class
    
    return 0;
}
```

#### Important Points about Friends

1. Friendship is not symmetric (if A is a friend of B, B is not automatically a friend of A)
2. Friendship is not transitive (if A is a friend of B, and B is a friend of C, A is not automatically a friend of C)
3. Friendship is not inherited (if a base class has a friend, derived classes don't inherit that friendship)
4. Friends violate encapsulation to some extent, so use them judiciously

### Default Access in Classes and Structs

The default access specifier is different in classes and structs:

```cpp
class MyClass {
    int x;  // Private by default in classes
public:
    int y;  // Explicitly public
};

struct MyStruct {
    int x;  // Public by default in structs
private:
    int y;  // Explicitly private
};

int main() {
    MyClass c;
    // c.x = 10;  // ERROR - private by default
    c.y = 20;     // OK - public
    
    MyStruct s;
    s.x = 10;     // OK - public by default
    // s.y = 20;  // ERROR - explicitly private
    
    return 0;
}
```

### Access Control and Inheritance

Access specifiers also control how members are inherited:

```cpp
class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;
};

class PublicDerived : public Base {
    // publicVar remains public
    // protectedVar remains protected
    // privateVar is not accessible
    
    void accessTest() {
        publicVar = 1;     // OK - public in base
        protectedVar = 2;  // OK - protected in base
        // privateVar = 3; // ERROR - private in base, not accessible
    }
};

class ProtectedDerived : protected Base {
    // publicVar becomes protected
    // protectedVar remains protected
    // privateVar is not accessible
    
    void accessTest() {
        publicVar = 1;     // OK - protected in derived
        protectedVar = 2;  // OK - protected in derived
        // privateVar = 3; // ERROR - private in base, not accessible
    }
};

class PrivateDerived : private Base {
    // publicVar becomes private
    // protectedVar becomes private
    // privateVar is not accessible
    
    void accessTest() {
        publicVar = 1;     // OK - private in derived
        protectedVar = 2;  // OK - private in derived
        // privateVar = 3; // ERROR - private in base, not accessible
    }
};

int main() {
    PublicDerived d1;
    d1.publicVar = 1;      // OK - public in derived
    // d1.protectedVar = 2; // ERROR - protected in derived
    // d1.privateVar = 3;   // ERROR - not accessible
    
    ProtectedDerived d2;
    // d2.publicVar = 1;    // ERROR - protected in derived
    // d2.protectedVar = 2; // ERROR - protected in derived
    // d2.privateVar = 3;   // ERROR - not accessible
    
    PrivateDerived d3;
    // d3.publicVar = 1;    // ERROR - private in derived
    // d3.protectedVar = 2; // ERROR - private in derived
    // d3.privateVar = 3;   // ERROR - not accessible
    
    return 0;
}
```

### Best Practices for Access Control

1. **Public Interface**: Expose only what's necessary in the public interface
2. **Private Implementation**: Keep implementation details private
3. **Protected for Inheritance**: Use protected for members that derived classes need to access
4. **Minimize Friend Declarations**: Use friends sparingly
5. **Accessors and Mutators**: Provide controlled access to private data through public methods
6. **Class Invariants**: Use private access to maintain class invariants (conditions that must always be true)
7. **Favor Encapsulation**: Restrict access to implementation details

```cpp
// Example of good access control design
class Temperature {
private:
    double celsius;
    
    // Private helper method
    double validateTemperature(double temp) {
        const double absoluteZero = -273.15;
        return (temp < absoluteZero) ? absoluteZero : temp;
    }
    
public:
    // Constructor ensures valid initialization
    Temperature(double c) : celsius(validateTemperature(c)) {}
    
    // Public accessors
    double getCelsius() const { return celsius; }
    double getFahrenheit() const { return celsius * 9.0/5.0 + 32; }
    double getKelvin() const { return celsius + 273.15; }
    
    // Public mutators with validation
    void setCelsius(double c) { celsius = validateTemperature(c); }
    
    void setFahrenheit(double f) {
        setCelsius((f - 32) * 5.0/9.0);
    }
    
    void setKelvin(double k) {
        setCelsius(k - 273.15);
    }
};

int main() {
    Temperature temp(25.0);
    cout << "Celsius: " << temp.getCelsius() << endl;
    cout << "Fahrenheit: " << temp.getFahrenheit() << endl;
    cout << "Kelvin: " << temp.getKelvin() << endl;
    
    temp.setFahrenheit(98.6);
    cout << "Body temperature in C: " << temp.getCelsius() << endl;
    
    // Invalid temperature is corrected automatically
    temp.setCelsius(-300);
    cout << "After setting to -300C, actual value: " << temp.getCelsius() << endl;
    
    return 0;
}
```

In this example:
- Private data (celsius) is protected from invalid modifications
- Public methods provide a controlled interface for using the class
- Class invariants (temperature cannot be below absolute zero) are enforced
- Implementation details (validation logic) are hidden

Access control is a fundamental aspect of encapsulation in object-oriented programming. By carefully designing what is accessible and what is hidden, you create classes that are easier to use correctly and harder to use incorrectly.
