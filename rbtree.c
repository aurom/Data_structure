#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rbtree.h"

/**Genera un nuevo nodo
* @return rb_node* -- referencia al nuevo nodo.
**/
rb_node* newrb_node()
{
	rb_node* node = (rb_node*) malloc(sizeof(rb_node));
	assert(node != NULL);
	node->element = NULL;
	node->color = RED;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	node->coloration = 0;
	node->height = 0;
}
	
/**
* Genera un nuevo RedBlack Tree
* @param elementsize -- tamaño de memoria usada para para 
* los elementos del Red Black Tree
* @param print -- función para imprimir los elementos del Red Black Tree
* @param comp -- función para comparar los elementos del Red Black Tree
* @return RBTree* -- regresa la regrencia del Red Black Tree 
* con las especificaciones dadas.
**/
RBTree* newRB(int elementsize, print_data print, compare comp)
{
	RBTree* newtree = (RBTree*) malloc(sizeof(RBTree)+elementsize);
	assert(newtree != NULL);
	newtree->root = NULL;
	newtree->print = print;
	newtree->comp = comp;
	newtree->e_size = elementsize;
}
/*rotacion con subarbol izquierdo*/
void rotationl(RBTree* tree, rb_node* node)
{
	rb_node* temp = node->left;
	node->left = temp->right;
	if(temp->right)
		temp->right->father = node;
	temp->father = node->father;
	if(!temp->father)
		tree->root = temp;
	else if (node == node->father->right)
		node->father->right = temp;
	else
		node->father->left = temp;
	temp->right = node;
	node->father = temp;
}

/*rotacion con subarbol derecho*/
rb_node* rotationr(RBTree* tree, rb_node* node)
{
	rb_node* temp = node->right;
	node->right = temp->left;
	if(temp->left)
		temp->left->father = node;
	temp->father = node->father;
	if(!node->father)
		tree->root = temp;
	else if(node == node->father->left)
		node->father->left = temp;
	else
		node->father->right = temp;
	temp->left = node;
	node->father = temp;
}
/**
* Destruye el Red Black Tree
* @param tree -- Red Black Tree a eliminar
**/
void destroy(RBTree* tree)
{
	rb_node* node = tree->root;
	rb_node* save;
	while(node) 
	{
		if(node->left)
		{
			save = node->left;
			node->left = save->right;
			save->right = node;
		}
		else
		{	
			save = node->right;
			free(node);
		}
		node = save;
	}
}
	
rb_node* find_min(RBTree* tree)
{
	if(!tree->root)
	{
		puts("Empty tree.");
		return NULL;
	}
	rb_node* node = tree->root;
	while(node)
		node = node->left;
	return node;
}
	
/**
* Regresa el elemento minimo del RedBlack Tree
* @return void* -- referencia al elemento minimo del arbol.
**/
void* e_min(RBTree* tree)
{
	if(!tree->root)
	{
		puts("Empty tree.");
		return NULL;
	}
	rb_node* min = find_min(tree);
	return min->element;
}
	
rb_node* find_max(RBTree* tree)
{
	if(!tree->root)
	{
		puts("Empty tree.");
		return NULL;
	}
	rb_node* node = tree->root;
	while(node)
		node = node->right;
	return node;
}
	
/**
* Regresa el elemento maximo del RedBlack Tree
* @return void* -- referencia al elemento minimo del arbol
**/
void* e_max(RBTree* tree)
{
	if(!tree->root)
	{
		puts("Empty tree.");
		return NULL;
	}
	rb_node* node = find_max(tree);
	return node->element;
}
rb_node* nmin(rb_node* node)
{
	while(node->left) 
		node = node->left;
	return node;
}

rb_node* nmax(rb_node* node)
{
	while(node->right)
		node = node->right;
	return node;
}
/**
* Regresa el sucesor de un nodo en un RedBlack Tree
* El sucesor es el que tiene el elemento mayor al nodo dado
**/
rb_node* nsuccesor(rb_node* node)
{
	if(!node)
		return NULL;
	if(node->right)
		return nmin(node->right);
	rb_node* aux = node->father;
	while(aux && node == aux->right)
	{
		node = aux;
		aux = aux->father;
	}
	return aux;
}

/**
* Regresa el sucesor de un elemento en el Red Black Tree
* El sucesor es el primer elemento mayor al dato pasado
* tree -- Red Black Tree en donde se buscara el sucesor
* data -- dato al que se le buscara el sucesor si el dato no esta en el Red Black tree
* regresa NULL
**/
void* succesor(RBTree* tree, void* data)
{
	rb_node* node = rb_find(tree,data);
	node = nsuccesor(node);
	return node->element;
}

