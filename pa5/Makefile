# Graham Greving
# ggreving@ucsc.edu
# CMPS 101: Introduction to Algorithms
# Pat Tantalo
# August 7, 2013
#
#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes FindComponents
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#  make submit		    submits the files on unix
#------------------------------------------------------------------------------
AUTHOR		   = Graham Greving
EMAIL		   = ggreving@ucsc.edu
EXEC 		   = FindComponents GraphTest GraphClient
BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = $(BASE_SOURCES:.c=.o)
EXEC_SOURCES   = $(EXEC:.c)
EXEC_OBJECTS   = $(EXEC_SOURCES:.c=.o)
HEADERS        = $(BASE_SOURCES:.c=.h)
OTHERS         = README Makefile
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full --show-reachable=yes
HOST 	       = $(findstring ucsc,$(shell hostname))
WARNING        = $(error CANNOT SUBMIT, NOT ON UNIX.UCSC)
ifeq ($(HOST),ucsc)
SUBMIT 		   = submit cmps101-pt.u13 pa5
endif

all: $(EXEC)

FindComponents: FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest: GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphClient: GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindComponents.o: FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o: GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

GraphClient.o: GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	$(REMOVE) $(EXEC) $(EXEC_OBJECTS) $(BASE_OBJECTS) *.o

checkFind: FindComponents
	$(MEMCHECK) FindComponents in1 out1

checkTest: GraphTest
	$(MEMCHECK) GraphTest

submit:
ifdef SUBMIT
	$(SUBMIT) README Makefile *.h Graph.c List.c FindComponents.c GraphTest.c 
else
	$(WARNING)
endif

git:
	git commit -a
