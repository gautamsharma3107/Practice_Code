# Object-Oriented Programming in C++

## Overview
Object-Oriented Programming (OOP) is a programming paradigm that uses "objects" to represent data and methods to manipulate that data. It promotes greater flexibility and maintainability in programming.

## Key Concepts

### 1. Classes and Objects
- **Class**: A blueprint for creating objects. It defines a datatype by bundling data and methods that work on that data.
- **Object**: An instance of a class. It contains real values instead of variables.

### 2. Access Specifiers
- **Public**: Members are accessible from outside the class.
- **Private**: Members are accessible only within the class.
- **Protected**: Members are accessible in the class and by derived class instances.

### 3. Constructors and Destructors
- **Constructor**: A special member function that is called when an object is instantiated. It initializes the object.
- **Destructor**: A special member function that is called when an object is destroyed. It cleans up resources.

### 4. Copy Constructors
- A constructor that creates a new object as a copy of an existing object.

### 5. Friend Functions
- Functions that are not members of a class but have access to its private and protected members.

### 6. Static Members
- Members that belong to the class rather than any object instance. They are shared among all instances of the class.
- Static data members are initialized outside the class and exist even when no objects of the class are created.
- Static member functions can only access static data members or other static member functions.

**Example:**
```cpp
class Counter {
private:
    static int count;  // Declaration of static member
    int id;
    
public:
    Counter() : id(++count) {
        std::cout << "Object " << id << " created\n";
    }
    
    ~Counter() {
        std::cout << "Object " << id << " destroyed\n";
        count--;
    }
    
    static int getCount() {  // Static member function
        return count;
    }
};

// Initialize static member outside the class
int Counter::count = 0;

int main() {
    std::cout << "Initial count: " << Counter::getCount() << std::endl;  // Access without object
    
    Counter c1;
    Counter c2;
    
    std::cout << "Count after creating objects: " << Counter::getCount() << std::endl;
    
    return 0;
}
```

### 7. Encapsulation
- The bundling of data and methods that operate on that data within one unit (class), restricting access to some of the object's components.
- Encapsulation provides data hiding and protection from unintended modifications.
- Implementation details are hidden from the user, exposing only necessary functionalities.

**Example:**
```cpp
class BankAccount {
private:
    std::string accountNumber;
    double balance;
    
    // Private method for validation
    bool isValidAmount(double amount) {
        return amount > 0;
    }
    
public:
    BankAccount(std::string accNo, double initialBalance) 
        : accountNumber(accNo), balance(initialBalance) {}
    
    // Public interface for depositing money
    bool deposit(double amount) {
        if (!isValidAmount(amount))
            return false;
        
        balance += amount;
        return true;
    }
    
    // Public interface for withdrawing money
    bool withdraw(double amount) {
        if (!isValidAmount(amount) || amount > balance)
            return false;
        
        balance -= amount;
        return true;
    }
    
    double getBalance() const {
        return balance;
    }
    
    std::string getAccountNumber() const {
        return accountNumber;
    }
};
```

### 8. Inheritance
- A mechanism where a new class inherits properties and behavior (methods) from an existing class. It promotes code reusability.
- **Types of Inheritance:**
  1. **Single Inheritance**: A derived class inherits from only one base class.
  2. **Multiple Inheritance**: A derived class inherits from multiple base classes.
  3. **Multilevel Inheritance**: A class derives from another derived class.
  4. **Hierarchical Inheritance**: Multiple classes derive from a single base class.
  5. **Hybrid Inheritance**: Combination of multiple and multilevel inheritance.

**Example of Single Inheritance:**
```cpp
class Person {
protected:
    std::string name;
    int age;
    
public:
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    void introduce() const {
        std::cout << "My name is " << name << " and I am " << age << " years old." << std::endl;
    }
};

class Student : public Person {
private:
    std::string studentId;
    double gpa;
    
public:
    Student(const std::string& n, int a, const std::string& id, double g)
        : Person(n, a), studentId(id), gpa(g) {}
    
    void displayRecord() const {
        introduce();  // Using base class method
        std::cout << "Student ID: " << studentId << ", GPA: " << gpa << std::endl;
    }
};
```

