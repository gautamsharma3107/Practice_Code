# Chapter 8: Standard Template Library (STL) (Part 2)

## 8.2.5 Queue

`std::queue` is a container adapter that gives the functionality of a first-in, first-out (FIFO) data structure. Like `std::stack`, it is built on top of other STL containers, with `std::deque` being the default.

### Key Features

- **FIFO (First-In, First-Out)**: Elements are inserted at the back and removed from the front
- **Container Adapter**: Built on top of other containers (typically deque)
- **Limited Interface**: Only allows operations appropriate for queues
- **No iterators**: Can't traverse all elements

### Basic Queue Operations

```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    // Create a queue with default container (deque)
    queue<int> numbers;
    
    // Add elements to the queue (at the back)
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);
    
    cout << "Queue size: " << numbers.size() << endl;
    cout << "Front element: " << numbers.front() << endl;
    cout << "Back element: " << numbers.back() << endl;
    
    // Remove elements from the queue (from the front)
    cout << "Processing queue: ";
    while (!numbers.empty()) {
        cout << numbers.front() << " ";
        numbers.pop();
    }
    cout << endl;
    
    cout << "Queue empty? " << (numbers.empty() ? "Yes" : "No") << endl;
    
    // Creating a queue with a different underlying container
    queue<string, vector<string>> strQueue;
    
    strQueue.push("First");
    strQueue.push("Second");
    strQueue.push("Third");
    
    cout << "String queue front: " << strQueue.front() << endl;
    cout << "String queue back: " << strQueue.back() << endl;
    
    return 0;
}
```

### Real-World Queue Applications

```cpp
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

// Example 1: Print queue simulation
class PrintQueue {
private:
    queue<string> documents;
    
public:
    void addDocument(const string& doc) {
        documents.push(doc);
        cout << "Added to print queue: " << doc << endl;
    }
    
    void processDocuments() {
        cout << "\nProcessing documents..." << endl;
        while (!documents.empty()) {
            string doc = documents.front();
            cout << "Printing: " << doc << endl;
            
            // Simulate printing time
            this_thread::sleep_for(chrono::milliseconds(500));
            
            documents.pop();
            cout << "Finished printing: " << doc << endl;
        }
    }
    
    int queueSize() const {
        return documents.size();
    }
};

// Example 2: BFS algorithm using queue for level-order traversal
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    cout << "Level order traversal: ";
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        cout << node->value << " ";
        
        if (node->left) {
            q.push(node->left);
        }
        
        if (node->right) {
            q.push(node->right);
        }
    }
    cout << endl;
}

int main() {
    // Example 1: Print queue
    PrintQueue printer;
    printer.addDocument("report.pdf");
    printer.addDocument("letter.doc");
    printer.addDocument("image.jpg");
    
    cout << "Queue size: " << printer.queueSize() << endl;
    printer.processDocuments();
    
    // Example 2: Level-order traversal of a binary tree using a queue
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    levelOrderTraversal(root);
    
    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}
```

### When to Use Queue

- When you need FIFO (First-In, First-Out) behavior
- For level-order traversals in trees/graphs (BFS - Breadth-First Search)
- For implementing buffers (e.g., print queue, task queue)
- For scheduling processes or tasks
- When order of processing is important

## 8.2.6 Priority Queue

`std::priority_queue` is a container adapter that provides constant time lookup of the largest (by default) element. It's implemented using a heap structure, which allows for efficient insertion and extraction of the highest priority element.

### Key Features

- **Priority-based**: Elements are retrieved according to priority, not insertion order
- **Container Adapter**: Built on top of other containers (typically vector)
- **Heap Structure**: Implemented as a max-heap by default (highest value has highest priority)
- **Fast Access to Highest Priority**: Constant time access to the top element
- **No iterators**: Can't traverse all elements

### Basic Priority Queue Operations

```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    // Default priority queue (max-heap)
    priority_queue<int> pq;
    
    // Insert elements
    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);
    
    cout << "Priority queue size: " << pq.size() << endl;
    cout << "Top element: " << pq.top() << endl;  // Highest value is on top
    
    // Process elements (highest priority first)
    cout << "Elements in priority order: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";  // Access highest priority element
        pq.pop();                 // Remove highest priority element
    }
    cout << endl;
    
    // Min-heap using custom comparator
    priority_queue<int, vector<int>, greater<int>> minPQ;
    
    minPQ.push(10);
    minPQ.push(30);
    minPQ.push(20);
    minPQ.push(5);
    
    cout << "\nMin priority queue top: " << minPQ.top() << endl;  // Lowest value on top
    
    cout << "Elements in ascending order: ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << endl;
    
    return 0;
}
```

