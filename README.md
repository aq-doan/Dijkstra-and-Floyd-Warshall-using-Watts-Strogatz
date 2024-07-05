# Graph Algorithms Project

This project implements and tests the Dijkstra's and Floyd-Warshall shortest path algorithms on a Watts-Strogatz graph.

## Introduction

This project focuses on comparing the performance of Dijkstra's and Floyd-Warshall algorithms for finding the shortest paths in a graph. It generates a Watts-Strogatz small-world graph and measures the execution time and memory usage of both algorithms.

## Features

- **Graph Generation**: Creates a Watts-Strogatz small-world graph.
- **Shortest Path Algorithms**:
  - **Dijkstra's Algorithm**: Computes the shortest path from a source vertex to a target vertex.
  - **Floyd-Warshall Algorithm**: Computes shortest paths between all pairs of vertices.
- **Performance Metrics**: Measures execution time and memory usage for each algorithm.
- **Output**: Prints the shortest path, total distance, execution time, and memory usage.

## Setup

### Prerequisites

- C compiler (e.g., `gcc`)

### Compilation

Compile the project using the following command:

```sh
gcc -o graph_algorithms main.c graph.c -std=c99
