#$Id: makefile 3948 2011-07-25 15:36:31Z haowu $

include makefile.inc

all: etc-geo etc-text etc-util etc.a 

etc.a: etc.a(geo/geo.o geo/kmeans.o geo/quadtree.o \
             text/analyzer.o text/dictionary.o text/doc_index.o text/table.o text/trie.o \
             util/heap.o util/search.o util/timer.o util/util.o util/vbe.o \
             base.o)

base.o : base.h

.PHONY : etc-geo etc-text etc-util

etc-geo:
	$(MAKE) -C geo

etc-text:
	$(MAKE) -C text

etc-util:
	$(MAKE) -C util

.PHONY : clean

clean :
	-rm *.a *.o
	$(MAKE) -C geo clean
	$(MAKE) -C text clean
	$(MAKE) -C util clean
