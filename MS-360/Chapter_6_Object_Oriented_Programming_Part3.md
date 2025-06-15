# Chapter 6: Object-Oriented Programming (Part 3)

## 6.7 Encapsulation & Abstraction

Encapsulation and abstraction are two fundamental principles of object-oriented programming that work together to create maintainable, robust software systems.

### Encapsulation

Encapsulation is the bundling of data and methods that operate on that data into a single unit (class) and restricting access to the internal representation of the object.

#### Key Aspects of Encapsulation:

1. **Data Hiding**: Making data members private so they can't be accessed directly from outside the class
2. **Access Control**: Using access specifiers (private, protected, public) to control visibility
3. **Interface Definition**: Providing a clean public interface for interacting with the object
4. **Implementation Protection**: Preventing external code from depending on implementation details

#### Benefits of Encapsulation:

1. **Improved Maintainability**: Implementation details can be changed without affecting client code
2. **Reduced Complexity**: Users only need to understand the public interface, not the internal implementation
3. **Better Control**: Validate inputs and maintain invariants through controlled access
4. **Modularity**: Classes become self-contained units that can be developed and tested independently

#### Example of Encapsulation:

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // Encapsulated data (hidden from outside)
    string accountNumber;
    double balance;
    string ownerName;
    double minimumBalance;
    
    // Private helper method
    bool isValidAmount(double amount) const {
        return amount > 0;
    }
    
public:
    // Constructor
    BankAccount(const string& accNo, const string& name, double initialBalance = 0.0)
        : accountNumber(accNo), ownerName(name), balance(initialBalance), minimumBalance(100.0) {
    }
    
    // Public interface methods
    void deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid amount for deposit." << endl;
        }
    }
    
    bool withdraw(double amount) {
        if (!isValidAmount(amount)) {
            cout << "Invalid amount for withdrawal." << endl;
            return false;
        }
        
        if (balance - amount < minimumBalance) {
            cout << "Withdrawal denied. Minimum balance would not be maintained." << endl;
            return false;
        }
        
        balance -= amount;
        cout << "Withdrawal successful. New balance: $" << balance << endl;
        return true;
    }
    
    // Getters (controlled access to private data)
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
    string getOwnerName() const { return ownerName; }
    
    // Setters with validation
    void setOwnerName(const string& name) {
        if (!name.empty()) {
            ownerName = name;
        }
    }
};

int main() {
    BankAccount account("123456789", "John Doe", 500.0);
    
    // Using the public interface
    account.deposit(200.0);
    account.withdraw(100.0);
    
    // Access data through getters
    cout << "Account: " << account.getAccountNumber() << endl;
    cout << "Owner: " << account.getOwnerName() << endl;
    cout << "Current Balance: $" << account.getBalance() << endl;
    
    // Cannot access private members directly
    // account.balance = 1000000.0;  // Error: 'balance' is private
    // account.minimumBalance = 0.0;  // Error: 'minimumBalance' is private
    
    return 0;
}
```

In this example:
- Data members are private, preventing direct external access
- Public methods provide a controlled interface for interacting with the account
- Business rules (minimum balance, valid amounts) are enforced within the class
- Internal implementation details (like the helper method) are hidden

### Abstraction

Abstraction is the concept of exposing only the essential features of an object while hiding the unnecessary details. It's about creating simple, high-level interfaces that hide complex implementations.

#### Key Aspects of Abstraction:

1. **Simplification**: Represent complex reality in a simplified model
2. **Selective Visibility**: Show only what's necessary for outside users
3. **Implementation Hiding**: Hide the "how" while exposing the "what"
4. **Focusing on Behavior**: Emphasize what an object does rather than how it does it

#### Mechanisms for Abstraction in C++:

1. **Abstract Classes**: Classes with at least one pure virtual function
2. **Interfaces**: Abstract classes with only pure virtual functions
3. **Encapsulation**: Hiding implementation details through access control

#### Example of Abstraction:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Abstract base class (interface)
class Shape {
public:
    // Pure virtual functions define the interface
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual string getName() const = 0;
    
    // Virtual destructor
    virtual ~Shape() {}
};

// Concrete implementation
class Circle : public Shape {
private:
    double radius;
    double centerX, centerY;
    
public:
    Circle(double r, double x = 0, double y = 0)
        : radius(r), centerX(x), centerY(y) {}
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void draw() const override {
        cout << "Drawing a circle at (" << centerX << ", " << centerY 
             << ") with radius " << radius << endl;
    }
    
    string getName() const override {
        return "Circle";
    }
};

// Another concrete implementation
class Rectangle : public Shape {
private:
    double width, height;
    double posX, posY;
    
public:
    Rectangle(double w, double h, double x = 0, double y = 0)
        : width(w), height(h), posX(x), posY(y) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "Drawing a rectangle at (" << posX << ", " << posY 
             << ") with width " << width << " and height " << height << endl;
    }
    
    string getName() const override {
        return "Rectangle";
    }
};

// Client code using abstraction
void printShapeInfo(const Shape& shape) {
    cout << "Shape: " << shape.getName() << endl;
    cout << "Area: " << shape.area() << endl;
    cout << "Perimeter: " << shape.perimeter() << endl;
    shape.draw();
    cout << endl;
}

int main() {
    Circle circle(5, 10, 20);
    Rectangle rectangle(4, 6, 15, 25);
    
    // Using shapes through their abstract interface
    printShapeInfo(circle);
    printShapeInfo(rectangle);
    
    // Collection of different shapes through common interface
    vector<Shape*> shapes;
    shapes.push_back(new Circle(3, 5, 5));
    shapes.push_back(new Rectangle(8, 2, 0, 0));
    shapes.push_back(new Circle(7, -10, 8));
    
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
        delete shape;
    }
    
    return 0;
}
```