**Example of Multiple Inheritance:**
```cpp
class Employee {
protected:
    std::string employeeId;
    double salary;
    
public:
    Employee(const std::string& id, double s) : employeeId(id), salary(s) {}
    
    void displaySalary() const {
        std::cout << "Salary: $" << salary << std::endl;
    }
};

class TeachingAssistant : public Student, public Employee {
private:
    std::string department;
    
public:
    TeachingAssistant(
        const std::string& n, int a,
        const std::string& studentId, double gpa,
        const std::string& empId, double salary,
        const std::string& dept
    ) : Student(n, a, studentId, gpa), 
        Employee(empId, salary), 
        department(dept) {}
    
    void displayInfo() const {
        displayRecord();  // From Student class
        displaySalary();  // From Employee class
        std::cout << "Department: " << department << std::endl;
    }
};
```

### 9. Polymorphism
- The ability to present the same interface for different underlying data types. It can be achieved through:
  - **Compile-time polymorphism** (function overloading and operator overloading)
  - **Run-time polymorphism** (method overriding)

#### Compile-time Polymorphism
- **Function Overloading**: Multiple functions with the same name but different parameters.
- **Operator Overloading**: Giving special meaning to operators for user-defined types.

**Example of Function Overloading:**
```cpp
class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
};
```

**Example of Operator Overloading:**
```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Overload + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    void display() const {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};
```

#### Run-time Polymorphism
- Achieved through **method overriding** and **virtual functions**.
- Base class pointer can point to derived class objects, and the appropriate function is called based on the actual object type.

**Example:**
```cpp
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape" << std::endl;
    }
    
    virtual double area() const {
        return 0;
    }
    
    // Virtual destructor ensures proper cleanup of derived objects
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        std::cout << "Drawing a circle" << std::endl;
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing a rectangle" << std::endl;
    }
    
    double area() const override {
        return width * height;
    }
};

int main() {
    Shape* shapes[3];
    shapes[0] = new Shape();
    shapes[1] = new Circle(5.0);
    shapes[2] = new Rectangle(4.0, 6.0);
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();  // Calls appropriate draw() method
        std::cout << "Area: " << shapes[i]->area() << std::endl;
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

### 10. Abstract Classes and Pure Virtual Functions
- **Abstract Class**: A class that cannot be instantiated and is designed to be a base class. It contains at least one pure virtual function.
- **Pure Virtual Function**: A function declared in a base class that has no definition relative to that class.

**Example:**
```cpp
class AbstractShape {
public:
    // Pure virtual functions
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    
    // Regular virtual function with implementation
    virtual void printInfo() const {
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
    
    // Virtual destructor
    virtual ~AbstractShape() {}
};

class Square : public AbstractShape {
private:
    double side;
    
public:
    Square(double s) : side(s) {}
    
    double area() const override {
        return side * side;
    }
    
    double perimeter() const override {
        return 4 * side;
    }
    
    void draw() const override {
        std::cout << "Drawing a square with side " << side << std::endl;
    }
};

class Triangle : public AbstractShape {
private:
    double a, b, c;  // Sides
    
public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}
    
    double area() const override {
        // Heron's formula for triangle area
        double s = (a + b + c) / 2;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }
    
    double perimeter() const override {
        return a + b + c;
    }
    
    void draw() const override {
        std::cout << "Drawing a triangle with sides " << a << ", " << b << ", " << c << std::endl;
    }
};
```

### 11. Interfaces
- A contract that a class can implement. It defines methods that must be created within any class that implements the interface.

**Example:**
```cpp
// Interface for drawable objects
class IDrawable {
public:
    virtual void draw() const = 0;
    virtual ~IDrawable() {}  // Virtual destructor is necessary for interfaces
};

// Interface for movable objects
class IMovable {
public:
    virtual void move(double x, double y) = 0;
    virtual ~IMovable() {}
};

// Player class implements both interfaces
class Player : public IDrawable, public IMovable {
private:
    double x, y;
    std::string name;
    
public:
    Player(const std::string& n, double posX, double posY)
        : name(n), x(posX), y(posY) {}
        
