# Chapter 10: Templates in C++ (Part 3)

## 10.6 Template Applications and Advanced Topics

Templates in C++ provide powerful mechanisms for generic programming and code generation. This section explores practical applications and advanced techniques for using templates in real-world scenarios.

### 10.6.1 Smart Pointers Implementation

Smart pointers are one of the most important applications of templates in C++. They provide automatic memory management while maintaining the efficiency of raw pointers. Let's explore how they're implemented:

```cpp
#include <iostream>
#include <memory>
#include <utility>

// Simple implementation of a unique_ptr-like smart pointer
template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {
        std::cout << "UniquePtr constructor called" << std::endl;
    }

    // Destructor
    ~UniquePtr() {
        std::cout << "UniquePtr destructor called" << std::endl;
        if (ptr) {
            delete ptr;
        }
    }

    // Delete copy constructor and assignment operator
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        std::cout << "UniquePtr move constructor called" << std::endl;
        other.ptr = nullptr;
    }

    // Move assignment operator
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        std::cout << "UniquePtr move assignment called" << std::endl;
        if (this != &other) {
            if (ptr) {
                delete ptr;
            }
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Accessor methods
    T* get() const { return ptr; }
    
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
    
    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // Reset with a new pointer
    void reset(T* p = nullptr) {
        if (ptr) {
            delete ptr;
        }
        ptr = p;
    }
};

// Example usage
int main() {
    // Create a smart pointer to an integer
    UniquePtr<int> p1(new int(42));
    std::cout << "p1 value: " << *p1 << std::endl;
    
    // Move ownership
    UniquePtr<int> p2 = std::move(p1);
    std::cout << "p2 value: " << *p2 << std::endl;
    
    // Create a smart pointer to a class
    class Test {
    public:
        Test() { std::cout << "Test constructor" << std::endl; }
        ~Test() { std::cout << "Test destructor" << std::endl; }
        void hello() { std::cout << "Hello from Test" << std::endl; }
    };
    
    UniquePtr<Test> p3(new Test());
    p3->hello();  // Using arrow operator
    
    // Reset with a new object
    p3.reset(new Test());
    
    return 0;  // All objects automatically cleaned up
}
```

Key concepts in smart pointer implementation:
1. **Type parameterization**: The template parameter `T` allows the smart pointer to work with any type.
2. **RAII principle**: Resources are acquired in the constructor and released in the destructor.
3. **Move semantics**: Ownership can be transferred efficiently between smart pointers.
4. **Deleted copy operations**: Prevents multiple pointers from owning the same resource.
5. **Operator overloading**: Makes smart pointers behave like raw pointers.

### 10.6.2 Expression Templates

Expression templates are an advanced technique used to optimize operations on complex expressions by deferring evaluation and avoiding unnecessary temporaries:

```cpp
#include <iostream>

// Forward declarations
template<typename T> class Scalar;
template<typename L, typename R> class Addition;
template<typename L, typename R> class Multiplication;

// Base expression template class
template<typename Derived>
class Expression {
public:
    // Cast this expression to its derived type
    const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
    
    // Evaluate the expression (to be implemented by derived classes)
    double evaluate() const {
        return derived().evaluate();
    }
};

// Scalar expression (a terminal node in expression tree)
template<typename T>
class Scalar : public Expression<Scalar<T>> {
private:
    T value;
    
public:
    explicit Scalar(T val) : value(val) {}
    
    // Evaluation of a scalar is just its value
    double evaluate() const {
        return static_cast<double>(value);
    }
};

// Addition expression: L + R
template<typename L, typename R>
class Addition : public Expression<Addition<L, R>> {
private:
    const L& left;
    const R& right;
    
public:
    Addition(const L& l, const R& r) : left(l), right(r) {}
    
    // Evaluate by adding the evaluated operands
    double evaluate() const {
        return left.evaluate() + right.evaluate();
    }
};

// Multiplication expression: L * R
template<typename L, typename R>
class Multiplication : public Expression<Multiplication<L, R>> {
private:
    const L& left;
    const R& right;
    
public:
    Multiplication(const L& l, const R& r) : left(l), right(r) {}
    
    // Evaluate by multiplying the evaluated operands
    double evaluate() const {
        return left.evaluate() * right.evaluate();
    }
};

// Operator overloads for creating expression templates

// Addition of two expressions
template<typename L, typename R>
Addition<L, R> operator+(const Expression<L>& left, const Expression<R>& right) {
    return Addition<L, R>(left.derived(), right.derived());
}

// Multiplication of two expressions
template<typename L, typename R>
Multiplication<L, R> operator*(const Expression<L>& left, const Expression<R>& right) {
    return Multiplication<L, R>(left.derived(), right.derived());
}

// Vector class that uses expression templates
template<typename T, int Size>
class Vector : public Expression<Vector<T, Size>> {
private:
    T data[Size];
    
public:
    // Default constructor
    Vector() {
        for (int i = 0; i < Size; ++i) {
            data[i] = T(0);
        }
    }
    
    // Copy constructor from another vector
    Vector(const Vector<T, Size>& other) {
        for (int i = 0; i < Size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // Constructor from expression
    template<typename Expr>
    Vector(const Expression<Expr>& expr) {
        const Expr& e = expr.derived();
        for (int i = 0; i < Size; ++i) {
            data[i] = e[i];  // Assumes expression supports indexing
        }
    }
    
    // Assignment from expression
    template<typename Expr>
    Vector<T, Size>& operator=(const Expression<Expr>& expr) {
        const Expr& e = expr.derived();
        for (int i = 0; i < Size; ++i) {
            data[i] = e[i];
        }
        return *this;
    }
    
    // Access elements
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    // Evaluate (for expression template interface)
    double evaluate() const {
        double sum = 0;
        for (int i = 0; i < Size; ++i) {
            sum += data[i];
        }
        return sum;
    }
    
    // Display vector contents
    void print() const {
        std::cout << "[";
        for (int i = 0; i < Size; ++i) {
            std::cout << data[i];
            if (i < Size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Vector addition expression
template<typename L, typename R, int Size>
class VectorAddition : public Expression<VectorAddition<L, R, Size>> {
private:
    const L& left;
    const R& right;
    
public:
    VectorAddition(const L& l, const R& r) : left(l), right(r) {}
    
    // Access element at index (for efficient evaluation)
    double operator[](int index) const {
        return left[index] + right[index];
    }
    
    // Evaluate the entire expression
    double evaluate() const {
        double sum = 0;
        for (int i = 0; i < Size; ++i) {
            sum += (*this)[i];
        }
        return sum;
    }
};

// Overload + for vectors
template<typename T, int Size>
VectorAddition<Vector<T, Size>, Vector<T, Size>, Size> operator+(
    const Vector<T, Size>& left, const Vector<T, Size>& right) {
    return VectorAddition<Vector<T, Size>, Vector<T, Size>, Size>(left, right);
}

int main() {
    // Scalar expressions
    Scalar<int> a(10), b(20), c(30);
    auto expr = a + b * c;
    std::cout << "Result of a + b * c: " << expr.evaluate() << std::endl;
    
    // Vector expressions
    Vector<double, 3> v1, v2, v3;
    
    // Initialize vectors
    v1[0] = 1.0; v1[1] = 2.0; v1[2] = 3.0;
    v2[0] = 4.0; v2[1] = 5.0; v2[2] = 6.0;
    
    // The following will create an expression object, not perform calculations yet
    auto vecExpr = v1 + v2;
    
    // Assign expression to v3, which evaluates the expression
    v3 = vecExpr;
    
    // Display results
    std::cout << "v1: "; v1.print();
    std::cout << "v2: "; v2.print();
    std::cout << "v3 = v1 + v2: "; v3.print();
    
    return 0;
}
```

