/*
* Graham Greving
* ggreving@ucsc.edu
* List.c
* Implementation file for List ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//structs

//private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int cursorIndex;
} ListObj;

//Constructors and Destructors

// newNode()
// Returns reference to new Node object. Initializes next, prev and data fields.
// Private.
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->previous = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->cursorIndex = -1;
	L->cursor = NULL;
	return L;
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *ppL to NULL
void freeList(List* pL) {
	if (pL == NULL || *pL == NULL) {return;}
	while (length(*pL) != 0) {deleteFront(*pL);}
	free(*pL);
	*pL = NULL;
}

// Access Functions

// length()
// Returns the length of L
int length(List L) {
	if (L == NULL) {
		printf("List Error: length() called on NULL List reference\n");
		exit (1);
	}
	return L->length;
}

// getIndex()
// Returns the index of the cursor
int getIndex(List L) {
	if (L == NULL) {
		printf("List Error: getIndex() called on NULL List reference\n");
		exit (1);
	}
	return L->cursorIndex;
}

// front()
// Returns the value at the front of L
int front(List L) {
	if (L == NULL) {
		printf("List Error: front() called on NULL List reference\n");
		exit (1);
	} else if (L->length == 0) {
		printf("List Error: front() called on empty List\n");
		exit (1);		
	} else {
		return (L->front->data);
	}
}

// back()
// Returns the value at the back of L
int back(List L) {
	if (L == NULL) {
		printf("List Error: front() called on NULL List reference\n");
		exit (1);
	} else if (L->length == 0) {
		printf("List Error: front() called on empty List\n");
		exit (1);		
	} else {
		return (L->back->data);
	}
}

// getElement()
// Returns the value of the cursor
int getElement(List L) {
	if (L == NULL) {
		printf("List Error: getElement() called on NULL List reference\n");
		exit (1);
	} else if (L->cursor == NULL) {
		printf("List Error: getElement() called on List with undefined cursor\n");
		exit (1);		
	} else {
		return (L->cursor->data);
	}
}

// equals()
// Returns 1 if List A == List B, else returns 0
int equals(List A, List B) {
	if (A == NULL || B == NULL) {
		printf("List Error: getElement() called on NULL List reference\n");
		exit (1);
	} else if (A->length == B->length) {
		if (A->front->data == B->front->data && A->back->data == B->back->data) {
			Node J = A->front;
			Node K = B->front;
			while (J->next != NULL && K->next != NULL) {
				if (J->data == K->data) {
					J = J->next;
					K = K->next;
				} break;
			} return 1;
		}
	} return 0;
}

// Manipulation Procedures

// clear()
// Removes every entry in the List
void clear(List L) {
	if (L == NULL) {
		printf("List Error: clear() called on NULL List reference\n");
		exit (1);
	} else {
		while (length(L)!=0) {deleteFront(L);}
	}
}

// moveTo()
// Moves the cursor to index i
void moveTo(List L, int i) {
	if (L == NULL) {
		printf("List Error: moveTo() called on NULL List reference\n");
		exit (1);
	}
	if (i == L->cursorIndex) return;
	if (i >= L->length || i < 0) {
		L->cursor = NULL;
		L->cursorIndex =-1;
		return;
	} if (i == 0) L->cursor = L->front;
	if (i == L->length-1) L->cursor = L->back;
	else {
		// Direction value, 0 = left, 1 = right
		int direction = 0;
		// Determine the three possible distances
		int d1 = (L->length-1) - i;
		int d2 = i;
		int d3 = abs(L->cursorIndex - i);
		// Find the shortest distance
		int min = d1;
		if (min > d2) min = d2;
		if (min > d3) min = d3;
		// Set up the traversal from the back of the list
		if (min == d1) {
			L->cursor = L->back;
			L->cursorIndex = L->length-1;
			direction = 0;
		}
		// Set up the traversal from the front of the list
		else if (min == d2) {
			L->cursor = L->front;
			L->cursorIndex = 0;
			direction = 1;
		}
		// Set up the traversal from the current cursor
		else if (min == d3) {
			if (i > L->cursorIndex) direction = 1;
		}
		// Traverse the List
		for(int j=0; j < min; j++) {
			if (direction == 1) moveNext(L);
			else movePrev(L);
		}
	}
	L->cursorIndex = i;
}

// movePrev()
// Moves the cursor to the previous index
void movePrev(List L) {
	if (L == NULL) {
		printf("List Error: movePrev() called on NULL List reference\n");
		exit (1);
	} else if (L->cursor == L->front || L->cursorIndex == -1) {
		L->cursor = NULL;
		L->cursorIndex = -1;
	} else {
		L->cursor = L->cursor->previous;
		L->cursorIndex--;
	}
}
// moveNext()
// Moves the cursor to the next index
void moveNext(List L) {
	if (L == NULL) {
		printf("List Error: moveNext() called on NULL List reference\n");
		exit (1);
	} else if (L->cursor == L->back || L->cursorIndex == -1) {
		L->cursor = NULL;
		L->cursorIndex = -1;
	} else {
		L->cursor = L->cursor->next;
		L->cursorIndex++;
	}
}
// prepend()
// Inserts data to the beginning of the list (before front)
void prepend(List L, int data) {
	if (L == NULL) {
		printf("List Error: prepend() called on NULL List reference\n");
		exit (1);
	} else if (L->length == 0) {
		Node N = newNode(data);
		L->front = L->back = N;
	} else {
		Node N = newNode(data);
		N->next = L->front;
		L->front->previous = N;
		L->front = N;
	}
	if (L->cursorIndex != -1) L->cursorIndex++;
	L->length++;
}

// append()
// Inserts data the the end of the list (after back)
void append(List L, int data) {
	if (L == NULL) {
		printf("List Error: append() called on NULL List reference\n");
		exit (1);
	} else if (L->length == 0) {
		Node N = newNode(data);
		L->front = L->back = N;
	} else {
		Node N = newNode(data);
		N->previous = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}
// insertBefore()
// Inserts data before the cursor
// Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data) {
	if (L == NULL) {
		printf("List Error: insertBefore() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: insertBefore() called on empty List\n");
		exit (1);
	} if (L->cursorIndex < 0) {
		printf("List Error: insertBefore() called on list w/ undefined cursor\n");
		exit (1);
	} else if (L->cursor == L->front) {
		prepend(L, data);
	} else {
		// Link the new node
		Node N = newNode(data);
		N->previous = L->cursor->previous;
		N->next = L->cursor;
		// Link the previous node
		L->cursor->previous->next = N;
		// Link the next node
		L->cursor->previous = N;
		// Update the fields
		L->cursorIndex++;
		L->length++;
	}
}
// insertAfter()
// Inserts data After the cursor
// Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List Error: insertAfter() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: insertAfter() called on empty List\n");
		exit (1);
	} if (L->cursorIndex < 0) {
		printf("List Error: insertAfter() called on list w/ undefined cursor\n");
		exit (1);
	} else if (L->cursor == L->back) {
		append(L, data);
	} else {
		// Link the new node
		Node N = newNode(data);
		N->previous = L->cursor;
		N->next = L->cursor->next;
		// Link the previous node
		L->cursor->next->previous = N;
		// Link the next node
		L->cursor->next = N;
		// Update the length
		L->length++;
	}
}
// deleteFront()
// Removes the element at the front of the list
void deleteFront(List L) {
	if (L == NULL) {
		printf("List Error: deleteFront() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: deleteFront() called on empty List\n");
		exit (1);
	} else  if (L->length == 1) {
		Node temp = L->front;
		L->front = NULL;
		freeNode(&temp);
	} else {
		Node temp = L->front;
		Node a = L->front->next;
		a->previous = NULL;
		L->front = a;
		if (L->cursorIndex != -1) L->cursorIndex--;
		if (L->cursor == temp) moveTo(L, -1);
		freeNode(&temp);
	} L->length--;
}

// deleteBack()
// Removes the element at the back of the list
void deleteBack(List L) {
	if (L == NULL) {
		printf("List Error: deleteBack() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: deleteBack() called on empty List\n");
		exit (1);
	} else  if (L->length == 1) {
		Node temp = L->back;
		L->back = NULL;
		freeNode(&temp);
	} else {
		Node temp = L->back;
		Node a = L->back->previous;
		a->next = NULL;
		L->back = a;
		if (L->cursor == temp) moveTo(L,-1);
		freeNode(&temp);
	} L->length--;
}

// delete()
// Removes the element pointed at by the cursor
// Pre: length()>0, getIndex()>=0
void delete(List L) {
	if (L == NULL) {
		printf("List Error: delete() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: delete() called on empty List\n");
		exit (1);
	} if (L->cursorIndex < 0) {
		printf("List Error: delete() called on list w/ undefined cursor\n");
		exit (1);
	} else if (L->cursor == L->back) {
		deleteBack(L);
	} else if (L->cursor == L->front) {
		deleteFront(L);
	} else {
		Node temp = L->cursor;
		Node a = L->cursor->previous;
		Node b = L->cursor->next;
		a->next = b;
		b->previous = a;
		freeNode(&temp);
		L->length--;
		moveTo(L, -1);
	}
}
// Other Operations

// printList()
// Prints each element of the list to specified file
void printList(FILE* out, List L) {
	if (L == NULL) {
		printf("List Error: printList() called on NULL List reference\n");
		exit (1);
	}
	Node N = NULL;

	for (N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%d ", N->data);
	}
	fprintf(out, "\n");
}

// copyList()
// Returns a new list which is a copy of List L
List copyList(List L) {
	if (L == NULL) {
		printf("List Error: copyList() called on NULL List reference\n");
		exit (1); 
	} else {
		List newL = newList();
		Node N;
		for (N = L->front; N!=NULL; N=N->next) {
			append(newL,N->data);
		}
		return newL;
	}
}