In this example:
- `Shape` is an abstract class defining operations all shapes must support
- `Circle` and `Rectangle` provide concrete implementations of those operations
- Client code (`printShapeInfo` and `main`) uses shapes through the abstract interface
- The details of how each shape calculates its area or draws itself are abstracted away

### Difference Between Encapsulation and Abstraction

While closely related, encapsulation and abstraction have distinct focuses:

| Aspect | Encapsulation | Abstraction |
|--------|--------------|-------------|
| **Focus** | Information hiding | Complexity reduction |
| **Purpose** | Bundle data and methods, control access | Simplify complex reality, focus on essentials |
| **Implementation** | Access specifiers (private, protected) | Abstract classes, interfaces |
| **Benefit** | Security, maintainability | Simplicity, modularity |
| **Level** | Primarily implementation level | Design level |

### Best Practices for Encapsulation and Abstraction

1. **Keep data members private**: Only expose them through controlled methods
2. **Validate inputs** in public methods to maintain object integrity
3. **Design stable public interfaces**: Avoid frequent changes to public APIs
4. **Use abstract classes** to define common behavior for related classes
5. **Program to interfaces**, not implementations
6. **Hide complexity** behind simple interfaces
7. **Separate interface from implementation** to allow independent evolution
8. **Don't expose implementation details** in public interfaces

## 6.8 this Pointer

The `this` pointer is a hidden parameter that is automatically passed to non-static member functions. It points to the object that invoked the member function.

### Key Characteristics of `this`:

1. **Implicit Parameter**: Automatically available in member functions
2. **Points to Current Object**: Refers to the instance being operated on
3. **Type**: For a class `X`, `this` has type `X* const` (`const X*` for const member functions)
4. **Not Available**: Cannot be used in static member functions (as they don't operate on specific objects)

### Common Uses of `this` Pointer:

#### 1. Disambiguating Member Variables and Parameters

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    // Parameter names same as member names
    Person(string name, int age) {
        // Use this-> to disambiguate
        this->name = name;
        this->age = age;
    }
    
    void display() const {
        cout << "Name: " << this->name << ", Age: " << this->age << endl;
    }
};

int main() {
    Person person("Alice", 25);
    person.display();
    
    return 0;
}
```

#### 2. Method Chaining (Fluent Interface)

```cpp
#include <iostream>
#include <string>
using namespace std;

class StringBuilder {
private:
    string data;
    
public:
    StringBuilder() : data("") {}
    
    // Return *this for method chaining
    StringBuilder& append(const string& str) {
        data += str;
        return *this;
    }
    
    StringBuilder& appendLine(const string& str) {
        data += str + "\n";
        return *this;
    }
    
    StringBuilder& clear() {
        data.clear();
        return *this;
    }
    
    string toString() const {
        return data;
    }
};

int main() {
    StringBuilder builder;
    
    // Method chaining using 'this' pointer
    string result = builder.append("Hello, ")
                           .append("World!")
                           .appendLine("")
                           .append("How are ")
                           .append("you?")
                           .toString();
    
    cout << result << endl;
    
    return 0;
}
```

#### 3. Passing the Current Object to Other Functions

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Event;  // Forward declaration

class EventListener {
public:
    virtual void onEvent(const Event& event) = 0;
    virtual ~EventListener() {}
};

class Event {
private:
    string name;
    string data;
    vector<EventListener*> listeners;
    
public:
    Event(const string& name, const string& data) 
        : name(name), data(data) {}
    
    void addListener(EventListener* listener) {
        listeners.push_back(listener);
    }
    
    void trigger() {
        cout << "Triggering event: " << name << endl;
        for (auto listener : listeners) {
            listener->onEvent(*this);  // Passing the current object
        }
    }
    
    string getName() const { return name; }
    string getData() const { return data; }
};

class Logger : public EventListener {
public:
    void onEvent(const Event& event) override {
        cout << "Logging: Event " << event.getName() 
             << " triggered with data: " << event.getData() << endl;
    }
};

class Notifier : public EventListener {
public:
    void onEvent(const Event& event) override {
        cout << "Notification: " << event.getName() << " occurred!" << endl;
    }
};

int main() {
    Logger logger;
    Notifier notifier;
    
    Event userLogin("UserLogin", "user_id=12345");
    
    userLogin.addListener(&logger);
    userLogin.addListener(&notifier);
    
    userLogin.trigger();
    
    return 0;
}
```

#### 4. Comparing Objects (Self-Reference Check)

```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int value;
    
public:
    MyClass(int val) : value(val) {}
    
    int getValue() const { return value; }
    
    bool isEqualTo(const MyClass& other) const {
        if (this == &other) {  // Compare addresses using 'this'
            cout << "Self-comparison detected" << endl;
            return true;  // An object is always equal to itself
        }
        return this->value == other.value;
    }
    
    MyClass& operator=(const MyClass& other) {
        // Check for self-assignment
        if (this != &other) {
            // Perform the assignment only if not self-assignment
            this->value = other.value;
        }
        return *this;
    }
};

int main() {
    MyClass obj1(42);
    MyClass obj2(42);
    MyClass obj3(100);
    
    cout << "obj1 equal to itself: " << obj1.isEqualTo(obj1) << endl;
    cout << "obj1 equal to obj2: " << obj1.isEqualTo(obj2) << endl;
    cout << "obj1 equal to obj3: " << obj1.isEqualTo(obj3) << endl;
    
    obj1 = obj3;  // Assignment operator uses 'this' to prevent self-assignment issues
    cout << "After assignment, obj1 value: " << obj1.getValue() << endl;
    
    return 0;
}
```

