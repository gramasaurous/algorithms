/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 7, 2013
*/
//Implementation file for Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
	int order;
	int size;
	int source;
	int *color;
	int *parent;
	int *distance;
	List *neighbors;
} GraphObj;

typedef enum color {
	WHITE,
	GRAY,
	BLACK
}color;

// Private Helper Classes
// insertSorted() inserts v into list u
// in it's numerical position
void insertSorted(List U, int v) {
	moveTo(U, 0);
	if (length(U) == 0) {
		append(U,v);
	}
	for (int i=0; i<length(U);i++) {
		moveTo(U,i);
		int cmp = getElement(U);
		// Insert before if lex. less than
		if (v == cmp) {
			break;
		} if (v < cmp) {
			insertBefore(U, v);
			break;
		// If reached the end of the list, append
		} else if (i == length(U)-1) {
			append(U,v);
			break;
		}
	}
}
// dequeue() returns and then removes the front of list Q
int dequeue(List Q) {
	if (Q == NULL) {
		printf("dequeue called on NULL List pointer\n");
		exit(1);
	} else if (length(Q) == 0) {
		printf("dequeue called on empty list\n");
		exit(1);
	}
	int x = front(Q);
	deleteFront(Q);
	return(x);
}

// newGraph() returns a Graph pointing to a newly
// created GraphObj representing a graph having n
// vertices and no edges
Graph newGraph(int n) {
	if (n < 1) {
		printf("Graph Error: newGraph() called with invalid order.\n");
		exit (1);
	}
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors 	= malloc((n+1)*sizeof(List));
	G->color 		= malloc((n+1)*sizeof(int));
	G->parent 		= malloc((n+1)*sizeof(int));
	G->distance 	= malloc((n+1)*sizeof(int));
	G->order 		= n;
	G->size 		= 0;
	G->neighbors[0] = NULL;
	G->source = NIL;
	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->color[i] = WHITE;
	}
	return G;
}

void freeGraph(Graph* pG) {
	// Free all of the Vertex adjacency lists
	for (int i = 1; i <=getOrder(*pG); i++) {
		freeList(&(*pG)->neighbors[i]);
	}
	// Free malloc'd memory for 
	free((*pG)->neighbors);
	free((*pG)->color);
	free((*pG)->distance);
	free((*pG)->parent);
	// NULLify the pointers
	(*pG)->neighbors = NULL;
	(*pG)->color = NULL;
	(*pG)->parent = NULL;
	(*pG)->distance = NULL;
	// Free the original malloc and NULLify the ptr
	free(*pG);
	*pG = NULL;
	return;
}

// Access functions
// Returns the number of vertices on Graph G
int getOrder(Graph G) {
	if (G != NULL) {
		return G->order;
	} else {
		printf("Error: getOrder called on NULL Graph pointer\n");
		exit(1);
	}
}
// Returns the number of edges on Graph G
int getSize(Graph G) {
	if (G != NULL) {
		return G->size;
	} else {
		printf("Error: getSize called on NULL Graph pointer\n");
		exit(1);
	}
}
// Returns the label of most recent vertex called by BFS()
// if BFS has not been called, returns NIL
int getSource(Graph G) {
	if (G != NULL) {
		return G->source;
	} else {
		printf("Error: getSize called on NULL Graph pointer\n");
		exit(1);
	}
}
// Returns the parent vertex of vertex u in the Breadth-First Tree
// created by BFS()
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Error: getParent called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || u > getOrder(G)) {
		printf("Error: getParent called with invalid indices.\n");
		exit(1);
	}
	return (G->parent[u]);
}
// Returns the distance from the most recent BFS source to vertex
// u, or INF if BFS() has not yet been called
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Error: getDist called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || u > getOrder(G)) {
		printf("Error: getDist called with invalid indices.\n");
		exit(1);
	}
	return (G->distance[u]);
}
// Appends to the List L the vertices of a shortest path in G
// from source to u, or appends to L the value NIL if no such
// path exists.
// pre: getSource()!=NIL (BFS() must be called b4 getPath())
void getPath(List L, Graph G, int u) {
	// for testing, this function prints all the neighbors of u
	if (getSource(G) == NIL) {
		printf("Error: getPath called before BFS\n");
		exit (1);
	} if (G->source == u) {
		append(L, u);
	} else if (G->parent[u] != NIL) {
		getPath(L, G, G->parent[u]);
		append(L,u);
	}
}

// Manipulation Procedures
void makeNull(Graph G) {
	if (G != NULL) {
		for (int i = 1; i <= getOrder(G); i++) {
			clear(G->neighbors[i]);
		}
		G->size = 0;
	} else {
		printf("Error: makeNull called on NULL Graph pointer\n");
		exit(1);
	}
}
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Error: addEdge called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
		printf("Error: addEdge called with invalid indices.\n");
		exit(1);
	} else if (u == v) {
		printf("Error: addEdge called with two identical indices.\n");
		exit(1);
	}
	// Sorted insert v into neighbors[u]
	List U = G->neighbors[u];
	insertSorted(U, v);
	// Sorted insert u into neighbors[V]
	List V = G->neighbors[v];
	insertSorted(V, u);
	// Update G's edge field
	G->size++;
}
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Error: addArc called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
		printf("Error: addArc called with invalid indices.\n");
		exit(1);
	}
	// Sorted insert v into neighbors[u]
	List U = G->neighbors[u];
	insertSorted(U, v);
}

void BFS(Graph G, int s) {
	if (G == NULL) {
		printf("Error: BFS called on NULL Graph pointer\n");
		exit(1);
	} else if (s < 1 || s > G->order) {
		printf("Error: BFS called with invalid source.\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] 	= WHITE;
		G->distance[i] 	= INF;
		G->parent[i] 	= NIL;
	}
	G->source = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List Q = newList();
	append(Q, s);
	while(length(Q) != 0) {
		int x = dequeue(Q);
		List X = G->neighbors[x];
		for (moveTo(X, 0); getIndex(X) != -1; moveNext(X)) {
			int y = getElement(X);
			if (G->color[y] == WHITE) {
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] +1;
				G->parent[y] = x;
				append(Q, y);
			}
		}
		G->color[x] = BLACK;
	}
	freeList(&Q);
}

// Other
// Prints the adjacency list representation of Graph G to FILE out
void printGraph(FILE* out, Graph G) {
	if (out == NULL) {
		exit(1);
	} else if (G == NULL) {
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out,"%d: ",i);
		printList(out,G->neighbors[i]);
	}
}