#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
Lnode* newNode(){
	Lnode* node = (Lnode*) malloc(sizeof(Lnode));
	assert(node != NULL);
	node->element = NULL;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

List* newList(int e_size, printData fprint, compare comp){
	List* lista = malloc(sizeof(List));
	lista->head = NULL;
	lista->tail = NULL;
	lista->length = 0;
	lista->print = fprint;
	lista->cmp = comp;
	return lista;
}

void list_destroy(List* lista)
{
	Lnode* current;
	while(lista->tail)
	{
		current = lista->tail;
		lista->tail = lista->tail->prev;
		free(current);
	}
}
/*busca un dato en la lista*/
Lnode* search(List* lista, void* data)
{
	if(lista->cmp(data,lista->head->element) == 0)
		return lista->head;
	if(lista->cmp(data,lista->tail->element) == 0)
		return lista->tail;
	Lnode* node = lista->head;
	while(node){
		if(lista->cmp(data,node->element) == 0)
			return node;
		node = node->next;
	}
	return NULL;
}
/*inserta un dato en la lista*/
void insert(List* lista, void* data){
	Lnode* node = newNode();
	node->element = malloc(lista->e_size);
	node->element = data;
	
	if(lista->length == 0){
		node->next = lista->head;
		node->prev = lista->tail;
		lista->head = node;
		lista->tail = node;
	}
	else
	{
		node->prev = lista->tail;
		lista->tail->next = node;
		lista->tail = node;
	}
	lista->length++;
}
/*borra un dato de la lista*/
void delete(List* lista,void* data)
{
	Lnode* node = search(lista,data);
	if(node == NULL)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	lista->length--;

	free(node->element);
	free(node);
}
/*regresa el dato minimo de la lista*/
void* minim(List* lista){
	void* min;
	Lnode* node = lista->head;
	min = node->element;
	while(node){
		if(lista->cmp)
			if(lista->cmp(min,node->element) > 0)
				min = node->element;
		node = node->next;
	}
	return min;
}
/*regresa el maximo dato de la lista*/
void* list_max(List* lista){
	void* max;
	Lnode* node = lista->head;
	max = node->element;
	while(node){
		if(lista->cmp)
			if(lista->cmp(max,node->element) < 0)
				max = node->element;
		node = node->next;
	}
	return max;
}
/*dado un dato regresa el siguiente mayor;
* si no existe regresa ese mismo dato*/
void* successor(List* lista,void* data){
	return NULL;
}
/*dado un dato regresa el siguiente menor;
* si no existe regresa ese mismo dato*/
void* predecessor(List* lista, void* data){
	return NULL;
}
/*regresa la inversa de una lista*/
List* inverse(List* lista){
	Lnode* node = lista->tail;
	List* inverse = newList(lista->e_size,lista->print,lista->cmp);
	while(node){
		insert(inverse,node->element);
		node = node->prev;
	}
	return inverse;
}
/*Hace una copia de la lista y la regresa*/
List* copia(List* lista){
	Lnode* node = lista->head;
	List* copia = newList(lista->e_size,lista->print,lista->cmp);
	while(node){
		insert(copia,node->element);
		node = node->next;
	}
}
/*regrea el tamaño de la lista*/
int list_length(List* lista){
	return lista->length;
}
/*concatena dos listas*/
List* concat(List* list1, List* list2){
	List* concat = list1;
	Lnode* node = list2->head;
	while(node){
		insert(concat,node->element);
		node = node->next;
	}
	return concat;	
}

void print_list(List* lista)
{
	if(!lista)
		printf("None\n");
	else
	{
		printf("[");
		Lnode* node = lista->head;
		while(node->next)
		{
			lista->print(node->element);
			node = node->next;
			printf(", ");
		}
		lista->print(node->element);
		printf("]\n");
	}
}
/*ordena la lista*/
void msort(List* lista){
	return;	
}