rb_node* npredeccesor(rb_node* node)
{
	if(!node)
		return NULL;
	if(node->left)
		return nmax(node->left);
	rb_node* aux = node->father;
	while(aux && node == aux->left)
	{
		node = aux;
		aux = aux->father;
	}
	return aux;
}
void* predeccesor(RBTree* tree, void* data)
{
	rb_node* node = rb_find(tree,data);
	node = npredeccesor(node);
	return node->element;
}

/**
* Regresa el nodo que contiene al elemento pasado
* @param tree -- arbol donde se buscara el nodo
* @param data -- dato a buscar en el arbol; si el dato no esta
* en el arbol regresa NULL
* @return rb_node* -- referencia al nodo con el dato pasado
**/
rb_node* rb_find(RBTree* tree, void* data)
{
	rb_node* node = tree->root;
	while(node)
	{
		if(tree->comp(data,node->element) < 0)
			node = node->left;
		else if (tree->comp(data,node->element) > 0)
			node = node->right;
		else
			return node;
	}
	return NULL;
}

/**
* Regresa la altura de un arbol
* este es el camino mas largo desde su raiz hasta una hoja
* tree -- arbol al cual le sacaremos la altura
* @return int -- altura del arbol
**/
int rb_height(RBTree* tree)
{
	if(!tree->root)
		return -1;
	else
		return tree->root->height;
}

/**
* Regresa la altura de un nodo
* este es el camino mas largo desde ese nodo hasta una de sus hojas
* @param tree -- arbol en donde se va a buscar la altura de uno de sus nodos
* @param node -- node al que regresaremos su altura
* @return int -- altura del nodo
**/
int rb_node_height(rb_node* node)
{
	if(!node)
		return -1;
	return node->height;
}

void rb_fix_insert(RBTree* tree, rb_node* to_fix)
{
	if(!to_fix->father->father)
		return;
	while(to_fix->color == RED)
	{
		rb_node* grandfa = to_fix->father->father;
		rb_node* uncle = NULL;
		if (to_fix->father == grandfa->left)
		{
			uncle = grandfa->right;
			if(uncle && uncle->color == RED)
			{
				to_fix->father->color = uncle->color = BLACK;
				grandfa->color = RED;
				to_fix = grandfa;
			}
			else
			{ 	
				if (to_fix == to_fix->father->right)
				{
					to_fix = to_fix->father;
					rotationr(tree,to_fix);
				}
				to_fix->father->color = BLACK;
				to_fix->father->father->color = RED;
				rotationl(tree,to_fix->father->father);
			}
		}
		else
		{
			uncle = grandfa->left;
			if(uncle && uncle->color == RED)
			{
				to_fix->father->color = uncle->color = BLACK;
				grandfa->color = RED;
				to_fix = grandfa;
			}
			else 
			{
				if (to_fix == to_fix->father->left)
				{
				to_fix = to_fix->father;
				rotationl(tree,to_fix);
				}
				to_fix->father->color = BLACK;
				to_fix->father->father->color = RED;
				rotationr(tree,to_fix->father->father);
			}
		}
	}
	tree->root->color = BLACK;
}


/**
* Inserta un nuevo elemento al Red Black Tree
* @param tree -- arbol al que se le añadira un nuevo elemento
* @param data -- elemento a añadir
**/
void rb_insert(RBTree* tree, void* data)
{
	rb_node* newnode = newrb_node();
	newnode->element = malloc(tree->e_size);
	newnode->element = data;
	if(!tree->root)
	{
		newnode->color = BLACK;
		tree->root = newnode;

	}
	else
	{
		rb_node* node = tree->root;
		while(node)
		{
			if(tree->comp(data,node->element) < 0)
				node = node->left;
			else if(tree->comp(data,node->element) > 0)
				node = node->right;
			else
				return;
		}
		newnode->father = node;
		if(tree->comp(data,node->element) < 0)
			node->left = newnode;
		else
			node->right = newnode;

		rb_fix_insert(tree,newnode);
	}
}

/*cambiamos el lugar de u por v en el arbol tree*/
rb_change(RBTree* tree, rb_node* u, rb_node* v)
{
	if(tree->root == u)
		tree->root = v;
	else if(u == u->father->left)
		u->father->left = v;
	else u->father->right = v;
	v->father = u->father;
}

