
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "graph.h"
#define NUM_VERTICES 1000

// Function to generate a random weight between 1 and 100
int generate_random_weight() {
    return rand() % 100 + 1; // Generate random weight between 1 and 100
}

// Function to create a graph with random weighted edges
Graph create_random_graph(int num_vertices) {
    Graph G = new_g(num_vertices);

    // Add random weighted edges to the graph
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            ed_add(&G, i, j, generate_random_weight());
        }
    }

    return G;
}

// Function to print the shortest path
void print_shortest_path(EdgeList path, int total_distance) {
    EdgeNodePtr current = path.head;
    while (current != NULL) {
        printf("%d -> ", current->edge.to_vertex);
        current = current->next;
    }
    printf("NULL\n");
    printf("Total distance: %d\n", total_distance);
}

// Function to test Dijkstra's shortest path algorithm
void test_dijkstra_shortest_path(Graph* G, int from, int to) {
    int total_distance;
    EdgeList dijkstra_path = shortest_path_Dijkstra(G, from, to, &total_distance);
    printf("Dijkstra's shortest path from vertex %d to %d:\n", from, to);
    print_shortest_path(dijkstra_path, total_distance);
}

// Function to test Floyd-Warshall shortest path algorithm
void test_floyd_warshall_shortest_path(Graph* G, int from, int to) {
    int total_distance;
    EdgeList floyd_path = shortest_path_FloydWarshall(G, from, to, &total_distance);
    printf("Floyd-Warshall shortest path from vertex %d to %d:\n", from, to);
    print_shortest_path(floyd_path, total_distance);
}

// Function to clean up the graph
void cleanup_graph(Graph* G) {
    des_g(G);
}

int main() {

    /* test by inserting in the program
    int vertices = 5;
    Graph G = create_graph(vertices);

    // Add edges to the graph
    add_edge(G, 0, 1);
    add_edge(G, 0, 2);
    add_edge(G, 1, 3);
    add_edge(G, 2, 3);
    add_edge(G, 3, 4);

    // Get the indegree of each vertex
    int* indegree = get_indegree(G);
    printf("Indegree of each vertex:\n");
    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }
    free(indegree);

    // Destroy the graph to free memory
    destroy_graph(G);


    destroy_graph(G);
    */

    /* test input.txt
    const char* filename = "input.txt";
    test_graph_operations(filename);
    */
    srand(time(NULL)); // Initialize random number generator

    int num_vertices = 10;
    Graph G = create_random_graph(num_vertices);

    // Test Dijkstra's shortest path algorithm
    test_dijkstra_shortest_path(&G, 0, num_vertices - 1);

    // Test Floyd-Warshall shortest path algorithm
    test_floyd_warshall_shortest_path(&G, 0, num_vertices - 1);

    // Clean up the graph
    cleanup_graph(&G);

    return 0;
}

