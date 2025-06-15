# Chapter 6: Object-Oriented Programming (Part 2)

## 6.5 Inheritance

Inheritance is a fundamental concept in object-oriented programming that allows you to create new classes (derived/child classes) from existing ones (base/parent classes). The derived class inherits attributes and behaviors from the base class, and can also extend or modify them.

### Core Concepts of Inheritance

1. **Base Class (Parent Class)**: The original class that shares its features
2. **Derived Class (Child Class)**: The new class that inherits features
3. **"is-a" Relationship**: Inheritance establishes an "is-a" relationship between classes
4. **Code Reuse**: Inheritance promotes code reuse and organization
5. **Specialization**: Derived classes can specialize behavior of base classes

### Basic Syntax

```cpp
class BaseClass {
    // Base class members
};

class DerivedClass : access-specifier BaseClass {
    // Derived class members
    // Inherits members from BaseClass
};
```

The `access-specifier` can be:
- `public`: Public and protected members of the base class remain public and protected in the derived class
- `protected`: Public and protected members of the base class become protected in the derived class
- `private`: Public and protected members of the base class become private in the derived class

### 6.5.1 Single Inheritance

Single inheritance is the simplest form where a class inherits from only one base class.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Vehicle {
private:
    string make;
    string model;
    int year;
    
protected:
    double price;
    
public:
    Vehicle(const string& make, const string& model, int year, double price)
        : make(make), model(model), year(year), price(price) {
        cout << "Vehicle constructor called" << endl;
    }
    
    ~Vehicle() {
        cout << "Vehicle destructor called" << endl;
    }
    
    void displayInfo() const {
        cout << year << " " << make << " " << model 
             << ", Price: $" << price << endl;
    }
    
    void start() const {
        cout << "Vehicle started" << endl;
    }
    
    void stop() const {
        cout << "Vehicle stopped" << endl;
    }
    
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
};

// Derived class
class Car : public Vehicle {
private:
    int numDoors;
    double engineSize;  // in liters
    
public:
    Car(const string& make, const string& model, int year, double price,
        int doors, double engine)
        : Vehicle(make, model, year, price),  // Call base class constructor
          numDoors(doors), engineSize(engine) {
        cout << "Car constructor called" << endl;
    }
    
    ~Car() {
        cout << "Car destructor called" << endl;
    }
    
    void displayCarInfo() const {
        // Access base class public methods
        displayInfo();
        cout << "Doors: " << numDoors << ", Engine: " << engineSize << "L" << endl;
    }
    
    void applyDiscount(double percentage) {
        // Can access protected members from base class
        double discountAmount = price * percentage / 100.0;
        price -= discountAmount;
        cout << "Discount of " << percentage << "% applied. New price: $" << price << endl;
    }
};

int main() {
    Car myCar("Toyota", "Corolla", 2023, 25000, 4, 1.8);
    
    myCar.displayCarInfo();
    
    // Accessing base class methods
    myCar.start();
    myCar.stop();
    
    // Using derived class method
    myCar.applyDiscount(10);
    
    return 0;
}
```

#### Key Aspects of Single Inheritance

1. **Constructor and Destructor Order**
   - Base class constructor is called before derived class constructor
   - Derived class destructor is called before base class destructor
   - This ensures proper initialization and cleanup

2. **Access Control**
   - Public inheritance: "is-a" relationship (Car is-a Vehicle)
   - Private members of base class are never directly accessible in derived class
   - Public members of base class become public in derived class (with public inheritance)
   - Protected members of base class are accessible in derived class

3. **Method Overriding**
   - Derived class can override (redefine) methods from the base class
   - The most specific version of the method is called

```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    void draw() const {
        cout << "Drawing a shape" << endl;
    }
    
    double area() const {
        cout << "Shape::area() called" << endl;
        return 0.0;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    // Override the base class method
    double area() const {
        cout << "Circle::area() called" << endl;
        return 3.14159 * radius * radius;
    }
    
    // Add new functionality
    double circumference() const {
        return 2 * 3.14159 * radius;
    }
};

