/*
* Anh Quan Doan 624501
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph create_graph(int v) {

    Graph G;
    G.V = v;

    G.edges = malloc(G.V * sizeof * G.edges);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }
    return G;
}

/*Adds an edges to the AdgeList */
void add_edge(Graph G, int from, int to) {
    EdgeNodePtr node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Error allocating memory for EdgeNode in add_edge().\n");
        exit(EXIT_FAILURE);
    }

    node->edge.to_vertex = to;
    node->next = G.edges[from].head;
    G.edges[from].head = node;
}



int* get_indegree(Graph G)
{
    EdgeNodePtr c;
    int* in = calloc(G.V, sizeof(int));


    for (int i = 0; i < G.V; i++) {
        in[i] = 0;
    }

    for (int i = 0; i < G.V; i++) {
        c = G.edges[i].head;

        while (c != NULL) {
            int to_vertex = c->edge.to_vertex;
            in[to_vertex]++;
            c = c->next;
        }

    }
    return in;
}


EdgeList construct_path(int* prev, int source) {
    EdgeList path;
    path.head = NULL;

    int vertex = source;
    while (vertex != -1) {
        EdgeNodePtr node = malloc(sizeof(*node));
        if (node == NULL) {
            fprintf(stderr, "Error allocating memory for EdgeNode in construct_path().\n");
            exit(EXIT_FAILURE);
        }
        node->edge.to_vertex = vertex;
        node->edge.weight = 0;
        node->next = path.head;
        path.head = node;
        vertex = prev[vertex];
    }

    return path;
}

EdgeList shortest_path(Graph G, int source, int* dist, int* prev) {
    // Initialize distance and previous arrays
    for (int v = 0; v < G.V; v++) {
        dist[v] = INT_MAX;
        prev[v] = -1;
    }
    dist[source] = 0;

    // Create a priority queue (Q) using an array-based min-heap
    int* Q = malloc(G.V * sizeof(int));
    int Q_size = G.V;
    for (int v = 0; v < G.V; v++) {
        Q[v] = v;
    }

    while (Q_size > 0) {
        // Find the vertex with the minimum distance
        int u = -1;
        int min_dist = INT_MAX;
        for (int i = 0; i < Q_size; i++) {
            if (dist[Q[i]] < min_dist) {
                min_dist = dist[Q[i]];
                u = Q[i];
            }
        }

        // Remove u from Q
        int u_index = -1;
        for (int i = 0; i < Q_size; i++) {
            if (Q[i] == u) {
                u_index = i;
                break;
            }
        }
        if (u_index != -1) {
            Q[u_index] = Q[Q_size - 1];
            Q_size--;
        }

        // Update distances and previous vertices for u's neighbors
        EdgeNodePtr c = G.edges[u].head;
        while (c != NULL) {
            int v = c->edge.to_vertex;
            int weight = c->edge.weight;
            int alt = dist[u] + weight;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
            }
            c = c->next;
        }
    }

    free(Q);

    // Construct the path and return it
    return construct_path(prev, source);
}



void destroy_graph(Graph G) {

    for (int i = 0; i < G.V; i++) {
        EdgeNodePtr c = G.edges[i].head;

        while (c != NULL) {
            EdgeNodePtr free_graph = c;
            c = c->next;
            free(free_graph);
        }
    }
    free(G.edges);
}

