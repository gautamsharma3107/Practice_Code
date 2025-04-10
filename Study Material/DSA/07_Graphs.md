# Graph Data Structures

## 1. Graph Terminology
- **Graph**: A collection of nodes (vertices) and edges connecting pairs of nodes.
- **Vertex**: A single node in a graph.
- **Edge**: A connection between two vertices.
- **Directed Graph**: A graph where edges have a direction (from one vertex to another).
- **Undirected Graph**: A graph where edges do not have a direction.
- **Weighted Graph**: A graph where edges have weights (costs).
- **Degree**: The number of edges connected to a vertex.

## 2. Graph Representations
- **Adjacency Matrix**: A 2D array where the cell at row i and column j indicates the presence (and weight) of an edge between vertices i and j.
- **Adjacency List**: An array of lists where each list corresponds to a vertex and contains a list of its adjacent vertices.

### Example of Adjacency List Representation
```
0: [1, 2]
1: [0, 3]
2: [0]
3: [1]
```

## 3. Graph Traversals
- **Depth-First Search (DFS)**: A traversal method that explores as far as possible along each branch before backtracking.
- **Breadth-First Search (BFS)**: A traversal method that explores all neighbors at the present depth prior to moving on to nodes at the next depth level.

### Problem Exercises
1. Implement DFS and BFS for a graph represented as an adjacency list.
   - [DFS Problem](https://leetcode.com/problems/number-of-islands/)
   - [BFS Problem](https://leetcode.com/problems/clone-graph/)

## 4. Shortest Path Algorithms
- **Dijkstra's Algorithm**: Finds the shortest path from a source vertex to all other vertices in a weighted graph with non-negative weights.
- **Bellman-Ford Algorithm**: Computes shortest paths from a single source vertex to all vertices in a graph, handling negative weights.
- **Floyd-Warshall Algorithm**: A dynamic programming algorithm to find shortest paths in a weighted graph with positive or negative edge weights (but no negative cycles).

### Problem Exercises
1. Implement Dijkstra's algorithm.
   - [Dijkstra's Problem](https://leetcode.com/problems/network-delay-time/)
2. Implement Bellman-Ford algorithm.
   - [Bellman-Ford Problem](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
3. Implement Floyd-Warshall algorithm.
   - [Floyd-Warshall Problem](https://leetcode.com/problems/cheapest-flights-within-k-stops/)

## 5. Minimum Spanning Trees
- **Kruskal's Algorithm**: A greedy algorithm that finds the minimum spanning tree for a connected weighted graph.
- **Prim's Algorithm**: Another greedy algorithm that builds the minimum spanning tree by adding edges one at a time.

### Problem Exercises
1. Implement Kruskal's algorithm.
   - [Kruskal's Problem](https://leetcode.com/problems/connecting-cities-with-minimum-cost/)
2. Implement Prim's algorithm.
   - [Prim's Problem](https://leetcode.com/problems/minimum-spanning-tree/)

## 6. Topological Sorting
- A linear ordering of vertices in a directed acyclic graph (DAG) such that for every directed edge u -> v, vertex u comes before v in the ordering.

### Problem Exercises
1. Implement topological sorting using DFS.
   - [Topological Sort Problem](https://leetcode.com/problems/course-schedule/)
2. Implement Kahn's algorithm for topological sorting.
   - [Kahn's Algorithm Problem](https://leetcode.com/problems/course-schedule-ii/)

## Conclusion
Understanding graph data structures and their algorithms is crucial for solving complex problems in computer science. Practice implementing these concepts through the provided exercises to strengthen your skills.