Key benefits of expression templates:
1. **Lazy evaluation**: Operations are performed only when needed.
2. **Elimination of temporaries**: Intermediate results aren't stored in memory.
3. **Loop fusion**: Operations that would require multiple loops can be combined into one.
4. **Domain-specific optimizations**: The compile-time expression tree can be analyzed and optimized.

### 10.6.3 Template-Based Design Patterns

Templates enable powerful implementations of design patterns with compile-time flexibility. Here are some common patterns implemented with templates:

#### Factory Pattern

```cpp
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>

// Base product class
class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

// Concrete products
class ConcreteProductA : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

// Template factory
template<typename ProductType>
class DefaultFactoryPolicy {
public:
    static std::unique_ptr<ProductType> create() {
        return std::make_unique<ProductType>();
    }
};

// Specialized factory policy
template<>
class DefaultFactoryPolicy<ConcreteProductB> {
public:
    static std::unique_ptr<ConcreteProductB> create() {
        // Special initialization for ProductB
        auto product = std::make_unique<ConcreteProductB>();
        std::cout << "Special initialization for ConcreteProductB" << std::endl;
        return product;
    }
};

// Factory class using policy-based design
template<typename ProductBaseType>
class Factory {
private:
    using CreatorFunc = std::function<std::unique_ptr<ProductBaseType>()>;
    std::map<std::string, CreatorFunc> creators;

public:
    template<typename ConcreteProduct, typename FactoryPolicy = DefaultFactoryPolicy<ConcreteProduct>>
    void registerProduct(const std::string& id) {
        creators[id] = []() { return FactoryPolicy::create(); };
    }

    std::unique_ptr<ProductBaseType> createProduct(const std::string& id) {
        auto it = creators.find(id);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }
};

int main() {
    Factory<Product> factory;
    
    // Register products with the factory
    factory.registerProduct<ConcreteProductA>("A");
    factory.registerProduct<ConcreteProductB>("B");
    
    // Create products
    auto productA = factory.createProduct("A");
    auto productB = factory.createProduct("B");
    
    if (productA) productA->use();
    if (productB) productB->use();
    
    // Try to create an unregistered product
    auto unknownProduct = factory.createProduct("C");
    if (unknownProduct) {
        unknownProduct->use();
    } else {
        std::cout << "Unknown product ID" << std::endl;
    }
    
    return 0;
}
```

#### Singleton Pattern

```cpp
#include <iostream>
#include <string>

// Template-based singleton pattern
template<typename T>
class Singleton {
private:
    static T* instance;
    
    // Make constructors private to prevent external instantiation
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    
public:
    static T& getInstance() {
        if (!instance) {
            instance = new T();
        }
        return *instance;
    }
    
    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }
};

// Initialize static member
template<typename T>
T* Singleton<T>::instance = nullptr;

// Example usage with a configuration manager
class ConfigManager : public Singleton<ConfigManager> {
    friend class Singleton<ConfigManager>;  // Allow Singleton to access private constructor
    
private:
    std::string appName;
    bool debugMode;
    
    ConfigManager() : appName("Default App"), debugMode(false) {
        std::cout << "ConfigManager created" << std::endl;
    }
    
    ~ConfigManager() {
        std::cout << "ConfigManager destroyed" << std::endl;
    }
    
public:
    void setAppName(const std::string& name) { appName = name; }
    std::string getAppName() const { return appName; }
    
    void setDebugMode(bool debug) { debugMode = debug; }
    bool isDebugMode() const { return debugMode; }
    
    void displayConfig() const {
        std::cout << "Application: " << appName << std::endl;
        std::cout << "Debug Mode: " << (debugMode ? "enabled" : "disabled") << std::endl;
    }
};

// Another singleton example
class Logger : public Singleton<Logger> {
    friend class Singleton<Logger>;  // Allow Singleton to access private constructor
    
private:
    bool enabled;
    
    Logger() : enabled(true) {
        std::cout << "Logger created" << std::endl;
    }
    
    ~Logger() {
        std::cout << "Logger destroyed" << std::endl;
    }
    
public:
    void log(const std::string& message) {
        if (enabled) {
            std::cout << "LOG: " << message << std::endl;
        }
    }
    
    void setEnabled(bool enable) { enabled = enable; }
    bool isEnabled() const { return enabled; }
};

int main() {
    // Get the ConfigManager instance
    ConfigManager& config = ConfigManager::getInstance();
    config.setAppName("My Application");
    config.setDebugMode(true);
    config.displayConfig();
    
    // Get the Logger instance
    Logger& logger = Logger::getInstance();
    logger.log("Application started");
    
    // Both refer to the same instances
    ConfigManager& config2 = ConfigManager::getInstance();
    Logger& logger2 = Logger::getInstance();
    
    std::cout << "Same config instance: " << (&config == &config2 ? "yes" : "no") << std::endl;
    std::cout << "Same logger instance: " << (&logger == &logger2 ? "yes" : "no") << std::endl;
    
    // Clean up (in real applications, singletons often live until program termination)
    ConfigManager::destroyInstance();
    Logger::destroyInstance();
    
    return 0;
}
```