int main() {
    Shape genericShape;
    Circle circle(5.0);
    
    genericShape.draw();  // Drawing a shape
    circle.draw();        // Drawing a shape (inherited from Shape)
    
    cout << "Generic shape area: " << genericShape.area() << endl;
    cout << "Circle area: " << circle.area() << endl;
    cout << "Circle circumference: " << circle.circumference() << endl;
    
    return 0;
}
```

### 6.5.2 Multiple Inheritance

Multiple inheritance allows a class to inherit from more than one base class.

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
        cout << "Person constructor called" << endl;
    }
    
    ~Person() {
        cout << "Person destructor called" << endl;
    }
    
    void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    void sleep() const {
        cout << name << " is sleeping" << endl;
    }
};

class Employee {
private:
    int employeeId;
    double salary;
    
public:
    Employee(int id, double s) : employeeId(id), salary(s) {
        cout << "Employee constructor called" << endl;
    }
    
    ~Employee() {
        cout << "Employee destructor called" << endl;
    }
    
    void displayEmployeeInfo() const {
        cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
    }
    
    void work() const {
        cout << "Employee is working" << endl;
    }
};

// Multiple inheritance
class Manager : public Person, public Employee {
private:
    string department;
    
public:
    Manager(const string& name, int age, int id, double salary, const string& dept)
        : Person(name, age), Employee(id, salary), department(dept) {
        cout << "Manager constructor called" << endl;
    }
    
    ~Manager() {
        cout << "Manager destructor called" << endl;
    }
    
    void displayManagerInfo() const {
        displayInfo();           // From Person
        displayEmployeeInfo();   // From Employee
        cout << "Department: " << department << endl;
    }
    
    void manage() const {
        cout << "Manager is managing the " << department << " department" << endl;
    }
};

int main() {
    Manager manager("John Smith", 35, 12345, 75000, "Engineering");
    
    // Access methods from both base classes
    manager.displayManagerInfo();
    manager.sleep();  // From Person
    manager.work();   // From Employee
    manager.manage(); // From Manager
    
    return 0;
}
```

#### Challenges of Multiple Inheritance: The Diamond Problem

One of the main issues with multiple inheritance is the "Diamond Problem," which occurs when a class inherits from two classes that have a common base class.

```cpp
#include <iostream>
using namespace std;

class PoweredDevice {
private:
    int powerUsage;
    
public:
    PoweredDevice(int power) : powerUsage(power) {
        cout << "PoweredDevice constructor called with power: " << power << endl;
    }
    
    void usePower() const {
        cout << "Using " << powerUsage << " watts of power" << endl;
    }
};

class Scanner : public PoweredDevice {
public:
    Scanner(int power) : PoweredDevice(power) {
        cout << "Scanner constructor called" << endl;
    }
    
    void scan() const {
        cout << "Scanning document" << endl;
        usePower();
    }
};

class Printer : public PoweredDevice {
public:
    Printer(int power) : PoweredDevice(power) {
        cout << "Printer constructor called" << endl;
    }
    
    void print() const {
        cout << "Printing document" << endl;
        usePower();
    }
};

// Diamond problem occurs here
class Copier : public Scanner, public Printer {
public:
    Copier(int scannerPower, int printerPower) 
        : Scanner(scannerPower), Printer(printerPower) {
        cout << "Copier constructor called" << endl;
    }
    
    void copy() const {
        scan();
        print();
    }
};

int main() {
    Copier copier(100, 200);
    
    // Problem: Which usePower() method to call?
    // This would be ambiguous:
    // copier.usePower();  // Ambiguous - from Scanner or Printer?
    
    // We have to specify:
    copier.Scanner::usePower();
    copier.Printer::usePower();
    
    // But methods unique to each class work fine
    copier.scan();
    copier.print();
    copier.copy();
    
    return 0;
}
```

#### Solving the Diamond Problem with Virtual Inheritance

Virtual inheritance solves the diamond problem by ensuring only one instance of the common base class:

```cpp
#include <iostream>
using namespace std;

class PoweredDevice {
private:
    int powerUsage;
    
public:
    PoweredDevice(int power) : powerUsage(power) {
        cout << "PoweredDevice constructor called with power: " << power << endl;
    }
    
    void usePower() const {
        cout << "Using " << powerUsage << " watts of power" << endl;
    }
};

// Use virtual inheritance
class Scanner : virtual public PoweredDevice {
public:
    Scanner(int power) : PoweredDevice(power) {
        cout << "Scanner constructor called" << endl;
    }
    
    void scan() const {
        cout << "Scanning document" << endl;
        usePower();
    }
};

// Use virtual inheritance
class Printer : virtual public PoweredDevice {
public:
    Printer(int power) : PoweredDevice(power) {
        cout << "Printer constructor called" << endl;
    }
    
    void print() const {
        cout << "Printing document" << endl;
        usePower();
    }
};

class Copier : public Scanner, public Printer {
public:
    // With virtual inheritance, the most derived class is responsible
    // for calling the constructor of the virtual base class
    Copier(int power) 
        : PoweredDevice(power), Scanner(power), Printer(power) {
        cout << "Copier constructor called" << endl;
    }
    
    void copy() const {
        scan();
        print();
    }
};

int main() {
    Copier copier(150);
    
    // No ambiguity - only one PoweredDevice instance exists
    copier.usePower();
    
    copier.copy();
    
    return 0;
}
```

