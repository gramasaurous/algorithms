//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "List.h"

int main(int argc, char* argv[]){

	int i;
	List A = newList();
	List B = newList();

	for (i=0; i< 10; i++) {
		append(A,i);
		prepend(B,i);
	}

	//method of traversing the list.
	for (moveTo(A,length(A)-1); getIndex(A)!=-1; movePrev(A)) {
		//fprintf(stdout, "%d ", getElement(A));
		fprintf(stdout, "%d ", getElement(A));
	}
	printf("\n");

	for (int i = 0; i < length(A); i++) {
		moveTo(A, i);
		fprintf(stdout, "%d ", getElement(A));
	}
	printf("\n");

	int insert = 69;

	printList(stdout, A);
	moveTo(A,0);
	insertBefore(A, insert);
	printList(stdout, A);
	moveTo(A, length(A)-1);
	insertBefore(A, insert);
	printList(stdout, A);
	moveTo(A, 6);
	insertBefore(A, insert);
	printList(stdout, A);

	insert = 11;
	printf("\n");
	printList(stdout, B);
	moveTo(B,0);
	insertAfter(B, insert);
	printList(stdout, B);
	moveTo(B, length(B)-1);
	insertAfter(B, insert);
	printList(stdout, B);
	moveTo(B, 6);
	insertAfter(B, insert);
	printList(stdout, B);
	
	printf("\n");

	printList(stdout, A);
	printList(stdout, B);
	
	int loopBound = length(A);
	for (int i = 0; i < loopBound;i++) deleteFront(A);
	printList(stdout, A);

	//freeList(&A);
	//freeList(&B);

	return(0);
}
