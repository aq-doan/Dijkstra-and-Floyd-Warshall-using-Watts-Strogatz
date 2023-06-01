
/*
* Anh Quan Doan 624501
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include <assert.h>


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








void des_g(Graph G) {

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

