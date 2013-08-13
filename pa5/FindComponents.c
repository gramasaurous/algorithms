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
	// Populate the S with the vertices of G
	List S = newList();
	for (int i = 1; i <= getOrder(G); i++) {
		append(S, i);
	}
	// Run DFS on G
	DFS(G, S);
	fprintf(stdout, "\n");
	fprintf(stdout, "x:  d  f  p\n");
	for(int i=1; i<=getOrder(G); i++){
		int d,f,p;
		d = getDiscover(G,i);
		f = getFinish(G,i);
		p = getParent(G,i);
		fprintf(stdout, "%d: %2d %2d %2d\n", i, d, f, p);
	}
	// Transpose G
	Graph T = transpose(G);

	// Run DFS on G^T (in order of finish times of DFS on G)
	DFS(T,S);
	fprintf(stdout, "\n");
	fprintf(stdout, "x:  d  f  p\n");
	for(int i=1; i<=getOrder(T); i++){
		int d,f,p;
		d = getDiscover(T,i);
		f = getFinish(T,i);
		p = getParent(T,i);
		fprintf(stdout, "%d: %2d %2d %2d\n", i, d, f, p);
	}
	// Print the Graph
	printGraph(out, G);

	// Clean up
	freeGraph(&G);
	freeList(&S);
	fclose(in);
	fclose(out);
}