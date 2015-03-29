#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
Snode* newNode_Stack(int data)
{
	Snode* top = (Snode*) malloc(sizeof(Stack));
	top->element = data;
	top->prev = NULL;
}
Stack* newStack()
{
	Stack* pila = (Stack*) malloc(sizeof(Stack));
	assert(pila != NULL);
	pila->top = NULL;
	pila->count = 0;
}

int empty(Stack* pila){
	if (pila->top == NULL)
		return 1;
	else
		return 0;
}
Stack* push(Stack* pila, int data)
{
	Snode* tmp =  newNode_Stack(data);
	pila->top->prev = pila->top;
	pila->top = tmp;
	return pila;
}
int pop(Stack* pila){
	if(empty(pila))
	{
		puts("Empty Stack");
		return;
	}

	int data = pila->top->element;
	Snode* tmp = pila->top;
	pila->top = pila->top->prev;
	free(tmp);
	return data;
}