#### Best Practices for Multiple Inheritance

1. **Use it sparingly**: Multiple inheritance often introduces complexity
2. **Prefer composition**: Consider using composition over multiple inheritance
3. **Use virtual inheritance** when inheriting from classes with a common base
4. **Keep interface and implementation separate**: Use multiple inheritance primarily for interface inheritance
5. **Avoid name collisions**: Prevent ambiguity by using different names or explicit qualification

### 6.5.3 Multilevel Inheritance

Multilevel inheritance creates a chain of inheritance where a derived class becomes the base class for another derived class.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
protected:
    string name;
    
public:
    Animal(const string& n) : name(n) {
        cout << "Animal constructor called" << endl;
    }
    
    ~Animal() {
        cout << "Animal destructor called" << endl;
    }
    
    void eat() const {
        cout << name << " is eating" << endl;
    }
    
    void sleep() const {
        cout << name << " is sleeping" << endl;
    }
};

// First level of inheritance
class Mammal : public Animal {
private:
    int pregnancyDuration;  // in months
    
public:
    Mammal(const string& n, int duration) 
        : Animal(n), pregnancyDuration(duration) {
        cout << "Mammal constructor called" << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destructor called" << endl;
    }
    
    void giveBirth() const {
        cout << name << " gives birth after " << pregnancyDuration 
             << " months of pregnancy" << endl;
    }
};

// Second level of inheritance
class Cat : public Mammal {
private:
    bool isIndoor;
    
public:
    Cat(const string& n, bool indoor) 
        : Mammal(n, 2), isIndoor(indoor) {  // Cats have a 2-month pregnancy
        cout << "Cat constructor called" << endl;
    }
    
    ~Cat() {
        cout << "Cat destructor called" << endl;
    }
    
    void purr() const {
        cout << name << " is purring" << endl;
    }
    
    void displayInfo() const {
        cout << name << " is a " << (isIndoor ? "indoor" : "outdoor") << " cat" << endl;
    }
};

int main() {
    Cat myCat("Whiskers", true);
    
    // Methods from Animal (base class)
    myCat.eat();
    myCat.sleep();
    
    // Method from Mammal (intermediate class)
    myCat.giveBirth();
    
    // Methods from Cat (derived class)
    myCat.purr();
    myCat.displayInfo();
    
    return 0;
}
```

#### Key Aspects of Multilevel Inheritance

1. **Constructor/Destructor Chain**:
   - Constructors are called in order from base to most derived
   - Destructors are called in reverse order, from most derived to base

2. **Method Resolution**:
   - Calls to methods are resolved by searching first in the most derived class
   - If not found, the search continues up the inheritance hierarchy

3. **Access Control Propagation**:
   - Access specifiers apply at each level of inheritance
   - Private members of Animal are not directly accessible in Cat

#### Potential Issues with Deep Inheritance Hierarchies

1. **Complexity**: Deep hierarchies can be hard to understand and maintain
2. **Fragility**: Changes in base classes impact all derived classes
3. **Performance**: Long chains of virtual function calls may affect performance
4. **Inheritance leakage**: Implementation details may leak through the hierarchy

### 6.5.4 Hierarchical Inheritance

Hierarchical inheritance occurs when multiple classes inherit from a single base class.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Employee {
protected:
    string name;
    int id;
    double baseSalary;
    
public:
    Employee(const string& n, int i, double salary)
        : name(n), id(i), baseSalary(salary) {
        cout << "Employee constructor called" << endl;
    }
    
    ~Employee() {
        cout << "Employee destructor called" << endl;
    }
    
    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id
             << ", Base Salary: $" << baseSalary << endl;
    }
    
    virtual double calculateSalary() const {
        return baseSalary;
    }
};

// Derived class 1
class Developer : public Employee {
private:
    string programmingLanguage;
    int linesOfCode;
    
public:
    Developer(const string& n, int i, double salary,
             const string& lang, int loc)
        : Employee(n, i, salary), 
          programmingLanguage(lang),
          linesOfCode(loc) {
        cout << "Developer constructor called" << endl;
    }
    
    ~Developer() {
        cout << "Developer destructor called" << endl;
    }
    
    void writeCode() const {
        cout << name << " is writing code in " << programmingLanguage << endl;
    }
    
    double calculateSalary() const override {
        // Bonus based on lines of code
        return baseSalary + (linesOfCode / 1000) * 500;
    }
};

// Derived class 2
class Manager : public Employee {
private:
    int teamSize;
    
public:
    Manager(const string& n, int i, double salary, int size)
        : Employee(n, i, salary), teamSize(size) {
        cout << "Manager constructor called" << endl;
    }
    
    ~Manager() {
        cout << "Manager destructor called" << endl;
    }
    
    void manageMeeting() const {
        cout << name << " is conducting a meeting with " 
             << teamSize << " team members" << endl;
    }
    
    double calculateSalary() const override {
        // Managers get bonus based on team size
        return baseSalary + teamSize * 1000;
    }
};

// Derived class 3
class Designer : public Employee {
private:
    string designTool;
    int projects;
    
public:
    Designer(const string& n, int i, double salary,
             const string& tool, int p)
        : Employee(n, i, salary), designTool(tool), projects(p) {
        cout << "Designer constructor called" << endl;
    }
    
    ~Designer() {
        cout << "Designer destructor called" << endl;
    }
    
    void createDesign() const {
        cout << name << " is creating designs using " << designTool << endl;
    }
    
    double calculateSalary() const override {
        // Designers get bonus based on projects
        return baseSalary + projects * 750;
    }
};

int main() {
    Developer dev("Alice", 1001, 70000, "C++", 5000);
    Manager mgr("Bob", 2001, 85000, 8);
    Designer des("Charlie", 3001, 65000, "Photoshop", 12);
    
    cout << "\nEmployee Information:" << endl;
    cout << "-------------------" << endl;
    
    dev.displayInfo();
    cout << "Total Salary: $" << dev.calculateSalary() << endl;
    dev.writeCode();
    
    cout << endl;
    
    mgr.displayInfo();
    cout << "Total Salary: $" << mgr.calculateSalary() << endl;
    mgr.manageMeeting();
    
    cout << endl;
    
    des.displayInfo();
    cout << "Total Salary: $" << des.calculateSalary() << endl;
    des.createDesign();
    
    return 0;
}
```