#### Observer Pattern

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Forward declaration
template<typename T> class Subject;

// Observer template base class
template<typename T>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const T& data) = 0;
    
    // Auto-register with subject
    void observeSubject(Subject<T>* subject) {
        subject->addObserver(this);
        subjects.push_back(subject);
    }
    
    // Clean up registrations when destroyed
    void cleanup() {
        for (auto subject : subjects) {
            subject->removeObserver(this);
        }
        subjects.clear();
    }
    
private:
    std::vector<Subject<T>*> subjects;
};

// Subject template base class
template<typename T>
class Subject {
public:
    void addObserver(Observer<T>* observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(Observer<T>* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    void notifyObservers(const T& data) {
        for (auto observer : observers) {
            observer->update(data);
        }
    }
    
private:
    std::vector<Observer<T>*> observers;
};

// Example usage with temperature monitoring
struct WeatherData {
    double temperature;
    double humidity;
    double pressure;
    
    WeatherData(double t = 0.0, double h = 0.0, double p = 0.0)
        : temperature(t), humidity(h), pressure(p) {}
};

// Concrete subject
class WeatherStation : public Subject<WeatherData> {
private:
    WeatherData currentData;
    
public:
    void setMeasurements(double temperature, double humidity, double pressure) {
        currentData = WeatherData(temperature, humidity, pressure);
        notifyObservers(currentData);
    }
    
    WeatherData getCurrentData() const {
        return currentData;
    }
};

// Concrete observers
class TemperatureDisplay : public Observer<WeatherData> {
public:
    TemperatureDisplay() = default;
    
    ~TemperatureDisplay() {
        cleanup();  // Clean up observer registrations
    }
    
    void update(const WeatherData& data) override {
        std::cout << "Temperature Display: " << data.temperature << "°C" << std::endl;
    }
};

class WeatherStatsTracker : public Observer<WeatherData> {
private:
    double minTemp = 1000.0;
    double maxTemp = -1000.0;
    double tempSum = 0.0;
    int numReadings = 0;
    
public:
    WeatherStatsTracker() = default;
    
    ~WeatherStatsTracker() {
        cleanup();  // Clean up observer registrations
    }
    
    void update(const WeatherData& data) override {
        double temp = data.temperature;
        
        minTemp = std::min(minTemp, temp);
        maxTemp = std::max(maxTemp, temp);
        tempSum += temp;
        ++numReadings;
        
        std::cout << "Weather Stats:" << std::endl;
        std::cout << "  Min temperature: " << minTemp << "°C" << std::endl;
        std::cout << "  Max temperature: " << maxTemp << "°C" << std::endl;
        std::cout << "  Average temperature: " << (tempSum / numReadings) << "°C" << std::endl;
    }
};

int main() {
    WeatherStation weatherStation;
    
    auto tempDisplay = std::make_unique<TemperatureDisplay>();
    auto statsTracker = std::make_unique<WeatherStatsTracker>();
    
    // Register observers with the subject
    tempDisplay->observeSubject(&weatherStation);
    statsTracker->observeSubject(&weatherStation);
    
    // Simulate weather changes
    std::cout << "Weather update 1:" << std::endl;
    weatherStation.setMeasurements(25.2, 65.0, 1013.1);
    
    std::cout << "\nWeather update 2:" << std::endl;
    weatherStation.setMeasurements(26.8, 70.0, 1012.5);
    
    std::cout << "\nWeather update 3:" << std::endl;
    weatherStation.setMeasurements(24.5, 80.0, 1010.3);
    
    return 0;
}
```

### 10.6.4 CRTP (Curiously Recurring Template Pattern)

The Curiously Recurring Template Pattern (CRTP) is a C++ idiom where a class derives from a template class that takes the derived class as a template parameter:

```cpp
#include <iostream>
#include <string>
#include <memory>

// Base class template using CRTP
template<typename Derived>
class Base {
public:
    void interface() {
        // Call the implementation in the derived class
        static_cast<Derived*>(this)->implementation();
    }
    
    // Default implementation that can be overridden
    void implementation() {
        std::cout << "Base implementation" << std::endl;
    }
    
    // Static polymorphism example
    void doSomething() {
        std::cout << "Doing pre-work in base..." << std::endl;
        static_cast<Derived*>(this)->implementation();
        std::cout << "Doing post-work in base..." << std::endl;
    }
};

// Derived class using CRTP
class Derived1 : public Base<Derived1> {
public:
    // Override implementation
    void implementation() {
        std::cout << "Derived1 implementation" << std::endl;
    }
};

// Another derived class
class Derived2 : public Base<Derived2> {
public:
    // Override implementation
    void implementation() {
        std::cout << "Derived2 implementation" << std::endl;
    }
};

// Example of CRTP for static polymorphism with countable mixin
template<typename Derived>
class ObjectCounter {
private:
    static inline size_t count = 0;  // C++17 inline static

protected:
    ObjectCounter() {
        ++count;
    }
    
    ~ObjectCounter() {
        --count;
    }
    
public:
    static size_t getCount() {
        return count;
    }
};

// Classes that want to be counted
class Widget : public ObjectCounter<Widget> {
public:
    Widget() { std::cout << "Widget created" << std::endl; }
    ~Widget() { std::cout << "Widget destroyed" << std::endl; }
};

class Gadget : public ObjectCounter<Gadget> {
public:
    Gadget() { std::cout << "Gadget created" << std::endl; }
    ~Gadget() { std::cout << "Gadget destroyed" << std::endl; }
};

int main() {
    // Test basic CRTP
    Derived1 d1;
    Derived2 d2;
    
    // Call interface method which will use the derived implementation
    d1.interface();  // Calls Derived1::implementation()
    d2.interface();  // Calls Derived2::implementation()
    
    // Call method with pre/post work
    d1.doSomething();
    
    // Test object counter
    std::cout << "\nInitial count - Widgets: " << Widget::getCount() 
              << ", Gadgets: " << Gadget::getCount() << std::endl;
    
    {
        Widget w1, w2;
        Gadget g1;
        
        std::cout << "After creating objects - Widgets: " << Widget::getCount() 
                  << ", Gadgets: " << Gadget::getCount() << std::endl;
    }  // Objects go out of scope and are destroyed
    
    std::cout << "Final count - Widgets: " << Widget::getCount() 
              << ", Gadgets: " << Gadget::getCount() << std::endl;
    
    return 0;
}
```

Benefits of CRTP:
1. **Static polymorphism**: Achieved at compile time without the overhead of virtual functions
2. **Mixins**: Add functionality to classes without multiple inheritance issues
3. **Template method pattern**: Base class defines the algorithm structure, derived classes provide specific implementations
4. **Per-class storage**: Each derived class gets its own set of static variables

### 10.6.5 Traits and Policy Classes

Traits and policy classes are powerful template techniques for customizing behavior:

#### Traits Classes

Traits classes provide a way to access information about types:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>

// A traits class for containers
template<typename Container>
struct ContainerTraits {
    // Default implementation for common containers
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using iterator = typename Container::iterator;
    
    static constexpr bool has_random_access = false;  // Default assumption
};

// Specialization for std::vector
template<typename T, typename Allocator>
struct ContainerTraits<std::vector<T, Allocator>> {
    using value_type = typename std::vector<T, Allocator>::value_type;
    using size_type = typename std::vector<T, Allocator>::size_type;
    using iterator = typename std::vector<T, Allocator>::iterator;
    
    static constexpr bool has_random_access = true;  // Vector has random access
};

// Specialization for std::list
template<typename T, typename Allocator>
struct ContainerTraits<std::list<T, Allocator>> {
    using value_type = typename std::list<T, Allocator>::value_type;
    using size_type = typename std::list<T, Allocator>::size_type;
    using iterator = typename std::list<T, Allocator>::iterator;
    
    static constexpr bool has_random_access = false;  // List doesn't have random access
};

// Function that uses traits to optimize container operations
template<typename Container>
void process(Container& c) {
    using Traits = ContainerTraits<Container>;
    using value_type = typename Traits::value_type;
    
    std::cout << "Container with value type: " << typeid(value_type).name() << std::endl;
    
    // Use traits to optimize operations
    if constexpr (Traits::has_random_access) {
        std::cout << "Using random access optimization..." << std::endl;
        // Direct access to each element
        for (typename Traits::size_type i = 0; i < c.size(); ++i) {
            c[i] = static_cast<value_type>(i);
        }
    } else {
        std::cout << "Using sequential access..." << std::endl;
        // Sequential traversal
        typename Traits::size_type i = 0;
        for (auto& elem : c) {
            elem = static_cast<value_type>(i++);
        }
    }
}

// Custom traits for numeric types to provide common operations
template<typename T, typename Enable = void>
struct NumericTraits {
    static constexpr bool is_numeric = false;
    static constexpr bool is_integral = false;
    static constexpr bool is_floating_point = false;
    
    // These won't be used for non-numeric types, but we need them for compilation
    static T zero() { return T(); }
    static T one() { return T(); }
};

// Specialization for integral types
template<typename T>
struct NumericTraits<T, typename std::enable_if<std::is_integral<T>::value>::type> {
    static constexpr bool is_numeric = true;
    static constexpr bool is_integral = true;
    static constexpr bool is_floating_point = false;
    
    static T zero() { return 0; }
    static T one() { return 1; }
    static T max_value() { return std::numeric_limits<T>::max(); }
    static T min_value() { return std::numeric_limits<T>::min(); }
};

// Specialization for floating-point types
template<typename T>
struct NumericTraits<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
    static constexpr bool is_numeric = true;
    static constexpr bool is_integral = false;
    static constexpr bool is_floating_point = true;
    
    static T zero() { return 0.0; }
    static T one() { return 1.0; }
    static T max_value() { return std::numeric_limits<T>::max(); }
    static T min_value() { return std::numeric_limits<T>::lowest(); }  // Note: lowest for float
    static T epsilon() { return std::numeric_limits<T>::epsilon(); }
    
    // Check if two floating-point values are approximately equal
    static bool approx_equal(T a, T b, T tolerance = epsilon()) {
        return std::abs(a - b) <= tolerance;
    }
};

int main() {
    // Test container traits
    std::vector<int> vec(5);
    std::list<double> lst(5);
    
    process(vec);
    process(lst);
    
    std::cout << "\nVector contents: ";
    for (const auto& v : vec) std::cout << v << " ";
    std::cout << std::endl;
    
    std::cout << "List contents: ";
    for (const auto& v : lst) std::cout << v << " ";
    std::cout << std::endl;
    
    // Test numeric traits
    using IntTraits = NumericTraits<int>;
    using DoubleTraits = NumericTraits<double>;
    using StringTraits = NumericTraits<std::string>;
    
    std::cout << "\nNumeric traits for int:" << std::endl;
    std::cout << "Is numeric: " << IntTraits::is_numeric << std::endl;
    std::cout << "Is integral: " << IntTraits::is_integral << std::endl;
    std::cout << "Is floating point: " << IntTraits::is_floating_point << std::endl;
    std::cout << "Zero value: " << IntTraits::zero() << std::endl;
    std::cout << "Max value: " << IntTraits::max_value() << std::endl;
    
    std::cout << "\nNumeric traits for double:" << std::endl;
    std::cout << "Is numeric: " << DoubleTraits::is_numeric << std::endl;
    std::cout << "Is integral: " << DoubleTraits::is_integral << std::endl;
    std::cout << "Is floating point: " << DoubleTraits::is_floating_point << std::endl;
    std::cout << "Epsilon: " << DoubleTraits::epsilon() << std::endl;
    
    double a = 0.1 + 0.2;
    double b = 0.3;
    std::cout << "0.1 + 0.2 == 0.3? " << DoubleTraits::approx_equal(a, b) << std::endl;
    
    std::cout << "\nNumeric traits for string:" << std::endl;
    std::cout << "Is numeric: " << StringTraits::is_numeric << std::endl;
    
    return 0;
}
```

#### Policy Classes

Policy classes encapsulate behaviors that can be combined to customize class behavior:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <mutex>
#include <string>
#include <memory>

// Threading policies
class SingleThreadPolicy {
public:
    void lock() const {}  // No-op
    void unlock() const {}  // No-op
    
    const char* name() const { return "Single-threaded"; }
};

class MultiThreadPolicy {
private:
    mutable std::mutex mtx;
    
public:
    void lock() const { mtx.lock(); }
    void unlock() const { mtx.unlock(); }
    
    const char* name() const { return "Multi-threaded"; }
};

// Storage policies
template<typename T>
class VectorStorage {
protected:
    std::vector<T> data;
    
public:
    void add(const T& item) { data.push_back(item); }
    
    T& get(size_t index) { 
        if (index >= data.size()) throw std::out_of_range("Index out of bounds");
        return data[index]; 
    }
    
    size_t size() const { return data.size(); }
    
    const char* name() const { return "Vector storage"; }
};

template<typename T>
class ListStorage {
protected:
    std::list<T> data;
    
public:
    void add(const T& item) { data.push_back(item); }
    
    T& get(size_t index) { 
        if (index >= data.size()) throw std::out_of_range("Index out of bounds");
        auto it = data.begin();
        std::advance(it, index);
        return *it; 
    }
    
    size_t size() const { return data.size(); }
    
    const char* name() const { return "List storage"; }
};

// Allocation policies
template<typename T>
class DefaultAllocPolicy {
public:
    T* allocate() { return new T(); }
    void deallocate(T* ptr) { delete ptr; }
    
    const char* name() const { return "Default allocation"; }
};

template<typename T>
class CountingAllocPolicy {
private:
    static inline size_t allocCount = 0;
    static inline size_t deallocCount = 0;
    
public:
    T* allocate() { 
        ++allocCount; 
        return new T(); 
    }
    
    void deallocate(T* ptr) { 
        delete ptr; 
        ++deallocCount; 
    }
    
    static size_t getAllocCount() { return allocCount; }
    static size_t getDeallocCount() { return deallocCount; }
    
    const char* name() const { return "Counting allocation"; }
};

// Main container class that combines policies
template<
    typename T,
    typename ThreadingPolicy = SingleThreadPolicy,
    template<typename> class StoragePolicy = VectorStorage,
    template<typename> class AllocPolicy = DefaultAllocPolicy
>
class Container : private ThreadingPolicy, private StoragePolicy<T>, private AllocPolicy<T> {
public:
    // Add item with thread safety
    void add(const T& item) {
        ThreadingPolicy::lock();
        StoragePolicy<T>::add(item);
        ThreadingPolicy::unlock();
    }
    
    // Get item with thread safety
    T& get(size_t index) {
        ThreadingPolicy::lock();
        try {
            T& result = StoragePolicy<T>::get(index);
            ThreadingPolicy::unlock();
            return result;
        } catch (...) {
            ThreadingPolicy::unlock();
            throw;
        }
    }
    
    // Create a new item using the allocation policy
    std::unique_ptr<T> createItem() {
        ThreadingPolicy::lock();
        T* item = AllocPolicy<T>::allocate();
        ThreadingPolicy::unlock();
        
        // Use unique_ptr with custom deleter
        return std::unique_ptr<T>(item, [this](T* ptr) {
            ThreadingPolicy::lock();
            AllocPolicy<T>::deallocate(ptr);
            ThreadingPolicy::unlock();
        });
    }
    
    // Get information about the container
    void printInfo() const {
        std::cout << "Container Info:" << std::endl;
        std::cout << "- Thread policy: " << ThreadingPolicy::name() << std::endl;
        std::cout << "- Storage policy: " << StoragePolicy<T>::name() << std::endl;
        std::cout << "- Allocation policy: " << AllocPolicy<T>::name() << std::endl;
        std::cout << "- Size: " << StoragePolicy<T>::size() << " items" << std::endl;
    }
};

int main() {
    // Single-threaded container with vector storage and default allocation
    Container<int> basicContainer;
    basicContainer.printInfo();
    
    for (int i = 0; i < 5; ++i) {
        basicContainer.add(i * 10);
    }
    
    std::cout << "\nBasic container contents:" << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        std::cout << "Item " << i << ": " << basicContainer.get(i) << std::endl;
    }
    
    // Multi-threaded container with list storage and counting allocation
    Container<std::string, MultiThreadPolicy, ListStorage, CountingAllocPolicy> advancedContainer;
    advancedContainer.printInfo();
    
    advancedContainer.add("Hello");
    advancedContainer.add("Policy-based");
    advancedContainer.add("Design");
    
    std::cout << "\nAdvanced container contents:" << std::endl;
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "Item " << i << ": " << advancedContainer.get(i) << std::endl;
    }
    
