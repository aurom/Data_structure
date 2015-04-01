#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
Snode* newNode_Stack()
{
	Snode* top = (Snode*) malloc(sizeof(Snode));
	top->element = NULL;
	top->prev = NULL;
}
Stack* newStack(int elementsize, printData print)
{
	Stack* pila = (Stack*) malloc(sizeof(Stack));
	assert(pila != NULL);
	pila->top = NULL;
	pila->count = 0;
	pila->e_size = elementsize;
	pila->print = print;
}

int is_sempty(Stack* pila){
	if (pila->top == NULL)
		return TRUE;
	else
		return FALSE;
}

void push(Stack* pila, void* data)
{
	Snode* node =  newNode_Stack();
	node->element = malloc(pila->e_size);
	node->element = data;
	node->prev = pila->top;
	pila->top = node;
	pila->count++;
}
void* pop(Stack* pila){
	if(is_sempty(pila))
	{
		puts("Empty Stack");
		return NULL;
	}

	void* data = pila->top->element;
	Snode* tmp = pila->top;
	pila->top = tmp->prev;
	pila->count--;
	free(tmp);
	return data;
}

int s_length(Stack* pila)
{
	return pila->count;
}

void printStack(Stack* pila)
{
	if(is_sempty(pila))
		printf("None\n");
	else
	{
		Snode* node = pila->top;
		while(node){
			printf(" |");
			pila->print(node->element);
			node = node->prev;
			printf(" |");
			printf("\n");
		}
		printf("____________\n");
	}
}