### Custom Priority and Complex Types

```cpp
#include <iostream>
#include <queue>
#include <string>
#include <functional>  // For std::greater
using namespace std;

// Define a custom type
struct Task {
    string name;
    int priority;  // Higher number = higher priority
    
    Task(const string& n, int p) : name(n), priority(p) {}
    
    // Operator overloading method
    bool operator<(const Task& other) const {
        return priority < other.priority;  // For max-heap (highest priority on top)
    }
};

// Alternative approach: Custom comparator class
struct TaskComparator {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority < b.priority;  // For max-heap
    }
};

int main() {
    // Method 1: Using operator overloading
    priority_queue<Task> taskQueue;
    
    // Add tasks
    taskQueue.push(Task("Read emails", 10));
    taskQueue.push(Task("Write report", 50));
    taskQueue.push(Task("Meet client", 100));
    taskQueue.push(Task("Coffee break", 5));
    
    cout << "Processing tasks (using operator overloading):" << endl;
    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.top();
        cout << "Processing: " << currentTask.name << " (Priority: " << currentTask.priority << ")" << endl;
        taskQueue.pop();
    }
    
    // Method 2: Using custom comparator
    priority_queue<Task, vector<Task>, TaskComparator> taskQueue2;
    
    // Add tasks
    taskQueue2.push(Task("Read emails", 10));
    taskQueue2.push(Task("Write report", 50));
    taskQueue2.push(Task("Meet client", 100));
    taskQueue2.push(Task("Coffee break", 5));
    
    cout << "\nProcessing tasks (using custom comparator):" << endl;
    while (!taskQueue2.empty()) {
        Task currentTask = taskQueue2.top();
        cout << "Processing: " << currentTask.name << " (Priority: " << currentTask.priority << ")" << endl;
        taskQueue2.pop();
    }
    
    // Method 3: Lambda function as comparator (C++11)
    auto cmp = [](const Task& a, const Task& b) { 
        return a.priority < b.priority;  // For max-heap
    };
    priority_queue<Task, vector<Task>, decltype(cmp)> taskQueue3(cmp);
    
    // Add tasks
    taskQueue3.push(Task("Read emails", 10));
    taskQueue3.push(Task("Write report", 50));
    taskQueue3.push(Task("Meet client", 100));
    taskQueue3.push(Task("Coffee break", 5));
    
    cout << "\nProcessing tasks (using lambda comparator):" << endl;
    while (!taskQueue3.empty()) {
        Task currentTask = taskQueue3.top();
        cout << "Processing: " << currentTask.name << " (Priority: " << currentTask.priority << ")" << endl;
        taskQueue3.pop();
    }
    
    return 0;
}
```

### Real-World Priority Queue Applications

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Example 1: Emergency Room Triage System
class Patient {
private:
    string name;
    int severity;  // 1-10, 10 being most severe
    time_t arrivalTime;
    
public:
    Patient(const string& n, int sev) 
        : name(n), severity(sev), arrivalTime(time(nullptr)) {}
    
    string getName() const { return name; }
    int getSeverity() const { return severity; }
    time_t getArrivalTime() const { return arrivalTime; }
    
    // For display
    string getTimeString() const {
        char buffer[26];
        struct tm* timeinfo = localtime(&arrivalTime);
        strftime(buffer, 26, "%H:%M:%S", timeinfo);
        return string(buffer);
    }
};

// Comparator for patients - higher severity first, then earlier arrival
struct PatientComparator {
    bool operator()(const Patient& a, const Patient& b) const {
        if (a.getSeverity() != b.getSeverity()) {
            return a.getSeverity() < b.getSeverity();  // Higher severity first
        }
        return a.getArrivalTime() > b.getArrivalTime();  // Earlier arrival time for equal severity
    }
};

// Example 2: Dijkstra's Algorithm
class Graph {
private:
    int V;  // Number of vertices
    vector<vector<pair<int, int>>> adj;  // Adjacency list: (vertex, weight)
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));  // For undirected graph
    }
    
    // Dijkstra's algorithm using priority queue
    void shortestPath(int src) {
        // Min-heap priority queue
        // Pair: (distance, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance array
        vector<int> dist(V, INT_MAX);
        
        // Insert source with distance 0
        pq.push(make_pair(0, src));
        dist[src] = 0;
        
        cout << "Dijkstra's Algorithm from vertex " << src << ":" << endl;
        
        while (!pq.empty()) {
            // Extract minimum distance vertex
            int u = pq.top().second;
            pq.pop();
            
            // Visit all adjacent vertices
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                // If there's a shorter path to v through u
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        
        // Print shortest distances
        cout << "Shortest distances from source:" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }
};

