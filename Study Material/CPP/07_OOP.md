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

### 7. Encapsulation
- The bundling of data and methods that operate on that data within one unit (class), restricting access to some of the object's components.

### 8. Inheritance
- A mechanism where a new class inherits properties and behavior (methods) from an existing class. It promotes code reusability.

### 9. Polymorphism
- The ability to present the same interface for different underlying data types. It can be achieved through:
  - **Compile-time polymorphism** (function overloading and operator overloading)
  - **Run-time polymorphism** (method overriding)

### 10. Abstract Classes and Pure Virtual Functions
- **Abstract Class**: A class that cannot be instantiated and is designed to be a base class. It contains at least one pure virtual function.
- **Pure Virtual Function**: A function declared in a base class that has no definition relative to that class.

### 11. Interfaces
- A contract that a class can implement. It defines methods that must be created within any class that implements the interface.

## Problem Exercises
1. **Create a Class**: Design a class `Car` with attributes like `make`, `model`, and `year`. Implement methods to display the car's details.
   - [Problem Link](https://www.example.com/problem1)

2. **Inheritance Example**: Create a base class `Animal` with a method `sound()`. Derive classes `Dog` and `Cat` that override the `sound()` method.
   - [Problem Link](https://www.example.com/problem2)

3. **Polymorphism**: Implement a function that takes a base class pointer and calls the overridden method in derived classes.
   - [Problem Link](https://www.example.com/problem3)

4. **Abstract Class**: Create an abstract class `Shape` with a pure virtual function `area()`. Derive classes `Circle` and `Rectangle` that implement the `area()` method.
   - [Problem Link](https://www.example.com/problem4)

5. **Friend Function**: Implement a friend function that can access private members of a class `Box`.
   - [Problem Link](https://www.example.com/problem5)

## Additional Resources
- [C++ OOP Concepts](https://www.example.com/oop-concepts)
- [C++ Programming Tutorials](https://www.example.com/cpp-tutorials)