#include <stdio.h>
#include <stlib.h>
#include <assert.h>
#include "list.h"
Lnode* newNode(int data){
	Lnode* node = (Lnode*) malloc(sizeof(Lnode));
	assert(node != NULL);
	nodo->element = data;
	nodo->prev = NULL;
	nodo->next = NULL;
	return node;
}
List* newList(){
	List* lista = (List*) malloc(sizeof(List));
	assert(lista != NULL);
	lista->head = NULL;
	lista->tail = NULL;
	lista->length = 0;
}
/*busca un dato en la lista*/
Lnode* search(List* lista, int data)
{
	if(data == lista->head->element)
		return lista->head;
	if(data == lista->tail->element)
		return lista->tail;
	Lnode* node = lista->head;
	while(node){
		if(node->element == data)
			return node;
		node = node->next;
	}
	return NULL;
}
/*inserta un dato en la lista*/
void insert(List* lista, int data){
	Lnode* node = newNode(data);
	node->next = lista->head;
	if(lista->head != NULL)
		lista->head->prev = node;
	lista->head = node;
	lista->length++;
}
/*borra un dato de la lista*/
void delete(List* lista,int data)
{
	Lnode* node = search(lista,data);
	if(node == NULL)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	lista->length--;
}
/*regresa el dato minimo de la lista*/
int minim(List* lista){
	int min;
	Lnode* node = lista->head;
	min = node->element;
	while(node){
		if(min > node->element)
			min = node->element;
		node = node->next;
	}
}
/*regresa el maximo dato de la lista*/
int max(List* lista){
	int max;
	Lnode* node = lista->head;
	max = node->element;
	while(node){
		if(max < node->element)
			max = node->element;
		node = node->next;
	}
}
/*dado un dato regresa el siguiente mayor;
* si no existe regresa ese mismo dato*/
int successor(List*,int){
	return 0;
}
/*dado un dato regresa el siguiente menor;
* si no existe regresa ese mismo dato*/
int predecessor(List*, int){
	return 0;
}
/*regresa la inversa de una lista*/
List* inverse(List* lista){
	Lnode* node = lista->tail;
	List* inverse = newList();
	while(node){
		insert(inverse,node->element);
		node = node->prev;
	}
	return inverse;
}
/*Hace una copia de la lista y la regresa*/
List* copia(List* lista){
	Lnode* node = lista->head;
	List* copia = newList();
	while(node){
		insert(copia,node->element)
		node = node->next;
	}
}
/*regrea el tamaño de la lista*/
int length(List* lista){
	return lista->length;
}
/*concatena dos listas*/
Lista* concat(List* list1, List* list2){
	List* concat = list1;
	Lnode* node = list2->head;
	while(node){
		insert(concat,node->element);
		node = node->next;
	}
	return concat;	
}
/*ordena la lista*/
void msort(List*){
	
}
