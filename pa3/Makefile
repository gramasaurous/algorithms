#------------------------------------------------------------------------------
# * Graham Greving
# * ggreving@ucsc.edu
# * CMPS 101: Introduction to Algorithms
# * Pat Tantalo
# * July 24, 2013
#
#------------------------------------------------------------------------------ 

MAINCLASS  = Sparse
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE) Manifest

submit:
	submit cmps101-pt.u13 pa3 $(SOURCES)
