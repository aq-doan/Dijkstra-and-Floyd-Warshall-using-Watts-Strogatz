#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct edge {
	int to_vertex;
	int weight;
} Edge;

typedef struct edgeNode {
	Edge edge;
	struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
	EdgeNodePtr head;
} EdgeList;

typedef struct graph {
	int V;
	EdgeList* edges;
} Graph;

Graph create_graph(int v);

void add_edge(Graph G, int from, int to);


int* get_indegree(Graph G);


void destroy_graph(Graph G);

EdgeList shortest_path(Graph G, int source, int* dist, int* prev);