#### Benefits of Hierarchical Inheritance

1. **Code Organization**: Common attributes and behaviors are defined in the base class
2. **Code Reuse**: Derived classes reuse code from the base class
3. **Specialization**: Each derived class can add its own specialized functionality
4. **Polymorphism**: Base class pointers can refer to objects of any derived class (discussed in section 6.6)

#### Potential Issues

1. **Base Class Changes**: Changes to the base class affect all derived classes
2. **Design Constraints**: The base class design influences all derived classes
3. **Feature Bloat**: The base class may accumulate features to support all derived classes

### 6.5.5 Hybrid Inheritance

Hybrid inheritance is a combination of multiple inheritance types (like multilevel and multiple inheritance).

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    
public:
    Person(const string& n, int a) : name(n), age(a) {
        cout << "Person constructor called" << endl;
    }
    
    void displayPerson() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// First level derived class
class Student : virtual public Person {
protected:
    int studentId;
    
public:
    Student(const string& n, int a, int id)
        : Person(n, a), studentId(id) {
        cout << "Student constructor called" << endl;
    }
    
    void displayStudent() const {
        cout << "Student ID: " << studentId << endl;
    }
};

// First level derived class
class Employee : virtual public Person {
protected:
    int employeeId;
    double salary;
    
public:
    Employee(const string& n, int a, int id, double s)
        : Person(n, a), employeeId(id), salary(s) {
        cout << "Employee constructor called" << endl;
    }
    
    void displayEmployee() const {
        cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
    }
};

// Second level derived class (multiple + multilevel)
class TeachingAssistant : public Student, public Employee {
private:
    string department;
    int hoursPerWeek;
    
public:
    TeachingAssistant(const string& n, int a, int studentId, int employeeId,
                     double salary, const string& dept, int hours)
        : Person(n, a),  // Must initialize virtual base class
          Student(n, a, studentId),
          Employee(n, a, employeeId, salary),
          department(dept), hoursPerWeek(hours) {
        cout << "TeachingAssistant constructor called" << endl;
    }
    
    void displayTA() const {
        // Base class display methods
        displayPerson();
        displayStudent();
        displayEmployee();
        
        // Additional TA information
        cout << "Department: " << department << endl;
        cout << "Hours per week: " << hoursPerWeek << endl;
    }
};

