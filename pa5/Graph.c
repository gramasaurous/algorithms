/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 7, 2013
* Implementation file for Graph ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
	int order;
	int size;
	int *color;
	int *parent;
	int *discover;
	int *finish;
	List *neighbors;
} GraphObj;

typedef enum color {
	WHITE,
	GREY,
	BLACK
}color;

// Private Helper Classes
void insertSorted(List U, int v);
int pop(List S);
void push(List S, int x);
void visit(Graph G, List S, int u, int *time);

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
	G->discover 	= malloc((n+1)*sizeof(int));
	G->finish	 	= malloc((n+1)*sizeof(int));
	G->order 		= n;
	G->size 		= 0;
	G->neighbors[0] = NULL;
	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->parent[i] 	= NIL;
		G->discover[i] 	= UNDEF;
		G->color[i] 	= WHITE;
		G->finish[i] 	= UNDEF;
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
	free((*pG)->discover);
	free((*pG)->finish);
	free((*pG)->parent);
	// NULLify the pointers
	(*pG)->neighbors = NULL;
	(*pG)->color 	 = NULL;
	(*pG)->parent 	 = NULL;
	(*pG)->discover  = NULL;
	(*pG)->finish  = NULL;
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
// Returns the discover time of vertex u
int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("Error: getDiscover called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || u > getOrder(G)) {
		printf("Error: getDiscover called with invalid indices.\n");
		exit(1);
	}
	return (G->discover[u]);
}
// Returns the finish time of vertex u
int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("Error: getFinish called on NULL Graph pointer\n");
		exit(1);
	} else if (u < 1 || u > getOrder(G)) {
		printf("Error: getFinish called with invalid indices.\n");
		exit(1);
	}
	return (G->finish[u]);
}

// Manipulation Procedures
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

// Performs the Depth First Search Algorithm on Graph G
// Pre: getLength(S) == getOrder(G)
void DFS(Graph G, List S) {
	// Check for NULL Pointer or invalid List
	if (G == NULL) {
		printf("Error: DFS called on NULL Graph pointer\n");
		exit(1);
	} else if (S == NULL) {
		printf("Error: DFS called on NULL List pointer\n");
		exit(1);
	} else if (length(S) != getOrder(G)) {
		printf("Error: DFS called with invalid List.\n");
		exit(1);
	}
	// Perform The Algorithm
	// Initialize the vertices and set time to 0
	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] 	= WHITE;
		G->discover[i] 	= UNDEF;
		G->finish[i]	= UNDEF;
		G->parent[i] 	= NIL;
	}
	int time = 0;
	// Visit each vertex in G
	List T = copyList(S);
	//printf("T, copy of S:\n");
	//printList(stdout, T);
	clear(S);
	// Cycle through the adjacency list
	for (moveTo(T,0); getIndex(T) != -1; moveNext(T)) {
		int u = getElement(T);
		if (G->color[u] == WHITE) {
			visit(G, S, u, &time);
		}
	}
	freeList(&T);
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
// Returns a new Graph which is the copy of Graph G
//
Graph copyGraph(Graph G) {
	if (G == NULL) {
		printf("Error: transpose called on NULL Graph pointer.\n");
	}
	Graph T = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		List I = G->neighbors[i];
		for (moveTo(I, 0); getIndex(I) != -1; moveNext(I)) {
			int x = getElement(I);
			addArc(T,i,x);
		}
	}
	return (T);
}
// Returns a new Graph which is the transpose of Graph G
//
Graph transpose(Graph G) {
	if (G == NULL) {
		printf("Error: transpose called on NULL Graph pointer.\n");
	}
	Graph T = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(T); i++) {
		List I = G->neighbors[i];
		for (moveTo(I, 0); getIndex(I) != -1; moveNext(I)) {
			int x = getElement(I);
			// if (length(G->neighbors[x]) == 0) continue;
			addArc(T,x,i);
		}
	}
	return (T);
}

// Implementation of Private Helper Classes
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
// pop() returns and then removes the front of list Q
int pop(List S) {
	if (S == NULL) {
		printf("pop called on NULL List pointer\n");
		exit(1);
	} else if (length(S) == 0) {
		printf("pop called on empty list\n");
		exit(1);
	}
	int x = front(S);
	deleteFront(S);
	return(x);
}
void push (List S, int x) {
	prepend(S, x);
}
void visit(Graph G, List S, int u, int *time) {
	if (S == NULL || time == NULL) {
		printf("Error: Visit called with null pointers\n");
		exit (1);
	}
	G->color[u] = GREY;
	G->discover[u] = ++(*time);
	// printf("Vertex: %d discovered at time: %d.\n", u, (*time));
	List adj = G->neighbors[u];
	for (moveTo(adj, 0); getIndex(adj) != -1; moveNext(adj)) {
		int y = getElement(adj);
		if (G->color[y] == WHITE) {
			G->parent[y] = u;
			visit(G, S, y, time);
		}
	}
	G->color[u] = BLACK;
	G->finish[u] = ++(*time);
	// printf("Vertex: %d finished at time: %d.\n", u, (*time));
	push(S, u);
	// printf("Push! %d\n", u);
}
