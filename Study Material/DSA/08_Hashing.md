# Hashing in Data Structures

## 1. Introduction

Hashing is a technique used to map data of arbitrary size to fixed-size values, typically for fast data retrieval. It is widely used in data structures like hash tables, sets, and maps, enabling average-case constant time complexity for search, insert, and delete operations.

---

## 2. Hash Functions

A **hash function** transforms a given key into an integer (the hash code), which is then mapped to an index in a hash table.

### Properties of a Good Hash Function

- **Deterministic**: Same input always yields the same output.
- **Efficient**: Should be fast to compute.
- **Uniform Distribution**: Should distribute keys evenly to minimize collisions.
- **Minimize Collisions**: Different keys should map to different indices as much as possible.

### Common Hashing Methods

- **Division Method**: `index = key % table_size`
- **Multiplication Method**: `index = floor(table_size * (key * A % 1))` where `0 < A < 1`
- **String Hashing**: For strings, polynomial rolling hash is common.

#### Example: Simple Integer Hash Function (Division Method)

```cpp
#include <iostream>
int hashFunction(int key, int tableSize) {
    return key % tableSize;
}
```

#### Example: String Hash Function (Polynomial Rolling)

```cpp
#include <string>
int stringHash(const std::string& s, int tableSize) {
    const int p = 31;
    long long hash = 0, p_pow = 1;
    for (char c : s) {
        hash = (hash + (c - 'a' + 1) * p_pow) % tableSize;
        p_pow = (p_pow * p) % tableSize;
    }
    return (int)hash;
}
```

---

## 3. Collisions and Resolution Techniques

A **collision** occurs when two different keys hash to the same index. Handling collisions efficiently is crucial for hash table performance.

### 3.1 Chaining

Each table index points to a linked list (or vector) of entries.

#### Example: Hash Table with Chaining

```cpp
#include <vector>
#include <list>
class HashTableChaining {
    std::vector<std::list<int>> table;
    int size;
public:
    HashTableChaining(int sz) : size(sz), table(sz) {}
    void insert(int key) {
        int idx = key % size;
        table[idx].push_back(key);
    }
    bool search(int key) {
        int idx = key % size;
        for (int x : table[idx])
            if (x == key) return true;
        return false;
    }
};
```

### 3.2 Open Addressing

All elements are stored in the table itself. On collision, probe for the next available slot.

- **Linear Probing**: Check next slot sequentially.
- **Quadratic Probing**: Check slots at quadratic intervals.
- **Double Hashing**: Use a second hash function for step size.

#### Example: Linear Probing

```cpp
#include <vector>
class HashTableLinearProbing {
    std::vector<int> table;
    int size;
    int EMPTY = -1;
public:
    HashTableLinearProbing(int sz) : size(sz), table(sz, EMPTY) {}
    void insert(int key) {
        int idx = key % size;
        while (table[idx] != EMPTY) {
            idx = (idx + 1) % size;
        }
        table[idx] = key;
    }
    bool search(int key) {
        int idx = key % size;
        int start = idx;
        while (table[idx] != EMPTY) {
            if (table[idx] == key) return true;
            idx = (idx + 1) % size;
            if (idx == start) break;
        }
        return false;
    }
};
```

---

## 4. Load Factor and Rehashing

- **Load Factor (α)**: `number of elements / table size`
- High load factor increases collisions.
- **Rehashing**: When load factor exceeds a threshold (e.g., 0.7), resize the table (usually double the size) and re-insert all elements.

#### Example: Demonstrating Load Factor

```cpp
#include <iostream>
#include <vector>
class SimpleHashTable {
    std::vector<int> table;
    int count, size;
    int EMPTY = -1;
public:
    SimpleHashTable(int sz) : size(sz), table(sz, EMPTY), count(0) {}
    void insert(int key) {
        if ((double)count / size > 0.7) {
            std::cout << "Rehash needed!\n";
            // Rehashing logic would go here
        }
        int idx = key % size;
        while (table[idx] != EMPTY) idx = (idx + 1) % size;
        table[idx] = key;
        count++;
    }
};
```

---

## 5. Applications of Hashing

- **Dictionaries/Maps**: Fast key-value lookup.
- **Sets**: Fast membership testing.
- **Databases**: Indexing for quick search.
- **Caching**: Store and retrieve computed results.
- **Cryptography**: Data integrity and authentication.

---

## 6. Example Problems

### 6.1. Find Duplicates in an Array

```cpp
#include <unordered_set>
#include <vector>
bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}
```

### 6.2. Design a Simple HashMap

```cpp
#include <vector>
#include <list>
class MyHashMap {
    static const int SIZE = 1009;
    std::vector<std::list<std::pair<int, int>>> table;
public:
    MyHashMap() : table(SIZE) {}
    void put(int key, int value) {
        int idx = key % SIZE;
        for (auto& p : table[idx]) {
            if (p.first == key) { p.second = value; return; }
        }
        table[idx].emplace_back(key, value);
    }
    int get(int key) {
        int idx = key % SIZE;
        for (auto& p : table[idx]) {
            if (p.first == key) return p.second;
        }
        return -1;
    }
    void remove(int key) {
        int idx = key % SIZE;
        table[idx].remove_if([key](const std::pair<int, int>& p) { return p.first == key; });
    }
};
```

---

## 7. Summary

Hashing is a foundational concept in computer science, enabling efficient data storage and retrieval. Mastery of hash functions, collision resolution, and practical implementation is essential for building high-performance applications.

---

## 8. Further Reading and Practice

- [LeetCode: Design HashMap](https://leetcode.com/problems/design-hashmap/)
- [GeeksforGeeks: Hashing Data Structure](https://www.geeksforgeeks.org/hashing-data-structure/)
- [HackerRank: Hash Tables](https://www.hackerrank.com/domains/tutorials/10-days-of-javascript)
- [CodeSignal: Hash Table Problems](https://codesignal.com/)