#$Id: makefile 3948 2011-07-25 15:36:31Z haowu $

include ../makefile.inc

all: etc-util.a

etc-util.a: etc-util.a(heap.o search.o timer.o util.o vbe.o)

heap.o      : heap.h
search.o    : search.h
timer.o     : timer.h
util.o      : util.h
vbe.o       : vbe.h
raw_query.o : raw_query.h

.PHONY : clean

clean :
	-rm *.a *.o
