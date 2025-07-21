# Advanced Data Structures

This document provides an in-depth overview of advanced data structures, their use cases, and C++ implementations. Mastery of these structures is crucial for efficient algorithm design and tackling complex computational problems.

---

## 1. Trie (Prefix Tree)

**Definition:**  
A Trie is a tree-like data structure that efficiently stores and retrieves keys in a dataset of strings. Each node represents a character of a string.

**Use Cases:**  
- Autocomplete systems  
- Spell checkers  
- IP routing  
- Dictionary implementations

**Operations:**  
- Insert a word  
- Search for a word  
- Delete a word

**Complexity:**  
- Insert/Search/Delete: O(m), where m is the length of the word

**C++ Example:**
```cpp
// filepath: example_trie.cpp
#include <iostream>
#include <unordered_map>
using namespace std;

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return true;
    }
};
int main() {
    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // 1
    cout << trie.search("app") << endl;     // 0
    cout << trie.startsWith("app") << endl; // 1
    trie.insert("app");
    cout << trie.search("app") << endl;     // 1
    return 0;
}
```

---

## 2. Segment Tree

**Definition:**  
A Segment Tree is a binary tree used for storing intervals or segments. It allows efficient range queries and updates.

**Use Cases:**  
- Range sum/min/max queries  
- Dynamic array queries  
- Interval updates

**Operations:**  
- Build  
- Update  
- Query

**Complexity:**  
- Build: O(n)  
- Update/Query: O(log n)

**C++ Example:**
```cpp
// filepath: example_segment_tree.cpp
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree, arr;
    int n;
    void build(int node, int l, int r) {
        if (l == r) tree[node] = arr[l];
        else {
            int m = (l + r) / 2;
            build(2*node, l, m);
            build(2*node+1, m+1, r);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) tree[node] = val;
        else {
            int m = (l + r) / 2;
            if (idx <= m) update(2*node, l, m, idx, val);
            else update(2*node+1, m+1, r, idx, val);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        return query(2*node, l, m, ql, qr) + query(2*node+1, m+1, r, ql, qr);
    }
public:
    SegmentTree(const vector<int>& input) : arr(input) {
        n = arr.size();
        tree.resize(4*n);
        build(1, 0, n-1);
    }
    void update(int idx, int val) { update(1, 0, n-1, idx, val); }
    int query(int l, int r) { return query(1, 0, n-1, l, r); }
};
int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);
    cout << st.query(1, 3) << endl; // 3+5+7=15
    st.update(1, 10);
    cout << st.query(1, 3) << endl; // 10+5+7=22
    return 0;
}
```

---

## 3. Disjoint Set Union (Union-Find)

**Definition:**  
A Disjoint Set (Union-Find) is a data structure that keeps track of a partition of a set into disjoint subsets.

**Use Cases:**  
- Network connectivity  
- Kruskal's MST algorithm  
- Connected components

**Operations:**  
- Find (with path compression)  
- Union (by rank/size)

**Complexity:**  
- Nearly O(1) per operation (amortized, using path compression and union by rank)

**C++ Example:**
```cpp
// filepath: example_union_find.cpp
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else { parent[yr] = xr; rank[xr]++; }
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};
int main() {
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(1, 2);
    cout << uf.connected(0, 2) << endl; // 1
    cout << uf.connected(0, 3) << endl; // 0
    return 0;
}
```

---

## 4. Fenwick Tree (Binary Indexed Tree)

**Definition:**  
A Fenwick Tree is a data structure that provides efficient methods for cumulative frequency tables and prefix sums.

**Use Cases:**  
- Range sum queries  
- Frequency counting  
- Inversion count

**Operations:**  
- Update  
- Query (prefix sum)

**Complexity:**  
- Update/Query: O(log n)

**C++ Example:**
```cpp
// filepath: example_fenwick_tree.cpp
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
    vector<int> bit;
    int n;
public:
    FenwickTree(int size) : n(size) { bit.assign(n+1, 0); }
    void update(int idx, int delta) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }
    int query(int idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
    int rangeQuery(int l, int r) {
        return query(r) - query(l-1);
    }
};
int main() {
    FenwickTree ft(5);
    ft.update(0, 1);
    ft.update(1, 2);
    ft.update(2, 3);
    cout << ft.rangeQuery(0, 2) << endl; // 1+2+3=6
    return 0;
}
```

---

## 5. Suffix Tree and Suffix Array

**Definition:**  
- **Suffix Tree:** A compressed trie of all the suffixes of a given string.
- **Suffix Array:** A sorted array of all suffixes of a string.

**Use Cases:**  
- Fast substring search  
- Longest repeated substring  
- Pattern matching

**Operations:**  
- Build  
- Search

**Complexity:**  
- Suffix Array Build: O(n log n)  
- Suffix Tree Build: O(n) (advanced algorithms)

**C++ Example (Suffix Array):**
```cpp
// filepath: example_suffix_array.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> buildSuffixArray(const string& s) {
    int n = s.size();
    vector<pair<string, int>> suffixes;
    for (int i = 0; i < n; ++i)
        suffixes.push_back({s.substr(i), i});
    sort(suffixes.begin(), suffixes.end());
    vector<int> sa;
    for (auto& p : suffixes) sa.push_back(p.second);
    return sa;
}
int main() {
    string s = "banana";
    vector<int> sa = buildSuffixArray(s);
    for (int idx : sa) cout << idx << " "; // 5 3 1 0 4 2
    cout << endl;
    return 0;
}
```

---

## 6. Bloom Filter

**Definition:**  
A Bloom Filter is a probabilistic data structure for set membership queries, allowing false positives but no false negatives.

**Use Cases:**  
- Caching  
- Databases  
- Network security

**Operations:**  
- Insert  
- Query

**Complexity:**  
- O(k) per operation, where k is the number of hash functions

**C++ Example:**
```cpp
// filepath: example_bloom_filter.cpp
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class BloomFilter {
    vector<bool> bitArray;
    int size;
    hash<string> hash_fn;
public:
    BloomFilter(int sz) : size(sz), bitArray(sz) {}
    void insert(const string& s) {
        int h1 = hash_fn(s) % size;
        int h2 = (hash_fn(s + "salt") % size);
        bitArray[h1] = true;
        bitArray[h2] = true;
    }
    bool possiblyContains(const string& s) {
        int h1 = hash_fn(s) % size;
        int h2 = (hash_fn(s + "salt") % size);
        return bitArray[h1] && bitArray[h2];
    }
};
int main() {
    BloomFilter bf(100);
    bf.insert("hello");
    cout << bf.possiblyContains("hello") << endl; // 1
    cout << bf.possiblyContains("world") << endl; // 0 (most likely)
    return 0;
}
```

---

## Conclusion

Mastering these advanced data structures will significantly enhance your ability to solve complex algorithmic problems efficiently. Practice implementing and applying them to various problems to solidify your understanding.

---