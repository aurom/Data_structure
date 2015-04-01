HEADERS = list.h stack.h queue.h avltree.h rbtree.h

default: test_structures

list.o: list.c $(HEADERS)
	gcc -c list.c -o list.o

stack.o: stack.c $(HEADERS)
	gcc -c stack.c -o stack.o

queue.o: queue.c $(HEADERS)
	gcc -c queue.c -o queue.o

avltree.o: avltree.c $(HEADERS)
	gcc -c avltree.c -o avltree.o

rbtree.o: rbtree.c $(HEADERS)
	gcc -c rbtree.c -o rbtree.o

test_structures.o: test_structures.c $(HEADERS)
	gcc -c test_structures.c -o test_structures.o

test_structures: list.o stack.o queue.o avltree.o rbtree.o test_structures.o 
	gcc -o test_structures list.o stack.o queue.o avltree.o rbtree.o test_structures.o