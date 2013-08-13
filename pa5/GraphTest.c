/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 7, 2013
*/

// This file is a test harness for the Graph ADT defined in Graph.c
// There are 13 functions defined in Graph.h, 2 constructors/destructors
// 6 accessor methods, 4 manipulation procedures, and one print methodd
// Each will be tested thoroughly in this harness.

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main (int argc, char **argv) {
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   //Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   return(0);
}
