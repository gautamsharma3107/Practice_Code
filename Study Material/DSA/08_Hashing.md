# Hashing

## Introduction to Hashing
Hashing is a technique used to uniquely identify a specific object from a group of similar objects. It is commonly used in data structures such as hash tables to enable fast data retrieval.

## Hash Functions
A hash function takes an input (or 'key') and returns a fixed-size string of bytes. The output is typically a hash code that represents the input data. A good hash function has the following properties:
- **Deterministic**: The same input will always produce the same output.
- **Fast computation**: The hash function should be quick to compute.
- **Uniform distribution**: The hash values should be uniformly distributed to minimize collisions.

### Common Hash Functions
- **Division Method**: Hash value is computed as `key mod table_size`.
- **Multiplication Method**: Hash value is computed using a constant multiplier.
- **Cryptographic Hash Functions**: Such as SHA-256, used for security purposes.

## Collision Resolution Techniques
When two keys hash to the same index, a collision occurs. There are several techniques to handle collisions:
1. **Chaining**: Each index in the hash table points to a linked list of entries that hash to the same index.
2. **Open Addressing**: All elements are stored in the hash table itself. If a collision occurs, the algorithm searches for the next available slot.
   - **Linear Probing**: Check the next slot sequentially.
   - **Quadratic Probing**: Check slots at intervals of squares.
   - **Double Hashing**: Use a second hash function to determine the step size.

## Load Factor and Rehashing
- **Load Factor**: The ratio of the number of entries to the number of slots in the hash table. A higher load factor increases the chance of collisions.
- **Rehashing**: When the load factor exceeds a certain threshold, the hash table is resized, and all existing entries are rehashed to the new table.

## Applications of Hashing
- **Data Retrieval**: Fast access to data using keys.
- **Caching**: Storing frequently accessed data for quick retrieval.
- **Data Integrity**: Verifying data integrity using hash values.
- **Cryptography**: Ensuring secure data transmission.

## Problem Exercises
1. Implement a hash table with collision resolution using chaining.
   - [LeetCode Problem: Design a HashMap](https://leetcode.com/problems/design-a-hashmap/)
   
2. Implement a hash table with open addressing.
   - [GeeksforGeeks Problem: Implement Hash Table](https://www.geeksforgeeks.org/design-a-hash-table/)
   
3. Analyze the performance of different collision resolution techniques.
   - [HackerRank Problem: Hash Tables - Ransom Note](https://www.hackerrank.com/challenges/ctci-ransom-note/problem)

4. Create a program to demonstrate the load factor and rehashing.
   - [CodeSignal Problem: Hash Table](https://codesignal.com/)

5. Solve a problem using hashing to find duplicates in an array.
   - [LeetCode Problem: Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) 

## Conclusion
Hashing is a powerful technique that enhances the efficiency of data retrieval and storage. Understanding hash functions, collision resolution techniques, and their applications is crucial for implementing effective data structures.