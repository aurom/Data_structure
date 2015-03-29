

typedef struct stack_node Snode;
typedef struct stack_struct Stack;

struct stack_node{
	int data;
	snode* prev;
}
struct stack_struct {
	snode top;
}
Snode* newNode_Stack(int);
Stack* newStack();
int empty(Stack*);
Stack* push(Stack*, int);
Stack* pop(Stack*);