    // Create items using allocation policy
    auto item1 = advancedContainer.createItem();
    auto item2 = advancedContainer.createItem();
    *item1 = "Allocated string 1";
    *item2 = "Allocated string 2";
    
    std::cout << "\nAllocated items:" << std::endl;
    std::cout << *item1 << std::endl;
    std::cout << *item2 << std::endl;
    
    // Check allocation statistics
    std::cout << "\nAllocation statistics:" << std::endl;
    std::cout << "- Allocations: " << CountingAllocPolicy<std::string>::getAllocCount() << std::endl;
    std::cout << "- Deallocations: " << CountingAllocPolicy<std::string>::getDeallocCount() << std::endl;
    
    return 0;
}
```

### 10.6.6 Template Method Chaining

Template method chaining (fluent interfaces) can be implemented with templates to create expressive APIs:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Forward declaration of builder class
template<typename BuilderType>
class QueryBuilderBase;

// Chain-enabled WHERE clause builder
template<typename BuilderType>
class WhereClause {
private:
    QueryBuilderBase<BuilderType>& builder;
    bool hasWhere = false;
    
public:
    explicit WhereClause(QueryBuilderBase<BuilderType>& b) : builder(b) {}
    
    BuilderType& where(const std::string& condition) {
        builder.addClause(hasWhere ? "AND" : "WHERE", condition);
        hasWhere = true;
        return static_cast<BuilderType&>(builder);
    }
    
    BuilderType& orWhere(const std::string& condition) {
        builder.addClause("OR", condition);
        hasWhere = true;
        return static_cast<BuilderType&>(builder);
    }
};

// Chain-enabled ORDER BY clause builder
template<typename BuilderType>
class OrderByClause {
private:
    QueryBuilderBase<BuilderType>& builder;
    bool hasOrderBy = false;
    
public:
    explicit OrderByClause(QueryBuilderBase<BuilderType>& b) : builder(b) {}
    
    BuilderType& orderBy(const std::string& column, bool ascending = true) {
        std::string direction = ascending ? "ASC" : "DESC";
        builder.addClause(hasOrderBy ? "," : "ORDER BY", column + " " + direction);
        hasOrderBy = true;
        return static_cast<BuilderType&>(builder);
    }
};

// Base query builder with common functionality
template<typename BuilderType>
class QueryBuilderBase : public WhereClause<BuilderType>, 
                         public OrderByClause<BuilderType> {
private:
    std::string tableName;
    std::vector<std::string> clauses;
    
protected:
    QueryBuilderBase(const std::string& table)
        : WhereClause<BuilderType>(*this),
          OrderByClause<BuilderType>(*this),
          tableName(table) {}
    
    // Make base class a friend to access addClause
    friend class WhereClause<BuilderType>;
    friend class OrderByClause<BuilderType>;
    
    // Add a clause to the query
    void addClause(const std::string& keyword, const std::string& clause) {
        clauses.push_back(keyword + " " + clause);
    }
    
public:
    // Get the generated SQL query
    std::string getSQL() const {
        std::ostringstream sql;
        sql << getQueryPrefix() << " FROM " << tableName;
        
        for (const auto& clause : clauses) {
            sql << " " << clause;
        }
        
        return sql.str();
    }
    
    // Execute the query (in a real system, this would run the SQL)
    void execute() {
        std::cout << "Executing SQL: " << getSQL() << std::endl;
        // In real code: run the SQL and return results
    }
    
    // Must be overridden by derived classes
    virtual std::string getQueryPrefix() const = 0;
};

// Concrete Select query builder
class SelectQueryBuilder : public QueryBuilderBase<SelectQueryBuilder> {
private:
    std::string columns;
    
public:
    SelectQueryBuilder() : QueryBuilderBase("") {}
    
    // Start building a SELECT query
    SelectQueryBuilder& from(const std::string& table) {
        // Reset the table name in the base class
        tableName = table;
        return *this;
    }
    
    // Select specific columns
    SelectQueryBuilder& select(const std::string& columnList) {
        columns = columnList;
        return *this;
    }
    
    // Override to provide SELECT-specific prefix
    std::string getQueryPrefix() const override {
        return "SELECT " + (columns.empty() ? "*" : columns);
    }
};

// Concrete Update query builder
class UpdateQueryBuilder : public QueryBuilderBase<UpdateQueryBuilder> {
private:
    std::string setClause;
    
public:
    UpdateQueryBuilder(const std::string& table) : QueryBuilderBase(table) {}
    
    // Set values to update
    UpdateQueryBuilder& set(const std::string& updates) {
        setClause = updates;
        return *this;
    }
    
    // Override to provide UPDATE-specific prefix
    std::string getQueryPrefix() const override {
        return "UPDATE " + tableName + " SET " + setClause;
    }
};

// Concrete Delete query builder
class DeleteQueryBuilder : public QueryBuilderBase<DeleteQueryBuilder> {
public:
    DeleteQueryBuilder(const std::string& table) : QueryBuilderBase(table) {}
    
    // Override to provide DELETE-specific prefix
    std::string getQueryPrefix() const override {
        return "DELETE";
    }
};

// Entry point for query building
class QueryBuilder {
public:
    static SelectQueryBuilder select(const std::string& columns = "*") {
        return SelectQueryBuilder().select(columns);
    }
    
    static UpdateQueryBuilder update(const std::string& table) {
        return UpdateQueryBuilder(table);
    }
    
    static DeleteQueryBuilder deleteFrom(const std::string& table) {
        return DeleteQueryBuilder(table);
    }
};

int main() {
    // Build and execute a SELECT query
    auto selectQuery = QueryBuilder::select("id, name, email")
        .from("users")
        .where("status = 'active'")
        .andWhere("age > 18")
        .orderBy("name")
        .orderBy("id", false);  // DESC
        
    std::cout << "Select SQL: " << selectQuery.getSQL() << std::endl;
    selectQuery.execute();
    
    // Build and execute an UPDATE query
    auto updateQuery = QueryBuilder::update("users")
        .set("status = 'inactive', last_login = CURRENT_TIMESTAMP")
        .where("last_login < '2023-01-01'")
        .orWhere("status = 'pending'");
        
    std::cout << "\nUpdate SQL: " << updateQuery.getSQL() << std::endl;
    updateQuery.execute();
    
    // Build and execute a DELETE query
    auto deleteQuery = QueryBuilder::deleteFrom("temp_sessions")
        .where("created_at < '2023-01-01'")
        .andWhere("status = 'expired'");
        
    std::cout << "\nDelete SQL: " << deleteQuery.getSQL() << std::endl;
    deleteQuery.execute();
    
    return 0;
}
```

