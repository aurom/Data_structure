#ifndef STACK_H
#define STACK_H

#define TRUE 1
#define FALSE 0

	typedef	void (*printData)(void*);
	typedef struct stack_node Snode;
	typedef struct stack_struct Stack;

	struct stack_node{
		void* element;
		Snode* prev;
	};

	struct stack_struct {
		Snode* top;
		printData print;
		int count;
		int e_size;
	};

	Snode* newNode_Stack();
	Stack* newStack(int, printData);
	int is_sempty(Stack*);
	void push(Stack*, void*);
	void* pop(Stack*);
	int s_length(Stack*);
	void printStack(Stack*);
	
#endif // STACK_H