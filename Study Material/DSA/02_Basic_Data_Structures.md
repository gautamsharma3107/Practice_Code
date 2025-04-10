# Basic Data Structures

This document covers the fundamental data structures used in programming, specifically focusing on arrays, dynamic arrays, strings, linked lists, stacks, and queues. Each section includes explanations, examples, and problem exercises with links to relevant coding platforms.

## 1. Arrays
- **Definition**: A collection of elements identified by index or key.
- **Characteristics**:
  - Fixed size
  - Homogeneous elements
- **Example**: 
  ```cpp
  int arr[5] = {1, 2, 3, 4, 5};
  ```
- **Problem Exercises**:
  - [Array Rotation](https://leetcode.com/problems/rotate-array/)
  - [Find the Missing Number](https://leetcode.com/problems/missing-number/)

## 2. Dynamic Arrays
- **Definition**: Arrays that can grow or shrink in size during runtime.
- **Characteristics**:
  - Resizable
  - Can store heterogeneous elements (in languages like Python)
- **Example**: 
  ```cpp
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  ```
- **Problem Exercises**:
  - [Implement Dynamic Array](https://leetcode.com/problems/design-a-dynamic-array/)
  - [Find the Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)

## 3. Strings
- **Definition**: A sequence of characters.
- **Characteristics**:
  - Immutable in some languages (e.g., Java)
  - Can be mutable (e.g., C++ with `std::string`)
- **Example**: 
  ```cpp
  std::string str = "Hello, World!";
  ```
- **Problem Exercises**:
  - [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
  - [Valid Anagram](https://leetcode.com/problems/valid-anagram/)

## 4. Linked Lists
- **Definition**: A linear data structure where elements are stored in nodes, each pointing to the next.
- **Types**:
  - Singly Linked List
  - Doubly Linked List
  - Circular Linked List
- **Example**: 
  ```cpp
  struct Node {
      int data;
      Node* next;
  };
  ```
- **Problem Exercises**:
  - [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
  - [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)

## 5. Stacks
- **Definition**: A linear data structure that follows the Last In First Out (LIFO) principle.
- **Operations**:
  - Push
  - Pop
  - Peek
- **Example**: 
  ```cpp
  std::stack<int> s;
  s.push(1);
  s.pop();
  ```
- **Problem Exercises**:
  - [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
  - [Min Stack](https://leetcode.com/problems/min-stack/)

## 6. Queues
- **Definition**: A linear data structure that follows the First In First Out (FIFO) principle.
- **Operations**:
  - Enqueue
  - Dequeue
  - Front
- **Example**: 
  ```cpp
  std::queue<int> q;
  q.push(1);
  q.pop();
  ```
- **Problem Exercises**:
  - [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
  - [Circular Queue](https://leetcode.com/problems/design-circular-queue/)

## Conclusion
Understanding these basic data structures is crucial for efficient programming and algorithm design. Practice the exercises linked above to strengthen your knowledge and skills in using these data structures effectively.