int main() {
    TeachingAssistant ta("David", 25, 10045, 5001, 20000, "Computer Science", 20);
    
    cout << "\nTeaching Assistant Information:" << endl;
    cout << "-----------------------------" << endl;
    ta.displayTA();
    
    return 0;
}
```

#### Key Aspects of Hybrid Inheritance

1. **Complexity Management**: Virtual inheritance is often necessary to avoid the diamond problem
2. **Constructor Initialization**: The most derived class must initialize virtual base classes directly
3. **Multiple Inheritance Paths**: Methods can be inherited through multiple paths
4. **Name Resolution**: May require explicit qualification to resolve ambiguities

### Inheritance Best Practices

1. **Use "is-a" relationships**: Inheritance should represent an "is-a" relationship (Car is-a Vehicle)
2. **Prefer composition for "has-a" relationships**: Use composition instead of inheritance for "has-a" relationships
3. **Keep inheritance hierarchies shallow**: Avoid deep inheritance chains
4. **Design for inheritance or prohibit it**:
   - Design classes explicitly for inheritance, or
   - Make them final/sealed to prevent inheritance
5. **Use virtual destructors** in base classes when using polymorphism
6. **Follow the Liskov Substitution Principle**: Derived classes should be substitutable for their base classes
7. **Don't override non-virtual methods**: Override only virtual methods from base classes
8. **Access base class methods explicitly** when needed using scope resolution operator (`::`)
9. **Initialize base classes properly** in constructors
10. **Consider alternatives to multiple inheritance** where possible

## 6.6 Polymorphism

Polymorphism allows objects of different classes to be treated as objects of a common base class. The word polymorphism means "many forms." In C++, polymorphism can be:

1. **Compile-time polymorphism** (static binding): Function overloading, operator overloading
2. **Runtime polymorphism** (dynamic binding): Virtual functions, function overriding

### 6.6.1 Compile-time Polymorphism (Function/Operator Overloading)

Compile-time polymorphism is resolved at compile time and doesn't require any runtime type checking.

#### Function Overloading

Function overloading allows multiple functions with the same name but different parameters:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    // Overloaded functions with different parameter types
    int add(int a, int b) {
        cout << "Adding two integers" << endl;
        return a + b;
    }
    
    double add(double a, double b) {
        cout << "Adding two doubles" << endl;
        return a + b;
    }
    
    string add(const string& a, const string& b) {
        cout << "Concatenating two strings" << endl;
        return a + b;
    }
    
    // Overloaded functions with different number of parameters
    int add(int a, int b, int c) {
        cout << "Adding three integers" << endl;
        return a + b + c;
    }
    
    // Overloaded functions with different parameter order
    double add(int a, double b) {
        cout << "Adding integer and double" << endl;
        return a + b;
    }
    
    double add(double a, int b) {
        cout << "Adding double and integer" << endl;
        return a + b;
    }
};

int main() {
    Calculator calc;
    
    cout << "Result: " << calc.add(5, 3) << endl;
    cout << "Result: " << calc.add(3.5, 2.7) << endl;
    cout << "Result: " << calc.add("Hello, ", "World!") << endl;
    cout << "Result: " << calc.add(1, 2, 3) << endl;
    cout << "Result: " << calc.add(10, 3.5) << endl;
    cout << "Result: " << calc.add(2.5, 10) << endl;
    
    return 0;
}
```

The compiler determines which function to call based on:
1. Number of arguments
2. Types of arguments
3. Const-ness of arguments
4. Reference qualifiers (lvalue/rvalue)

#### Function Overloading Resolution

The compiler follows these steps to resolve function calls:
1. Find exact matches (considering trivial conversions)
2. Try standard conversions (like int to double)
3. Try user-defined conversions
4. Try ellipsis matches
5. If multiple matches are found at the same level, the call is ambiguous

```cpp
#include <iostream>
using namespace std;

void display(int x) {
    cout << "Integer: " << x << endl;
}

void display(double x) {
    cout << "Double: " << x << endl;
}

void display(char* x) {
    cout << "String: " << x << endl;
}

int main() {
    display(10);        // Calls display(int)
    display(10.5);      // Calls display(double)
    display("Hello");   // Calls display(char*)
    
    // What happens with this?
    // display('A');   // 'A' is a char, not int or double
    // The char 'A' is implicitly converted to int, calling display(int)
    
    return 0;
}
```

#### Function Overloading vs Function Overriding

- **Overloading**: Multiple functions with the same name but different parameters
- **Overriding**: Redefining a function from a base class in a derived class (same name, same parameters)

#### Operator Overloading

Operator overloading allows you to redefine how operators work for user-defined types:

