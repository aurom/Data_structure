#ifndef _LIST_H
#define _LIST_H

	typedef int (*compare)(void*,void*);
	typedef	void (*printData)(void*);
	//typedef	void (*freeData)(void*);
	typedef struct nodo_lista Lnode;
	typedef struct lista_struct List;
	struct nodo_lista {
		void* element;
		Lnode* next;
		Lnode* prev;
	};

	struct lista_struct{
		Lnode* head;
		Lnode* tail;
		int length;
		int e_size;
		printData print;
		compare cmp;
	};

	Lnode* newNode();
	List* newList(int,printData,compare);

	void list_destroy(List*);
	/*busca un dato en la lista*/
	Lnode* search(List*, void*);
	/*inserta un dato en la lista*/
	void insert(List*, void*);
	/*borra un dato de la lista*/
	void delete(List*,void*);
	/*regresa el dato minimo de la lista*/
	void* minim(List*);
	/*regresa el maximo dato de la lista*/
	void* max(List*);
	/*dado un dato regresa el siguiente mayor;
	* si no existe regresa ese mismo dato*/
	void* successor(List*,void*);
	/*dado un dato regresa el siguiente menor;
	* si no existe regresa ese mismo dato*/
	void* predecessor(List*, void*);
	/*regresa la inversa de una lista*/
	List* inverse(List*);
	/*Hace una copia de la lista y la regresa*/
	List* copia(List*);
	/*regrea el tamaño de la lista*/
	int length(List*);
	/*concatena dos listas*/
	List* concat(List*, List*);
	/*ordena la lista*/
	void msort(List*);
	/*imprime la lista*/
	void print_list(List*);

#endif