

typedef struct stack_node Snode;
typedef struct stack_struct Stack;

struct stack_node{
	int element;
	Snode* prev;
};

struct stack_struct {
	Snode* top;
	int count;
	int (*compare)(void*,void*);
	void (*printData)(void*);
	void (*freeData)(void*);
};

Snode* newNode_Stack(int);
Stack* newStack();
int empty(Stack*);
Stack* push(Stack*, int);
int pop(Stack*);
int length(Stack*);