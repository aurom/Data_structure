#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

Qnode* newQnode(int data){
	Qnode* nodo = (Qnode*) malloc(sizeof(Qnode));
	nodo->element = data;
	nodo->prev = NULL;
	nodo->next = NULL;
}
Queue* newQueue()
{
	Queue* cola = (Queue*) malloc(sizeof(Queue));
	cola->head = NULL;
	cola->tail = NULL;
}

void enqueue(Queue* cola,int data){
	Qnode* tmp = newQnode(data);
	cola->tail->next = tmp;
	tmp->prev = cola->tail;
	cola->tail = tmp;
}
int dequeue(Queue* cola){
	int data = cola->head->element;
	Qnode* tmp = cola->head;
	cola->head = cola->head->prev;
	cola->head->prev->next = NULL;
	free(tmp);
	return data;
}