    void draw() const override {
        std::cout << "Drawing player " << name << " at position (" << x << ", " << y << ")" << std::endl;
    }
    
    void move(double newX, double newY) override {
        x = newX;
        y = newY;
        std::cout << "Player " << name << " moved to (" << x << ", " << y << ")" << std::endl;
    }
};

// Enemy class also implements both interfaces
class Enemy : public IDrawable, public IMovable {
private:
    double x, y;
    int power;
    
public:
    Enemy(int p, double posX, double posY)
        : power(p), x(posX), y(posY) {}
        
    void draw() const override {
        std::cout << "Drawing enemy with power " << power << " at position ("
                  << x << ", " << y << ")" << std::endl;
    }
    
    void move(double newX, double newY) override {
        x = newX;
        y = newY;
        std::cout << "Enemy moved to (" << x << ", " << y << ")" << std::endl;
    }
};

void gameLoop(const std::vector<IDrawable*>& drawables) {
    // Draw all drawable objects
    for (const auto& drawable : drawables) {
        drawable->draw();
    }
}
```

## Problem Exercises

### 1. Create a Class
Design a class `Car` with attributes like `make`, `model`, and `year`. Implement methods to display the car's details.

**Solution:**
```cpp
#include <iostream>
#include <string>

class Car {
private:
    std::string make;
    std::string model;
    int year;
    double price;

public:
    // Constructor
    Car(std::string mk, std::string mdl, int yr, double pr)
        : make(mk), model(mdl), year(yr), price(pr) {}
        
    // Getter methods
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    
    // Setter methods
    void setPrice(double pr) { price = pr; }
    
    // Display car details
    void displayDetails() const {
        std::cout << year << " " << make << " " << model << std::endl;
        std::cout << "Price: $" << price << std::endl;
    }
    
    // Method to apply discount
    void applyDiscount(double percentage) {
        if (percentage > 0 && percentage < 100) {
            price = price * (1 - percentage/100.0);
            std::cout << "After " << percentage << "% discount, new price: $" << price << std::endl;
        }
    }
};

int main() {
    Car myCar("Toyota", "Corolla", 2022, 25000);
    myCar.displayDetails();
    
    myCar.applyDiscount(10);
    myCar.displayDetails();
    
    return 0;
}
```

### 2. Inheritance Example
Create a base class `Animal` with a method `sound()`. Derive classes `Dog` and `Cat` that override the `sound()` method.

**Solution:**
```cpp
#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;
    int age;
    
public:
    Animal(const std::string& n, int a) : name(n), age(a) {}
    
    virtual void sound() const {
        std::cout << "Animal makes a sound" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    virtual ~Animal() {}
};

class Dog : public Animal {
private:
    std::string breed;
    
public:
    Dog(const std::string& n, int a, const std::string& b)
        : Animal(n, a), breed(b) {}
    
    void sound() const override {
        std::cout << name << " the dog barks: Woof! Woof!" << std::endl;
    }
    
    void displayBreed() const {
        std::cout << "Breed: " << breed << std::endl;
    }
};

class Cat : public Animal {
private:
    bool isIndoor;
    
public:
    Cat(const std::string& n, int a, bool indoor)
        : Animal(n, a), isIndoor(indoor) {}
    
    void sound() const override {
        std::cout << name << " the cat meows: Meow! Meow!" << std::endl;
    }
    
    void displayHabitat() const {
        std::cout << name << " is an " << (isIndoor ? "indoor" : "outdoor") << " cat." << std::endl;
    }
};

int main() {
    Animal animal("Generic Animal", 5);
    Dog dog("Rex", 3, "German Shepherd");
    Cat cat("Whiskers", 2, true);
    
    std::cout << "--- Animal Info ---" << std::endl;
    animal.displayInfo();
    animal.sound();
    
    std::cout << "\n--- Dog Info ---" << std::endl;
    dog.displayInfo();  // Inherited method
    dog.displayBreed(); // Dog-specific method
    dog.sound();        // Overridden method
    
    std::cout << "\n--- Cat Info ---" << std::endl;
    cat.displayInfo();   // Inherited method
    cat.displayHabitat(); // Cat-specific method
    cat.sound();         // Overridden method
    
    return 0;
}
```

### 3. Polymorphism
Implement a function that takes a base class pointer and calls the overridden method in derived classes.

**Solution:**
```cpp
#include <iostream>
#include <vector>

