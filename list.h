typedef nodo_lista Lnode;
typedef lista_struct List;

struct nodo_lista {
	int element;
	Lnode* next;
	Lnode* prev;
};

struct lista_struct{
	Lnode* head;
	Lnode* tail;
	int length;
}
Lnode* newNode(int);
List* newList();
/*busca un dato en la lista*/
int search(List*, int);
/*inserta un dato en la lista*/
void insert(List*, int);
/*borra un dato de la lista*/
void delete(List*,int);
/*regresa el dato minimo de la lista*/
int minim(List*);
/*regresa el maximo dato de la lista*/
int max(List*);
/*dado un dato regresa el siguiente mayor;
* si no existe regresa ese mismo dato*/
int successor(List*,int);
/*dado un dato regresa el siguiente menor;
* si no existe regresa ese mismo dato*/
int predecessor(List*, int);
/*regresa la inversa de una lista*/
List* inverse(List*);
/*Hace una copia de la lista y la regresa*/
List* copia(List*);
/*regrea el tamaño de la lista*/
int length(List*);
/*concatena dos listas*/
Lista* concat(List*, List*);
/*ordena la lista*/
void msort(List*);
/*imprime la lista*/
void print_list(List*);