#### 5. Implementing Wrapper Classes (Delegation)

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// The actual implementation class
class DatabaseConnection {
public:
    void connect(const string& connectionString) {
        cout << "Connecting to: " << connectionString << endl;
    }
    
    void executeQuery(const string& query) {
        cout << "Executing: " << query << endl;
    }
    
    void disconnect() {
        cout << "Disconnecting from database" << endl;
    }
};

// Wrapper class that delegates to the implementation
class Database {
private:
    unique_ptr<DatabaseConnection> connection;
    
public:
    Database() : connection(make_unique<DatabaseConnection>()) {}
    
    Database* connect(const string& connectionString) {
        connection->connect(connectionString);
        return this;  // Return this for method chaining
    }
    
    Database* query(const string& sql) {
        connection->executeQuery(sql);
        return this;
    }
    
    void close() {
        connection->disconnect();
    }
};

int main() {
    // Using the wrapper with method chaining
    Database* db = new Database();
    db->connect("server=localhost;database=testdb;")
      ->query("SELECT * FROM users")
      ->query("UPDATE users SET active = 1");
    
    db->close();
    delete db;
    
    return 0;
}
```

### Understanding `this` Under the Hood

When you call a member function on an object, the compiler effectively transforms it:

```cpp
// Your code:
obj.function(arg1, arg2);

// What effectively happens:
Class::function(&obj, arg1, arg2);
```

The compiler passes the address of the object (`&obj`) as a hidden first parameter, which becomes the `this` pointer inside the function.

### Best Practices for Using `this`:

1. **Use it for disambiguation** when parameter names conflict with member names
2. **Return `*this` for method chaining** where it makes the interface more fluent
3. **Check for self-reference** in assignment operators and comparison methods
4. **Make it explicit** when it improves readability
5. **Don't use `this` unnecessarily** when there's no ambiguity
6. **Remember it's implicit** in all non-static member function calls

## 6.9 Friend Functions and Classes

C++'s access control normally prevents external functions and classes from accessing private or protected members. Friend declarations allow you to grant specific external functions or classes access to these private details.

### Friend Functions

A friend function is a non-member function that has access to private and protected members of a class.

```cpp
#include <iostream>
using namespace std;

class Box {
private:
    double length;
    double width;
    double height;
    
public:
    Box(double l, double w, double h) : length(l), width(w), height(h) {}
    
    // Regular member function
    double volume() const {
        return length * width * height;
    }
    
    // Friend function declaration
    friend void displayBoxDimensions(const Box& box);
    
    // Friend function to add two boxes
    friend Box addBoxes(const Box& b1, const Box& b2);
};

// Friend function definition - can access private members
void displayBoxDimensions(const Box& box) {
    cout << "Box dimensions: " << box.length << " x "
         << box.width << " x " << box.height << endl;
}

// Another friend function
Box addBoxes(const Box& b1, const Box& b2) {
    // Can access private members of both boxes
    Box result(
        b1.length + b2.length,
        b1.width + b2.width,
        b1.height + b2.height
    );
    return result;
}

int main() {
    Box smallBox(1, 2, 3);
    Box bigBox(4, 5, 6);
    
    // Call member function
    cout << "Small box volume: " << smallBox.volume() << endl;
    
    // Call friend functions
    displayBoxDimensions(smallBox);
    
    Box combinedBox = addBoxes(smallBox, bigBox);
    displayBoxDimensions(combinedBox);
    
    return 0;
}
```

### Friend Classes

A friend class can access private and protected members of the class that declares it as a friend.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student; // Forward declaration

class Course {
private:
    string name;
    int maxCapacity;
    int enrolledCount;
    
public:
    Course(const string& name, int capacity)
        : name(name), maxCapacity(capacity), enrolledCount(0) {}
        
    // This method needs access to Student's private members
    void enrollStudent(Student& student);
    
    string getName() const { return name; }
    int getCapacity() const { return maxCapacity; }
    int getEnrolledCount() const { return enrolledCount; }
};

class Student {
private:
    string name;
    int id;
    int courseCount;
    static const int MAX_COURSES = 5;
    
    // Friend class declaration
    friend class Course;
    
public:
    Student(const string& name, int id)
        : name(name), id(id), courseCount(0) {}
    
    string getName() const { return name; }
    int getId() const { return id; }
    int getCourseCount() const { return courseCount; }
};

// Now we can define this method, which accesses Student's private members
void Course::enrollStudent(Student& student) {
    if (enrolledCount < maxCapacity && student.courseCount < student.MAX_COURSES) {
        enrolledCount++;
        student.courseCount++;  // Can access private member because Course is a friend
        cout << "Enrolled " << student.name << " in " << name << endl;
    } else if (enrolledCount >= maxCapacity) {
        cout << "Course " << name << " is full!" << endl;
    } else {
        cout << "Student " << student.name << " has too many courses!" << endl;
    }
}

int main() {
    Student alice("Alice", 12345);
    Student bob("Bob", 67890);
    
    Course cpp("C++ Programming", 3);
    Course java("Java Programming", 2);
    Course python("Python Programming", 2);
    
    cpp.enrollStudent(alice);
    cpp.enrollStudent(bob);
    java.enrollStudent(alice);
    
    cout << alice.getName() << " is enrolled in " << alice.getCourseCount() << " courses." << endl;
    cout << bob.getName() << " is enrolled in " << bob.getCourseCount() << " courses." << endl;
    cout << cpp.getName() << " has " << cpp.getEnrolledCount() << "/" << cpp.getCapacity() << " students." << endl;
    
    return 0;
}
```

