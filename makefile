# Dependency rules for non-file targets
all: testsymtablelist
clobber: clean
	rm -f *~ \#*\#
clean: rm -f testsymtable *.o 
# Dependency rules for file targets
testsymtablelist: testsymtable.o symtablelist.o 
	gcc217 testsymtable.o symtablelist.o –o testsymtablelist
testsymtable.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c
symtablelist.o: symtablelist.c symtable.h
	gcc217 -c symtablelist.c