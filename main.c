#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "graph.h"



// Function to test Dijkstra's shortest path algorithm
void test_dijkstra_shortest_path(Graph* G, int from, int to) {
    int total_distance;
    EdgeList dijkstra_path = shortest_path_Dijkstra(G, from, to, &total_distance);
    printf("Dijkstra's shortest path from vertex %d to %d:\n", from, to);
    //print_shortest_path(dijkstra_path, total_distance);
}

// Function to test Floyd-Warshall shortest path algorithm
void test_floyd_warshall_shortest_path(Graph* G, int from, int to) {
    int total_distance;
    EdgeList floyd_path = shortest_path_FloydWarshall(G, from, to, &total_distance);
    printf("Floyd-Warshall shortest path from vertex %d to %d:\n", from, to);
    //print_shortest_path(floyd_path, total_distance);
}

// Function to clean up the graph
void cleanup_graph(Graph* G) {
    des_g(G);
}

void print_shortest_path(EdgeList path, int total_distance) {
    EdgeNodePtr current = path.head;
    while (current != NULL) {
        printf("%d ", current->edge.to_vertex);
        current = current->next;
        if (current != NULL) {
            printf("-> ");
        }
    }
}

int main() {
    int size = 10;
    int neighbours = 2;
    float alpha = 0.3;

    Graph G = watts_strogatz(size, neighbours, alpha);

    int from = 0;
    int to = size - 1;

    int distance_dijkstra;
    EdgeList shortest_path_dijkstra = shortest_path_Dijkstra(&G, from, to, &distance_dijkstra);

    int distance_floydwarshall;
    EdgeList shortest_path_floydwarshall = shortest_path_FloydWarshall(&G, from, to, &distance_floydwarshall);

    printf("Shortest path from vertex %d to %d using Dijkstra's algorithm:\n", from, to);
    printf("Distance: %d\n", distance_dijkstra);
    printf("Path: ");
    print_shortest_path(shortest_path_dijkstra, distance_dijkstra);

    printf("Shortest path from vertex %d to %d using Floyd-Warshall algorithm:\n", from, to);
    printf("Distance: %d\n", distance_floydwarshall);
    printf("Path: ");
    print_shortest_path(shortest_path_floydwarshall, distance_floydwarshall);

    // Cleanup
    des_g(&G);

    return 0;
}