### Friend Member Functions

You can also declare specific member functions of another class as friends:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Engine; // Forward declaration

class Car {
private:
    string model;
    int year;
    Engine* engine;
    
public:
    Car(const string& model, int year);
    void displayDetails() const;
    
    // Friend declaration for specific Engine member function
    friend void Engine::modifyCar(Car& car);
};

class Engine {
private:
    int horsepower;
    string type;
    
public:
    Engine(int hp, const string& t) : horsepower(hp), type(t) {}
    
    void displaySpecs() const {
        cout << "Engine Type: " << type << ", Horsepower: " << horsepower << endl;
    }
    
    // This function can access Car's private members
    void modifyCar(Car& car);
};

// Now we can define Car constructor, since Engine is fully defined
Car::Car(const string& m, int y) : model(m), year(y) {
    engine = new Engine(150, "V6");
}

void Car::displayDetails() const {
    cout << "Car: " << model << " (" << year << ")" << endl;
    engine->displaySpecs();
}

// Define the friend member function
void Engine::modifyCar(Car& car) {
    cout << "Modifying " << car.model << "'s engine..." << endl;
    delete car.engine;  // Can access private members
    car.engine = new Engine(horsepower + 50, "Turbocharged " + type);
    cout << "Upgrade complete!" << endl;
}

int main() {
    Car myCar("Toyota Camry", 2022);
    myCar.displayDetails();
    
    // Create an engine object to call the friend member function
    Engine enhancedEngine(200, "V8");
    enhancedEngine.modifyCar(myCar);
    
    myCar.displayDetails();
    
    return 0;
}
```

### Friendship Properties

1. **Friendship is not symmetric**: If class A is a friend of B, B is not automatically a friend of A
2. **Friendship is not transitive**: If A is a friend of B and B is a friend of C, A is not automatically a friend of C
3. **Friendship is not inherited**: If a base class declares a friend, derived classes don't automatically have that friend

### When to Use Friends

Friends should be used sparingly as they can reduce encapsulation. Good cases for friends include:

1. **Operator overloading** where operators need access to private data
2. **Helper functions** that need intimate access to class internals
3. **Tightly coupled classes** that form a subsystem and need to access each other's internals
4. **Unit testing** where test classes may need to access private members

### Best Practices for Friends

1. **Use friends sparingly**: Every friend declaration weakens encapsulation
2. **Prefer member functions** when possible
3. **Consider accessors/mutators** before making a friend
4. **Document friend relationships** to make dependencies clear
5. **Group related classes** that share friendship
6. **Don't make every function or class a friend** - be selective
7. **Watch for compilation dependencies** - forward declarations may be needed

## 6.10 Static Members

Static members belong to the class itself rather than to any specific instance of the class. They exist even if no objects of the class have been created and are shared among all instances.

### Static Data Members

Static data members have these key properties:
- Shared among all class instances
- Exist even when no objects exist
- Only one copy exists regardless of how many class objects are created
- Must be defined outside the class (except for inline initialization of const static members in C++17)

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    
    // Static data member declaration
    static double interestRate;
    
    // Const static data member (can be initialized inline in modern C++)
    static const int minPasswordLength = 8;
    
    // Static counter to generate account numbers
    static int nextAccountId;
    
public:
    BankAccount(double initialBalance = 0.0) 
        : balance(initialBalance) {
        // Generate unique account number
        accountNumber = "ACC" + to_string(nextAccountId++);
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " to account " << accountNumber << endl;
        }
    }
    
    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Applied interest: $" << interest << " to account " << accountNumber << endl;
    }
    
    // Static method to set interest rate
    static void setInterestRate(double rate) {
        if (rate >= 0 && rate <= 0.5) {  // Reasonable limits
            interestRate = rate;
            cout << "Interest rate updated to " << rate * 100 << "%" << endl;
        } else {
            cout << "Invalid interest rate" << endl;
        }
    }
    
    // Static method to get interest rate
    static double getInterestRate() {
        return interestRate;
    }
    
    // Regular (non-static) methods
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
    
    static int getMinPasswordLength() {
        return minPasswordLength;
    }
};

// Definition of static data members (required)
double BankAccount::interestRate = 0.03;  // 3% initial interest rate
int BankAccount::nextAccountId = 1000;

int main() {
    // Accessing static members without any objects
    cout << "Initial interest rate: " << BankAccount::getInterestRate() << endl;
    cout << "Minimum password length: " << BankAccount::getMinPasswordLength() << endl;
    
    // Create some accounts
    BankAccount acc1(1000);
    BankAccount acc2(2000);
    
    // Display account info
    cout << "\nAccount Information:" << endl;
    cout << acc1.getAccountNumber() << ": $" << acc1.getBalance() << endl;
    cout << acc2.getAccountNumber() << ": $" << acc2.getBalance() << endl;
    
    // Apply interest to accounts
    acc1.applyInterest();
    acc2.applyInterest();
    
    // Update interest rate (affects all accounts)
    BankAccount::setInterestRate(0.04);  // 4%
    
    // Apply interest again with new rate
    acc1.applyInterest();
    acc2.applyInterest();
    
    // Display final balances
    cout << "\nFinal Account Balances:" << endl;
    cout << acc1.getAccountNumber() << ": $" << acc1.getBalance() << endl;
    cout << acc2.getAccountNumber() << ": $" << acc2.getBalance() << endl;
    
    return 0;
}
```

