# Trees Data Structures Notes

This file contains comprehensive notes on tree data structures, including their types, properties, implementations, and applications. Each section includes C++ examples and problem exercises with links to relevant coding platforms for practice.

## Table of Contents
1. [Introduction to Trees](#introduction-to-trees)
2. [Binary Trees](#1-binary-trees)
3. [Binary Search Trees (BST)](#2-binary-search-trees-bst)
4. [Self-Balancing Trees](#3-self-balancing-trees)
5. [B-Trees](#4-b-trees)
6. [Heaps](#5-heaps)
7. [Tree Traversals](#6-tree-traversals)
8. [Tree-Based Problems](#7-tree-based-problems)
9. [Conclusion](#conclusion)

## Introduction to Trees

A tree is a hierarchical data structure consisting of nodes connected by edges. Trees are widely used because they represent hierarchical relationships effectively.

**Terminology**:
- **Root**: The topmost node of a tree
- **Node**: An element in a tree that stores data and maintains links to its children
- **Edge**: The connection between two nodes
- **Parent**: A node that has children
- **Child**: A node that has a parent
- **Leaf Node**: A node with no children
- **Internal Node**: A node with at least one child
- **Depth of a Node**: Length of the path from root to the node
- **Height of a Node**: Length of the path from the node to the deepest leaf
- **Height of a Tree**: Height of the root node

## 1. Binary Trees

### Definition and Properties
A binary tree is a tree data structure where each node has at most two children, referred to as the left child and the right child.

**Properties**:
- The maximum number of nodes at level `l` is `2^l` (root level is 0)
- The maximum number of nodes in a binary tree of height `h` is `2^(h+1) - 1`
- The minimum height of a binary tree with `n` nodes is `⌊log2(n)⌋`
- In a binary tree with `n` nodes, the number of leaf nodes is `(n+1)/2`

### Types of Binary Trees
1. **Full Binary Tree**: Every node has 0 or 2 children
2. **Complete Binary Tree**: All levels are completely filled except possibly the last level, which is filled from left to right
3. **Perfect Binary Tree**: All internal nodes have exactly two children and all leaf nodes are at the same level
4. **Balanced Binary Tree**: The height of the left and right subtrees of every node differ by at most 1
5. **Degenerate Tree**: Every parent node has only one child, essentially becoming a linked list

### C++ Implementation of a Binary Tree

```cpp
#include <iostream>
using namespace std;

// Structure for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    // Constructor
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Function to create a new node
Node* createNode(int data) {
    return new Node(data);
}

// Example usage
int main() {
    // Create root node
    Node* root = createNode(1);
    
    // Create children
    root->left = createNode(2);
    root->right = createNode(3);
    
    // Add more nodes
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    
    cout << "Binary Tree created successfully!" << endl;
    cout << "Root: " << root->data << endl;
    cout << "Left Child: " << root->left->data << endl;
    cout << "Right Child: " << root->right->data << endl;
    
    return 0;
}
```

### Common Operations on Binary Trees
- **Insertion**: Add a new node to the tree
- **Deletion**: Remove a node from the tree
- **Traversal**: Visit all nodes in the tree (covered in detail in [Tree Traversals](#6-tree-traversals))
- **Search**: Find a specific node in the tree

### Applications of Binary Trees
- Expression evaluation and syntax parsing
- Huffman coding for data compression
- Priority queues (using binary heaps)
- Binary Search Trees for efficient searching

### Exercises
- Implement a binary tree in C++
- Count the number of nodes in a binary tree
- Find the height of a binary tree
- [Binary Tree Implementation Problem](https://www.geeksforgeeks.org/binary-tree-implementation/)
- [Find diameter of a binary tree](https://leetcode.com/problems/diameter-of-binary-tree/)

## 2. Binary Search Trees (BST)

### Definition and Properties
A Binary Search Tree is a binary tree where the left child contains only nodes with values less than the parent node, and the right child only contains nodes with values greater than the parent node.

**Properties**:
- In-order traversal of BST gives a sorted sequence
- The time complexity for search, insert, and delete operations is O(h), where h is the height of the tree
- For a balanced BST, the height is O(log n), making operations O(log n)
- Worst case (skewed tree): O(n) for all operations

### C++ Implementation of a Binary Search Tree

```cpp
#include <iostream>
using namespace std;

// Structure for a BST node
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    // Constructor
    BSTNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;
    
    // Private helper methods
    BSTNode* insertRecursive(BSTNode* node, int value) {
        if (node == nullptr) {
            return new BSTNode(value);
        }
        
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        
        return node;
    }
    
    BSTNode* searchRecursive(BSTNode* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        
        if (value < node->data) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }
    
    void inOrderTraversal(BSTNode* node) {
        if (node == nullptr) return;
        
        inOrderTraversal(node->left);
        cout << node->data << " ";
        inOrderTraversal(node->right);
    }
    
    BSTNode* findMin(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    
    BSTNode* deleteNode(BSTNode* root, int value) {
        if (root == nullptr) return root;
        
        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        } else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        } else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node with two children
            BSTNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }
    
public:
    BST() : root(nullptr) {}
    
    // Public methods
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    
    bool search(int value) {
        return searchRecursive(root, value) != nullptr;
    }
    
    void remove(int value) {
        root = deleteNode(root, value);
    }
    
    void display() {
        cout << "In-order traversal: ";
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    
    // Insert nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    // Display the tree
    tree.display();
    
    // Search for nodes
    cout << "Search for 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search for 90: " << (tree.search(90) ? "Found" : "Not Found") << endl;
    
    // Delete a node
    tree.remove(30);
    cout << "After deleting 30: ";
    tree.display();
    
    return 0;
}
```

### Operations on BST
- **Insertion**: O(log n) average, O(n) worst case
- **Deletion**: O(log n) average, O(n) worst case
- **Search**: O(log n) average, O(n) worst case

### Applications of BST
- Database indexing
- Symbol tables in compilers
- Priority queues
- Sorting algorithms (Tree sort)

### Exercises
- Implement a binary search tree with insertion and search functions
- Find the kth smallest/largest element in a BST
- Convert a sorted array to a balanced BST
- [Binary Search Tree Problem](https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/)
- [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

## 3. Self-Balancing Trees

### Definition and Purpose
Self-balancing trees are binary search trees that automatically maintain their balance during insertions and deletions. They ensure that the height remains O(log n), guaranteeing O(log n) time complexity for operations.

### AVL Trees

#### Definition and Properties
An AVL tree is a self-balancing binary search tree where the difference between heights of left and right subtrees cannot exceed one for all nodes.

**Balance Factor** = Height of left subtree - Height of right subtree

For each node, the balance factor must be -1, 0, or 1.

#### Rotations in AVL Trees
1. **Left Rotation**: Used when right subtree becomes heavier
2. **Right Rotation**: Used when left subtree becomes heavier
3. **Left-Right Rotation**: A left rotation followed by a right rotation
4. **Right-Left Rotation**: A right rotation followed by a left rotation

#### C++ Implementation of AVL Tree

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }
    
    int balanceFactor(AVLNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    
    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    AVLNode* insertNode(AVLNode* node, int value) {
        // Normal BST insertion
        if (node == nullptr) {
            return new AVLNode(value);
        }
        
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            // Equal values not allowed
            return node;
        }
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = balanceFactor(node);
        
        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inOrderTraversal(AVLNode* node) {
        if (node == nullptr) return;
        
        inOrderTraversal(node->left);
        cout << node->data << "(" << balanceFactor(node) << ") ";
        inOrderTraversal(node->right);
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int value) {
        root = insertNode(root, value);
    }
    
    void display() {
        cout << "In-order traversal with balance factors: ";
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree avl;
    
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    
    avl.display();
    
    return 0;
}
```

### Red-Black Trees

#### Definition and Properties
A red-black tree is a self-balancing binary search tree with the following properties:
1. Each node is either red or black
2. The root is black
3. All leaves (NULL nodes) are black
4. If a node is red, both its children are black
5. Every path from a node to any of its descendant NULL nodes has the same number of black nodes

#### Advantages of Red-Black Trees
- Guaranteed O(log n) operations
- More efficient for frequent insertions and deletions compared to AVL trees
- Used in many standard libraries (e.g., C++ STL map, set)

### Splay Trees

Splay trees are self-adjusting binary search trees that move recently accessed items to the root. They provide amortized O(log n) performance.

### Exercises
- Implement an AVL tree with rotation operations
- Implement a Red-Black tree and perform insertions
- Compare the performance of AVL and Red-Black trees for various operations
- [AVL Tree Problem](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
- [Red-Black Tree Problem](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction/)

## 4. B-Trees

### Definition and Properties
B-Trees are self-balancing search trees that maintain sorted data and allow searches, insertions, and deletions in logarithmic time. Unlike binary trees, B-Trees are optimized for systems that read and write large blocks of data, such as disk storage.

**Properties**:
- A B-tree of order `m`:
  - Every node has at most `m` children
  - Every non-leaf node (except root) has at least `⌈m/2⌉` children
  - The root has at least two children if it is not a leaf node
  - All leaves appear on the same level
  - A non-leaf node with k children contains k-1 keys

### Structure of a B-Tree Node
- **Keys**: Sorted array of keys
- **Children**: Array of pointers to child nodes
- **Leaf status**: Whether the node is a leaf node or not
- **Key count**: Number of keys currently stored in the node

### C++ Implementation of B-Tree

```cpp
#include <iostream>
#include <vector>
using namespace std;

// A B-Tree node
class BTreeNode {
private:
    bool leaf;
    vector<int> keys;
    vector<BTreeNode*> children;
    int t; // Minimum degree (defines the range for number of keys)
    
public:
    BTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf) {
        // Constructor
        keys.reserve(2*t - 1); // A node can contain at most 2t-1 keys
        if (!leaf) {
            children.reserve(2*t); // A node can have at most 2t children
        }
    }
    
    // Function to traverse all nodes in a subtree rooted with this node
    void traverse() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!leaf) {
                children[i]->traverse();
            }
            cout << " " << keys[i];
        }
        
        // Print the subtree rooted with the last child
        if (!leaf) {
            children[i]->traverse();
        }
    }
    
    // Function to search a key in a subtree rooted with this node
    BTreeNode* search(int k) {
        int i = 0;
        while (i < keys.size() && k > keys[i]) {
            i++;
        }
        
        // If the key is found here
        if (i < keys.size() && k == keys[i]) {
            return this;
        }
        
        // If key is not found here and this is a leaf node
        if (leaf) {
            return nullptr;
        }
        
        // Go to the appropriate child
        return children[i]->search(k);
    }
    
    // Make this accessible to BTree class
    friend class BTree;
};

// A B-Tree
class BTree {
private:
    BTreeNode* root;
    int t; // Minimum degree
    
    // Function to split the child y of this node
    void splitChild(BTreeNode* x, int i) {
        // Create a new node which is going to store (t-1) keys of y
        BTreeNode* z = new BTreeNode(t, x->children[i]->leaf);
        BTreeNode* y = x->children[i];
        
        // Copy the last (t-1) keys of y to z
        for (int j = 0; j < t-1; j++) {
            z->keys.push_back(y->keys[j+t]);
        }
        
        // Copy the last t children of y to z
        if (!y->leaf) {
            for (int j = 0; j < t; j++) {
                z->children.push_back(y->children[j+t]);
            }
        }
        
        // Reduce the number of keys in y
        y->keys.resize(t-1);
        
        // Since this node is going to have a new child, create space for it
        x->children.insert(x->children.begin() + i + 1, z);
        
        // Copy the middle key of y to this node
        x->keys.insert(x->keys.begin() + i, y->keys[t-1]);
    }
    
    // Insert a key in a non-full node
    void insertNonFull(BTreeNode* x, int k) {
        int i = x->keys.size() - 1;
        
        if (x->leaf) {
            // Insert into a leaf node
            // Find the location of new key and move all greater keys one space ahead
            while (i >= 0 && k < x->keys[i]) {
                i--;
            }
            x->keys.insert(x->keys.begin() + i + 1, k);
        } else {
            // Insert into an internal node
            // Find the child which is going to have the new key
            while (i >= 0 && k < x->keys[i]) {
                i--;
            }
            i++;
            
            // See if the found child is full
            if (x->children[i]->keys.size() == 2*t - 1) {
                // If the child is full, split it
                splitChild(x, i);
                
                // After splitting, the middle key goes up and
                // the node splits into two. See which of the two
                // is going to have the new key
                if (k > x->keys[i]) {
                    i++;
                }
            }
            insertNonFull(x->children[i], k);
        }
    }
    
public:
    BTree(int _t) : t(_t), root(nullptr) {
        // Constructor
    }
    
    void traverse() {
        if (root) {
            root->traverse();
        }
    }
    
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
    
    void insert(int k) {
        // If tree is empty
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(k);
            return;
        }
        
        // If root is full, then tree grows in height
        if (root->keys.size() == 2*t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            
            // Split the old root and move one key to the new root
            splitChild(s, 0);
            
            // New root has two children. Decide which one is going to have the new key
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            insertNonFull(s->children[i], k);
            
            root = s;
        } else {
            insertNonFull(root, k);
        }
    }
};

int main() {
    BTree t(3); // A B-Tree with minimum degree 3
    
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    
    cout << "Traversal of the B-tree: ";
    t.traverse();
    cout << endl;
    
    int key = 6;
    if (t.search(key) != nullptr) {
        cout << key << " is found in the B-tree" << endl;
    } else {
        cout << key << " is not found in the B-tree" << endl;
    }
    
    key = 15;
    if (t.search(key) != nullptr) {
        cout << key << " is found in the B-tree" << endl;
    } else {
        cout << key << " is not found in the B-tree" << endl;
    }
    
    return 0;
}
```

### Applications of B-Trees
- Database indexing
- File systems (e.g., NTFS, HFS, etc.)
- Key-value stores
- Search engines

### B+ Trees
B+ Trees are a variant of B-Trees with all keys stored in the leaves, and the leaves connected via pointers to form a linked list. This design is particularly useful for range queries and database systems.

### Exercises
- Implement a B-tree and perform insertion and deletion operations
- Compare the performance of B-trees with Binary Search Trees
- Implement a B+ tree
- [B-Tree Problem](https://www.geeksforgeeks.org/b-tree-set-1-introduction/)
- [Database index implementation using B+ trees](https://www.geeksforgeeks.org/introduction-of-b-tree/)

## 5. Heaps

### Definition and Properties
A heap is a specialized tree-based data structure that satisfies the heap property: if P is a parent node of C, then the key of P is either greater than or equal to (in a max heap) or less than or equal to (in a min heap) the key of C.

**Types**:
1. **Max Heap**: The key of each node is greater than or equal to its children's keys
2. **Min Heap**: The key of each node is less than or equal to its children's keys

### Binary Heap Implementation

A binary heap is typically implemented using an array, where for a node at index i:
- Left child: 2i + 1
- Right child: 2i + 2
- Parent: (i - 1) / 2

#### C++ Implementation of Binary Heap

```cpp
#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        // If we reach the root or the current node is already greater than its parent
        if (i == 0 || heap[parent(i)] <= heap[i]) {
            return;
        }
        
        // Swap with parent
        swap(heap[i], heap[parent(i)]);
        
        // Recursively heapify the parent
        heapifyUp(parent(i));
    }
    
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        // Compare with left child
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        // Compare with right child
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        // If a child is smaller than the current node
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    MinHeap() {}
    
    void insert(int key) {
        // Insert at the end
        heap.push_back(key);
        
        // Fix the min heap property
        int index = heap.size() - 1;
        heapifyUp(index);
    }
    
    int extractMin() {
        if (heap.size() == 0) {
            throw out_of_range("Heap is empty");
        }
        
        int min = heap[0];
        
        // Replace root with the last element
        heap[0] = heap.back();
        heap.pop_back();
        
        // Fix the min heap property
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return min;
    }
    
    int getMin() {
        if (heap.size() == 0) {
            throw out_of_range("Heap is empty");
        }
        return heap[0];
    }
    
    void decreaseKey(int i, int new_val) {
        if (i >= heap.size() || new_val > heap[i]) {
            return;
        }
        
        heap[i] = new_val;
        heapifyUp(i);
    }
    
    void deleteKey(int i) {
        if (i >= heap.size()) {
            return;
        }
        
        decreaseKey(i, INT_MIN);
        extractMin();
    }
    
    bool isEmpty() {
        return heap.size() == 0;
    }
    
    int size() {
        return heap.size();
    }
    
    void printHeap() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

// Implementation of MaxHeap
class MaxHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        if (i == 0 || heap[parent(i)] >= heap[i]) {
            return;
        }
        
        swap(heap[i], heap[parent(i)]);
        heapifyUp(parent(i));
    }
    
    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }
        
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }
        
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }
    
public:
    MaxHeap() {}
    
    void insert(int key) {
        heap.push_back(key);
        int index = heap.size() - 1;
        heapifyUp(index);
    }
    
    int extractMax() {
        if (heap.size() == 0) {
            throw out_of_range("Heap is empty");
        }
        
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return max;
    }
    
    void printHeap() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

// Example usage
int main() {
    MinHeap minHeap;
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(15);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(45);
    
    cout << "Min Heap: ";
    minHeap.printHeap();
    
    cout << "The min value is: " << minHeap.getMin() << endl;
    cout << "Extracting min: " << minHeap.extractMin() << endl;
    cout << "Min Heap after extraction: ";
    minHeap.printHeap();
    
    MaxHeap maxHeap;
    maxHeap.insert(3);
    maxHeap.insert(2);
    maxHeap.insert(15);
    maxHeap.insert(5);
    maxHeap.insert(4);
    maxHeap.insert(45);
    
    cout << "Max Heap: ";
    maxHeap.printHeap();
    
    cout << "Extracting max: " << maxHeap.extractMax() << endl;
    cout << "Max Heap after extraction: ";
    maxHeap.printHeap();
    
    return 0;
}
```

### Heap Sort
Heap sort is a comparison-based sorting algorithm that uses a binary heap data structure.

```cpp
// Heap Sort implementation
void heapSort(vector<int>& arr) {
    // Build max heap
    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        heapify(arr, arr.size(), i);
    }
    
    // Extract elements from the heap one by one
    for (int i = arr.size() - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // Move current root to end
        heapify(arr, i, 0);    // Max heapify the reduced heap
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
```

### Applications of Heaps
- Priority queues
- Heap sort algorithm
- Graph algorithms (Dijkstra's, Prim's)
- K-way merging
- Finding K largest/smallest elements

### Exercises
- Implement a max heap and min heap with insertion and deletion operations
- Implement heap sort algorithm
- Solve the problem of finding the k largest elements in an array using heaps
- [Heap Problem](https://www.geeksforgeeks.org/heap-sort/)
- [Find k largest elements in an array](https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/)

## 6. Tree Traversals

Tree traversal is a process of visiting all nodes in a tree. The order in which nodes are visited can be different, leading to different traversal algorithms.

### Types of Tree Traversals

1. **Depth-First Traversals**:
   - **In-order**: Left, Root, Right
   - **Pre-order**: Root, Left, Right
   - **Post-order**: Left, Right, Root

2. **Breadth-First Traversal**:
   - **Level-order**: Visit nodes level by level, from left to right

### C++ Implementation of Tree Traversals

```cpp
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Depth-first traversals
void inOrderTraversal(Node* root) {
    if (root == nullptr) return;
    
    inOrderTraversal(root->left);      // Left
    cout << root->data << " ";         // Root
    inOrderTraversal(root->right);     // Right
}

void preOrderTraversal(Node* root) {
    if (root == nullptr) return;
    
    cout << root->data << " ";         // Root
    preOrderTraversal(root->left);     // Left
    preOrderTraversal(root->right);    // Right
}

void postOrderTraversal(Node* root) {
    if (root == nullptr) return;
    
    postOrderTraversal(root->left);    // Left
    postOrderTraversal(root->right);   // Right
    cout << root->data << " ";         // Root
}

// Breadth-first (level-order) traversal
void levelOrderTraversal(Node* root) {
    if (root == nullptr) return;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        cout << current->data << " ";
        
        if (current->left != nullptr) {
            q.push(current->left);
        }
        
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// Example usage
int main() {
    // Create a sample tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    /*
         1
       /   \
      2     3
     / \   / \
    4   5 6   7
    */
    
    cout << "In-order traversal: ";
    inOrderTraversal(root);
    cout << endl;
    
    cout << "Pre-order traversal: ";
    preOrderTraversal(root);
    cout << endl;
    
    cout << "Post-order traversal: ";
    postOrderTraversal(root);
    cout << endl;
    
    cout << "Level-order traversal: ";
    levelOrderTraversal(root);
    cout << endl;
    
    return 0;
}
```

### Applications of Different Traversals
- **In-order**: Used to get sorted output from a binary search tree
- **Pre-order**: Used to create a copy of a tree or evaluate prefix expressions
- **Post-order**: Used to delete a tree or evaluate postfix expressions
- **Level-order**: Used in level-order problems or breadth-first search

### Morris Traversal (Constant Space)
Morris traversal is a way to traverse binary trees without using recursion or a stack. It uses threading to achieve O(1) space complexity.

```cpp
// Morris In-order Traversal
void morrisInOrderTraversal(Node* root) {
    Node* current = root;
    while (current != nullptr) {
        if (current->left == nullptr) {
            cout << current->data << " ";
            current = current->right;
        } else {
            Node* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
}
```

### Exercises
- Implement all tree traversal algorithms for a binary tree
- Implement iterative versions of depth-first traversals using a stack
- Implement Morris traversal for constant space in-order traversal
- [Tree Traversal Problem](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)
- [Diagonal traversal of Binary Tree](https://www.geeksforgeeks.org/diagonal-traversal-of-binary-tree/)

## 7. Tree-Based Problems

Trees are frequently used in algorithmic problem-solving. Here are some common tree-based problems:

### Finding Height of a Tree
```cpp
int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + max(leftHeight, rightHeight);
}
```

### Checking if a Binary Tree is Balanced
```cpp
bool isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    if (abs(leftHeight - rightHeight) <= 1 && 
        isBalanced(root->left) && 
        isBalanced(root->right)) {
        return true;
    }
    
    return false;
}
```

### Finding the Lowest Common Ancestor (LCA) of Two Nodes
```cpp
Node* findLCA(Node* root, int n1, int n2) {
    if (root == nullptr) {
        return nullptr;
    }
    
    // If either n1 or n2 matches the root's value, report it
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    
    // Look for n1 and n2 in left and right subtrees
    Node* leftLCA = findLCA(root->left, n1, n2);
    Node* rightLCA = findLCA(root->right, n1, n2);
    
    // If both of the above calls return non-NULL, then one key
    // is present in once subtree and other is present in other,
    // so this node is the LCA
    if (leftLCA && rightLCA) {
        return root;
    }
    
    // Otherwise check if left subtree or right subtree is LCA
    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}
```

### Diameter of a Binary Tree
The diameter of a binary tree is the longest path between any two nodes in the tree. This path may or may not pass through the root.

```cpp
int diameterOfBinaryTree(Node* root) {
    int diameter = 0;
    calculateHeight(root, diameter);
    return diameter;
}

int calculateHeight(Node* node, int& diameter) {
    if (node == nullptr) {
        return 0;
    }
    
    int leftHeight = calculateHeight(node->left, diameter);
    int rightHeight = calculateHeight(node->right, diameter);
    
    // Update diameter if needed
    diameter = max(diameter, leftHeight + rightHeight);
    
    // Return height of current node
    return 1 + max(leftHeight, rightHeight);
}
```

### Serializing and Deserializing Binary Trees
Serialization is converting a data structure into a sequence of bytes that can be stored or transmitted. Deserialization is reconstructing the data structure from this sequence.

```cpp
// Serialize a binary tree to a string
string serialize(Node* root) {
    if (root == nullptr) {
        return "null,";
    }
    
    string result = to_string(root->data) + ",";
    result += serialize(root->left);
    result += serialize(root->right);
    
    return result;
}

// Helper function for deserialization
Node* deserializeHelper(queue<string>& nodes) {
    string val = nodes.front();
    nodes.pop();
    
    if (val == "null") {
        return nullptr;
    }
    
    Node* root = new Node(stoi(val));
    root->left = deserializeHelper(nodes);
    root->right = deserializeHelper(nodes);
    
    return root;
}

// Deserialize a string to a binary tree
Node* deserialize(string data) {
    queue<string> nodes;
    string val = "";
    
    for (char c : data) {
        if (c == ',') {
            nodes.push(val);
            val = "";
        } else {
            val += c;
        }
    }
    
    if (!val.empty()) {
        nodes.push(val);
    }
    
    return deserializeHelper(nodes);
}
```

### Exercises
- Solve problems related to tree height and balance checking
- Implement an algorithm to find the lowest common ancestor of two nodes
- Calculate the diameter of a binary tree
- [Tree Height Problem](https://www.geeksforgeeks.org/find-height-binary-tree/)
- [Lowest Common Ancestor Problem](https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree/)
- [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

## Conclusion

Trees are fundamental data structures in computer science with a wide range of applications. They provide efficient solutions for many problems, particularly those involving hierarchical data and search operations.

Key takeaways from this file:
1. Binary trees are the foundation for many other tree structures
2. Binary search trees provide efficient searching, insertion, and deletion operations
3. Self-balancing trees like AVL and Red-Black trees ensure O(log n) performance
4. B-Trees are optimized for systems that read and write large blocks of data
5. Heaps provide efficient implementation for priority queues
6. Different tree traversal methods serve different purposes

Understanding tree data structures is crucial for solving complex problems efficiently. Continue practicing the exercises linked in each section to strengthen your knowledge and skills in this area.

### Additional Resources
- [Visualgo - Binary Search Tree Visualization](https://visualgo.net/en/bst)
- [Brilliant.org - Trees](https://brilliant.org/wiki/trees/)
- [Coursera - Data Structures](https://www.coursera.org/learn/data-structures)