# Snap Urban Routing System

A C++ urban routing system inspired by intelligent city navigation applications. The project models a city network as a weighted directed graph and implements shortest-path algorithms and multi-destination route planning.

## Overview

The Snap Urban Routing System simulates urban navigation by representing intersections as vertices and roads as directed edges.

Instead of considering distance alone, the system calculates route costs using multiple factors, including road distance, traffic conditions, weather or road-condition weights, and intersection delays.

The application supports single-destination shortest-path queries, negative-cycle detection, and multi-destination route planning for delivery scenarios.

## Features

### 🗺️ Graph Modeling

- Directed, weighted graph representation
- Adjacency-list data structure
- Edge and intersection-delay modeling
- File-based graph loading
- Input validation and error handling

### 🧭 Shortest-Path Algorithms

- **Dijkstra's Algorithm** for graphs without negative edge weights
- **Bellman-Ford Algorithm** for graphs with negative edge weights
- Shortest-path reconstruction
- Detection of reachable negative cycles
- Handling of unreachable destinations

### 🛵 Multi-Destination Route Planning

- Nearest Neighbor heuristic for selecting the next destination
- Repeated shortest-path queries between destinations
- Route construction across multiple destinations
- Return-to-start routing
- Total route-cost calculation
- Handling of unreachable destinations and negative cycles

### 🛡️ Input Validation & Error Handling

- Graph configuration validation
- Edge endpoint validation
- Rejection of negative distance, traffic, and road-condition inputs
- Source and destination validation
- Missing or malformed input detection
- Informative error messages for invalid graph data

### 🧪 Testing & Evaluation

- Nine test input files
- Tests for invalid graph data
- Unreachable destination scenarios
- Negative-edge handling
- Negative-cycle detection
- Successful single-destination and multi-destination routing scenarios

## Technologies Used

- **C++**
- **Standard Template Library (STL)**
- **Graph Data Structures**
- **Priority Queue / Min-Heap**
- **File I/O**
- **Graph Algorithms**

## Project Structure

```text
Snap-Urban-Routing-System/
├── main.cpp
├── graph.cpp
├── graph.h
├── dijkstra.cpp
├── dijkstra.h
├── bellman_ford.cpp
├── bellman_ford.h
├── nearest_neighbor.cpp
├── nearest_neighbor.h
├── map.txt
├── test1.txt
├── test2.txt
├── test3.txt
├── test4.txt
├── test5.txt
├── test6.txt
├── test7.txt
├── test8.txt
├── test9.txt
├── DA-Project-Report.pdf
├── DA-Project-Report.docx
└── README.md
```

## Getting Started

### Prerequisites

Before running the application, make sure you have:

- A C++ compiler that supports C++11 or later
- GCC / G++ or an equivalent C++ compiler
- A terminal or command-line environment

### Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/parnyaazimi/Snap-Urban-Routing-System.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Snap-Urban-Routing-System
   ```

3. Compile the source files using G++:

   ```bash
   g++ -std=c++11 -O2 main.cpp graph.cpp dijkstra.cpp bellman_ford.cpp nearest_neighbor.cpp -o routing
   ```

4. Run the application from the project directory:

   ```bash
   ./routing
   ```

   On Windows, run the generated executable with:

   ```cmd
   routing.exe
   ```

> **Note:** The application loads `map.txt` from the current working directory. Make sure the file is available there before running the program.

## Input Format

The graph is loaded from a text file containing the number of nodes, the number of edges, node delays, edge definitions, and the source and destination nodes.

The input structure is:

1. The first line contains the number of nodes (`N`) and edges (`M`).
2. The next `N` values specify the delay associated with each node.
3. The next `M` lines define directed edges using the format:

   ```text
   from to distance traffic road_condition
   ```

4. The final line contains the source node followed by one or more destination nodes.

When a single destination is provided, the application calculates a shortest path. When multiple destinations are provided, it uses the Nearest Neighbor heuristic to construct a route that visits all requested destinations and returns to the source.

Node indices are zero-based.

## Algorithms

### Dijkstra's Algorithm

Uses a minimum-priority queue to calculate shortest paths in graphs with non-negative edge costs.

### Bellman-Ford Algorithm

Relaxes graph edges repeatedly to calculate shortest paths when negative edge costs are present. It also checks for reachable negative cycles.

### Nearest Neighbor

A greedy heuristic for multi-destination routing. At each step, it selects the nearest reachable unvisited destination based on the calculated shortest-path cost. After visiting all destinations, it attempts to return to the starting node.

> **Note:** Nearest Neighbor is a heuristic and does not guarantee the globally optimal multi-destination route.

## Cost Model

The cost of traversing an edge is calculated using the following model:

```text
cost = (distance × traffic × road_condition) + destination_delay
```

The destination intersection's delay is added to the physical and environmental edge-cost factors.

## 🤝 Teamwork & Acknowledgements

This project was developed collaboratively with a teammate as part of a university course project. We shared responsibilities equally throughout the design and implementation of the urban routing system, working together to achieve the project's objectives.

I appreciate my teammate's collaboration and contributions throughout the project.

## Academic Information

- **Course:** Algorithm Analysis and Design
- **Academic Level:** Bachelor's Degree - Fourth Semester
- **Project Type:** Team University Course Project
- **Instructor:** Dr. Arman Sepehr
- **Completion Date:** July 2026

## Project Purpose

This project demonstrates the practical application of graph theory, shortest-path algorithms, greedy heuristics, input validation, and computational complexity analysis in an urban navigation scenario.
