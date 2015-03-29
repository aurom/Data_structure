
#define RED 1
#define BLACK 0

//typedef struct rb_node rb_node;
typedef struct RBTree RBTree;
struct RBTree
{
	int element;
	int color;
	RBTree* father;
	RBTree* left;
	RBTree* right;
	int height;
	int coloration;
};

RBTree* newRB(int data);
RBTree* findmin(RBTree*);
RBTree* findmax(RBTree*);
RBTree* find(RBTree*, int);
RBTree* succesor(RBTree*, int);
RBTree* predeccesor(RBTree*, int);
int height(RBTree*);
RBTree* rb_insert(RBTree*, int);
RBTree* rb_delete(RBTree*, int);
int getElement(RBTree*);
RBTree* getParent(RBTree*, RBTree*);