int main() {
    // Example 1: Emergency Room Triage
    priority_queue<Patient, vector<Patient>, PatientComparator> emergencyRoom;
    
    emergencyRoom.push(Patient("John Doe", 3));
    this_thread::sleep_for(chrono::seconds(1));
    emergencyRoom.push(Patient("Jane Smith", 8));  // Higher priority
    this_thread::sleep_for(chrono::seconds(1));
    emergencyRoom.push(Patient("Bob Johnson", 2));
    this_thread::sleep_for(chrono::seconds(1));
    emergencyRoom.push(Patient("Alice Brown", 8));  // Same priority as Jane, but later arrival
    this_thread::sleep_for(chrono::seconds(1));
    emergencyRoom.push(Patient("Charlie Davis", 10));  // Highest priority
    
    cout << "Emergency Room - Treating patients in priority order:" << endl;
    while (!emergencyRoom.empty()) {
        const Patient& patient = emergencyRoom.top();
        cout << "Treating: " << patient.getName() 
             << " (Severity: " << patient.getSeverity() 
             << ", Arrived: " << patient.getTimeString() << ")" << endl;
        emergencyRoom.pop();
    }
    
    // Example 2: Dijkstra's Algorithm
    cout << "\nDijkstra's Algorithm Example:" << endl;
    Graph g(6);  // Graph with 6 vertices
    
    // Adding edges (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    g.shortestPath(0);  // Find shortest paths from vertex 0
    
    return 0;
}
```

### When to Use Priority Queue

- When you need to process elements based on priority rather than arrival order
- For algorithms like Dijkstra's shortest path, Prim's MST, Huffman coding, etc.
- For scheduling systems (e.g., process schedulers, task management)
- For simulations where events need to be processed in order of importance
- For implementing a dynamic median finder

## 8.2.7 Set & Multiset

`std::set` and `std::multiset` are associative containers that store elements in a sorted order. The main difference is that `set` contains only unique elements, while `multiset` allows duplicates.

### Key Features

#### Common Features
- **Ordered**: Elements are always sorted according to a comparison function
- **Tree-Based**: Typically implemented as a Red-Black Tree (a type of self-balancing binary search tree)
- **No Direct Element Modification**: Elements are const once inserted (to maintain order)
- **Logarithmic Operations**: Most operations are O(log n)

#### Set-Specific Features
- **Unique Elements**: No duplicates allowed
- **Key is Value**: The element value itself is the key

#### Multiset-Specific Features
- **Allows Duplicates**: The same value can appear multiple times
- **Consistent Ordering**: Equal elements appear in the order they were inserted

### Basic Set Operations

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    // Create a set of integers
    set<int> numbers;
    
    // Insert elements
    numbers.insert(30);
    numbers.insert(10);
    numbers.insert(50);
    numbers.insert(20);
    numbers.insert(10);  // Duplicate, will be ignored
    
    // Display set size
    cout << "Set size: " << numbers.size() << endl;
    
    // Check if an element exists
    if (numbers.find(20) != numbers.end()) {
        cout << "20 is in the set" << endl;
    }
    
    if (numbers.count(25) > 0) {  // Another way to check
        cout << "25 is in the set" << endl;
    } else {
        cout << "25 is not in the set" << endl;
    }
    
    // Iterate through the set (will be in sorted order)
    cout << "Set elements: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Remove elements
    numbers.erase(20);
    
    // Check if removal was successful
    if (numbers.find(20) == numbers.end()) {
        cout << "20 is no longer in the set" << endl;
    }
    
    // Different ways to insert
    auto result = numbers.insert(40);
    if (result.second) {
        cout << "40 was inserted successfully" << endl;
    }
    
    numbers.insert({5, 15, 25});  // Insert multiple elements (C++11)
    
    // Set operations with iterators
    auto it = numbers.begin();
    advance(it, 2);  // Move iterator forward by 2 positions
    
    cout << "Third element in sorted set: " << *it << endl;
    
    cout << "Final set: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Multiset Operations

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    // Create a multiset of integers
    multiset<int> numbers;
    
    // Insert elements
    numbers.insert(30);
    numbers.insert(10);
    numbers.insert(50);
    numbers.insert(20);
    numbers.insert(10);  // Duplicate allowed in multiset
    numbers.insert(10);  // Another duplicate
    
    // Display multiset size
    cout << "Multiset size: " << numbers.size() << endl;
    
    // Count occurrences of an element
    cout << "Count of 10: " << numbers.count(10) << endl;
    
    // Iterate through the multiset (will be in sorted order)
    cout << "Multiset elements: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Find elements
    auto range = numbers.equal_range(10);  // Get range of elements equal to 10
    cout << "Elements equal to 10: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Erase elements
    int eraseCount = numbers.erase(10);  // Erase all elements with value 10
    cout << "Erased " << eraseCount << " occurrences of 10" << endl;
    
    // Erase a single element
    auto it = numbers.find(30);
    if (it != numbers.end()) {
        numbers.erase(it);  // Erase just one occurrence
    }
    
    cout << "Multiset after erasing: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Custom Comparators

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

// Custom comparison function for strings (case insensitive)
struct CaseInsensitiveCompare {
    bool operator()(const string& a, const string& b) const {
        // Convert to lowercase for comparison
        string aLower = a;
        string bLower = b;
        transform(aLower.begin(), aLower.end(), aLower.begin(), ::tolower);
        transform(bLower.begin(), bLower.end(), bLower.begin(), ::tolower);
        return aLower < bLower;
    }
};

// Custom struct with custom comparison
struct Person {
    string name;
    int age;
    
    Person(const string& n, int a) : name(n), age(a) {}
    
    // For displaying
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.name << " (" << p.age << ")";
    }
};

// Compare persons by age
struct CompareByAge {
    bool operator()(const Person& a, const Person& b) const {
        return a.age < b.age;
    }
};

int main() {
    // Set with custom comparator
    set<string, CaseInsensitiveCompare> names;
    
    names.insert("Apple");
    names.insert("banana");
    names.insert("Cherry");
    names.insert("apple");  // Will be considered duplicate of "Apple"
    
    cout << "Names set size: " << names.size() << endl;
    cout << "Names set elements: ";
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    // Set of custom objects with custom comparison
    set<Person, CompareByAge> people;
    
    people.insert(Person("Alice", 30));
    people.insert(Person("Bob", 25));
    people.insert(Person("Charlie", 40));
    people.insert(Person("David", 25));  // Same age as Bob, both will be included
    
    cout << "\nPeople sorted by age: " << endl;
    for (const auto& person : people) {
        cout << "  " << person << endl;
    }
    
    // Using a lambda as comparator (C++14 and later)
    auto nameLengthComp = [](const string& a, const string& b) {
        return a.length() < b.length() || (a.length() == b.length() && a < b);
    };
    
    set<string, decltype(nameLengthComp)> namesByLength(nameLengthComp);
    
    namesByLength.insert("Apple");
    namesByLength.insert("Banana");
    namesByLength.insert("Cat");
    namesByLength.insert("Dog");
    namesByLength.insert("Elephant");
    
    cout << "\nNames sorted by length: ";
    for (const auto& name : namesByLength) {
        cout << name << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Set Operations (Union, Intersection, Difference)

```cpp
#include <iostream>
#include <set>
#include <algorithm>  // For set_intersection, set_union, set_difference
#include <vector>
using namespace std;

