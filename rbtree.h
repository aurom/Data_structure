
#ifndef RBTREE_H
#define RBTREE_H

	/*definimos nuestro apuntador a una funcion para imprimir los datos del arbol*/
	typedef void (*print_data)(void*);
	/*definimos nuestro apuntador a una funcion para comparar datos del arbol */
	typedef int (*compare)(void*,void*);
	/*Usamos un enum para los colores del Red Black Tree*/
	typedef enum {RED,BLACK}Color;
	typedef struct rb_node rb_node;
	typedef struct RBTree RBTree;

	/**
	* Estructura de un nodo del RedBlack Tree
	* element -- elemento del nodo
	* color -- determina si es RED o BLACK
	* father -- padre del nodo
	* left -- hijo izquierdo del nodo
	* right -- hijo derecho del nodo
	* height -- altura del nodo
	* coloration -- coloracion del nodo.
	**/
	struct rb_node
	{
		void* element;
		Color color;
		rb_node* father;
		rb_node* left;
		rb_node* right;
		int height;
		int coloration;
	};
	/**
	* Estructura de una Red Black Tree
	* root -- raíz del arbol (main node)
	* print -- función para imprimir sus elementos
	* comp -- función para comparar sus elementos
	* e_size -- tamaño de memoria usada por los elementos del Red Black Tree
	**/
	struct RBTree
	{
		rb_node* root;
		print_data print;
		compare comp;
		int e_size;
	};

	/**Genera un nuevo nodo
	* @return rb_node* -- referencia al nuevo nodo.
	**/
	rb_node* newrb_node();
	
	/**
	* Genera un nuevo RedBlack Tree
	* @param elementsize -- tamaño de memoria usada para para 
	* los elementos del Red Black Tree
	* @param print -- función para imprimir los elementos del Red Black Tree
	* @param comp -- función para comparar los elementos del Red Black Tree
	* @return RBTree* -- regresa la regrencia del Red Black Tree 
	* con las especificaciones dadas.
	**/
	RBTree* newRB(int elementsize, print_data print, compare comp);

	/**
	* Destruye el Red Black Tree
	* @param tree -- Red Black Tree a eliminar
	**/
	void destroy(RBTree* tree);
	
	rb_node* find_min(RBTree* tree);
	
	/**
	* Regresa el elemento minimo del RedBlack Tree
	* @return void* -- referencia al elemento minimo del arbol.
	**/
	void* e_min(RBTree* tree);
	
	rb_node* find_max(RBTree* tree);
	
	/**
	* Regresa el elemento maximo del RedBlack Tree
	* @return void* -- referencia al elemento minimo del arbol
	**/
	void* e_max(RBTree* tree);
	/**
	* Regresa el sucesor de un nodo en un RedBlack Tree
	* El sucesor es el que tiene el elemento mayor al nodo dado
	**/
	rb_node* nsuccesor(rb_node* node);
	/**
	* Regresa el sucesor de un elemento en el Red Black Tree
	* El sucesor es el primer elemento mayor al dato pasado
	* tree -- Red Black Tree en donde se buscara el sucesor
	* data -- dato al que se le buscara el sucesor si el dato no esta en el Red Black tree
	* regresa NULL
	**/
	void* succesor(RBTree* tree, void* data);

	rb_node* npredeccesor(rb_node* node);

	void* predeccesor(RBTree* tree, void* data);

	/**
	* Regresa el nodo que contiene al elemento pasado
	* @param tree -- arbol donde se buscara el nodo
	* @param data -- dato a buscar en el arbol; si el dato no esta
	* en el arbol regresa NULL
	* @return rb_node* -- referencia al nodo con el dato pasado
	**/
	rb_node* rb_find(RBTree* tree, void* data);

	/**
	* Regresa la altura de un arbol
	* este es el camino mas largo desde su raiz hasta una hoja
	* tree -- arbol al cual le sacaremos la altura
	* @return int -- altura del arbol
	**/
	int rb_height(RBTree* tree);

	/**
	* Inserta un nuevo elemento al Red Black Tree
	* @param tree -- arbol al que se le añadira un nuevo elemento
	* @param data -- elemento a añadir
	**/
	void rb_insert(RBTree* tree, void* data);

	/**
	* Elimina un elemento del Red Black Tree
	* @param tree -- arbol al que se le eliminara un elemento
	* @param data -- dato a eliminar, si el dato no esta no hace nada.
	**/
	void rb_delete(RBTree* tree, void* data);

	/**
	* Regresa el elemento de un nodo 
	* @param node -- nodo del elemento.
	* @return void* -- elemento del nodo
	**/
	void* get_element(RBTree* tree,rb_node* node);

	/**
	* Imprime el Red Black Tree.
	* @param tree -- Red Black Tree a imprimir.
	**/
	void print_rb(RBTree* tree);

	/**
	* Regresa el pariente mas cercano de dos nodos
	* @param node1, node2 -- nodos a los que se busca el ancestro mas cercano.
	* @return rb_node* -- el ancestro mas cercano de los dos nodos.
	**/
	void* close_parent(RBTree* tree, void* data1, void* data2);


#endif // RBTREE_H