### Static Member Functions

Static member functions have these key characteristics:
- Belong to the class, not to objects
- Can be called using the class name (without creating objects)
- Can only access static members directly
- Don't have a `this` pointer
- Cannot be declared as `const`, `virtual` or `volatile`

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Logger {
private:
    // Static data members
    static int messageCount;
    static bool debugMode;
    static string logFilePath;
    static vector<string> messageHistory;
    
    // Non-static data member
    string componentName;
    
public:
    // Enum for log levels
    enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };
    
    // Constructor
    Logger(const string& component) : componentName(component) {}
    
    // Static method to configure the logger
    static void configure(bool debug, const string& filePath) {
        debugMode = debug;
        logFilePath = filePath;
        
        log("Logger", INFO, "Logger configured. Debug mode: " + 
            string(debugMode ? "ON" : "OFF") + ", Log file: " + logFilePath);
    }
    
    // Static method to get current timestamp
    static string getTimestamp() {
        time_t now = time(nullptr);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return buffer;
    }
    
    // Static logging method that can be called without an instance
    static void log(const string& component, LogLevel level, const string& message) {
        string levelStr;
        switch (level) {
            case DEBUG: levelStr = "DEBUG"; break;
            case INFO: levelStr = "INFO"; break;
            case WARNING: levelStr = "WARNING"; break;
            case ERROR: levelStr = "ERROR"; break;
            case CRITICAL: levelStr = "CRITICAL"; break;
        }
        
        // Skip debug messages if debug mode is off
        if (level == DEBUG && !debugMode) return;
        
        // Format the log message
        string timestamp = getTimestamp();
        string formattedMessage = timestamp + " [" + levelStr + "] " + 
                                 component + ": " + message;
        
        // Print to console
        cout << formattedMessage << endl;
        
        // Add to history
        messageHistory.push_back(formattedMessage);
        messageCount++;
        
        // In a real logger, we would write to a file here
        // ofstream logFile(logFilePath, ios::app);
        // logFile << formattedMessage << endl;
    }
    
    // Non-static method that uses the component name from the instance
    void logMessage(LogLevel level, const string& message) {
        log(componentName, level, message);
    }
    
    // Static methods to get statistics
    static int getMessageCount() { return messageCount; }
    static vector<string> getRecentMessages(int count) {
        vector<string> recent;
        int start = max(0, static_cast<int>(messageHistory.size()) - count);
        for (size_t i = start; i < messageHistory.size(); i++) {
            recent.push_back(messageHistory[i]);
        }
        return recent;
    }
};

// Define static members
int Logger::messageCount = 0;
bool Logger::debugMode = false;
string Logger::logFilePath = "app.log";
vector<string> Logger::messageHistory;

int main() {
    // Configure the logger
    Logger::configure(true, "application.log");
    
    // Use static logging methods directly
    Logger::log("Main", Logger::INFO, "Application started");
    Logger::log("Main", Logger::DEBUG, "Debug message from main");
    
    // Create logger instances for different components
    Logger networkLogger("Network");
    Logger dbLogger("Database");
    
    // Use instance methods
    networkLogger.logMessage(Logger::WARNING, "Network latency high");
    dbLogger.logMessage(Logger::ERROR, "Failed to connect to database");
    
    // Get statistics using static methods
    cout << "\nTotal log messages: " << Logger::getMessageCount() << endl;
    
    cout << "\nRecent messages:" << endl;
    vector<string> recentLogs = Logger::getRecentMessages(3);
    for (const auto& log : recentLogs) {
        cout << log << endl;
    }
    
    return 0;
}
```

### Static Initialization

Static member initialization can be tricky, especially with complex data types or interdependencies:

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Configuration {
private:
    // Static const members can be initialized inline
    static const int MAX_CONNECTIONS = 100;
    static const bool DEFAULT_LOGGING = true;
    
    // Non-const static members must be initialized outside the class
    static string appName;
    static map<string, string> settings;
    
public:
    static void initialize(const string& name) {
        appName = name;
        settings["logging"] = DEFAULT_LOGGING ? "enabled" : "disabled";
        settings["max_connections"] = to_string(MAX_CONNECTIONS);
        settings["theme"] = "default";
    }
    
    static void setSetting(const string& key, const string& value) {
        settings[key] = value;
    }
    
    static string getSetting(const string& key) {
        auto it = settings.find(key);
        return it != settings.end() ? it->second : "";
    }
    
    static void displayConfig() {
        cout << "Application: " << appName << endl;
        cout << "Settings:" << endl;
        for (const auto& [key, value] : settings) {
            cout << "  " << key << ": " << value << endl;
        }
    }
};

// Static member initialization
string Configuration::appName = "Unnamed App";
map<string, string> Configuration::settings;

class ApplicationModule {
private:
    string moduleName;
    
public:
    ApplicationModule(const string& name) : moduleName(name) {
        cout << "Module initialized: " << moduleName << endl;
        
        // Access application configuration (static members of another class)
        string logSetting = Configuration::getSetting("logging");
        cout << "Logging is " << logSetting << " for module " << moduleName << endl;
    }
    
    void run() {
        cout << "Running module: " << moduleName << endl;
    }
};

int main() {
    // Initialize configuration before using modules
    Configuration::initialize("My Application");
    Configuration::setSetting("database", "mysql://localhost:3306/mydb");
    
    // Display configuration
    Configuration::displayConfig();
    
    // Create application modules
    ApplicationModule module1("Core");
    ApplicationModule module2("UI");
    
    // Run modules
    module1.run();
    module2.run();
    
    return 0;
}
```