// Helper function to print any container
template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << name << ": ";
    for (const auto& item : c) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    // Create sets
    set<int> set1 = {1, 2, 3, 5, 7, 9};
    set<int> set2 = {2, 4, 5, 6, 8};
    
    printContainer(set1, "Set 1");
    printContainer(set2, "Set 2");
    
    // Union: Elements in either set1 or set2
    vector<int> unionSet;
    set_union(set1.begin(), set1.end(), 
              set2.begin(), set2.end(),
              back_inserter(unionSet));
    
    printContainer(unionSet, "Union");
    
    // Intersection: Elements in both set1 and set2
    vector<int> intersectionSet;
    set_intersection(set1.begin(), set1.end(),
                     set2.begin(), set2.end(),
                     back_inserter(intersectionSet));
    
    printContainer(intersectionSet, "Intersection");
    
    // Difference: Elements in set1 but not in set2
    vector<int> differenceSet;
    set_difference(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   back_inserter(differenceSet));
    
    printContainer(differenceSet, "Set1 - Set2");
    
    // Symmetric difference: Elements in either set but not in both
    vector<int> symmetricDiff;
    set_symmetric_difference(set1.begin(), set1.end(),
                            set2.begin(), set2.end(),
                            back_inserter(symmetricDiff));
    
    printContainer(symmetricDiff, "Symmetric Difference");
    
    // You can also do these operations manually
    set<int> manualUnion;
    manualUnion.insert(set1.begin(), set1.end());
    manualUnion.insert(set2.begin(), set2.end());
    
    printContainer(manualUnion, "Manual Union");
    
    return 0;
}
```

### Real-World Applications of Set and Multiset

```cpp
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

