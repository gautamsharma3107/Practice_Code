# Basic Data Structures

This document provides a comprehensive overview of fundamental data structures essential for programming and algorithmic problem-solving. Each section includes detailed explanations, C++ implementation examples, time complexity analysis, and practice problems.

## 1. Arrays

### Definition
An array is a collection of elements stored at contiguous memory locations, identified by index or key. Arrays are among the oldest and most important data structures and are used as the building blocks for many other data structures.

### Characteristics
- **Fixed size**: Size must be declared at compile time in many languages (C, C++)
- **Homogeneous elements**: All elements must be of the same data type
- **Random access**: Elements can be accessed directly using indices (O(1) time)
- **Memory efficiency**: Low overhead as only the data is stored

### Time Complexity
- **Access**: O(1)
- **Search**: O(n) for linear search, O(log n) for binary search (if sorted)
- **Insertion/Deletion**: O(n) (requires shifting elements)

### C++ Implementation
```cpp
#include <iostream>
using namespace std;

int main() {
    // Declaration and initialization
    int arr1[5];                     // Declaration
    int arr2[5] = {1, 2, 3, 4, 5};   // Declaration with initialization
    
    // Accessing elements
    cout << "Third element: " << arr2[2] << endl;  // Output: 3
    
    // Modifying elements
    arr2[2] = 10;
    cout << "Modified third element: " << arr2[2] << endl;  // Output: 10
    
    // Traversal
    cout << "Array elements: ";
    for(int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    // Multi-dimensional array
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    // Accessing elements in multi-dimensional array
    cout << "Element at matrix[1][2]: " << matrix[1][2] << endl;  // Output: 6
    
    return 0;
}
```

