# Modern C++ Features

This document covers various modern features introduced in C++11 and later versions, enhancing the language's usability, performance, and safety.

## 1. Auto Keyword and Type Inference
- The `auto` keyword allows the compiler to automatically deduce the type of a variable from its initializer.
- Example:
  ```cpp
  auto x = 5; // x is of type int
  auto y = 3.14; // y is of type double
  ```

## 2. Range-Based For Loops
- A simpler syntax for iterating over containers.
- Example:
  ```cpp
  std::vector<int> vec = {1, 2, 3, 4, 5};
  for (auto& element : vec) {
      std::cout << element << " ";
  }
  ```

## 3. Lambda Expressions
- Anonymous functions that can be defined inline.
- Example:
  ```cpp
  auto add = [](int a, int b) { return a + b; };
  std::cout << add(5, 3); // Outputs 8
  ```

## 4. nullptr
- A type-safe null pointer constant.
- Example:
  ```cpp
  int* ptr = nullptr; // ptr is a null pointer
  ```

## 5. Smart Pointers
- `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr` help manage dynamic memory automatically.
- Example:
  ```cpp
  std::unique_ptr<int> ptr(new int(5));
  ```

## 6. Move Semantics and Rvalue References
- Allows resources to be moved rather than copied, improving performance.
- Example:
  ```cpp
  std::vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = std::move(vec1); // vec1 is now empty
  ```

## 7. std::tuple and std::pair
- `std::pair` holds two values, while `std::tuple` can hold multiple values of different types.
- Example:
  ```cpp
  std::pair<int, std::string> p = {1, "example"};
  std::tuple<int, double, std::string> t = {1, 3.14, "tuple"};
  ```

## 8. std::optional and std::variant
- `std::optional` represents an optional value, while `std::variant` can hold one of several types.
- Example:
  ```cpp
  std::optional<int> opt = 5; // or std::nullopt
  std::variant<int, std::string> var = "Hello";
  ```

## 9. Concurrency and Multithreading
- C++11 introduced a standard library for multithreading, including `std::thread`, `std::mutex`, and `std::future`.
- Example:
  ```cpp
  std::thread t([] { std::cout << "Hello from thread!"; });
  t.join();
  ```

## 10. Regular Expressions
- Support for regular expressions is provided through the `<regex>` library.
- Example:
  ```cpp
  std::regex pattern(R"(\d+)");
  std::string text = "There are 123 apples";
  std::smatch match;
  if (std::regex_search(text, match, pattern)) {
      std::cout << "Found: " << match[0] << std::endl;
  }
  ```

## Problem Exercises
1. **Auto Keyword**: Create a function that returns a vector of integers and use `auto` to iterate through it.
   - [LeetCode Problem](https://leetcode.com/problems/two-sum/)
   
2. **Range-Based For Loops**: Write a program that takes a list of numbers and prints their squares using a range-based for loop.
   - [HackerRank Problem](https://www.hackerrank.com/challenges/c-tutorial-for-loop/problem)

3. **Lambda Expressions**: Implement a sorting function using a lambda expression.
   - [Codewars Problem](https://www.codewars.com/kata/sort-the-odd/train/cpp)

4. **Smart Pointers**: Create a class that uses smart pointers to manage its resources.
   - [GeeksforGeeks Problem](https://www.geeksforgeeks.org/smart-pointers-in-c/)

5. **Concurrency**: Write a program that spawns multiple threads to perform a task concurrently.
   - [LeetCode Problem](https://leetcode.com/problems/print-in-order/)

6. **Regular Expressions**: Validate an email address using regular expressions.
   - [HackerRank Problem](https://www.hackerrank.com/challenges/validating-email-addresses-with-a-filter/problem)

These exercises will help reinforce your understanding of modern C++ features and their applications.