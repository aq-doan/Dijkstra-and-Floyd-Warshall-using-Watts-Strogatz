
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
void check_vertex(Graph* self, int vertex) {
    assert(vertex >= 0 && vertex < self->V + 1);
}

//apply Dijkstra shortest path
void algo_dijkstra_process(Graph* self, int from, int* w, int* current_v) {

    bool* visited = malloc(self->V * sizeof(bool));


    for (int v = 0; v < self->V; v++) {
        w[v] = INT_MAX / 2;
        current_v[v] = -1;
        visited[v] = false;
    }

  
    w[from] = 0; 


    for (int i = 0; i < self->V; i++) {
   
        int u = -1;
        for (int v = 0; v < self->V; v++) {
            if (!visited[v] && (u == -1 || w[v] < w[u])) {
                u = v;
            }
        }

        visited[u] = true;

     
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
//apply Dijkstra

EdgeList shortest_path_Dijkstra(Graph* self, int from, int to, int* total) {
    int* a = malloc(self->V * sizeof(int));
    int* b = malloc(self->V * sizeof(int));
    algo_dijkstra_process(self, from, a, b);

    if (total != NULL) {
        *total = a[to];
    }

    EdgeList shortest_path = { .head = NULL };

    while (to != -1) {
        EdgeNodePtr n = malloc(sizeof(struct edgeNode));
        *n = (struct edgeNode){ .edge.to_vertex = to, .edge.weight = 0 };
        n->next = shortest_path.head;
        shortest_path.head = n;
        to = b[to];
    }

    free(a);
    free(b);

    return shortest_path;
}

// Apply Floyd–Warshall algorithm on a graph by solving all pairs shortest paths.
void algo_floyd_warshall_process(Graph* self, int** total_array, int** to_array) {
    int V = self->V;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            total_array[i][j] = INT_MAX / 2;
            to_array[i][j] = -1;
        }
    }

    for (int v = 0; v < V; v++) {
        EdgeNodePtr current = self->edges[v].head;
        while (current != NULL) {
            int to = current->edge.to_vertex;
            total_array[v][to] = current->edge.weight;
            to_array[v][to] = to;
            current = current->next;
        }
        total_array[v][v] = 0;
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int new_dist = total_array[i][k] + total_array[k][j];
                if (new_dist < total_array[i][j]) {
                    total_array[i][j] = new_dist;
                    to_array[i][j] = to_array[i][k];
                }
            }
        }
    }
}

EdgeList shortest_path_FloydWarshall(Graph* self, int from, int to, int* distance) {
    int** distance_array = malloc(self->V * sizeof(*distance_array));
    int** n_array = malloc(self->V * sizeof(*n_array));

    for (int i = 0; i < self->V; i++) {
        distance_array[i] = malloc(self->V * sizeof(int));
        memset(distance_array[i], INT_MAX / 2, self->V * sizeof(int));
        n_array[i] = malloc(self->V * sizeof(int));
        memset(n_array[i], -1, self->V * sizeof(int));

        distance_array[i][i] = 0;
    }

    algo_floyd_warshall_process(self, distance_array, n_array);

    if (distance != NULL) {
        *distance = distance_array[from][to];
    }

    EdgeList shortest_path = { .head = NULL };

    if (n_array[from][to] != -1) {
        for (int vertex = from; vertex != to; vertex = n_array[vertex][to]) {
            EdgeNodePtr n_ed = malloc(sizeof(*n_ed));
            n_ed->edge.to_vertex = vertex;
            n_ed->edge.weight = 0;
            n_ed->next = shortest_path.head;
            shortest_path.head = n_ed;
        }

        // Add the last vertex (to) to the path
        EdgeNodePtr n_ed = malloc(sizeof(*n_ed));
        n_ed->edge.to_vertex = to;
        n_ed->edge.weight = 0;
        n_ed->next = shortest_path.head;
        shortest_path.head = n_ed;

        // Reverse the order of vertices in the path
        EdgeNodePtr prev = NULL;
        EdgeNodePtr current = shortest_path.head;
        EdgeNodePtr next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        shortest_path.head = prev;
    }

    for (int i = 0; i < self->V; i++) {
        free(distance_array[i]);
        free(n_array[i]);
    }
    free(distance_array);
    free(n_array);

    return shortest_path;
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

//generate graph and randomly add weight to the edge
Graph watts_strogatz(int size, int neighbours, float alpha) {
    srand(time(NULL));  // Seed the random number generator
    Graph G;
    G.V = size;
    G.edges = malloc(G.V * sizeof * G.edges);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }

    for (int u = 0; u < G.V; u++) {
        // add edges for neighbors
        for (int i = 1; i <= neighbours / 2; i++) {
            int v = (u + i) % G.V;

            // add edges to random vertices with probability beta
            if ((float)rand() / RAND_MAX < alpha) {
                v = (int)(((float)rand() / RAND_MAX) * G.V);
            }

            // add edges in both directions
            EdgeNodePtr uv;
            uv = malloc(sizeof * uv);
            uv->edge.to_vertex = v;
            uv->edge.weight = rand() % 100;  // Assign a random weight between 0 and 99
            uv->next = G.edges[u].head;
            G.edges[u].head = uv;

            EdgeNodePtr vu;
            vu = malloc(sizeof * vu);
            vu->edge.to_vertex = u;
            vu->edge.weight = rand() % 100;  // Assign a random weight between 0 and 99
            vu->next = G.edges[v].head;
            G.edges[v].head = vu;
        }
    }

    return G;
}

