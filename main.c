#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "graph.h"


/*
// Function to test Dijkstra's shortest path algorithm
void test_dijkstra_shortest_path(Graph* G, int from, int to) {
    clock_t start_time = clock();
    int total_distance;
    EdgeList dijkstra_path = shortest_path_Dijkstra(G, from, to, &total_distance);
    clock_t end_time = clock();

    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Dijkstra's shortest path from vertex %d to %d:\n", from, to);
    printf("Execution time: %.6f seconds\n", execution_time);

    size_t path_size = 0;
    EdgeNodePtr current = dijkstra_path.head;
    while (current != NULL) {
        path_size += sizeof(Edge);
        current = current->next;
    }

    size_t graph_size = sizeof(Graph);

    printf("Memory space used by Dijkstra's algorithm:\n");
    printf("Path size: %zu bytes\n", path_size);
    printf("Graph size: %zu bytes\n", graph_size);

    // print_shortest_path(dijkstra_path, total_distance);
    // Cleanup dijkstra_path
    // ...
}

// Function to test Floyd-Warshall shortest path algorithm
void test_floyd_warshall_shortest_path(Graph* G, int from, int to) {
    clock_t start_time = clock();
    int total_distance;
    EdgeList floyd_path = shortest_path_FloydWarshall(G, from, to, &total_distance);
    clock_t end_time = clock();

    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Floyd-Warshall shortest path from vertex %d to %d:\n", from, to);
    printf("Execution time: %.6f seconds\n", execution_time);

    size_t path_size = 0;
    EdgeNodePtr current = floyd_path.head;
    while (current != NULL) {
        path_size += sizeof(Edge);
        current = current->next;
    }

    size_t graph_size = sizeof(Graph);

    printf("Memory space used by Floyd-Warshall algorithm:\n");
    printf("Path size: %zu bytes\n", path_size);
    printf("Graph size: %zu bytes\n", graph_size);

    // print_shortest_path(floyd_path, total_distance);
    // Cleanup floyd_path
    // ...
}

int main() {
    int size, neighbours;
    float alpha;

    printf("Enter the graph size: ");
    scanf("%d", &size);

    printf("Enter the number of neighbors: ");
    scanf("%d", &neighbours);

    printf("Enter the alpha value: ");
    scanf("%f", &alpha);

    Graph G = watts_strogatz(size, neighbours, alpha);
    Graph G2 = G;

    int from1, to1, from2, to2;

    printf("Enter the source vertex for algorithms: ");
    scanf("%d", &from1);

    printf("Enter the destination vertex for algorithms: ");
    scanf("%d", &to1);
    from2 = from1;
    to2 = to1;

    // Repeat the tests for different input sizes
    int num_tests = 5;
    for (int i = 0; i < num_tests; i++) {
        Graph G = watts_strogatz(size, neighbours, alpha);
        Graph G2 = G;

        // Test Dijkstra's algorithm
        printf("Test %d - Dijkstra's algorithm:\n", i + 1);
        test_dijkstra_shortest_path(&G, from1, to1);

        // Test Floyd-Warshall algorithm
        printf("Test %d - Floyd-Warshall algorithm:\n", i + 1);
        test_floyd_warshall_shortest_path(&G2, from2, to2);

        // Cleanup G and G2
        des_g(&G);
        des_g(&G2);

        printf("\n");
    }

    return 0;
}
*/
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
    int size, neighbours;
    float alpha;

    printf("Enter the graph size: ");
    scanf("%d", &size);

    printf("Enter the number of neighbors: ");
    scanf("%d", &neighbours);

    printf("Enter the alpha value: ");
    scanf("%f", &alpha);

    Graph G = watts_strogatz(size, neighbours, alpha);
    Graph G2 = G;

    int from1, to1, from2, to2;

    printf("Enter the source vertex for Dijkstra's algorithm: ");
    scanf("%d", &from1);

    printf("Enter the destination vertex for Dijkstra's algorithm: ");
    scanf("%d", &to1);
    from2 = from1;
    to2 = to1;

    int distance_dijkstra;
    EdgeList shortest_path_dijkstra = shortest_path_Dijkstra(&G, from1, to1, &distance_dijkstra);

    int distance_floydwarshall;
    EdgeList shortest_path_floydwarshall = shortest_path_FloydWarshall(&G2, from2, to2, &distance_floydwarshall);

    printf("Shortest path from vertex %d to %d using Dijkstra's algorithm:\n", from1, to1);
    printf("Distance: %d\n", distance_dijkstra);
    printf("Path: ");
    print_shortest_pathA(shortest_path_dijkstra, distance_dijkstra);
    printf("\n");
    printf("Shortest path from vertex %d to %d using Floyd-Warshall algorithm:\n", from2, to2);
    printf("Distance: %d\n", distance_floydwarshall);
    printf("Path: ");
    print_shortest_pathB(shortest_path_floydwarshall, distance_floydwarshall);

    // Cleanup
    des_g(&G);
    des_g(&G2);

    return 0;
}