// Example 1: Word uniqueness checker
void uniqueWordsChecker(const string& text) {
    // Split text into words
    vector<string> words;
    string word;
    for (char c : text) {
        if (isalpha(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    
    // Use a set to find unique words
    set<string> uniqueWords;
    multiset<string> allWords;
    
    for (const auto& w : words) {
        uniqueWords.insert(w);
        allWords.insert(w);
    }
    
    cout << "Text analysis:" << endl;
    cout << "Total word count: " << words.size() << endl;
    cout << "Unique word count: " << uniqueWords.size() << endl;
    
    // Find duplicate words
    cout << "\nWords that appear more than once:" << endl;
    for (const auto& w : uniqueWords) {
        int count = allWords.count(w);
        if (count > 1) {
            cout << "  \"" << w << "\" appears " << count << " times" << endl;
        }
    }
}

// Example 2: Room scheduling system
class TimeSlot {
private:
    int startHour;   // 0-23
    int endHour;     // 0-23
    
public:
    TimeSlot(int start, int end) : startHour(start), endHour(end) {}
    
    int getStart() const { return startHour; }
    int getEnd() const { return endHour; }
    
    bool operator<(const TimeSlot& other) const {
        return startHour < other.startHour;
    }
    
    friend ostream& operator<<(ostream& os, const TimeSlot& ts) {
        return os << ts.startHour << ":00-" << ts.endHour << ":00";
    }
};

class RoomScheduler {
private:
    set<TimeSlot> bookedTimeSlots;
    
public:
    bool bookRoom(int startHour, int endHour) {
        if (startHour >= endHour || startHour < 0 || endHour > 24) {
            cout << "Invalid time slot" << endl;
            return false;
        }
        
        TimeSlot newSlot(startHour, endHour);
        
        // Check for conflicts
        for (const auto& slot : bookedTimeSlots) {
            if (!(endHour <= slot.getStart() || startHour >= slot.getEnd())) {
                cout << "Conflict with existing booking: " << slot << endl;
                return false;
            }
        }
        
        // No conflicts, book the room
        bookedTimeSlots.insert(newSlot);
        cout << "Room booked for " << newSlot << endl;
        return true;
    }
    
    void displaySchedule() {
        if (bookedTimeSlots.empty()) {
            cout << "No bookings yet" << endl;
            return;
        }
        
        cout << "Current room schedule:" << endl;
        for (const auto& slot : bookedTimeSlots) {
            cout << "  " << slot << endl;
        }
    }
    
    vector<TimeSlot> getAvailableSlots(int minDuration) {
        vector<TimeSlot> availableSlots;
        
        // Start with full day availability
        vector<TimeSlot> freeTime;
        
        if (bookedTimeSlots.empty()) {
            freeTime.push_back(TimeSlot(0, 24));
        } else {
            // Add start of day to first booking
            auto firstBooking = bookedTimeSlots.begin();
            if (firstBooking->getStart() > 0) {
                freeTime.push_back(TimeSlot(0, firstBooking->getStart()));
            }
            
            // Add gaps between bookings
            auto it = bookedTimeSlots.begin();
            auto nextIt = it;
            ++nextIt;
            
            while (nextIt != bookedTimeSlots.end()) {
                if (nextIt->getStart() > it->getEnd()) {
                    freeTime.push_back(TimeSlot(it->getEnd(), nextIt->getStart()));
                }
                it = nextIt;
                ++nextIt;
            }
            
            // Add end of last booking to end of day
            auto lastBooking = --bookedTimeSlots.end();
            if (lastBooking->getEnd() < 24) {
                freeTime.push_back(TimeSlot(lastBooking->getEnd(), 24));
            }
        }
        
        // Filter by minimum duration
        for (const auto& slot : freeTime) {
            if (slot.getEnd() - slot.getStart() >= minDuration) {
                availableSlots.push_back(slot);
            }
        }
        
        return availableSlots;
    }
};

int main() {
    // Example 1: Word uniqueness checker
    string text = "The quick brown fox jumps over the lazy dog. The dog was not amused.";
    uniqueWordsChecker(text);
    
    // Example 2: Room scheduling system
    cout << "\nRoom Scheduling Example:" << endl;
    RoomScheduler scheduler;
    
    scheduler.bookRoom(9, 10);   // 9:00-10:00
    scheduler.bookRoom(11, 13);  // 11:00-13:00
    scheduler.bookRoom(14, 16);  // 14:00-16:00
    
    // Try to book a conflicting slot
    scheduler.bookRoom(12, 14);  // Conflicts with 11:00-13:00
    
    // Display schedule
    scheduler.displaySchedule();
    
    // Get available slots with minimum duration 2 hours
    cout << "\nAvailable slots (2+ hours duration):" << endl;
    auto availableSlots = scheduler.getAvailableSlots(2);
    for (const auto& slot : availableSlots) {
        cout << "  " << slot << endl;
    }
    
    return 0;
}
```

### When to Use Set and Multiset

**Use Set When:**
- You need to maintain a collection of unique elements in sorted order
- You frequently check for element existence
- You need to iterate through elements in sorted order
- Set operations like union, intersection, or difference are needed

**Use Multiset When:**
- You need to maintain a sorted collection that allows duplicates
- You need to count occurrences of elements
- You want to maintain insertion order for equal elements

## 8.2.8 Map & Multimap

`std::map` and `std::multimap` are associative containers that store key-value pairs in a sorted order according to the key. Like with set/multiset, the main difference is that `map` contains unique keys, while `multimap` allows duplicate keys.

### Key Features

#### Common Features
- **Key-Value Storage**: Each element is a pair of key and value
- **Ordered by Key**: Elements are sorted by key using a comparison function
- **Tree-Based**: Typically implemented as a Red-Black Tree
- **Logarithmic Operations**: Most operations are O(log n)

#### Map-Specific Features
- **Unique Keys**: Each key can only appear once
- **Direct Value Access**: Values can be accessed using `operator[]` with the key

#### Multimap-Specific Features
- **Allows Duplicate Keys**: Multiple values can be associated with the same key
- **No `operator[]`**: Since keys aren't unique, direct access via `operator[]` isn't provided

### Basic Map Operations

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Create a map (string keys, int values)
    map<string, int> ages;
    
    // Insert elements (multiple ways)
    ages["Alice"] = 30;                            // Using operator[]
    ages.insert(pair<string, int>("Bob", 25));     // Using insert() with pair
    ages.insert(make_pair("Charlie", 35));         // Using make_pair
    ages.insert({"David", 28});                    // Using initializer list (C++11)
    
    // Display map size
    cout << "Map size: " << ages.size() << endl;
    
    // Access elements
    cout << "Alice's age: " << ages["Alice"] << endl;
    cout << "Bob's age: " << ages.at("Bob") << endl;  // at() throws exception if key not found
    
    // Checking if a key exists
    if (ages.find("Eve") != ages.end()) {
        cout << "Eve's age: " << ages["Eve"] << endl;
    } else {
        cout << "Eve is not in the map" << endl;
    }
    
    // Using operator[] with a new key inserts a default-constructed value
    cout << "Eve's age (default): " << ages["Eve"] << endl;  // Creates entry with value 0
    cout << "Map size after accessing Eve: " << ages.size() << endl;
    
    // Iterate through the map (will be in sorted order by key)
    cout << "\nAll entries:" << endl;
    for (const auto& entry : ages) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    // Update a value
    ages["Alice"] = 31;
    
    // Another way to insert/update
    ages.insert_or_assign("Frank", 45);  // C++17
    
    // Erase an entry
    ages.erase("Eve");
    
    // Check if removal was successful
    if (ages.find("Eve") == ages.end()) {
        cout << "\nEve was removed from the map" << endl;
    }
    
    // Another way to iterate
    cout << "\nAll entries after modifications:" << endl;
    for (auto it = ages.begin(); it != ages.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    
    return 0;
}
```

### Multimap Operations

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Create a multimap (string keys, int values)
    multimap<string, int> scores;
    
    // Insert elements
    scores.insert(make_pair("Alice", 85));
    scores.insert(make_pair("Bob", 92));
    scores.insert(make_pair("Charlie", 78));
    scores.insert(make_pair("Alice", 90));  // Duplicate key
    scores.insert(make_pair("Alice", 88));  // Another duplicate
    
    // Display multimap size
    cout << "Multimap size: " << scores.size() << endl;
    
    // Count entries with a specific key
    cout << "Alice's entry count: " << scores.count("Alice") << endl;
    
    // Find entries with a specific key
    cout << "\nAlice's scores:" << endl;
    auto range = scores.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    
    // Iterate through all entries
    cout << "\nAll scores:" << endl;
    for (const auto& entry : scores) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    // Erase entries with a specific key
    int removed = scores.erase("Alice");  // Removes all entries with key "Alice"
    cout << "\nRemoved " << removed << " entries for Alice" << endl;
    
    // Erase a single entry
    auto it = scores.find("Bob");
    if (it != scores.end()) {
        scores.erase(it);  // Erase just this entry
        cout << "Removed one entry for Bob" << endl;
    }
    
    // Check remaining entries
    cout << "\nRemaining entries:" << endl;
    for (const auto& entry : scores) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    return 0;
}
```

### Maps with Custom Keys

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

// Custom key type
struct Person {
    string firstName;
    string lastName;
    
    Person(const string& first, const string& last) 
        : firstName(first), lastName(last) {}
    
    // Required for map: operator< for comparison
    bool operator<(const Person& other) const {
        // Sort by last name, then first name
        if (lastName != other.lastName) {
            return lastName < other.lastName;
        }
        return firstName < other.firstName;
    }
    
    // For display
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.firstName << " " << p.lastName;
    }
};

// Custom comparator approach
struct CaseInsensitiveCompare {
    bool operator()(const string& a, const string& b) const {
        string aLower = a;
        string bLower = b;
        transform(aLower.begin(), aLower.end(), aLower.begin(), ::tolower);
        transform(bLower.begin(), bLower.end(), bLower.begin(), ::tolower);
        return aLower < bLower;
    }
};

int main() {
    // Map with custom key type
    map<Person, string> phoneBook;
    
    // Insert entries
    phoneBook[Person("John", "Doe")] = "555-1234";
    phoneBook[Person("Jane", "Doe")] = "555-2345";
    phoneBook[Person("John", "Smith")] = "555-3456";
    
    // Display entries (sorted by last name, then first name)
    cout << "Phone book entries:" << endl;
    for (const auto& entry : phoneBook) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    // Map with custom comparator
    map<string, int, CaseInsensitiveCompare> caseInsensitiveMap;
    
    caseInsensitiveMap["Apple"] = 1;
    caseInsensitiveMap["banana"] = 2;
    caseInsensitiveMap["Cherry"] = 3;
    
    // "apple" is treated as the same key as "Apple" due to case-insensitive comparison
    caseInsensitiveMap["apple"] = 4;  // This will update the value for "Apple"
    
    cout << "\nCase-insensitive map:" << endl;
    for (const auto& entry : caseInsensitiveMap) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    return 0;
}
```

### Real-World Applications of Map and Multimap

```cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Example 1: Word frequency counter
map<string, int> countWordFrequency(const string& text) {
    map<string, int> frequency;
    
    istringstream iss(text);
    string word;
    
    while (iss >> word) {
        // Remove punctuation
        word.erase(remove_if(word.begin(), word.end(), 
                           [](char c) { return !isalpha(c); }),
                 word.end());
        
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        // Count only non-empty words
        if (!word.empty()) {
            frequency[word]++;
        }
    }
    
    return frequency;
}

// Example 2: Student grade tracker
class GradeTracker {
private:
    // Map: student name -> map of subject -> grades
    map<string, map<string, vector<int>>> studentGrades;
    
public:
    // Add a grade for a student in a subject
    void addGrade(const string& student, const string& subject, int grade) {
        studentGrades[student][subject].push_back(grade);
    }
    
    // Get average grade for a student in a subject
    double getAverage(const string& student, const string& subject) {
        if (studentGrades.find(student) == studentGrades.end() ||
            studentGrades[student].find(subject) == studentGrades[student].end() ||
            studentGrades[student][subject].empty()) {
            return 0.0;
        }
        
        const vector<int>& grades = studentGrades[student][subject];
        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        
        return static_cast<double>(sum) / grades.size();
    }
    
    // Get overall average for a student
    double getOverallAverage(const string& student) {
        if (studentGrades.find(student) == studentGrades.end()) {
            return 0.0;
        }
        
        int totalSum = 0;
        int totalCount = 0;
        
        for (const auto& subjectPair : studentGrades[student]) {
            for (int grade : subjectPair.second) {
                totalSum += grade;
                totalCount++;
            }
        }
        
        return totalCount > 0 ? static_cast<double>(totalSum) / totalCount : 0.0;
    }
    
    // Display all grades
    void displayAllGrades() {
        for (const auto& studentPair : studentGrades) {
            cout << "Student: " << studentPair.first << endl;
            
            for (const auto& subjectPair : studentPair.second) {
                cout << "  Subject: " << subjectPair.first << ", Grades: ";
                
                for (int grade : subjectPair.second) {
                    cout << grade << " ";
                }
                
                cout << "(Avg: " << getAverage(studentPair.first, subjectPair.first) << ")" << endl;
            }
            
            cout << "  Overall Average: " << getOverallAverage(studentPair.first) << endl;
        }
    }
};

// Example 3: Movie database with multimap
class MovieDatabase {
private:
    // Multimap: genre -> movie title
    multimap<string, string> moviesByGenre;
    
    // Map: movie title -> year
    map<string, int> movieYears;
    
public:
    // Add a movie to the database
    void addMovie(const string& title, int year, const vector<string>& genres) {
        movieYears[title] = year;
        
        for (const string& genre : genres) {
            moviesByGenre.insert({genre, title});
        }
    }
    
    // Find movies by genre
    vector<pair<string, int>> findMoviesByGenre(const string& genre) {
        vector<pair<string, int>> result;
        
        auto range = moviesByGenre.equal_range(genre);
        for (auto it = range.first; it != range.second; ++it) {
            const string& title = it->second;
            int year = movieYears[title];
            result.push_back({title, year});
        }
        
        return result;
    }
    
    // Display all genres and their movies
    void displayByGenre() {
        string currentGenre;
        
        for (const auto& entry : moviesByGenre) {
            if (entry.first != currentGenre) {
                currentGenre = entry.first;
                cout << "\nGenre: " << currentGenre << endl;
            }
            
            cout << "  " << entry.second << " (" << movieYears[entry.second] << ")" << endl;
        }
    }
    
    // Count movies per genre
    map<string, int> countByGenre() {
        map<string, int> counts;
        
        for (const auto& entry : moviesByGenre) {
            counts[entry.first]++;
        }
        
        return counts;
    }
};

int main() {
    // Example 1: Word frequency counter
    string text = "The quick brown fox jumps over the lazy dog. The dog was not amused. Quick thinking saved the day.";
    
    map<string, int> wordFreq = countWordFrequency(text);
    
    cout << "Word Frequency:" << endl;
    for (const auto& entry : wordFreq) {
        cout << entry.first << ": " << entry.second << endl;
    }
    
    // Example 2: Student grade tracker
    cout << "\nGrade Tracker Example:" << endl;
    GradeTracker tracker;
    
    tracker.addGrade("Alice", "Math", 95);
    tracker.addGrade("Alice", "Math", 88);
    tracker.addGrade("Alice", "English", 92);
    tracker.addGrade("Bob", "Math", 78);
    tracker.addGrade("Bob", "Physics", 85);
    tracker.addGrade("Bob", "Physics", 90);
    
    tracker.displayAllGrades();
    
    // Example 3: Movie database
    cout << "\nMovie Database Example:" << endl;
    MovieDatabase movieDB;
    
    movieDB.addMovie("The Shawshank Redemption", 1994, {"Drama"});
    movieDB.addMovie("The Godfather", 1972, {"Crime", "Drama"});
    movieDB.addMovie("Pulp Fiction", 1994, {"Crime", "Drama"});
    movieDB.addMovie("The Dark Knight", 2008, {"Action", "Crime", "Drama"});
    movieDB.addMovie("Inception", 2010, {"Action", "Sci-Fi", "Thriller"});
    
    cout << "Movies by genre:" << endl;
    movieDB.displayByGenre();
    
    cout << "\nMovies in Drama genre:" << endl;
    auto dramaMovies = movieDB.findMoviesByGenre("Drama");
    for (const auto& movie : dramaMovies) {
        cout << "  " << movie.first << " (" << movie.second << ")" << endl;
    }
    
    cout << "\nMovie counts by genre:" << endl;
    auto genreCounts = movieDB.countByGenre();
    for (const auto& entry : genreCounts) {
        cout << "  " << entry.first << ": " << entry.second << " movies" << endl;
    }
    
    return 0;
}
```

### When to Use Map and Multimap

**Use Map When:**
- You need to associate values with unique keys
- You need fast key-based lookups
- You need to maintain a sorted collection of key-value pairs
- You need to update values associated with keys

**Use Multimap When:**
- You need to associate multiple values with the same key
- You need to maintain key-value pairs in sorted order
- You need to find all values associated with a specific key
- You're implementing a dictionary with multiple definitions per word

### Performance Considerations

1. **Memory Overhead**: Maps and sets use more memory than unordered versions due to tree structure
2. **Insertion/Deletion/Lookup**: O(log n) complexity for map, set, multimap, multiset
3. **Iteration**: Very efficient, proportional to the number of elements

### Choosing Between Container Types

| Need | Recommended Container |
|------|----------------------|
| Fast lookup by key with unique keys | unordered_map (if order doesn't matter), map (if order matters) |
| Fast lookup by key with duplicate keys | unordered_multimap (if order doesn't matter), multimap (if order matters) |
| Collection of unique items | unordered_set (if order doesn't matter), set (if order matters) |
| Collection with duplicates | unordered_multiset (if order doesn't matter), multiset (if order matters) |
| Fast insertions/deletions at both ends | deque |
| Fast random access and dynamic size | vector |
| Fast insertions/deletions anywhere | list |
