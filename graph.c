
/*
* Anh Quan Doan 624501
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"


Graph new_g(int v) {

    Graph G;
    G.V = v;

    G.edges = malloc(G.V * sizeof * G.edges);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }
    return G;
}

/*Adds an edges to the AdgeList */
void ed_add(Graph G, int from, int to) {
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