class Vehicle {
protected:
    std::string brand;
    int year;
    
public:
    Vehicle(const std::string& b, int y) : brand(b), year(y) {}
    
    virtual void start() const {
        std::cout << "The vehicle is starting" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << year << " " << brand;
    }
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    int numDoors;
    
public:
    Car(const std::string& b, int y, int doors)
        : Vehicle(b, y), numDoors(doors) {}
    
    void start() const override {
        std::cout << "The car engine ignites with a roar" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << " Car with " << numDoors << " doors" << std::endl;
    }
};

class Motorcycle : public Vehicle {
private:
    std::string type; // Sport, Cruiser, etc.
    
public:
    Motorcycle(const std::string& b, int y, const std::string& t)
        : Vehicle(b, y), type(t) {}
    
    void start() const override {
        std::cout << "The motorcycle engine revs loudly" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << " " << type << " Motorcycle" << std::endl;
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& b, int y)
        : Vehicle(b, y) {}
    
    void start() const override {
        std::cout << "The bicycle is ready to pedal" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << " Bicycle" << std::endl;
    }
};

// Polymorphic function that works with any Vehicle type
void testDrive(const Vehicle& vehicle) {
    std::cout << "Testing vehicle: ";
    vehicle.displayInfo();
    vehicle.start();
    std::cout << "------------------" << std::endl;
}

int main() {
    Car car("Toyota", 2022, 4);
    Motorcycle motorcycle("Harley-Davidson", 2021, "Cruiser");
    Bicycle bicycle("Giant", 2023);
    
    // Using the polymorphic function with different vehicle types
    testDrive(car);
    testDrive(motorcycle);
    testDrive(bicycle);
    
    // Demonstrating polymorphism with container of pointers
    std::vector<Vehicle*> vehicles;
    vehicles.push_back(new Car("Honda", 2020, 2));
    vehicles.push_back(new Motorcycle("Ducati", 2023, "Sport"));
    vehicles.push_back(new Bicycle("Trek", 2022));
    
    std::cout << "\nVehicle Fleet Information:\n";
    for (const auto& vehicle : vehicles) {
        vehicle->displayInfo();
        vehicle->start();
        std::cout << std::endl;
    }
    
    // Clean up
    for (auto* vehicle : vehicles) {
        delete vehicle;
    }
    
    return 0;
}
```

### 4. Abstract Class
Create an abstract class `Shape` with a pure virtual function `area()`. Derive classes `Circle` and `Rectangle` that implement the `area()` method.

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <cmath>

class Shape {
protected:
    std::string color;
    
public:
    Shape(const std::string& c) : color(c) {}
    
    // Pure virtual function - makes Shape an abstract class
    virtual double area() const = 0;
    
    // Pure virtual function for perimeter/circumference
    virtual double perimeter() const = 0;
    
    // Regular virtual function
    virtual void display() const {
        std::cout << "Shape with color " << color << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
    
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const std::string& c, double r) : Shape(c), radius(r) {}
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void display() const override {
        std::cout << "Circle with color " << color << " and radius " << radius << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Circumference: " << perimeter() << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(const std::string& c, double l, double w) 
        : Shape(c), length(l), width(w) {}
    
    double area() const override {
        return length * width;
    }
    
    double perimeter() const override {
        return 2 * (length + width);
    }
    
    void display() const override {
        std::cout << "Rectangle with color " << color << std::endl;
        std::cout << "Length: " << length << ", Width: " << width << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c; // Three sides of the triangle
    
public:
    Triangle(const std::string& color, double side1, double side2, double side3)
        : Shape(color), a(side1), b(side2), c(side3) {}
        
    double area() const override {
        // Heron's formula
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double perimeter() const override {
        return a + b + c;
    }
    
    void display() const override {
        std::cout << "Triangle with color " << color << std::endl;
        std::cout << "Sides: " << a << ", " << b << ", " << c << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
};

int main() {
    // Shape shape("Red");  // Error: Cannot instantiate abstract class
    
    Circle circle("Blue", 5.0);
    Rectangle rectangle("Green", 4.0, 6.0);
    Triangle triangle("Yellow", 3.0, 4.0, 5.0);
    
    circle.display();
    std::cout << std::endl;
    rectangle.display();
    std::cout << std::endl;
    triangle.display();
    
    std::cout << "\nPolymorphic container of shapes:" << std::endl;
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle("Purple", 3.0));
    shapes.push_back(new Rectangle("Orange", 2.0, 7.0));
    shapes.push_back(new Triangle("Pink", 5.0, 5.0, 8.0));
    
    for (const auto& shape : shapes) {
        shape->display();
        std::cout << std::endl;
    }
    
    // Clean up
    for (auto* shape : shapes) {
        delete shape;
    }
    
    return 0;
}
```

