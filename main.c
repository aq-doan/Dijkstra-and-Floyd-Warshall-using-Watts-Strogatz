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

void print_shortest_pathA(EdgeList path, int total_distance) {
    EdgeNodePtr current = path.head;
    while (current != NULL) {
        printf("%d ", current->edge.to_vertex);
        current = current->next;
        if (current != NULL) {
            printf("-> ");
        }
        
    }
    free(current);

}
void print_shortest_pathB(EdgeList path, int total_distance) {
    EdgeNodePtr current = path.head;
    while (current != NULL) {
        printf("%d ", current->edge.to_vertex);
        current = current->next;
        if (current != NULL) {
            printf("-> ");
        }

    }
    free(current);

}

int main() {
    int size = 100;
    int neighbours = 15;
    float alpha = 1;

    Graph G = watts_strogatz(size, neighbours, alpha);
    Graph G2 = G;
    int from1 = 0;
    int to1 = size - 1;
    int from2 = 0;
    int to2 = size - 1;
    int distance_dijkstra;
    EdgeList shortest_path_dijkstra = shortest_path_Dijkstra(&G, from1, to1, &distance_dijkstra);

    int distance_floydwarshall;
    EdgeList shortest_path_floydwarshall = shortest_path_FloydWarshall(&G2, from2, to2, &distance_floydwarshall);

    printf("Shortest path from vertex %d to %d using Dijkstra's algorithm:\n", from1, to1);
    printf("Distance: %d\n", distance_dijkstra);
    printf("Path: ");
    print_shortest_pathA(shortest_path_dijkstra, distance_dijkstra);

    printf("Shortest path from vertex %d to %d using Floyd-Warshall algorithm:\n", from2, to2);
    printf("Distance: %d\n", distance_floydwarshall);
    printf("Path: ");
    print_shortest_pathB(shortest_path_floydwarshall, distance_floydwarshall);

    // Cleanup
    des_g(&G);

    return 0;
}