```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Overload the + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // Overload the * operator
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    
    // Overload the == operator
    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }
    
    // Overload the != operator
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Overload the << operator as a friend function
    friend ostream& operator<<(ostream& os, const Complex& c);
    
    // Overload the >> operator as a friend function
    friend istream& operator>>(istream& is, Complex& c);
};

// Implementation of friend functions outside the class
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0)
        os << "+" << c.imag << "i";
    else
        os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}

int main() {
    Complex a(3, 4);
    Complex b(1, 2);
    
    // Using overloaded operators
    Complex c = a + b;
    Complex d = a * b;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << c << endl;
    cout << "a * b = " << d << endl;
    
    if (a == b)
        cout << "a equals b" << endl;
    else
        cout << "a does not equal b" << endl;
    
    // Using overloaded input operator
    Complex userInput;
    cin >> userInput;
    cout << "You entered: " << userInput << endl;
    
    return 0;
}
```

#### Commonly Overloaded Operators

| Category | Operators |
|----------|-----------|
| Arithmetic | `+`, `-`, `*`, `/`, `%`, `++`, `--` |
| Comparison | `==`, `!=`, `<`, `>`, `<=`, `>=` |
| Logical | `!`, `&&`, `\|\|` |
| Bitwise | `&`, `\|`, `^`, `~`, `<<`, `>>` |
| Assignment | `=`, `+=`, `-=`, `*=`, `/=`, etc. |
| Memory | `new`, `delete`, `new[]`, `delete[]` |
| Other | `()`, `[]`, `->`, `,` |

#### Rules and Best Practices for Operator Overloading

1. **Can't change precedence**: The precedence of operators remains the same
2. **Can't change arity**: Unary operators remain unary, binary operators remain binary
3. **Can't create new operators**: You can only overload existing operators
4. **Can't overload operators for built-in types**: Only for user-defined types
5. **Some operators can't be overloaded**: `.`, `.*`, `::`, `? :`, `sizeof`
6. **Member vs. Non-member**:
   - Binary operators with left-side object: Usually member functions
   - Binary operators with modified left operand: Non-member functions
   - Assignment, subscript, function call: Must be members
7. **Return appropriate types**: 
   - Arithmetic operators usually return by value
   - Assignment operators return a reference to *this

### 6.6.2 Run-time Polymorphism (Virtual Functions, vtables)

Runtime polymorphism is achieved through virtual functions and is resolved at runtime based on the actual type of the object.

#### Virtual Functions

