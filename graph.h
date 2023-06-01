#pragma once


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

Graph new_g(int v);

void check_vertex(Graph* self, int vertex);

void ed_add(Graph* self, int from, int to, int w);

void des_g(Graph* G);

EdgeList shortest_path_Dijkstra(Graph* G, int from, int to, int* total);

EdgeList shortest_path_FloydWarshall(Graph* G, int from, int to, int* distance);

Graph watts_strogatz(int size, int neighbours, float alpha);