### Singleton Pattern Using Static Members

The Singleton pattern ensures that a class has only one instance and provides a global access point to that instance:

```cpp
#include <iostream>
#include <string>
using namespace std;

class DatabaseConnection {
private:
    // Private static instance of the class
    static DatabaseConnection* instance;
    
    // Connection details
    string host;
    string username;
    string password;
    bool connected;
    
    // Private constructor to prevent direct instantiation
    DatabaseConnection() : host("localhost"), username(""), password(""), connected(false) {
        cout << "Database connection object created" << endl;
    }
    
    // Prevent copying and assignment
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
public:
    // Static method to get the singleton instance
    static DatabaseConnection* getInstance() {
        if (instance == nullptr) {
            instance = new DatabaseConnection();
        }
        return instance;
    }
    
    // Static method to release the instance
    static void releaseInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
            cout << "Database connection instance released" << endl;
        }
    }
    
    // Connection methods
    bool connect(const string& h, const string& user, const string& pass) {
        host = h;
        username = user;
        password = pass;
        
        // Simulate connection
        cout << "Connecting to " << host << " as " << username << "..." << endl;
        connected = true;
        return connected;
    }
    
    void disconnect() {
        if (connected) {
            cout << "Disconnecting from " << host << endl;
            connected = false;
        }
    }
    
    bool isConnected() const {
        return connected;
    }
    
    // Query execution method
    void executeQuery(const string& query) {
        if (connected) {
            cout << "Executing on " << host << ": " << query << endl;
        } else {
            cout << "Cannot execute query: Not connected" << endl;
        }
    }
};

// Initialize static member
DatabaseConnection* DatabaseConnection::instance = nullptr;

// Function that uses the database connection
void performDatabaseOperations() {
    // Get the singleton instance
    DatabaseConnection* db = DatabaseConnection::getInstance();
    
    // Use the connection
    if (!db->isConnected()) {
        db->connect("database.server.com", "admin", "secure_password");
    }
    
    db->executeQuery("SELECT * FROM users");
    db->executeQuery("UPDATE products SET stock = stock - 1 WHERE id = 42");
}

int main() {
    cout << "Program started" << endl;
    
    // First use of database - instance will be created
    performDatabaseOperations();
    
    // Second use of database - same instance will be used
    DatabaseConnection* db = DatabaseConnection::getInstance();
    db->executeQuery("SELECT * FROM orders WHERE status = 'pending'");
    
    // Clean up
    DatabaseConnection::releaseInstance();
    
    cout << "Program ended" << endl;
    return 0;
}
```

### Thread Safety Considerations with Static Members

Static members can cause issues in multi-threaded applications. Here's a thread-safe singleton:

```cpp
#include <iostream>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

class ThreadSafeSingleton {
private:
    static ThreadSafeSingleton* instance;
    static mutex instanceMutex;
    string data;
    
    // Private constructor
    ThreadSafeSingleton() : data("Initial value") {
        cout << "Singleton constructed" << endl;
    }
    
    // Prevent copying
    ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
    ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;
    
public:
    // Thread-safe access to singleton instance
    static ThreadSafeSingleton* getInstance() {
        // Double-checked locking pattern
        if (instance == nullptr) {
            lock_guard<mutex> lock(instanceMutex);
            if (instance == nullptr) {
                instance = new ThreadSafeSingleton();
            }
        }
        return instance;
    }
    
    // Thread-safe data manipulation
    void setData(const string& newData) {
        lock_guard<mutex> lock(instanceMutex);
        data = newData;
        cout << "Data set to: " << data << endl;
    }
    
    string getData() {
        lock_guard<mutex> lock(instanceMutex);
        return data;
    }
    
    static void destroyInstance() {
        lock_guard<mutex> lock(instanceMutex);
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
            cout << "Singleton destroyed" << endl;
        }
    }
};

// Initialize static members
ThreadSafeSingleton* ThreadSafeSingleton::instance = nullptr;
mutex ThreadSafeSingleton::instanceMutex;

// Worker function for threads
void workerFunction(int id, const string& message) {
    cout << "Thread " << id << " running..." << endl;
    
    // Get singleton instance
    ThreadSafeSingleton* singleton = ThreadSafeSingleton::getInstance();
    
    // Read current data
    string currentData = singleton->getData();
    cout << "Thread " << id << " read: " << currentData << endl;
    
    // Simulate some work
    this_thread::sleep_for(chrono::milliseconds(100 * id));
    
    // Update data
    singleton->setData(message + " from thread " + to_string(id));
    
    cout << "Thread " << id << " finished" << endl;
}

int main() {
    cout << "Main thread started" << endl;
    
    // Create multiple threads that use the singleton
    thread t1(workerFunction, 1, "Hello");
    thread t2(workerFunction, 2, "Bonjour");
    thread t3(workerFunction, 3, "Hola");
    
    // Join threads
    t1.join();
    t2.join();
    t3.join();
    
    // Final value
    cout << "Final data: " << ThreadSafeSingleton::getInstance()->getData() << endl;
    
    // Clean up
    ThreadSafeSingleton::destroyInstance();
    
    cout << "Main thread ended" << endl;
    return 0;
}
```