void rb_fix_delete(RBTree* tree, rb_node* x)
{
	while(x != tree->root && x->color == BLACK)
	{
		rb_node* bro;
		if(x == x->father->left)
		{
			bro = x->father->right;
			if(bro->color == RED)
			{
				x->father->color = RED;
				bro->color = BLACK;
				rotationr(tree,x->father);
				bro = x->father->right;
			}
			if(bro->left->color == BLACK && bro->right->color == BLACK)
			{
				bro->color = RED;
				x = x->father;
			}
			else 
			{
				if (bro->right->color == BLACK)
				{
					bro->left->color = BLACK;
					bro->color = RED;
					rotationl(tree,bro);
					bro = x->father->right;
				}
				bro->color = x->father->color;
				x->father->color = BLACK;
				bro->right->color = BLACK;
				rotationr(tree,x->father);
				x = tree->root;
			}
		}
		else
		{
			bro = x->father->left;
			if(bro->color == RED)
			{
				x->father->color = RED;
				bro->color = BLACK;
				rotationl(tree,x->father);
				bro = x->father->left;
			}
			if(bro->left->color == BLACK && bro->right->color == BLACK)
			{
				bro->color = RED;
				x = x->father;
			}
			else
			{
				if(bro->left->color == BLACK)
				{
					bro->right->color = BLACK;
					bro->color = RED;
					rotationr(tree,bro);
					bro = x->father->left;
				}
				bro->color = x->father->color;
				x->father->color = BLACK;
				x->left->color = BLACK;
				rotationl(tree,x->father);
				x = tree->root;
			}
		}
	}
	x->color = BLACK;
}
/**
* Elimina un elemento del Red Black Tree
* @param tree -- arbol al que se le eliminara un elemento
* @param data -- dato a eliminar, si el dato no esta no hace nada.
**/
void rb_delete(RBTree* tree, void* data)
{
	if(!tree->root)
	{
		puts("Empty tree.");
		return;
	}
	rb_node* to_delete = rb_find(tree,data);
	if(!to_delete)
	{
		puts("No find the element.");
		return;
	}
	Color original = to_delete->color;
	rb_node* aux;
	rb_node* aux2;
	if(!to_delete->left)
	{
		aux = to_delete->right;
		rb_change(tree,to_delete,to_delete->right);
	}
	else if (!to_delete->right)
	{
		aux = to_delete->left;
		rb_change(tree,to_delete,to_delete->left);
	}
	else 
	{
		aux2 = to_delete;
		aux2 = nmin(to_delete->right);
		original = aux2->color;
		aux = aux2->right;
		if(aux2->father == to_delete)
			aux->father = aux2;
		else
		{
			rb_change(tree,aux2,aux2->right);
			aux2->right = to_delete->right;
			aux2->right->father = aux2;
		}
		rb_change(tree,to_delete,aux2);
		aux2->left = to_delete->left;
		aux2->left->father = aux2;
		aux2->color = to_delete->color;
	}
	if(original == BLACK)
		rb_fix_delete(tree,aux);
}

/**
* Regresa el elemento de un nodo 
* @param node -- nodo del elemento.
* @return void* -- elemento del nodo
**/
void* get_element(RBTree* tree,rb_node* node)
{
	if(node == tree->root)
		return tree->root->element;
	else
		return node->element;
}

void print_tree(rb_node* node, int level, print_data print)
{
	int i;
	if(!node)
	{
		printf("\n");
		return;
	}
	print_tree(node->right,level+1,print);
	for(i = 0; i < level; i++)
		putchar('\t');
	print(node->element);
	if(node->color == RED)
		printf(" (R)");
	else
		printf("(B)");
	print_tree(node->left,level+1,print);
}
/**
* Imprime el Red Black Tree.
* @param tree -- Red Black Tree a imprimir.
**/
void print_rb(RBTree* tree)
{
	print_tree(tree->root,0,tree->print);
}
/**
* Regresa el pariente mas cercano de dos nodos
* @param node1, node2 -- nodos a los que se busca el ancestro mas cercano.
* @return rb_node* -- el ancestro mas cercano de los dos nodos.
**/
rb_node* nclose_parent(rb_node* node1, rb_node* node2)
{
	while(node1)
	{
		node1->coloration = 1;
		node1 = node1->father;
	}
	while(node2->coloration == 0)
		node2 = node2->father;
	return node2;
}

void* close_parent(RBTree* tree, void* data1, void* data2)
{
	rb_node* node1 = rb_find(tree,data1);
	rb_node* node2 = rb_find(tree,data2);
	if(!node1 || !node2)
	{
		puts("Those elements aren't in the Tree.");
		return NULL;
	}
	return nclose_parent(node1,node2)->element;
}