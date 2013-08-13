/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 7, 2013
*/
// Client using Graph.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#ifndef MAX_LEN
#define MAX_LEN 160
#endif
typedef char *string;

int main (int argc, char* argv[]) {
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
		addEdge(G,x,y);
	}

	// Print the Graph
	printGraph(out, G);
	
	// Print the paths
	List L = newList();
	int source, dest;
	while (fscanf(in, "%d %d", &source, &dest)) {
		if (source == 0 && dest == 0) break;
		BFS(G, source);
		getPath(L, G, dest);
		fprintf(out, "\nThe distance from %d to %d is ", source, dest);
		if (length(L) == 0) {
			fprintf(out, "infinity\nNo %d-%d path exists\n", source, dest);
		} else {
			fprintf(out, "%d\n", getDist(G, dest));
			fprintf(out, "A shortest %d-%d path is: ", source, dest);
			printList(out, L);
		}
		clear(L);
	}
	// Clean up
	freeGraph(&G);
	freeList(&L);
	fclose(in);
	fclose(out);
}