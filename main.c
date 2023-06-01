#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

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
void display_graph(Graph* G) {
    for (int v = 0; v < G->V; v++) {
        printf("Vertex %d: ", v);

        EdgeNodePtr current = G->edges[v].head;
        while (current != NULL) {
            printf("(%d, weight: %d) ", current->edge.to_vertex, current->edge.weight);
            current = current->next;
        }

        printf("\n");
    }
}


int main() {
    // Generate the graph
    int num_vertices = 6;
    int k = 2;
    float beta = 0.5;
    Graph G = watts_strogatz(num_vertices, k, beta);

    // Display the graph
    display_graph(&G);

    // Clean up the graph
    des_g(&G);

    return 0;
}


