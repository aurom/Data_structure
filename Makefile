HEADERS = avltree.h

default: testTree

avltree.o: avltree.c $(HEADERS)
	gcc -c avltree.c -o avltree.o

test_tree.o: test_tree.c $(HEADERS)
	gcc -c test_tree.c -o test_tree.o

testTree: test_tree.o avltree.o
	gcc -o testTree test_tree.o avltree.o