# Comprehensive Guide to Problem-Solving Strategies in DSA

This document provides detailed strategies, explanations, and C++ code examples to help you master problem-solving in Data Structures and Algorithms (DSA).

---

## 1. Problem Decomposition

**Definition:**  
Break a complex problem into smaller, manageable sub-problems. Solve each independently, then combine the results.

**Example:**  
*Problem:* Find the sum of all even numbers in an array.

```cpp
// Decompose: (1) Filter even numbers, (2) Sum them
#include <iostream>
#include <vector>
using namespace std;

int sumOfEvens(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 == 0) sum += num;
    }
    return sum;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    cout << sumOfEvens(arr) << endl; // Output: 12
}
```

---

## 2. Pattern Recognition

**Definition:**  
Identify recurring patterns or structures in problems to apply known solutions or algorithms.

**Example:**  
*Problem:* Fibonacci sequence (classic DP pattern).

```cpp
#include <iostream>
#include <vector>
using namespace std;

int fibonacci(int n) {
    vector<int> dp(n+1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}

int main() {
    cout << fibonacci(6) << endl; // Output: 8
}
```

---

## 3. Time-Space Tradeoffs

**Definition:**  
Optimize between time and space complexity based on problem constraints.

**Example:**  
*Problem:* Find if an array contains duplicates.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool hasDuplicate(const vector<int>& arr) {
    unordered_set<int> seen;
    for (int num : arr) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 2};
    cout << (hasDuplicate(arr) ? "Yes" : "No") << endl; // Output: Yes
}
```
*Note:* Using a set increases space usage but reduces time complexity.

---

## 4. Incremental Approach

**Definition:**  
Start with a simple solution, then iteratively improve and optimize it.

**Example:**  
*Problem:* Reverse a string.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Initial simple approach
string reverseString(string s) {
    string res = "";
    for (int i = s.size()-1; i >= 0; --i)
        res += s[i];
    return res;
}

// Optimized in-place approach
void reverseStringInPlace(string& s) {
    int l = 0, r = s.size()-1;
    while (l < r) swap(s[l++], s[r--]);
}

int main() {
    string s = "hello";
    cout << reverseString(s) << endl; // Output: olleh
    reverseStringInPlace(s);
    cout << s << endl; // Output: olleh
}
```

---

## 5. Iterative Refinement

**Definition:**  
Continuously refine your solution using feedback, testing, and debugging.

**Example:**  
*Problem:* Find the maximum subarray sum (Kadane's Algorithm).

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxSubArraySum(const vector<int>& arr) {
    int maxSum = arr[0], currSum = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        currSum = max(arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << maxSubArraySum(arr) << endl; // Output: 6
}
```

---

## 6. Competitive Programming Strategies

- Practice regularly on platforms like LeetCode, Codeforces, AtCoder, etc.
- Focus on speed and accuracy.
- Learn to read and implement algorithms quickly.

**Example:**  
*Problem:* Check if a number is prime (frequent in contests).

```cpp
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    cout << (isPrime(17) ? "Prime" : "Not Prime") << endl; // Output: Prime
}
```

---

## 7. Interview Problem-Solving Techniques

- Practice explaining your thought process.
- Use whiteboard or paper to outline your approach.
- Communicate trade-offs and alternatives.

**Example:**  
*Problem:* Reverse a linked list.

```cpp
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
```

---

## Additional Resources

- [GeeksforGeeks Problem-Solving Techniques](https://www.geeksforgeeks.org/fundamentals-of-algorithms/)
- [TopCoder Tutorials](https://www.topcoder.com/community/competitive-programming/tutorials/)
- [LeetCode Explore](https://leetcode.com/explore/)
- [CP Algorithms](https://cp-algorithms.com/)

---

By mastering these strategies and practicing with real problems, you'll become a more effective and confident problem solver in DSA and coding interviews.