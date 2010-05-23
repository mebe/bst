CC = gcc -ansi -pedantic -Wall $(CCFLAGS)
all:
	make sl "CCFLAGS=-DNDEBUG"
debug:
	make sl "CCFLAGS=-UNDEBUG"
sl: sl.o bst.o
	 $(CC) -o sl sl.o bst.o
bst.o: bst.c bst.h
	$(CC) -c bst.c
sl.o: sl.c sl.h
	$(CC) -c sl.c
clean:
	rm *.o sl
