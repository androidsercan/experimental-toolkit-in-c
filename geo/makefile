#$Id: makefile 3948 2011-07-25 15:36:31Z haowu $

include ../makefile.inc

all: etc-geo.a

etc-geo.a: etc-geo.a(geo.o kmeans.o quadtree.o)

geo.o      : geo.h
kmeans.o   : kmeans.h
quadtree.o : quadtree.h

.PHONY : clean

clean :
	-rm *.a *.o
