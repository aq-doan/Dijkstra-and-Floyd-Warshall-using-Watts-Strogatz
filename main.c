#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph read_graph_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int num_vertices;
    fscanf(file, "%d", &num_vertices);
    Graph G = create_graph(num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        int vertex, num_edges;
        fscanf(file, "%d", &vertex);
        fscanf(file, "%d", &num_edges);

        for (int j = 0; j < num_edges; j++) {
            int to_vertex, weight;
            fscanf(file, "%d,%d", &to_vertex, &weight);
            add_edge(G, vertex, to_vertex);
        }
    }

    fclose(file);
    return G;
}

void print_indegree(Graph G) {
    int* indegree = get_indegree(G);
    printf("Indegree of each vertex:\n");
    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }
    free(indegree);
}

void test_graph_operations(const char* filename) {
    Graph G = read_graph_from_file(filename);

    printf("Graph created from %s:\n", filename);
    printf("Number of vertices: %d\n", G.V);

    print_indegree(G);

    destroy_graph(G);
}

int main() {
    /*
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
    const char* filename = "input.txt";
    test_graph_operations(filename);
    return 0;
}
