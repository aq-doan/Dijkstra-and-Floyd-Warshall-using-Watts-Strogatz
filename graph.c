
/*
* Anh Quan Doan 624501
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include <assert.h>
typedef int bool;
#define true 1
#define false 0


Graph new_g(int v) {

    Graph G;
    G.V = v;

    G.edges = malloc(G.V * sizeof * G.edges);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }
    return G;
}

//add weighted edge to the graph
void ed_add(Graph* self, int from, int to, int w) {
    // ensure both vertices are valid
    check_vertex(self, from);
    check_vertex(self, to);

    // create a new edge node
    EdgeNodePtr node = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->edge.to_vertex = to;
    node->edge.weight = w;
    node->next = NULL;

    // find the correct position to insert the new edge node
    EdgeNodePtr* current = &(self->edges[from].head);
    while (*current != NULL && (*current)->edge.to_vertex < to) {
        current = &((*current)->next);
    }

    // insert the new edge node
    node->next = *current;
    *current = node;
}


// Check for vertex in a graph
// and an error message will be displayed automatically.
void check_vertex(Graph* self, int v) {
    assert(v >= 0 && v < self->V);
    
}

//apply Dijkstra shortest path
void algo_dijkstra_process(Graph* self, int from, int* w, int* current_v) {
    // Instead of using sets, use an array to determine if each node has been visited
    bool* visited = malloc(self->V * sizeof(bool));

    // Initialise the arrays with default values
    for (int v = 0; v < self->V; v++) {
        w[v] = INT_MAX / 2;
        current_v[v] = -1;
        visited[v] = false;
    }

    // The source vertex is zero distance from itself
    w[from] = 0;

    // Loop until all vertices have been visited
    for (int i = 0; i < self->V; i++) {
        // Find the vertex with the shortest recorded distance among unvisited vertices
        int u = -1;
        for (int v = 0; v < self->V; v++) {
            if (!visited[v] && (u == -1 || w[v] < w[u])) {
                u = v;
            }
        }

        // Mark as visited
        visited[u] = true;

        // Update the distances and previous vertices for adjacent unvisited vertices
        EdgeNodePtr current = self->edges[u].head;
        while (current != NULL) {
            int dest = current->edge.to_vertex;
            if (!visited[dest]) {
                int alt = w[u] + current->edge.weight;
                if (alt < w[dest]) {
                    w[dest] = alt;
                    current_v[dest] = u;
                }
            }
            current = current->next;
        }
    }

    free(visited);
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

void des_g(Graph* self) {
    // Free the individual edge nodes for each vertex
    for (int v = 0; v < self->V; v++) {
        EdgeNodePtr current = self->edges[v].head;

        while (current != NULL) {
            EdgeNodePtr to_free = current;
            current = current->next;
            free(to_free);
        }
    }

    // Free the edges array
    free(self->edges);

    // Reset the graph structure
    self->edges = NULL;
    self->V = 0;
}