### 10.6.7 Type Erasure with Templates

Type erasure is a technique that allows you to use objects of different types through a common interface without inheritance:

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>

// Type-erased function wrapper
class AnyCallable {
private:
    struct CallableConcept {
        virtual ~CallableConcept() = default;
        virtual void call() const = 0;
        virtual std::unique_ptr<CallableConcept> clone() const = 0;
    };
    
    template<typename F>
    struct CallableModel : CallableConcept {
        F func;
        
        explicit CallableModel(F f) : func(std::move(f)) {}
        
        void call() const override {
            func();
        }
        
        std::unique_ptr<CallableConcept> clone() const override {
            return std::make_unique<CallableModel<F>>(func);
        }
    };
    
    std::unique_ptr<CallableConcept> callable;
    
public:
    AnyCallable() = default;
    
    template<typename F>
    AnyCallable(F f) : callable(std::make_unique<CallableModel<F>>(std::move(f))) {}
    
    AnyCallable(const AnyCallable& other) : callable(other.callable ? other.callable->clone() : nullptr) {}
    
    AnyCallable(AnyCallable&& other) noexcept = default;
    
    AnyCallable& operator=(const AnyCallable& other) {
        if (this != &other) {
            callable = other.callable ? other.callable->clone() : nullptr;
        }
        return *this;
    }
    
