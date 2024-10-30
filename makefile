# Macros
CC = gcc217
CFLAGS = 
# Dependency rules for non-file targets
all: testsymtablelist
clobber: clean
	rm -f *~ \#*\#
clean: 
	rm -f testsymtable *.o 
# Dependency rules for file targets
testsymtablelist: testsymtable.o symtablelist.o 
	$(CC) $(CFLAGS) testsymtable.o symtablelist.o –o testsymtablelist
testsymtable.o: testsymtable.c symtable.h
	$(CC) $(CFLAGS) -c testsymtable.c
symtablelist.o: symtablelist.c symtable.h
	$(CC) $(CFLAGS) -c symtablelist.c