### Best Practices for Static Members

1. **Use static data members for:**
   - Class-wide constants
   - Shared resources among all instances
   - Counters or statistics
   - Configuration settings

2. **Use static member functions for:**
   - Operations that don't require object state
   - Factory methods
   - Global access points (carefully)
   - Utility operations related to the class

3. **Follow these guidelines:**
   - Initialize static data members outside the class definition
   - Keep thread safety in mind for static members
   - Don't overuse static members as global variables
   - Document the purpose of static members
   - Consider alternatives to static members for complex scenarios

## 6.11 Object Slicing

Object slicing occurs when an object of a derived class is assigned to a base class object (not a pointer or reference). When this happens, the derived part of the object is "sliced off," leaving only the base class portion.

### Basic Example of Object Slicing

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
protected:
    string name;
    
public:
    Base(const string& n) : name(n) {}
    
    virtual void display() const {
        cout << "Base class: " << name << endl;
    }
    
    string getName() const { return name; }
};

class Derived : public Base {
private:
    int extraData;
    
public:
    Derived(const string& n, int extra) : Base(n), extraData(extra) {}
    
    void display() const override {
        cout << "Derived class: " << name << ", Extra data: " << extraData << endl;
    }
    
    int getExtraData() const { return extraData; }
};

int main() {
    Derived derived("Object1", 100);
    
    // No slicing - pointer points to Derived object
    Base* basePtr = &derived;
    basePtr->display();  // Calls Derived::display()
    
    // No slicing - reference to Derived object
    Base& baseRef = derived;
    baseRef.display();  // Calls Derived::display()
    
    // Object slicing happens here!
    Base baseObj = derived;  // Only Base part is copied
    baseObj.display();  // Calls Base::display()
    
    // We can't access derived class members through the sliced object
    // cout << baseObj.getExtraData();  // Error: Base has no getExtraData()
    
    return 0;
}
```

### Where Object Slicing Occurs

1. **During Assignment**:
```cpp
Derived derived("Derived object", 42);
Base base = derived;  // Slicing occurs
```

2. **Passing by Value to Functions**:
```cpp
void processBase(Base baseObj) {  // Slicing occurs if a Derived is passed
    baseObj.display();  // Always calls Base::display()
}

// Usage
Derived derived("Test", 100);
processBase(derived);  // Derived object is sliced to Base
```

3. **Returning by Value from Functions**:
```cpp
Base getObject() {
    Derived derived("From function", 200);
    return derived;  // Slicing occurs
}
```

4. **Storing in Containers of Base Objects**:
```cpp
vector<Base> objects;
objects.push_back(derived);  // Slicing occurs
```

### Issues Caused by Object Slicing

1. **Loss of Derived Class Data**:
   - Derived class members are lost during slicing
   - Only base class members remain

2. **Loss of Polymorphic Behavior**:
   - Virtual function calls no longer dispatch to derived implementations
   - Always call the base class versions

3. **Unexpected Behavior**:
   - Code that expects full objects may not work correctly
   - Can lead to subtle bugs that are hard to track

### Detailed Example Showing the Problems

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
    
    virtual double area() const {
        return 0.0;
    }
    
    virtual double perimeter() const {
        return 0.0;
    }
    
    virtual void display() const {
        cout << "Shape: " << name << endl;
    }
    
    string getName() const { return name; }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const string& n, double r) : Shape(n), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void display() const override {
        cout << "Circle: " << name << ", Radius: " << radius << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(const string& n, double w, double h) 
        : Shape(n), width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "Rectangle: " << name << ", Width: " << width 
             << ", Height: " << height << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

// Functions demonstrating different ways of passing objects
void displayByValue(Shape shape) {
    cout << "Display by value (slicing occurs): " << endl;
    shape.display();  // Always calls Shape::display()
    cout << endl;
}

void displayByPointer(Shape* shape) {
    cout << "Display by pointer (no slicing): " << endl;
    shape->display();  // Calls appropriate derived class display()
    cout << endl;
}

void displayByReference(const Shape& shape) {
    cout << "Display by reference (no slicing): " << endl;
    shape.display();  // Calls appropriate derived class display()
    cout << endl;
}

int main() {
    Circle circle("Circle1", 5.0);
    Rectangle rectangle("Rectangle1", 4.0, 6.0);
    
    cout << "Original objects:" << endl;
    circle.display();
    cout << endl;
    rectangle.display();
    cout << endl;
    
    // Demonstrate slicing with assignment
    cout << "Slicing with assignment:" << endl;
    Shape shape1 = circle;
    Shape shape2 = rectangle;
    shape1.display();  // Only Shape::display() is called
    shape2.display();  // Only Shape::display() is called
    cout << endl;
    
    // Demonstrate function calls with different parameter types
    displayByValue(circle);      // Slicing occurs
    displayByPointer(&circle);   // No slicing
    displayByReference(circle);  // No slicing
    
    // Demonstrate slicing in container
    cout << "Slicing in container:" << endl;
    vector<Shape> shapes;
    shapes.push_back(circle);     // Slicing occurs
    shapes.push_back(rectangle);  // Slicing occurs
    
    for (const auto& shape : shapes) {
        shape.display();  // Always calls Shape::display()
    }
    cout << endl;
    
    // Contrast with container of pointers (no slicing)
    cout << "Container of pointers (no slicing):" << endl;
    vector<Shape*> shapePointers;
    shapePointers.push_back(&circle);
    shapePointers.push_back(&rectangle);
    
    for (const auto& shapePtr : shapePointers) {
        shapePtr->display();  // Calls appropriate derived class display()
    }
    
    return 0;
}
```

