# Graph Data Structures

## 1. Graph Terminology
- **Graph**: A collection of nodes (vertices) and edges connecting pairs of nodes.
- **Vertex**: A single node in a graph.
- **Edge**: A connection between two vertices.
- **Directed Graph**: A graph where edges have a direction (from one vertex to another).
- **Undirected Graph**: A graph where edges do not have a direction.
- **Weighted Graph**: A graph where edges have weights (costs).
- **Degree**: The number of edges connected to a vertex.
  - In directed graphs: **In-degree** (edges coming in) and **Out-degree** (edges going out)
- **Path**: A sequence of vertices where each adjacent pair is connected by an edge.
- **Cycle**: A path that starts and ends at the same vertex.
- **Connected Graph**: A graph where there is a path between every pair of vertices.
- **Disconnected Graph**: A graph that is not connected.
- **Acyclic Graph**: A graph with no cycles.
- **DAG**: Directed Acyclic Graph - a directed graph with no cycles.

## 2. Graph Representations

### Adjacency Matrix
A 2D array where the cell at row i and column j indicates the presence (and weight) of an edge between vertices i and j.

#### C++ Implementation:
```cpp
// Adjacency Matrix representation
#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        // For undirected graph
        // adjMatrix[v][u] = weight;
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j = 0; j < V; j++) {
                if (adjMatrix[i][j] != 0)
                    cout << "(" << j << "," << adjMatrix[i][j] << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    
    cout << "Adjacency Matrix Representation:" << endl;
    g.printGraph();
    return 0;
}
```

**Time Complexity:**
- Space: O(V²) where V is the number of vertices
- Edge Insertion: O(1)
- Edge Deletion: O(1)
- Edge Query: O(1)

**Pros and Cons:**
- **Pros**: Fast edge lookup, simple to implement
- **Cons**: High space complexity, especially for sparse graphs

### Adjacency List
An array of lists where each list corresponds to a vertex and contains a list of its adjacent vertices.

#### C++ Implementation:
```cpp
// Adjacency List representation
#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adjList; // vertex, weight

public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight = 1) {
        adjList[u].push_back({v, weight});
        // For undirected graph
        // adjList[v].push_back({u, weight});
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (auto neighbor : adjList[i]) {
                cout << "(" << neighbor.first << "," << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    
    cout << "Adjacency List Representation:" << endl;
    g.printGraph();
    return 0;
}
```

**Expected Output:**
```
Adjacency List Representation:
0: (1,1) (2,1) 
1: (0,1) (3,1) 
2: (0,1) 
3: (1,1) 
```

**Time Complexity:**
- Space: O(V + E) where V is the number of vertices and E is the number of edges
- Edge Insertion: O(1)
- Edge Deletion: O(degree(V))
- Edge Query: O(degree(V))

**Pros and Cons:**
- **Pros**: Space-efficient for sparse graphs
- **Cons**: Slower edge lookups compared to adjacency matrix

## 3. Graph Traversals

### Depth-First Search (DFS)
A traversal method that explores as far as possible along each branch before backtracking.

#### C++ Implementation:
```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Recursive DFS
    void DFS_recursive(int start) {
        vector<bool> visited(V, false);
        DFS_util(start, visited);
    }

    void DFS_util(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                DFS_util(neighbor, visited);
            }
        }
    }

    // Iterative DFS
    void DFS_iterative(int start) {
        vector<bool> visited(V, false);
        stack<int> stack;
        
        stack.push(start);
        while (!stack.empty()) {
            int vertex = stack.top();
            stack.pop();
            
            if (!visited[vertex]) {
                cout << vertex << " ";
                visited[vertex] = true;
            }
            
            // Push all adjacent vertices to stack
            for (auto it = adjList[vertex].rbegin(); it != adjList[vertex].rend(); ++it) {
                if (!visited[*it]) {
                    stack.push(*it);
                }
            }
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    
    cout << "DFS Recursive starting from vertex 0: ";
    g.DFS_recursive(0);
    cout << endl;
    
    cout << "DFS Iterative starting from vertex 0: ";
    g.DFS_iterative(0);
    cout << endl;
    
    return 0;
}
```

**Time Complexity:** O(V + E) where V is the number of vertices and E is the number of edges.

**Applications of DFS:**
- Finding connected components
- Topological sorting
- Detecting cycles in a graph
- Solving maze puzzles
- Path finding algorithms

### Breadth-First Search (BFS)
A traversal method that explores all neighbors at the present depth prior to moving on to nodes at the next depth level.

#### C++ Implementation:
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            cout << vertex << " ";
            queue.pop();
            
            for (int neighbor : adjList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }

    // BFS for shortest path (returns distances from start)
    vector<int> BFS_shortestPath(int start) {
        vector<int> distance(V, -1);
        queue<int> queue;
        
        distance[start] = 0;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            
            for (int neighbor : adjList[vertex]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[vertex] + 1;
                    queue.push(neighbor);
                }
            }
        }
        
        return distance;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    
    cout << "BFS starting from vertex 0: ";
    g.BFS(0);
    cout << endl;
    
    vector<int> distances = g.BFS_shortestPath(0);
    cout << "Shortest distances from vertex 0:" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Distance to " << i << ": " << distances[i] << endl;
    }
    
    return 0;
}
```

**Time Complexity:** O(V + E) where V is the number of vertices and E is the number of edges.

**Applications of BFS:**
- Finding shortest paths in unweighted graphs
- Finding connected components
- Testing bipartiteness
- Web crawling
- Network broadcasting

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