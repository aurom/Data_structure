#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

Qnode* newQnode(){
	Qnode* nodo = (Qnode*) malloc(sizeof(Qnode));
	nodo->element = NULL;
	nodo->prev = NULL;
	nodo->next = NULL;
}
Queue* newQueue(int elementsize, printData print)
{	Queue* cola = (Queue*) malloc(sizeof(Queue));
	cola->head = NULL;
	cola->tail = NULL;
	cola->count = 0;
	cola->e_size = elementsize;
	cola->print = print;
}
int is_qempty(Queue* cola)
{
	if(!cola)
		return TRUE;
	else
		return FALSE;
}
void enqueue(Queue* cola, void* data){
	Qnode* tmp = newQnode();
	tmp->element = malloc(cola->e_size);
	tmp->element = data;
	tmp->prev = cola->tail;
	cola->tail->next = tmp;
	cola->tail = tmp;
	cola->count++;
}
void* dequeue(Queue* cola){
	if(is_qempty(cola))
	{
		puts("Empty queue");
		return NULL;
	}
	void* data = cola->head->element;
	Qnode* tmp = cola->head;
	cola->head = cola->head->next;
	cola->head->prev = NULL;
	cola->count--;
	free(tmp);
	return data;
}

int q_length(Queue* cola)
{
	return cola->count;
}

void printQueue(Queue* cola)
{
	if(!cola)
	{
		printf("None\n");
		return;
	}
	Qnode* node = cola->head;
	while(node)
	{
		printf("| ");
		cola->print(node->element);
		node = node->next;
		printf(" |");
	}
}