### 5. Friend Function
Implement a friend function that can access private members of a class `Box`.

**Solution:**
```cpp
#include <iostream>

class Box {
private:
    double length;
    double width;
    double height;
    
public:
    Box(double l = 0, double w = 0, double h = 0) 
        : length(l), width(w), height(h) {}
    
    // Member function to calculate volume
    double volume() const {
        return length * width * height;
    }
    
    // Friend function declaration
    friend void printBoxDimensions(const Box& box);
    
    // Friend function to compare two boxes
    friend Box compareBoxes(const Box& box1, const Box& box2);
    
    // Friend class declaration
    friend class BoxFactory;
};

// Friend function definition - can access private members of Box
void printBoxDimensions(const Box& box) {
    std::cout << "Box dimensions: " 
              << box.length << " x " 
              << box.width << " x " 
              << box.height << std::endl;
}

// Friend function that compares two boxes and returns the larger one
Box compareBoxes(const Box& box1, const Box& box2) {
    double vol1 = box1.volume();
    double vol2 = box2.volume();
    
    std::cout << "Box 1 volume: " << vol1 << std::endl;
    std::cout << "Box 2 volume: " << vol2 << std::endl;
    
    if (vol1 >= vol2) {
        std::cout << "Box 1 is larger or equal" << std::endl;
        return box1;
    } else {
        std::cout << "Box 2 is larger" << std::endl;
        return box2;
    }
}

// Friend class can access all private members of Box
class BoxFactory {
public:
    static Box createCube(double side) {
        return Box(side, side, side);
    }
    
    static void resizeBox(Box& box, double factor) {
        box.length *= factor;
        box.width *= factor;
        box.height *= factor;
    }
    
    static void displayBoxDetails(const Box& box) {
        std::cout << "Box details from factory:" << std::endl;
        std::cout << "Length: " << box.length << std::endl;
        std::cout << "Width: " << box.width << std::endl;
        std::cout << "Height: " << box.height << std::endl;
        std::cout << "Volume: " << box.volume() << std::endl;
    }
};

int main() {
    Box box1(2.0, 3.0, 4.0);
    Box box2(5.0, 1.0, 2.0);
    
    std::cout << "Box 1 volume: " << box1.volume() << std::endl;
    printBoxDimensions(box1);  // Using friend function
    
    std::cout << "\nComparing boxes:" << std::endl;
    Box largerBox = compareBoxes(box1, box2);  // Using friend function
    
    std::cout << "\nWorking with BoxFactory (friend class):" << std::endl;
    Box cube = BoxFactory::createCube(3.0);
    BoxFactory::displayBoxDetails(cube);
    
    std::cout << "\nResizing box:" << std::endl;
    BoxFactory::resizeBox(cube, 2.0);
    BoxFactory::displayBoxDetails(cube);
    
    return 0;
}
```

## Additional Resources
- [C++ OOP Concepts](https://www.example.com/oop-concepts)
- [C++ Programming Tutorials](https://www.example.com/cpp-tutorials)
- [C++ Reference Documentation](https://en.cppreference.com/w/)
- [Object-Oriented Design Patterns](https://refactoring.guru/design-patterns)