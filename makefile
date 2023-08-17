CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra 

BST = bst.c bst_test.c bst.h

DEBUG = yes



bst: $(OBJECTS)
	@$(CC) $(CFLAGS) $(BST) -o bst.out
	
make.o_bst: $(OBJECTS)
	@$(CC) $(CFLAGS) $(BST) -c 
	
clean_bst: 
	@rm *.out *.o
	
all_bst: debug make.o make
	
debug_bst: $(OBJECTS)
	@$(CC) $(CFLAGS) $(BST) -DDEBUG -g -o bst_debug.out 
	
release_bst: $(OBJECTS)
	@$(CC) $(CFLAGS) $(BST) -O3 -o bst_release.out 


	
