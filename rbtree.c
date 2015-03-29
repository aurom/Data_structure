#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rbtree.h"

/*Crea un nuevo arbol
* data -- elemento que tendra el nuevo arbol
*/
RBTree* newRB(int data){
	RBTree* tree = (RBTree*) malloc(sizeof(RBTree));
	assert(tree != NULL);
	tree->element = data;
	tree->color = RED;
	tree->father = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->height = 0;
	tree->coloration = 0;
}

/*Elimina el arbol*/
void makeEmpty(RBTree* tree)
{
	if(tree)
	{
		makeEmpty(tree->left);
		makeEmpty(tree->right);
		free(tree);
	}
	return;
}

/*Encuenta el subarbol minimo.
* tree - arbol donde se encontrara su minimo.
*/
RBTree* findmin(RBTree* tree)
{
	if(!tree)
		return NULL;
	while(tree->left)
		tree = tree->left;
	return tree;
}

/*Encuentra el subarbol maximo.
* tree -- arbol del que se encontrara su maximo
*/
RBTree* findmax(RBTree* tree)
{
	if(!tree)
		return NULL;
	while(tree->right)
		tree = tree->right;
	return tree;
}

/*Encuentra el arbol con el dato pasado
* tree -- arbol donde se buscara
* data -- elemento que se buscara en el arbo
* si no se encuentra o el arbol es vacio regresa NULL
*/
RBTree* find(RBTree* tree, int data)
{
	if(!tree)
		return NULL;
	while(tree && tree->element != data)
	{
		if(data < tree->element)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return tree;
}

/*Encuentra el siguiente mayor arbol del arbol con el dato pasado
* tree -- arbol base
* data -- elemento del arbol al que se le buscara el sucesor
* si ningun arbol tiene ese elemento regresa NULL
* si ese arbol es el mayor regresa ese arbol
*/
RBTree* succesor(RBTree* tree, int data)
{
	RBTree* node = find(tree,data);
	if(!node)
		return NULL;
	if(node->right)
		return findmin(node->right);
	RBTree* ancestor = node->father;
	while(ancestor && node == ancestor->right)
	{
		node = ancestor;
		ancestor = ancestor->father;
	}
}

/*Encuentra el arbol con elemento menor al elemento pasado
* tree --  arbol base
* data -- elemento del arbol al que se le buscara su predecesor
* si no hay un arbol con ese elemento regresa NULL
* si no hay un elemento menor regresa ese arbol
*/
RBTree* predeccesor(RBTree* tree, int data)
{
	RBTree* node = find(tree,data);
	if(!node)
		return NULL;
	if(node->left)
		return findmax(node->left);
	RBTree* ancestor = node->father;
	while(ancestor && node == ancestor->left)
	{
		node = ancestor;
		ancestor = ancestor->father;
	}
}

/*Altura del arbo*/
int height(RBTree* tree)
{
	return 0;
}

/*Rotacion con hijo izquierdo*/
RBTree* srotationleft(RBTree* tree)
{
	RBTree* rotate = tree->left;
	tree->left = rotate->right;
	rotate->right = tree;
	return rotate;
}

/*Rotacion con hijo derecho*/
RBTree* srotationright(RBTree* tree)
{
	RBTree* rotate = tree->right;
	tree->right = rotate->left;
	rotate->left = tree;
	return rotate;
}
/*Balanceamos el arbol con el nuevo nodo agregado*/
void rb_balance(RBTree* newtree)
{
	while(newtree->father && newtree->father->color == RED)
	{
		RBTree* grandfa = newtree->father->father;
		if(newtree->father == grandfa->left)//left
		{
			RBTree* uncle = grandfa->right;
			if(uncle->color == RED) //caso 1
			{
				newtree->father->color = uncle->color = BLACK;
				grandfa->color  = RED;
				newtree = grandfa;
			}
			else if (newtree == newtree->father->right) //caso 2
				newtree = srotationright(newtree->father); // para ponerlo en el caso 3
			
			newtree->father->color = BLACK; //caso 3
			newtree->father->father->color = RED;
		}
		else
		{
			RBTree* uncle = grandfa->right;
			if(uncle->color == RED)
			{
				newtree->father->color = uncle->color = BLACK;
				grandfa->color = RED;
				newtree = grandfa;
			}
			else if (newtree == newtree->father->left)
				newtree = srotationleft(newtree->father);
			newtree->father->color = BLACK;
			newtree->father->father->color = RED;
		}
	}
}

/*Inserta un nuevo elemento al arbol*/
RBTree* rb_insert(RBTree* tree, int data)
{
	RBTree* newtree = newRB(data);
	if(!tree){
		tree = newtree;
		tree->color = BLACK;
	}
	else
	{
		while(tree)
		{
			if(data < tree->element)
				tree = tree->left;
			else if(data > tree->element)
				tree = tree->right;
			else
				return tree; //ya esta el elemento
		}
		newtree->father = tree;
		if(data < tree->element)
			tree->left = newtree;
		else
			tree->right = newtree;
	}
	rb_balance(newtree);
	tree->color = BLACK;
	return tree;
}

void rb_change(RBTree* tree, RBTree* tree2)
{
	if(!tree->father)//tree es raiz
	{ 
		free(tree);	
		tree = tree2;
	}
	else if (tree == tree->father->left)
		tree->father->left = tree2;
	else
		tree->father->right = tree2;
	tree2->father = tree->father;
	tree2->left = tree->left;
	tree2->right = tree->right;
	tree2->color = tree->color;
	free(tree);
	tree = tree2;
}
void rb_delete_fix(RBTree* tree, RBTree* to_fix)
{
	while(to_fix != tree && to_fix->color == BLACK) //mientras no sea la raiz y el color sea negro
	{
		if(to_fix == to_fix->father->left) //si es hijo izquierdo
		{
			RBTree* bro = to_fix->father->right; //su hermano
			if(bro->color == RED)
			{
				bro->color = BLACK;
				to_fix->father->color = RED;
				to_fix->father = srotationright(to_fix->father); //ahora el padre sera el hermano
				bro = to_fix->father->right; //el padre anterior es el nuevo hermano
			}
			if(bro->left->color == BLACK && bro->right->color == BLACK) //los sobrinos
			{
				bro->color = RED; 
				to_fix = to_fix->father;//nos pasamos a arreglar al padre
			}
			else if (bro->right->color == BLACK)
			{
				bro->left->color = BLACK;
				bro->color = RED;
				bro = srotationleft(bro); //el hermano es el sobrino izquierdo
				bro = to_fix->father->right; //el sobrino izquierdo es el nuevo hermano
			}
			bro->color = to_fix->father->color; //le asignamos el color del padre
			to_fix->father->color = BLACK; // el padre lo ponemos en negro
			bro->right->color = BLACK; //sobrino izquierdo igual
			to_fix->father = srotationright(to_fix->father); // el padre ahora es el que estabamos arreglando
			to_fix = tree; //terminamos de arreglar
		}
		else //lo mismo pero con right
		{
			RBTree* bro = to_fix->father->left;
			if(bro->color == RED)
			{
				bro->color = BLACK;
				to_fix->father->color = RED;
				to_fix->father = srotationleft(to_fix->father);
				bro = to_fix->father->left;
			}
			if(bro->right->color == BLACK && bro->left->color == BLACK)
			{
				bro->color = RED;
				to_fix = to_fix->father;
			}
			else if(bro->left->color == BLACK)
			{
				bro->right->color = BLACK;
				bro->color = RED;
				bro = srotationright(bro);
				bro = to_fix->father->left;
			}
			bro->color = to_fix->father->color;
			to_fix->father->color = BLACK;
			bro->left->color = BLACK;
			to_fix->father = srotationleft(to_fix->father);
			to_fix = tree;
		}
	}
	to_fix->color = BLACK;
}
/*Borra un elemento del arbol */
RBTree* rb_delete(RBTree* tree, int data)
{
	if(!tree) // el arbol esta vacio
		return NULL;

	RBTree* to_remove = find(tree,data);
	if(!to_remove) //no se encontro el elemento.
		return NULL;

	if(!to_remove->left && !to_remove->right)//es hoja
	{
		if(to_remove == to_remove->father->right)
			to_remove->father->right = NULL;
		else
			to_remove->father->left = NULL;
		free(to_remove);
		return tree;
	}

	int original_color = to_remove->color;
	RBTree* aux;

	if(!to_remove->left) //solo tiene el hijo derecho
	{
		aux = to_remove->right;
		rb_change(to_remove,to_remove->right);
	}
	else if (!to_remove->right) //solo tiene el hijo izquierdo
	{
		aux = to_remove->left;
		rb_change(to_remove,to_remove->left);
	}
	else //tiene dos hijos
	{
		RBTree* aux2 = findmin(to_remove->right); //agarramos el minimo de su subarbol derecho para el intercambio
		original_color = aux2->color; //salvamos el color de aux2
		aux = aux2->right; //salvamos el derecho de aux2
		if(aux2->father == to_remove)
			aux->father = aux2;
		else
		{
			rb_change(aux2,aux2->right); //intercambiamos aux2 por su derecho
			aux2->right = to_remove->right;//el nuevo derecho sera el derecho del que se eliminara
			aux2->right->father = aux2; //le asiganmos el padre al nuevo derecho
		}
		rb_change(to_remove,aux2); //eliminamos to_remove y intercambiamos por aux2
	}
	if(original_color == BLACK) //si el color original es negro
		rb_delete_fix(tree, aux); //arreglamos las violaciones causadas
	return tree;
}


int getElement(RBTree* tree)
{
	return tree->element;
}

RBTree* getParent(RBTree* tree1, RBTree* tree2)
{
	while(tree1){
		tree1->coloration = 1;
		tree1 = tree1->father;
	}
	while(tree2) {
	    if(tree2->coloration == 1)
	    	return tree2;
	    tree2 = tree2->father;
	}
}