A virtual function is a member function that can be redefined in derived classes. The compiler determines which function to call at runtime:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape {
protected:
    string name;
    
public:
    Shape(const string& n) : name(n) {}
    
    // Virtual function
    virtual double area() const {
        return 0.0;
    }
    
    // Virtual function
    virtual double perimeter() const {
        return 0.0;
    }
    
    // Non-virtual function
    string getName() const {
        return name;
    }
    
    // Virtual destructor - important!
    virtual ~Shape() {
        cout << "Shape destructor: " << name << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const string& n, double r) : Shape(n), radius(r) {}
    
    // Override virtual function
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    // Override virtual function
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    ~Circle() {
        cout << "Circle destructor: " << name << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(const string& n, double w, double h)
        : Shape(n), width(w), height(h) {}
    
    // Override virtual function
    double area() const override {
        return width * height;
    }
    
    // Override virtual function
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    ~Rectangle() {
        cout << "Rectangle destructor: " << name << endl;
    }
};

int main() {
    // Create objects
    Circle circle("Circle1", 5.0);
    Rectangle rectangle("Rectangle1", 4.0, 6.0);
    
    // Direct calls - no polymorphism
    cout << "Direct calls:" << endl;
    cout << circle.getName() << " area: " << circle.area() << endl;
    cout << rectangle.getName() << " area: " << rectangle.area() << endl;
    
    // Polymorphic calls through base class pointers
    cout << "\nPolymorphic calls:" << endl;
    Shape* shapes[] = { &circle, &rectangle };
    
    for (Shape* shape : shapes) {
        cout << shape->getName() << " area: " << shape->area() << endl;
        cout << shape->getName() << " perimeter: " << shape->perimeter() << endl;
    }
    
    // Dynamic allocation
    Shape* dynamicCircle = new Circle("DynamicCircle", 3.0);
    Shape* dynamicRectangle = new Rectangle("DynamicRectangle", 2.0, 7.0);
    
    cout << "\nDynamically allocated objects:" << endl;
    cout << dynamicCircle->getName() << " area: " << dynamicCircle->area() << endl;
    cout << dynamicRectangle->getName() << " area: " << dynamicRectangle->area() << endl;
    
    // Clean up dynamic objects - virtual destructor ensures proper cleanup
    delete dynamicCircle;
    delete dynamicRectangle;
    
    return 0;
}
```

#### How Virtual Functions Work: The vtable

Virtual functions are implemented using a mechanism called the vtable (virtual function table):

1. **vtable**: A table of function pointers, one for each virtual function in the class
2. **vptr**: A hidden pointer added to objects of classes with virtual functions
3. **Working**:
   - Each class with virtual functions has its own vtable
   - Each object has a vptr pointing to its class's vtable
   - When a virtual function is called through a pointer or reference, the correct function is found via the vtable

```
Memory layout:

Base class object:
+----------------+
| vptr           | --> Base class vtable:
+----------------+      +-----------------+
| Base members   |      | Base::func1()   |
+----------------+      | Base::func2()   |
                        +-----------------+

Derived class object:
+----------------+
| vptr           | --> Derived class vtable:
+----------------+      +-------------------+
| Base members   |      | Derived::func1()  | (overridden)
+----------------+      | Base::func2()     | (inherited)
| Derived members|      +-------------------+
+----------------+
```

#### Virtual Destructors

When using polymorphism, base classes should have virtual destructors to ensure proper cleanup of derived classes:

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    
    // Case 1: Non-virtual destructor
    ~Base() { cout << "Base destructor" << endl; }
    
    // Case 2: Virtual destructor
    // virtual ~Base() { cout << "Base virtual destructor" << endl; }
};

class Derived : public Base {
private:
    int* data;
    
public:
    Derived() : Base() {
        cout << "Derived constructor" << endl;
        data = new int[100];
    }
    
    ~Derived() {
        cout << "Derived destructor" << endl;
        delete[] data;
    }
};

int main() {
    // Case 1: Direct object - always works correctly
    cout << "Creating and destroying Derived object directly:" << endl;
    {
        Derived d;
    }  // Both destructors called
    
    cout << "\nCreating and destroying via Base pointer:" << endl;
    {
        Base* b = new Derived();
        delete b;  // Without virtual destructor, only Base destructor is called!
                   // This leads to a memory leak as Derived's destructor is not called
    }
    
    return 0;
}
```

#### Pure Virtual Functions and Abstract Classes

A pure virtual function is declared with `= 0` and has no implementation in the base class. A class with at least one pure virtual function becomes an abstract class:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract class (has at least one pure virtual function)
class Shape {
protected:
    string name;
    
public:
    Shape(const string& n) : name(n) {}
    
    // Pure virtual function - must be implemented by derived classes
    virtual double area() const = 0;
    
    // Pure virtual function
    virtual double perimeter() const = 0;
    
    // Regular virtual function with default implementation
    virtual void display() const {
        cout << "Shape: " << name << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
    
    string getName() const {
        return name;
    }
    
    virtual ~Shape() {
        cout << "Shape destructor" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const string& n, double r) : Shape(n), radius(r) {}
    
    // Implementation of pure virtual function
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    // Implementation of pure virtual function
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    // Override virtual function
    void display() const override {
        cout << "Circle: " << name << endl;
        cout << "Radius: " << radius << endl;
        cout << "Area: " << area() << endl;
        cout << "Circumference: " << perimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(const string& n, double w, double h)
        : Shape(n), width(w), height(h) {}
    
    // Implementation of pure virtual function
    double area() const override {
        return width * height;
    }
    
    // Implementation of pure virtual function
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    // Using default display implementation from Shape
};

int main() {
    // Shape shape("GenericShape");  // Error - cannot instantiate abstract class
    
    Circle circle("Circle1", 5.0);
    Rectangle rectangle("Rectangle1", 4.0, 6.0);
    
    // Polymorphic container
    vector<Shape*> shapes;
    shapes.push_back(&circle);
    shapes.push_back(&rectangle);
    
    // Polymorphic behavior
    for (const Shape* shape : shapes) {
        shape->display();
        cout << endl;
    }
    
    return 0;
}
```

#### Key Points About Abstract Classes

1. **Cannot be instantiated** directly
2. **Can contain both pure virtual and regular functions**
3. **Derived classes must implement all pure virtual functions**
4. **Useful for defining interfaces** in C++

#### Virtual Function Table (vtable) in Detail

The vtable mechanism is how C++ implements runtime polymorphism:

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void func1() { cout << "Base::func1()" << endl; }
    virtual void func2() { cout << "Base::func2()" << endl; }
    void func3() { cout << "Base::func3()" << endl; }  // Non-virtual
    virtual ~Base() { cout << "Base destructor" << endl; }
};

class Derived : public Base {
public:
    // Override func1
    void func1() override { cout << "Derived::func1()" << endl; }
    // func2 is inherited from Base
    // Override non-virtual func3 (not polymorphic)
    void func3() { cout << "Derived::func3()" << endl; }
    ~Derived() { cout << "Derived destructor" << endl; }
};

int main() {
    cout << "Calling through Base pointer to Base object:" << endl;
    Base* b1 = new Base();
    b1->func1();  // Base::func1()
    b1->func2();  // Base::func2()
    b1->func3();  // Base::func3()
    delete b1;
    
    cout << "\nCalling through Base pointer to Derived object:" << endl;
    Base* b2 = new Derived();
    b2->func1();  // Derived::func1() - virtual, uses vtable
    b2->func2();  // Base::func2() - virtual, uses vtable
    b2->func3();  // Base::func3() - non-virtual, determined by pointer type
    delete b2;    // Calls both destructors due to virtual destructor
    
    cout << "\nCalling through Derived pointer to Derived object:" << endl;
    Derived* d = new Derived();
    d->func1();   // Derived::func1()
    d->func2();   // Base::func2()
    d->func3();   // Derived::func3() - non-virtual, determined by pointer type
    delete d;
    
    return 0;
}
```

#### Performance Considerations for Virtual Functions

1. **Memory Overhead**: Each object with virtual functions has a vptr
2. **Speed Overhead**: Virtual function calls require an extra indirection
3. **Cache Misses**: Virtual function calls can lead to more cache misses
4. **Compiler Optimization**: Virtual functions can limit optimizations like inlining

### Polymorphism Best Practices

1. **Use virtual destructors** in base classes
2. **Use the `override` keyword** (C++11) for derived class functions
3. **Use the `final` keyword** (C++11) to prevent further overriding
4. **Consider using pure virtual functions** for interfaces
5. **Be cautious with multiple inheritance** and virtual functions
6. **Avoid calling virtual functions in constructors/destructors**
7. **Understand the performance implications** of virtual functions
8. **Use runtime polymorphism only when needed**

```cpp
// Using override and final keywords
class Base {
public:
    virtual void foo() { cout << "Base::foo()" << endl; }
    virtual void bar() { cout << "Base::bar()" << endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void foo() override { cout << "Derived::foo()" << endl; }
    void bar() override final { cout << "Derived::bar()" << endl; }
};

class Further : public Derived {
public:
    void foo() override { cout << "Further::foo()" << endl; }
    // void bar() override { }  // Error: cannot override final function
};
```

#### Object Slicing

Object slicing occurs when a derived class object is assigned to a base class object (not a pointer or reference):

```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int baseValue;
    
public:
    Base(int value) : baseValue(value) {}
    
    virtual void display() const {
        cout << "Base class with value: " << baseValue << endl;
    }
};

class Derived : public Base {
private:
    int derivedValue;
    
public:
    Derived(int baseVal, int derivedVal) 
        : Base(baseVal), derivedValue(derivedVal) {}
    
    void display() const override {
        cout << "Derived class with base value: " << baseValue 
             << " and derived value: " << derivedValue << endl;
    }
};

void processReference(const Base& obj) {
    // No slicing here - virtual function call works correctly
    obj.display();
}

void processObject(Base obj) {
    // Object slicing! Only Base part is copied
    obj.display();  // Always calls Base::display
}

int main() {
    Derived derivedObj(10, 20);
    
    cout << "Original object:" << endl;
    derivedObj.display();  // Calls Derived::display
    
    cout << "\nThrough base reference (no slicing):" << endl;
    processReference(derivedObj);  // Calls Derived::display
    
    cout << "\nThrough base object (slicing occurs):" << endl;
    processObject(derivedObj);  // Calls Base::display
    
    cout << "\nAssignment to base (slicing):" << endl;
    Base baseObj = derivedObj;  // Object slicing!
    baseObj.display();  // Calls Base::display
    
    return 0;
}
```

To avoid object slicing:
1. Use pointers or references when working with polymorphic objects
2. Make base classes abstract to prevent direct instantiation
3. Delete the copy constructor and assignment operator if appropriate
4. Consider using shared ownership (shared_ptr) if ownership transfer is needed

Polymorphism is one of the most powerful features of C++ and object-oriented programming in general. It allows you to write code that works with objects of different types through a common interface, making your code more flexible and extensible.