### Avoiding Object Slicing

1. **Use Pointers or References**:
```cpp
void processShape(Shape& shape) {  // Use reference
    shape.display();  // Will call appropriate derived version
}

void processShapePtr(Shape* shape) {  // Use pointer
    if (shape) {
        shape->display();  // Will call appropriate derived version
    }
}
```

2. **Use Smart Pointers for Collections**:
```cpp
#include <memory>
#include <vector>

vector<unique_ptr<Shape>> shapes;
shapes.push_back(make_unique<Circle>("Circle1", 5.0));
shapes.push_back(make_unique<Rectangle>("Rectangle1", 4.0, 6.0));

for (const auto& shape : shapes) {
    shape->display();  // No slicing, correct polymorphic behavior
}
```

3. **Make Base Class Abstract**:
```cpp
class Shape {
public:
    virtual ~Shape() {}
    virtual double area() const = 0;  // Pure virtual function
    // ...
};
```

4. **Disable Slicing with Delete**:
```cpp
class Shape {
public:
    Shape(const Shape&) = delete;  // Delete copy constructor
    Shape& operator=(const Shape&) = delete;  // Delete copy assignment
    // ...
};
```

5. **Clone Pattern for Object Copying**:
```cpp
class Shape {
public:
    // ...
    virtual Shape* clone() const = 0;  // Virtual constructor pattern
};

class Circle : public Shape {
public:
    // ...
    Shape* clone() const override {
        return new Circle(*this);  // Create a full copy
    }
};
```

### Using the Clone Pattern in Detail

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Shape {
protected:
    string name;
    
public:
    Shape(const string& n) : name(n) {}
    virtual ~Shape() {}
    
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;
    
    string getName() const { return name; }
    
    // Virtual clone method
    virtual unique_ptr<Shape> clone() const = 0;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const string& n, double r) : Shape(n), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void display() const override {
        cout << "Circle: " << name << ", Radius: " << radius << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    double getRadius() const { return radius; }
    
    // Implement clone for Circle
    unique_ptr<Shape> clone() const override {
        return make_unique<Circle>(*this);
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(const string& n, double w, double h) 
        : Shape(n), width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "Rectangle: " << name << ", Width: " << width 
             << ", Height: " << height << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // Implement clone for Rectangle
    unique_ptr<Shape> clone() const override {
        return make_unique<Rectangle>(*this);
    }
};

class ShapeCollection {
private:
    vector<unique_ptr<Shape>> shapes;
    
public:
    void addShape(const Shape& shape) {
        // Use clone to add a full copy of the shape
        shapes.push_back(shape.clone());
    }
    
    void displayAll() const {
        for (const auto& shape : shapes) {
            shape->display();
            cout << endl;
        }
    }
    
    double getTotalArea() const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            total += shape->area();
        }
        return total;
    }
};

int main() {
    Circle circle("Circle1", 5.0);
    Rectangle rectangle("Rectangle1", 4.0, 6.0);
    
    // Create a collection and add shapes
    ShapeCollection collection;
    collection.addShape(circle);     // Adds a clone (no slicing)
    collection.addShape(rectangle);  // Adds a clone (no slicing)
    
    // Display all shapes (polymorphic behavior preserved)
    cout << "Shapes in collection:" << endl;
    collection.displayAll();
    
    cout << "Total area of all shapes: " << collection.getTotalArea() << endl;
    
    return 0;
}
```

### Best Practices to Avoid Object Slicing

1. **Never pass polymorphic objects by value**; use references or pointers instead
2. **Store collections of polymorphic objects as pointers or smart pointers**
3. **Use the clone pattern** for deep copying of polymorphic objects
4. **Consider making base classes abstract** to prevent instantiation and slicing
5. **Use final for classes not meant to be derived from** to prevent unexpected polymorphic behavior
6. **Make copy constructors private or deleted** in base classes if slicing would be problematic
7. **Understand when polymorphism is actually needed** and when simple value semantics suffice
8. **Document slicing risks** in classes where it might occur

### Recap of Key Object-Oriented Concepts (Topics 6.7-6.11)

1. **Encapsulation**
   - Bundle data with methods that operate on that data
   - Control access through public interfaces
   - Hide implementation details

2. **Abstraction**
   - Hide complexity by showing only essential features
   - Abstract classes define interfaces without implementation details
   - Focus on what an object does, not how it does it

3. **this Pointer**
   - Self-reference to the current object
   - Used to disambiguate variables, enable method chaining, etc.
   - Not available in static member functions

4. **Friend Functions/Classes**
   - Allow specific external functions or classes to access private members
   - Break encapsulation in controlled ways
   - Should be used sparingly

5. **Static Members**
   - Belong to the class itself rather than instances
   - Shared by all objects of the class
   - Can be accessed without creating objects

6. **Object Slicing**
   - Loss of derived class information when assigning to base class objects
   - Prevents polymorphic behavior
   - Avoided using references, pointers, or the clone pattern

These concepts work together to create well-organized, maintainable object-oriented systems. Understanding them thoroughly allows you to design classes that are robust, reusable, and correctly implement the appropriate relationships between objects.
