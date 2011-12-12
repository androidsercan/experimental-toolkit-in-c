#$Id: makefile 3944 2011-07-25 12:34:58Z haowu $

include ../makefile.inc

all: etc-text.a

etc-text.a: etc-text.a(analyzer.o dictionary.o doc_index.o table.o trie.o)

analyzer.o   : analyzer.h
dictionary.o : dictionary.h
doc_index.o  : doc_index.h
table.o      : table.h
trie.o       : trie.h

.PHONY : clean

clean :
	-rm *.a *.o
