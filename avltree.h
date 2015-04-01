#ifndef AVLTREE_H
#define AVLTREE_H

	typedef int (*compare)(void*,void*);
	typedef void (*printData)(void*);
	typedef struct avlnode AvlTree;
	struct avlnode{
		void* element;
		AvlTree* parent;
		AvlTree* left;
		AvlTree* right;
		printData print;
		compare comp;
		int e_size;
		int color;
		int height;
	};
	/*crea un arbol*/
	AvlTree* newAvl(int,printData,compare);
	/*borra el arbol*/
	void makeEmpty(AvlTree*);

	AvlTree* find(AvlTree*,void*);

	AvlTree* findmin(AvlTree*);

	AvlTree* findmax(AvlTree*);

	int height(AvlTree*);

	void avl_insert(AvlTree*, void*, printData, compare);

	void avl_delete(AvlTree*,void*);

	void* getElement(AvlTree*);

	void pintAVL(AvlTree*);

	AvlTree* getParent(AvlTree*, AvlTree*);

#endif // AVLTREE_H