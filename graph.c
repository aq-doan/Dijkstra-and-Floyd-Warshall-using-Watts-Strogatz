
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

EdgeList find_shortest_path_B(Graph* self, int from, int to, int* distance) {
    int** distance_array = malloc(self->V * sizeof(*distance_array));
    int** n_array = malloc(self->V * sizeof(*n_array));

    for (int i = 0; i < self->V; i++) {
        distance_array[i] = malloc(self->V * sizeof(**distance_array));
        n_array[i] = malloc(self->V * sizeof(**n_array));
        memset(distance_array[i], INT_MAX / 2, self->V * sizeof(**distance_array));
        memset(n_array[i], -1, self->V * sizeof(**n_array));
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
    }

    for (int i = 0; i < self->V; i++) {
        free(distance_array[i]);
        free(n_array[i]);
    }
    free(distance_array);
    free(n_array);

    return shortest_path;
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