    AnyCallable& operator=(AnyCallable&& other) noexcept = default;
    
    void operator()() const {
        if (callable) {
            callable->call();
        }
    }
    
    explicit operator bool() const {
        return callable != nullptr;
    }
};

// Type-erased container using templates
class AnyValue {
private:
    struct ValueConcept {
        virtual ~ValueConcept() = default;
        virtual std::unique_ptr<ValueConcept> clone() const = 0;
        virtual void print(std::ostream& os) const = 0;
        virtual std::string getTypeName() const = 0;
    };
    
    template<typename T>
    struct ValueModel : ValueConcept {
        T value;
        
        explicit ValueModel(T v) : value(std::move(v)) {}
        
        std::unique_ptr<ValueConcept> clone() const override {
            return std::make_unique<ValueModel<T>>(value);
        }
        
        void print(std::ostream& os) const override {
            os << value;
        }
        
        std::string getTypeName() const override {
            return typeid(T).name();
        }
    };
    
    std::unique_ptr<ValueConcept> content;
    
public:
    AnyValue() = default;
    
    template<typename T>
    explicit AnyValue(T value) : content(std::make_unique<ValueModel<T>>(std::move(value))) {}
    
    AnyValue(const AnyValue& other) : content(other.content ? other.content->clone() : nullptr) {}
    
