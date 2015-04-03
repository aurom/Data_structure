#ifndef AVLTREE_H
#define AVLTREE_H

	typedef int (*compare)(void*,void*);
	typedef void (*printData)(void*);
	typedef struct AvlTree AvlTree;

	struct AvlTree
	{
		void* element;
		AvlTree* father;
		AvlTree* left;
		AvlTree* right;
		int height;
		int color;
	};
	/*crea un arbol*/
	AvlTree* newAvl(void*,int);
	
	/*borra el arbol*/
	void makeEmpty(AvlTree*);

	AvlTree* find(AvlTree*,void*, compare);

	AvlTree* findmin(AvlTree*);

	AvlTree* findmax(AvlTree*);

	int height(AvlTree*);

	AvlTree* avl_insert(AvlTree*, void*, int, compare);

	AvlTree* avl_delete(AvlTree*,void*, compare);

	void* getElement(AvlTree*);

	void pintAVL(AvlTree*, printData);

	AvlTree* getParent(AvlTree*, void*, void*,compare);

#endif // AVLTREE_H