### Problem Exercises
- [Array Rotation](https://leetcode.com/problems/rotate-array/)
- [Find the Missing Number](https://leetcode.com/problems/missing-number/)
- [Two Sum](https://leetcode.com/problems/two-sum/)
- [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
- [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

## 2. Dynamic Arrays

### Definition
Dynamic arrays are arrays that can grow or shrink in size during runtime. Unlike static arrays, dynamic arrays automatically resize themselves when elements are added or removed.

### Characteristics
- **Resizable**: Can grow or shrink as needed
- **Efficient append**: Most operations are amortized O(1)
- **Dynamic memory allocation**: Uses heap memory
- **May store heterogeneous elements** (in languages like Python)

### Time Complexity
- **Access**: O(1)
- **Search**: O(n)
- **Append**: Amortized O(1)
- **Insert/Delete**: O(n) at arbitrary position

### C++ Implementation (using std::vector)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Declaration
    vector<int> vec;
    
    // Adding elements
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    // Size and capacity
    cout << "Size: " << vec.size() << endl;       // Output: 3
    cout << "Capacity: " << vec.capacity() << endl;
    
    // Accessing elements
    cout << "First element: " << vec[0] << endl;          // Output: 1
    cout << "Second element: " << vec.at(1) << endl;      // Output: 2 (with bounds checking)
    
    // Iteration
    cout << "Vector elements: ";
    for(int i : vec) {
        cout << i << " ";
    }
    cout << endl;
    
    // Inserting at arbitrary position
    vec.insert(vec.begin() + 1, 10);  // Insert 10 at index 1
    
    // Updated vector
    cout << "Updated vector: ";
    for(int i : vec) {
        cout << i << " ";
    }
    cout << endl;  // Output: 1 10 2 3
    
    // Removing elements
    vec.pop_back();  // Remove last element
    vec.erase(vec.begin() + 1);  // Remove element at index 1
    
    // Final vector
    cout << "Final vector: ";
    for(int i : vec) {
        cout << i << " ";
    }
    cout << endl;  // Output: 1 2
    
    return 0;
}
```

### Custom Implementation
```cpp
#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;
    int capacity;
    int size;
    
    void resize() {
        capacity *= 2;
        int* temp = new int[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

public:
    DynamicArray() {
        capacity = 2;
        size = 0;
        arr = new int[capacity];
    }
    
    ~DynamicArray() {
        delete[] arr;
    }
    
    void push_back(int val) {
        if(size == capacity) {
            resize();
        }
        arr[size++] = val;
    }
    
    int get(int index) {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }
    
    int getSize() {
        return size;
    }
    
    int getCapacity() {
        return capacity;
    }
};

int main() {
    DynamicArray dynArr;
    dynArr.push_back(1);
    dynArr.push_back(2);
    dynArr.push_back(3);
    
    cout << "Size: " << dynArr.getSize() << endl;
    cout << "Capacity: " << dynArr.getCapacity() << endl;
    cout << "Element at index 1: " << dynArr.get(1) << endl;
    
    return 0;
}
```

### Problem Exercises
- [Implement Dynamic Array](https://leetcode.com/problems/design-dynamic-array/)
- [Find the Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)
- [Merge Intervals](https://leetcode.com/problems/merge-intervals/)
- [Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

## 3. Strings

### Definition
A string is a sequence of characters that represents text. In C++, strings can be represented using character arrays or the `std::string` class from the standard library.

### Characteristics
- **Sequence of characters**: Stored contiguously in memory
- **Immutable in some languages**: Cannot be modified after creation (e.g., Java, Python)
- **Mutable in others**: Can be modified (e.g., C++ with `std::string`)
- **Special operations**: Concatenation, substring extraction, comparison

### Time Complexity
- **Access**: O(1)
- **Search**: O(n) for linear search, O(n+m) for pattern matching (KMP, Boyer-Moore)
- **Concatenation**: O(n) or O(n+m)
- **Substring**: O(k) where k is substring length

### C++ Implementation
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declaration and initialization
    string str1 = "Hello";
    string str2 = "World";
    
    // Concatenation
    string str3 = str1 + " " + str2;
    cout << "Concatenated string: " << str3 << endl;  // Output: Hello World
    
    // Length of string
    cout << "Length of str3: " << str3.length() << endl;  // Output: 11
    
    // Accessing characters
    cout << "First character: " << str3[0] << endl;  // Output: H
    cout << "Last character: " << str3[str3.length()-1] << endl;  // Output: d
    
    // Substring
    string substr = str3.substr(0, 5);
    cout << "Substring: " << substr << endl;  // Output: Hello
    
    // Finding in string
    size_t pos = str3.find("World");
    if(pos != string::npos) {
        cout << "'World' found at position: " << pos << endl;  // Output: 6
    }
    
    // Compare strings
    if(str1 == "Hello") {
        cout << "Strings are equal" << endl;
    }
    
    // String modification
    str1[0] = 'J';  // Change 'H' to 'J'
    cout << "Modified str1: " << str1 << endl;  // Output: Jello
    
    // Insert and erase
    str1.insert(1, "a");
    cout << "After insert: " << str1 << endl;  // Output: Jaello
    
    str1.erase(1, 1);
    cout << "After erase: " << str1 << endl;  // Output: Jello
    
    // Character arrays (C-style strings)
    char cstr[] = "C-style string";
    cout << "C-style string: " << cstr << endl;
    
    return 0;
}
```

### Common String Algorithms
```cpp
#include <iostream>
#include <string>
using namespace std;

// Check if a string is palindrome
bool isPalindrome(const string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while(left < right) {
        if(s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Reverse a string
string reverseString(const string& s) {
    string result = s;
    int left = 0;
    int right = s.length() - 1;
    
    while(left < right) {
        swap(result[left], result[right]);
        left++;
        right--;
    }
    return result;
}

int main() {
    string s1 = "radar";
    string s2 = "hello";
    
    cout << s1 << " is palindrome: " << (isPalindrome(s1) ? "Yes" : "No") << endl;
    cout << s2 << " is palindrome: " << (isPalindrome(s2) ? "Yes" : "No") << endl;
    
    cout << "Reverse of " << s2 << ": " << reverseString(s2) << endl;
    
    return 0;
}
```

### Problem Exercises
- [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- [Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
- [String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/)
- [Implement strStr()](https://leetcode.com/problems/implement-strstr/)

## 4. Linked Lists

### Definition
A linked list is a linear data structure where elements are stored in nodes, and each node points to the next node in the sequence. Unlike arrays, linked lists do not store elements in contiguous memory locations.

### Types
- **Singly Linked List**: Each node points to the next node
- **Doubly Linked List**: Each node points to both the next and previous nodes
- **Circular Linked List**: Last node points back to the first node

### Characteristics
- **Dynamic size**: Can grow or shrink during execution
- **Efficient insertion/deletion**: O(1) time if position is known
- **No random access**: Must traverse from beginning
- **More memory usage**: Stores both data and pointers

### Time Complexity
- **Access**: O(n)
- **Search**: O(n)
- **Insertion/Deletion**: O(1) at known position, O(n) if position needs to be found

### C++ Implementation - Singly Linked List
```cpp
#include <iostream>
using namespace std;

// Node structure for singly linked list
struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    
public:
    // Constructor
    LinkedList() : head(nullptr) {}
    
    // Destructor
    ~LinkedList() {
        Node* current = head;
        while(current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        if (!head) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    // Insert after a specific node
    void insertAfter(Node* prevNode, int value) {
        if (!prevNode) {
            cout << "Previous node cannot be null" << endl;
            return;
        }
        
        Node* newNode = new Node(value);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
    
    // Delete a node with given value
    void deleteNode(int value) {
        if (!head) return;
        
        // If head has the value
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        // Search for the node to delete
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        
        // If node found
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    
    // Search for a node
    bool search(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Print the linked list
    void printList() {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    LinkedList list;
    
    // Insert elements
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtBeginning(0);
    
    cout << "Original Linked List: ";
    list.printList();  // Output: 0 -> 1 -> 2 -> nullptr
    
    // Search for element
    cout << "Is 1 present? " << (list.search(1) ? "Yes" : "No") << endl;  // Output: Yes
    
    // Delete element
    list.deleteNode(1);
    cout << "After deleting 1: ";
    list.printList();  // Output: 0 -> 2 -> nullptr
    
    return 0;
}
```

### C++ Implementation - Doubly Linked List
```cpp
#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
    
    // Constructor
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    // Destructor
    ~DoublyLinkedList() {
        Node* current = head;
        while(current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        
        if (!head) {
            head = tail = newNode;
            return;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    
    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        if (!tail) {
            head = tail = newNode;
            return;
        }
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    // Print forward
    void printForward() {
        Node* current = head;
        while (current) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
    
    // Print backward
    void printBackward() {
        Node* current = tail;
        while (current) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    DoublyLinkedList dlist;
    
    // Insert elements
    dlist.insertAtEnd(1);
    dlist.insertAtEnd(2);
    dlist.insertAtBeginning(0);
    
    cout << "Forward traversal: ";
    dlist.printForward();  // Output: 0 <-> 1 <-> 2 <-> nullptr
    
    cout << "Backward traversal: ";
    dlist.printBackward();  // Output: 2 <-> 1 <-> 0 <-> nullptr
    
    return 0;
}
```

### Problem Exercises
- [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
- [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
- [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
- [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
- [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)

## 5. Stacks

### Definition
A stack is a linear data structure that follows the Last In First Out (LIFO) principle. Elements can only be inserted or removed from one end (top) of the stack.

### Characteristics
- **LIFO (Last In First Out)**: Last element added is the first to be removed
- **Operations**: Push (insert), Pop (remove), Peek (view top element)
- **Applications**: Function call management, expression evaluation, backtracking algorithms

### Time Complexity
- **Push**: O(1)
- **Pop**: O(1)
- **Peek**: O(1)
- **Search**: O(n)

### C++ Implementation - Using Array
```cpp
#include <iostream>
using namespace std;

class ArrayStack {
private:
    int* arr;
    int top;
    int capacity;
    
public:
    // Constructor
    ArrayStack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }
    
    // Destructor
    ~ArrayStack() {
        delete[] arr;
    }
    
    // Push operation
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = value;
    }
    
    // Pop operation
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top--];
    }
    
    // Peek operation
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return arr[top];
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return top == -1;
    }
    
    // Check if stack is full
    bool isFull() {
        return top == capacity - 1;
    }
    
    // Get stack size
    int size() {
        return top + 1;
    }
};

int main() {
    ArrayStack stack(5);
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    cout << "Top element: " << stack.peek() << endl;  // Output: 3
    cout << "Stack size: " << stack.size() << endl;   // Output: 3
    
    cout << "Popped: " << stack.pop() << endl;        // Output: 3
    cout << "Popped: " << stack.pop() << endl;        // Output: 2
    
    cout << "Stack size after pops: " << stack.size() << endl;  // Output: 1
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;  // Output: No
    
    return 0;
}
```

### C++ Implementation - Using std::stack
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    // Create a stack of integers
    stack<int> s;
    
    // Push elements
    s.push(1);
    s.push(2);
    s.push(3);
    
    cout << "Top element: " << s.top() << endl;  // Output: 3
    cout << "Stack size: " << s.size() << endl;  // Output: 3
    
    // Pop elements
    s.pop();
    cout << "After pop, top: " << s.top() << endl;  // Output: 2
    
    // Check if empty
    cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << endl;  // Output: No
    
    // Empty the stack
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;  // Output: 2 1
    
    return 0;
}
```

### Stack Applications
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to check if parentheses are balanced
bool areParenthesesBalanced(const string& expr) {
    stack<char> s;
    
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) {
                return false;
            }
            
            char top = s.top();
            s.pop();
            
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return s.empty();
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string& expr) {
    stack<int> s;
    
    for (char c : expr) {
        // If character is digit, push to stack
        if (isdigit(c)) {
            s.push(c - '0');
        } 
        // If operator, pop two elements and perform operation
        else {
            int val1 = s.top(); s.pop();
            int val2 = s.top(); s.pop();
            
            switch (c) {
                case '+': s.push(val2 + val1); break;
                case '-': s.push(val2 - val1); break;
                case '*': s.push(val2 * val1); break;
                case '/': s.push(val2 / val1); break;
            }
        }
    }
    
    return s.top();
}

int main() {
    // Test balanced parentheses
    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    
    cout << expr1 << " is " << (areParenthesesBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is " << (areParenthesesBalanced(expr2) ? "balanced" : "not balanced") << endl;
    
    // Test postfix evaluation
    string postfix = "23*5+";  // Equivalent to 2*3+5 = 11
    cout << "Result of " << postfix << " is " << evaluatePostfix(postfix) << endl;
    
    return 0;
}
```

### Problem Exercises
- [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [Min Stack](https://leetcode.com/problems/min-stack/)
- [Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
- [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
- [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## 6. Queues

### Definition
A queue is a linear data structure that follows the First In First Out (FIFO) principle. Elements are added at the rear (enqueue) and removed from the front (dequeue).

### Characteristics
- **FIFO (First In First Out)**: First element added is the first to be removed
- **Operations**: Enqueue (insert), Dequeue (remove), Front (view first element)
- **Applications**: Scheduling, resource allocation, breadth-first search

### Time Complexity
- **Enqueue**: O(1)
- **Dequeue**: O(1)
- **Front/Rear access**: O(1)
- **Search**: O(n)

### C++ Implementation - Using Array
```cpp
#include <iostream>
using namespace std;

class ArrayQueue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int size;
    
public:
    // Constructor
    ArrayQueue(int capacity) {
        this->capacity = capacity;
        front = 0;
        rear = -1;
        size = 0;
        arr = new int[capacity];
    }
    
    // Destructor
    ~ArrayQueue() {
        delete[] arr;
    }
    
    // Enqueue operation
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }
    
    // Dequeue operation
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int item = arr[front];
        front = (front + 1) % capacity;
        size--;
        return item;
    }
    
    // Get front element
    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }
    
    // Get rear element
    int getRear() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[rear];
    }
    
    // Check if queue is empty
    bool isEmpty() {
        return size == 0;
    }
    
    // Check if queue is full
    bool isFull() {
        return size == capacity;
    }
    
    // Get queue size
    int getSize() {
        return size;
    }
};

int main() {
    ArrayQueue queue(5);
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    cout << "Front element: " << queue.getFront() << endl;  // Output: 1
    cout << "Rear element: " << queue.getRear() << endl;    // Output: 3
    cout << "Queue size: " << queue.getSize() << endl;      // Output: 3
    
    cout << "Dequeued: " << queue.dequeue() << endl;        // Output: 1
    cout << "After dequeue, front: " << queue.getFront() << endl;  // Output: 2
    
    return 0;
}
```

### C++ Implementation - Using std::queue
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // Create a queue
    queue<int> q;
    
    // Enqueue elements
    q.push(1);
    q.push(2);
    q.push(3);
    
    cout << "Front element: " << q.front() << endl;  // Output: 1
    cout << "Back element: " << q.back() << endl;    // Output: 3
    cout << "Queue size: " << q.size() << endl;      // Output: 3
    
    // Dequeue element
    q.pop();
    cout << "After dequeue, front: " << q.front() << endl;  // Output: 2
    
    // Check if empty
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;  // Output: No
    
    // Empty the queue
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;  // Output: 2 3
    
    return 0;
}
```

### Queue Variants
```cpp
#include <iostream>
#include <queue>
using namespace std;

// Circular Queue implementation
class CircularQueue {
private:
    int* arr;
    int front, rear, capacity;
    
public:
    CircularQueue(int size) {
        arr = new int[size];
        capacity = size;
        front = rear = -1;
    }
    
    ~CircularQueue() {
        delete[] arr;
    }
    
    bool isEmpty() {
        return front == -1;
    }
    
    bool isFull() {
        return (rear + 1) % capacity == front;
    }
    
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        
        if (isEmpty()) {
            front = 0;
        }
        
        rear = (rear + 1) % capacity;
        arr[rear] = value;
    }
    
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        
        int value = arr[front];
        
        if (front == rear) {
            // Last element
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        
        return value;
    }
    
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }
};

int main() {
    // Priority Queue Example
    priority_queue<int> pq;
    
    pq.push(3);
    pq.push(1);
    pq.push(5);
    pq.push(2);
    
    cout << "Priority Queue (max at top): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";  // Output: 5 3 2 1
        pq.pop();
    }
    cout << endl;
    
    // Min Priority Queue
    priority_queue<int, vector<int>, greater<int>> min_pq;
    
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(5);
    min_pq.push(2);
    
    cout << "Min Priority Queue: ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";  // Output: 1 2 3 5
        min_pq.pop();
    }
    cout << endl;
    
    // Circular Queue example
    CircularQueue cq(5);
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    
    cout << "Circular Queue front: " << cq.peek() << endl;  // Output: 1
    cout << "Dequeued: " << cq.dequeue() << endl;          // Output: 1
    cout << "New front: " << cq.peek() << endl;            // Output: 2
    
    return 0;
}
```

### Problem Exercises
- [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- [Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)
- [Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
- [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

## Conclusion

Understanding these fundamental data structures is essential for efficient algorithm design and problem-solving in computer science. Each data structure has its own strengths and weaknesses, making them suitable for different types of problems:

1. **Arrays**: Best for fixed-size collections with frequent random access.
2. **Dynamic Arrays**: Ideal when resizing is needed but random access is still important.
3. **Strings**: Specialized for text processing and manipulation.
4. **Linked Lists**: Excellent for frequent insertions and deletions at arbitrary positions.
5. **Stacks**: Perfect for problems involving backtracking or nested structures.
6. **Queues**: Ideal for order processing, scheduling, and breadth-first algorithms.

Practice the provided exercises on LeetCode to strengthen your understanding of these data structures and their applications. As you progress, you'll develop intuition for which data structure to use for different types of problems.

Remember that mastering these basic data structures forms the foundation for understanding more complex structures like trees, graphs, hash tables, and heaps, which will be covered in subsequent materials.