    AnyValue(AnyValue&& other) noexcept = default;
    
    AnyValue& operator=(const AnyValue& other) {
        if (this != &other) {
            content = other.content ? other.content->clone() : nullptr;
        }
        return *this;
    }
    
    AnyValue& operator=(AnyValue&& other) noexcept = default;
    
    template<typename T>
    T& get() {
        auto* model = dynamic_cast<ValueModel<T>*>(content.get());
        if (!model) {
            throw std::bad_cast();
        }
        return model->value;
    }
    
    template<typename T>
    bool is() const {
        return dynamic_cast<ValueModel<T>*>(content.get()) != nullptr;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const AnyValue& any) {
        if (any.content) {
            any.content->print(os);
        } else {
            os << "[empty]";
        }
        return os;
    }
    
    std::string getTypeName() const {
        return content ? content->getTypeName() : "none";
    }
    
    explicit operator bool() const {
        return content != nullptr;
    }
};

int main() {
    // Test AnyCallable
    std::vector<AnyCallable> callbacks;
    
    // Add different types of callables
    callbacks.push_back([]{ std::cout << "Hello from lambda!" << std::endl; });
    
    struct Functor {
        void operator()() const { 
            std::cout << "Hello from functor!" << std::endl; 
        }
    };
    callbacks.push_back(Functor());
    
    void regularFunction() { 
        std::cout << "Hello from regular function!" << std::endl; 
    }
    callbacks.push_back(regularFunction);
    
    // Execute all callbacks
    std::cout << "Executing callbacks:" << std::endl;
    for (const auto& callback : callbacks) {
        callback();
    }
    
    // Test AnyValue
    std::vector<AnyValue> values;
    
    // Store different types
    values.push_back(AnyValue(42));
    values.push_back(AnyValue(std::string("Hello, world!")));
    values.push_back(AnyValue(3.14159));
    values.push_back(AnyValue(true));
    
    // Display all values
    std::cout << "\nStored values:" << std::endl;
    for (const auto& value : values) {
        std::cout << "Type: " << value.getTypeName() << ", Value: " << value << std::endl;
    }
    
    // Access specific value
    try {
        std::string& str = values[1].get<std::string>();
        str += " (modified)";
        
        std::cout << "\nModified string: " << str << std::endl;
        std::cout << "From container: " << values[1] << std::endl;
    } catch (const std::bad_cast& e) {
        std::cerr << "Type conversion failed: " << e.what() << std::endl;
    }
    
    // Check types
    std::cout << "\nType checking:" << std::endl;
    std::cout << "values[0] is int: " << values[0].is<int>() << std::endl;
    std::cout << "values[1] is string: " << values[1].is<std::string>() << std::endl;
    std::cout << "values[2] is double: " << values[2].is<double>() << std::endl;
    std::cout << "values[0] is double: " << values[0].is<double>() << std::endl;
    
    return 0;
}
```

### 10.6.8 Optimizing Template Code

Templates can lead to code bloat and increased compilation times if not used carefully. Here are some techniques to optimize template usage:

```cpp
#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <map>

// 1. Use explicit instantiation for common types
template <typename T>
class CommonContainer {
public:
    CommonContainer() { std::cout << "Instantiating for " << typeid(T).name() << std::endl; }
    void process(const T& value) { std::cout << "Processing: " << value << std::endl; }
};

