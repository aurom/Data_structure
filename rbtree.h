
#ifndef RBTREE_H
#define RBTREE_H
#define RED 1
#define BLACK 0

	typedef void (*printData)(void*);
	typedef int (*compare)(void*,void*);
	typedef struct RBTree RBTree;
	struct RBTree
	{
		void* element;
		int color;
		RBTree* father;
		RBTree* left;
		RBTree* right;
		int height;
		int coloration;
		printData print;
		compare comp;
	};
	void make_empty(RBTree*);
	RBTree* newRB(int,printData,compare);
	RBTree* find_min(RBTree*);
	RBTree* find_max(RBTree*);
	RBTree* rb_find(RBTree*, void*);
	RBTree* succesor(RBTree*, void*);
	RBTree* predeccesor(RBTree*, void*);
	int rb_height(RBTree*);
	void rb_insert(RBTree*, void*,int,printData,compare);
	void rb_delete(RBTree*, void*);
	void* get_element(RBTree*);
	RBTree* get_parent(RBTree*, RBTree*);
	void print_rb(RBTree*);

#endif // RBTREE_H