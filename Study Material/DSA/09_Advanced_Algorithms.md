# Advanced Algorithm Techniques

This document provides a comprehensive overview of advanced algorithm techniques, including detailed explanations, real-world applications, and C++ code examples. Mastering these techniques is essential for solving complex computational problems efficiently and excelling in technical interviews.

---

## 1. Divide and Conquer

**Definition:**  
Divide and Conquer is a paradigm that recursively breaks a problem into smaller subproblems, solves each independently, and then combines their solutions to solve the original problem.

**Key Characteristics:**
- Recursive decomposition
- Reduces problem size at each step
- Often leads to efficient algorithms (e.g., O(n log n) time)

**Applications:**
- Sorting large datasets (Merge Sort, Quick Sort)
- Searching (Binary Search)
- Matrix multiplication (Strassen's Algorithm)
- Closest pair of points problem

### Example: Merge Sort (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```

### Example: Binary Search (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <vector>
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

---

## 2. Greedy Algorithms

**Definition:**  
Greedy algorithms build up a solution piece by piece, always choosing the next piece that offers the most immediate benefit.

**Key Characteristics:**
- Makes locally optimal choices
- May not always yield a globally optimal solution
- Often simple and efficient

**Applications:**
- Scheduling (Activity Selection)
- Minimum Spanning Tree (Kruskal's, Prim's)
- Huffman Coding (Data Compression)
- Coin Change (when denominations are canonical)

### Example: Activity Selection Problem (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish;
};

bool compare(Activity a, Activity b) {
    return a.finish < b.finish;
}

void activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compare);
    cout << "Selected activities:\n";
    int lastFinish = -1;
    for (auto& act : activities) {
        if (act.start >= lastFinish) {
            cout << "[" << act.start << ", " << act.finish << "]\n";
            lastFinish = act.finish;
        }
    }
}
```

### Example: Huffman Coding (C++ - Conceptual)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <queue>
#include <vector>
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};
struct Compare {
    bool operator()(Node* l, Node* r) { return l->freq > r->freq; }
};
Node* buildHuffmanTree(const vector<pair<char, int>>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freq) pq.push(new Node(p.first, p.second));
    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node('\0', l->freq + r->freq);
        parent->left = l; parent->right = r;
        pq.push(parent);
    }
    return pq.top();
}
```

---

## 3. Dynamic Programming

**Definition:**  
Dynamic Programming (DP) solves complex problems by breaking them down into simpler subproblems and storing the results to avoid redundant computations.

**Key Characteristics:**
- Overlapping subproblems
- Optimal substructure
- Uses memoization or tabulation

**Applications:**
- Resource allocation (Knapsack)
- Sequence alignment (Longest Common Subsequence)
- Pathfinding (Floyd-Warshall, Bellman-Ford)
- Counting problems (Coin Change, Catalan numbers)

### Example: 0/1 Knapsack Problem (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <iostream>
#include <vector>
using namespace std;

int knapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (wt[i-1] <= w)
                dp[i][w] = max(dp[i-1][w], val[i-1] + dp[i-1][w-wt[i-1]]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}
```

### Example: Longest Common Subsequence (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <string>
#include <vector>
int lcs(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i-1] == b[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}
```

---

## 4. Backtracking

**Definition:**  
Backtracking is a general algorithm for finding all (or some) solutions to computational problems by incrementally building candidates and abandoning a candidate as soon as it is determined that it cannot lead to a valid solution.

**Key Characteristics:**
- Recursive exploration
- Explores all possibilities
- Prunes branches that cannot yield a valid solution

**Applications:**
- Constraint satisfaction (N-Queens, Sudoku)
- Generating permutations/combinations
- Puzzle solving (Crossword, Maze)

### Example: N-Queens Problem (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q') return false;
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q') return false;
    for (int i = row-1, j = col+1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q') return false;
    return true;
}

void solveNQueensUtil(int row, int n, vector<string>& board, vector<vector<string>>& res) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueensUtil(row+1, n, board, res);
            board[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    solveNQueensUtil(0, n, board, res);
    return res;
}
```

### Example: Generating All Permutations (C++)

```cpp
// filepath: c:\Users\Gautam Sharma\Documents\GitHub\Practice_Code\Study Material\DSA\09_Advanced_Algorithms.md
#include <vector>
#include <algorithm>
void permute(std::vector<int>& nums, int l, int r, std::vector<std::vector<int>>& res) {
    if (l == r) {
        res.push_back(nums);
        return;
    }
    for (int i = l; i <= r; ++i) {
        std::swap(nums[l], nums[i]);
        permute(nums, l+1, r, res);
        std::swap(nums[l], nums[i]);
    }
}
```

---

## Practice Problems

- [Merge Sort Implementation](https://leetcode.com/problems/sort-an-array/)
- [Quick Sort Implementation](https://www.geeksforgeeks.org/quick-sort/)
- [Binary Search Implementation](https://leetcode.com/problems/binary-search/)
- [Activity Selection Problem](https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/)
- [Huffman Coding](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)
- [Kruskal's Algorithm](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm/)
- [Fibonacci Sequence](https://leetcode.com/problems/fibonacci-number/)
- [0/1 Knapsack Problem](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)
- [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
- [N-Queens Problem](https://leetcode.com/problems/n-queens/)
- [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)
- [Permutations](https://leetcode.com/problems/permutations/)

---

## Conclusion

A solid understanding of these advanced algorithm techniques is crucial for tackling complex problems in competitive programming and technical interviews. Practice the provided examples and problems to deepen your mastery and develop strong problem-solving skills.