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


int main() {
    int num_vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);

    Graph G = new_g(num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        int num_edges;
        printf("Enter the number of edges for vertex %d: ", i);
        scanf("%d", &num_edges);

        for (int j = 0; j < num_edges; j++) {
            int to_vertex, weight;
            printf("Enter the edge (to_vertex, weight) for vertex %d: ", i);
            scanf("%d %d", &to_vertex, &weight);

            ed_add(&G, i, to_vertex, weight);
        }
    }

    int from, to;
    printf("Enter the source vertex: ");
    scanf("%d", &from);
    printf("Enter the destination vertex: ");
    scanf("%d", &to);

    // Calculate the shortest path using Dijkstra's algorithm
    int total_distance;
    EdgeList dijkstra_path = shortest_path_Dijkstra(&G, from, to, &total_distance);

    // Print the shortest path and total distance
    printf("Dijkstra's shortest path from vertex %d to %d:\n", from, to);
    EdgeNodePtr current = dijkstra_path.head;
    while (current != NULL) {
        printf("%d -> ", current->edge.to_vertex);
        current = current->next;
    }
    printf("NULL\n");
    printf("Total distance: %d\n", total_distance);

    // Calculate the shortest path using Floyd-Warshall algorithm
    EdgeList floyd_path = shortest_path_FloydWarshall(&G, from, to, &total_distance);

    // Print the shortest path and total distance
    printf("Floyd-Warshall shortest path from vertex %d to %d:\n", from, to);
    current = floyd_path.head;
    while (current != NULL) {
        printf("%d -> ", current->edge.to_vertex);
        current = current->next;
    }
    printf("NULL\n");
    printf("Total distance: %d\n", total_distance);

    // Clean up the graph
    des_g(&G);

   
    return 0;
}