// Explicit instantiation in the .cpp file (reduces compile time in headers)
template class CommonContainer<int>;
template class CommonContainer<double>;
template class CommonContainer<std::string>;

// 2. Use the Pimpl idiom to reduce compilation dependencies
template <typename T>
class PimplTemplate {
private:
    // Forward declaration of implementation
    class Impl;
    std::unique_ptr<Impl> pimpl;
    
public:
    PimplTemplate();
    ~PimplTemplate();
    void doSomething(const T& value);
};

// Implementation in .cpp file
template <typename T>
class PimplTemplate<T>::Impl {
public:
    void doSomething(const T& value) {
        std::cout << "Implementation doing something with: " << value << std::endl;
    }
};

template <typename T>
PimplTemplate<T>::PimplTemplate() : pimpl(std::make_unique<Impl>()) {}

template <typename T>
PimplTemplate<T>::~PimplTemplate() = default;

template <typename T>
void PimplTemplate<T>::doSomething(const T& value) {
    pimpl->doSomething(value);
}

// Explicit instantiation for common types
template class PimplTemplate<int>;
template class PimplTemplate<std::string>;

// 3. Use type erasure for template parameters that don't affect performance-critical code
class TypeErasedInterface {
public:
    virtual ~TypeErasedInterface() = default;
    virtual void process() = 0;
};

template <typename T>
class TypeErasedImpl : public TypeErasedInterface {
private:
    T value;
    
public:
    explicit TypeErasedImpl(T v) : value(std::move(v)) {}
    
    void process() override {
        std::cout << "Processing with type erasure: " << value << std::endl;
    }
};

// 4. Consider non-template base classes where possible
class NonTemplateBase {
public:
    virtual ~NonTemplateBase() = default;
    virtual void commonBehavior() {
        std::cout << "Common behavior in non-template base" << std::endl;
    }
};

template <typename T>
class TemplatedDerived : public NonTemplateBase {
private:
    T specificData;
    
public:
    explicit TemplatedDerived(T data) : specificData(std::move(data)) {}
    
    void specificBehavior() {
        std::cout << "Specific behavior with: " << specificData << std::endl;
    }
};

// 5. Use static polymorphism only where dynamic dispatch would be a performance bottleneck
template <typename T>
class StaticHandler {
public:
    void handle(const T& value) {
        std::cout << "Static handling of: " << value << std::endl;
    }
};

class DynamicHandler {
public:
    virtual ~DynamicHandler() = default;
    virtual void handle(int value) {
        std::cout << "Dynamic handling of int: " << value << std::endl;
    }
};

class SpecializedHandler : public DynamicHandler {
public:
    void handle(int value) override {
        std::cout << "Specialized handling of int: " << value * 2 << std::endl;
    }
};

int main() {
    // 1. Explicit instantiation example
    CommonContainer<int> intContainer;
    intContainer.process(42);
    
    CommonContainer<std::string> strContainer;
    strContainer.process("Hello");
    
    // 2. Pimpl idiom example
    PimplTemplate<int> pimplInt;
    pimplInt.doSomething(42);
    
    // 3. Type erasure example
    std::vector<std::unique_ptr<TypeErasedInterface>> objects;
    objects.push_back(std::make_unique<TypeErasedImpl<int>>(42));
    objects.push_back(std::make_unique<TypeErasedImpl<std::string>>("Hello"));
    objects.push_back(std::make_unique<TypeErasedImpl<double>>(3.14));
    
    for (const auto& obj : objects) {
        obj->process();
    }
    
    // 4. Non-template base example
    TemplatedDerived<int> derivedInt(42);
    derivedInt.commonBehavior();
    derivedInt.specificBehavior();
    
    TemplatedDerived<std::string> derivedStr("World");
    derivedStr.commonBehavior();
    derivedStr.specificBehavior();
    
    // 5. Static vs dynamic polymorphism
    StaticHandler<int> staticHandler;
    staticHandler.handle(42);
    
    DynamicHandler* dynamicHandler = new SpecializedHandler();
    dynamicHandler->handle(42);
    delete dynamicHandler;
    
    return 0;
}
```

### 10.6.9 Best Practices for Advanced Template Usage

1. **Document template requirements clearly**
   * Specify requirements for template parameters
   * Provide examples of valid template arguments
   * Document any implicit assumptions

2. **Use concept constraints in C++20**
   * Make requirements explicit with concepts
   * Provide better error messages for users
   * Enable more IDE support and better diagnostics

3. **Balance flexibility and usability**
   * Don't overtemplate code that doesn't need it
   * Consider providing non-template alternatives where appropriate
   * Keep the interface simple for common use cases

4. **Reduce compilation dependencies**
   * Use forward declarations where possible
   * Apply the Pimpl idiom for complex implementations
   * Consider explicit instantiation for common types

5. **Optimize for both compile time and runtime**
   * Be aware of template instantiation costs
   * Use explicit instantiation to reduce duplicate code generation
   * Apply techniques like external polymorphism for large class templates

6. **Test template code thoroughly**
   * Test with various combinations of template arguments
   * Include edge cases and custom types
   * Test with SFINAE or concept failures to ensure error messages are helpful

7. **Use meaningful template parameter names**
   * Prefer descriptive names like `ElementType` over just `T`
   * Document the purpose of each template parameter
   * Use consistent naming conventions across your codebase

8. **Consider compile-time and runtime tradeoffs**
   * Templates can move work from runtime to compile time
   * Balance between static and dynamic polymorphism based on performance needs
   * Use runtime polymorphism for flexibility, static for performance-critical code

9. **Apply template design patterns appropriately**
   * Use policy-based design for customizable behaviors
   * Apply CRTP for static polymorphism
   * Use type erasure for interface uniformity with implementation flexibility

10. **Manage complexity**
    * Keep template metaprograms as simple as possible
    * Provide higher-level abstractions over complex template implementations
    * Consider alternative approaches before diving into complex metaprogramming

By following these best practices and understanding the advanced techniques demonstrated in this section, you'll be able to leverage C++ templates to create efficient, flexible, and maintainable code for a wide range of applications.
