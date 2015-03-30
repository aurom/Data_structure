

//typedef void* any_t;
typedef int (*compare)(void* dato,void* element);
typedef struct avlnode AvlTree;
struct avlnode{
	void* element;
	AvlTree* parent;
	AvlTree* left;
	AvlTree* right;
	int height;
	int color;
	int (*compare)(void*,void*);
	void (*printData)(void*);
	void (*freeData)(void*);
};
/*crea un arbol*/
AvlTree* newAvl(void*);
/*borra el arbol*/
void makeEmpty();

AvlTree* find(AvlTree*,void*);

AvlTree* findmin(AvlTree*);

AvlTree* findmax(AvlTree*);

int height(AvlTree*);

AvlTree* insert(AvlTree*, void*, compare comparador);

AvlTree* delTree(AvlTree*,void*, compare comparador);

void* getElement(AvlTree*);

void pintTree(AvlTree*);

AvlTree* getPariente(AvlTree*, AvlTree*);

/*funcion para realizar comparacions*/