/* Graham Greving
* ggreving@ucsc.edu
* CMPS 101: Introduction to Algorithms
* Pat Tantalo
* August 7, 2013
*/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

//List Type
typedef struct  ListObj* List;

//Constructors and Destructors

//newList()
//Returns reference to new empty List object
List newList(void);

//freeList()
//Frees all heap memory associated with List *pL, and sets *ppL to NULL
void freeList(List* pL);

//Access Functions

//length()
//Returns the length of L
int length(List L);

//getIndex()
//Returns the index of the cursor
int getIndex(List L);

//front()
//Returns the value at the front of L
int front(List L);

//back()
//Returns the value at the back of L
int back(List L);

//getElement()
//Returns the value of the cursor
int getElement(List L);

//equals()
//Returns 1 if List A == List B, else returns 0
int equals(List A, List B);

//Manipulation Procedures

//clear()
//Removes every entry in the List
void clear(List L);

//moveTo()
//Moves the cursor to index i
void moveTo(List L, int i);

//movePrev()
//Moves the cursor to the previous index
void movePrev(List L);

//moveNext()
//Moves the cursor to the next index
void moveNext(List L);

//prepend()
//Inserts data to the beginning of the list (before front)
void prepend(List L, int data);

//append()
//Inserts data the the end of the lest (after back)
void append(List L, int data);

//insertBefore()
//Inserts data before the cursor
void insertBefore(List L, int data);

//insertAfter()
//Inserts data After the cursor
void insertAfter(List L, int data);

//deleteFront()
//Removes the element at the front of the list
void deleteFront(List L);

//deleteBack()
//Removes the element at the back of the list
void deleteBack(List L);

//delete()
//Removes the element pointed at by the cursor
void delete(List L);

//Other Operations

//printList()
//Prints each element of the list to specified file
void printList(FILE* out, List L);

//copyList()
//Returns a new list which is a copy of List L
List copyList(List L);

#endif