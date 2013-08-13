#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#       make ListTest          makes ListTest
#       make clean             removes .o files
#       make spotless          removes .o and executeables
#       make submit            submits necessary files (only on unix.ucsc.edu)
#
#------------------------------------------------------------------------------

Lex: Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o: Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o: ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

ListTest: ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o: List.c List.h
	gcc -c -std=c99 -Wall List.c

clean:
	rm -f Lex ListClient ListTest Lex *.o
 
submit:
	submit cmps101-pt.u13 pa2 Makefile README Lex.c List.c List.h ListClient.c
