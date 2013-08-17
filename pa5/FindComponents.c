/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 14, 2013
* Program which creates a graph from the input file, and determines
* it's connected components, printing them to the output file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#ifndef MAX_LEN
#define MAX_LEN 160
#endif
typedef char *string;

int main (int argc, char *argv[]) {
	// Check for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit (1);
	}
	// Init, open and check files
	FILE *in, *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL) {
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	} if (out == NULL) {
		printf("Unable to open file %s for writing.\n", argv[2]);
		exit(1);
	}

	// Collect number of vertices and init Graph
	int v;
	fscanf(in, "%d", &v);
	Graph G = newGraph(v);

	// Populate Graph
	int x,y;
	while (fscanf(in, "%d %d", &x, &y) == 2) {
		if (x == 0 && y == 0) break;
		addArc(G,x,y);
	}
	
	// Print G
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out,G);

	// Populate the S with the vertices of G
	List S = newList();
	for (int i = 1; i <= getOrder(G); i++) {
		append(S, i);
	}
	// Run DFS on G
	DFS(G, S);
	// Transpose G
	Graph T = transpose(G);
	// Run DFS on G^T (in order of finish times of DFS on G)
	DFS(T,S);

	// Determine the number of SSC's in G
	int count = 0;
	for (moveTo(S, 0); getIndex(S) != -1; moveNext(S)) {
			int x = getElement(S);
			if (x == -1) continue;
			int p = getParent(T, x);
			if (p == NIL) {
				count++;
				insertBefore(S, -1);
			}
	}
	int place = length(S) -1;
	fprintf(out, "Graph G contains %d strongly connected components:\n", count);
	for (int i = 1; i <= count; i++) {
		fprintf(out, "Component %d: ", i);
		for (moveTo(S, place); getIndex(S) != -1; movePrev(S)) {
			int g = getElement(S);
			if (g != -1)fprintf(out, "%d ", g);
			place--;
			if (g == -1) break;
		}
		fprintf(out,"\n");
	}
	// Clean up
	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);
	fclose(in);
	fclose(out);
}