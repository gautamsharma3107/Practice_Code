# Pattern Printing Questions (with Python & C++ Solutions)

Mastering loops is essential for pattern printing. Here are some classic problems with solutions.

---

## 1. Solid Rectangle

```
****
****
****
****
```

**Python**
```python
rows, cols = 4, 4
for i in range(rows):
    print('*' * cols)
```

**C++**
```cpp
int rows = 4, cols = 4;
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        std::cout << "*";
    }
    std::cout << std::endl;
}
```

---

## 2. Hollow Rectangle

```
****
*  *
*  *
****
```

**Python**
```python
rows, cols = 4, 4
for i in range(rows):
    if i == 0 or i == rows - 1:
        print('*' * cols)
    else:
        print('*' + ' ' * (cols - 2) + '*')
```

**C++**
```cpp
int rows = 4, cols = 4;
for (int i = 0; i < rows; ++i) {
    if (i == 0 || i == rows - 1) {
        for (int j = 0; j < cols; ++j) std::cout << "*";
    } else {
        std::cout << "*";
        for (int j = 0; j < cols - 2; ++j) std::cout << " ";
        std::cout << "*";
    }
    std::cout << std::endl;
}
```

---

## 3. Right-Angled Triangle

```
*
**
***
****
```

**Python**
```python
n = 4
for i in range(1, n + 1):
    print('*' * i)
```

**C++**
```cpp
int n = 4;
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

## 4. Inverted Right-Angled Triangle

```
****
***
**
*
```

**Python**
```python
n = 4
for i in range(n, 0, -1):
    print('*' * i)
```

**C++**
```cpp
int n = 4;
for (int i = n; i >= 1; --i) {
    for (int j = 0; j < i; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

## 5. Number Triangle

```
1
12
123
1234
```

**Python**
```python
n = 4
for i in range(1, n + 1):
    for j in range(1, i + 1):
        print(j, end='')
    print()
```

**C++**
```cpp
int n = 4;
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) std::cout << j;
    std::cout << std::endl;
}
```

---

## 6. Pyramid Pattern

```
   *
  ***
 *****
*******
```

**Python**
```python
n = 4
for i in range(n):
    print(' ' * (n - i - 1) + '*' * (2 * i + 1))
```

**C++**
```cpp
int n = 4;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - i - 1; ++j) std::cout << " ";
    for (int j = 0; j < 2 * i + 1; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

## 7. Inverted Pyramid

```
*******
 *****
  ***
   *
```

**Python**
```python
n = 4
for i in range(n):
    print(' ' * i + '*' * (2 * (n - i) - 1))
```

**C++**
```cpp
int n = 4;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) std::cout << " ";
    for (int j = 0; j < 2 * (n - i) - 1; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

## 8. Diamond Pattern

```
   *
  ***
 *****
*******
 *****
  ***
   *
```

**Python**
```python
n = 4
for i in range(n):
    print(' ' * (n - i - 1) + '*' * (2 * i + 1))
for i in range(n - 2, -1, -1):
    print(' ' * (n - i - 1) + '*' * (2 * i + 1))
```

**C++**
```cpp
int n = 4;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - i - 1; ++j) std::cout << " ";
    for (int j = 0; j < 2 * i + 1; ++j) std::cout << "*";
    std::cout << std::endl;
}
for (int i = n - 2; i >= 0; --i) {
    for (int j = 0; j < n - i - 1; ++j) std::cout << " ";
    for (int j = 0; j < 2 * i + 1; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

## 9. Floyd's Triangle

```
1
2 3
4 5 6
7 8 9 10
```

**Python**
```python
n = 4
num = 1
for i in range(1, n + 1):
    for j in range(i):
        print(num, end=' ')
        num += 1
    print()
```

**C++**
```cpp
int n = 4, num = 1;
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
        std::cout << num << " ";
        ++num;
    }
    std::cout << std::endl;
}
```

---

## 10. Butterfly Pattern

```
*      *
**    **
***  ***
********
********
***  ***
**    **
*      *
```

**Python**
```python
n = 4
for i in range(1, n + 1):
    print('*' * i + ' ' * (2 * (n - i)) + '*' * i)
for i in range(n, 0, -1):
    print('*' * i + ' ' * (2 * (n - i)) + '*' * i)
```

**C++**
```cpp
int n = 4;
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) std::cout << "*";
    for (int j = 0; j < 2 * (n - i); ++j) std::cout << " ";
    for (int j = 0; j < i; ++j) std::cout << "*";
    std::cout << std::endl;
}
for (int i = n; i >= 1; --i) {
    for (int j = 0; j < i; ++j) std::cout << "*";
    for (int j = 0; j < 2 * (n - i); ++j) std::cout << " ";
    for (int j = 0; j < i; ++j) std::cout << "*";
    std::cout << std::endl;
}
```

---

Practice these patterns to master loops and nested loops!
