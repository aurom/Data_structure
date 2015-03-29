#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avltree.h"

AvlTree* newAvl(void* data){
	AvlTree* tree = (AvlTree*) malloc(sizeof(AvlTree));
	assert(tree != NULL);
	tree->height = 0;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->element = data;
	tree->color = 0;
}

void makeEmpty(AvlTree* tree){
	if(tree)
	{
		makeEmpty(tree->left);
		makeEmpty(tree->right);
		free(tree);
	}
	return;
}

AvlTree* find(AvlTree* tree,void* data){
	if(tree == NULL)
		return NULL;
	if(data < tree->element)
		return find(tree->left,data);
	if(data > tree->element)
		return find(tree->right,data);
	else
		return tree;
}

AvlTree* findmin(AvlTree* tree){
	if(tree == NULL)
		return NULL;
	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}

AvlTree* findmax(AvlTree* tree)
{
	if(tree == NULL)
		return NULL;
	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

int height(AvlTree* tree)
{
	if(tree == NULL)
		return -1;
	else
		return tree->height;
}

int max(int a, int b)
{
	return a>b? a: b;
}

/*Rotacion con el hijo izquierdo */
AvlTree* srotationleft(AvlTree* tree)
{
	AvlTree* tree_balanceado = tree->left; //guardas el arbol izquierdo
	tree->left = tree_balanceado->right; //asignas el arbol derecho de tu arbol izquierdo como tu nuevo arbol izquierdo
	tree_balanceado->right = tree;// el arbol derecho de tu arbol izquierdo ahora es el arbol pasado
	tree->height = max(height(tree->left),height(tree->right)) + 1;
	tree_balanceado->height = max(height(tree_balanceado->left), tree->height) + 1;
	return tree_balanceado; //regresas el arbol balanceado
}
/*Rotacion con el hijo derecho */
AvlTree* srotationright(AvlTree* tree)
{
	AvlTree* tree_balanceado = tree->right; //guardas el arbol derecho
	tree->right = tree_balanceado->left; //el arbol derecho ahora es el arbol izquierdo del arbol derecho
	tree_balanceado->left = tree;//tu arbol ahora es el arbol izquierdo
	tree->height = max(height(tree->left),height(tree->right)) + 1;
	tree_balanceado->height = max(height(tree_balanceado->right), tree->height) + 1;
	return tree_balanceado; //regresas el arbol balanceado
}

/*Doble rotacion con el hijo izquierdo*/
AvlTree* drotationleft(AvlTree* tree)
{
	tree->left = srotationright(tree->left); //equilibras tu arbol izquierdo
	return srotationleft(tree);//equilibras el arbol
}

/*Doble rotacion con el hijo derecho */
AvlTree* drotationright(AvlTree* tree)
{
	tree->right = srotationleft(tree->right); //Equilibras tu arbol derecho
	return srotationright(tree); //equilibras el arbol
}

AvlTree* balance(AvlTree* tree)
{
	if(tree == NULL)
		return NULL;
	if(height(tree->left) - height(tree->right) > 1){//si esta desbalanceado por la izquierda
		if(height(tree->left->left) >= height(tree->left->right)) //el arbol izquierdo es el desbalanceado
			tree = srotationleft(tree); //rotacion simple al arbol izquierdo 
		else
			tree = drotationleft(tree);//los dos estan en desbalance
	}
	else if(height(tree->right)-height(tree->left) > 1){ //si esta desbalanceado por la derecha
			if(height(tree->right->right) >= height(tree->right->left)) //el arbol derecho es el desbalanceado
				tree = srotationright(tree);
			else
				tree = drotationright(tree); //los dos estan en desbalance
	}
	else
		;
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

AvlTree* insert(AvlTree* tree, void* data, compare comparador)
{		
	if(!tree)
		tree = newAvl(data);
	if(comparador(data,tree->element) < 0 ){
		tree->left = insert(tree->left,data, comparador);
		tree->left->parent = tree;
	}
	else if(comparador(data,tree->element) > 0){
		tree->right = insert(tree->right,data, comparador);
		tree->right->parent = tree;
	}
	else
		;
	return balance(tree); //balanceas el arbol despues de agregar.

}
AvlTree* delTree(AvlTree* tree ,void* data , compare comparador)
{
	if(!tree)
		return NULL;
	if(comparador(data, tree->element))
		tree->left = delTree(tree->left, data, comparador);
	else if(comparador(data,tree->element))
		tree->right = delTree(tree->right, data, comparador);
	else if(tree->left && tree->right)
	{
		tree->element = findmin(tree->right)->element;
		tree->right = delTree(tree->right, tree->element, comparador);
	}
	else
	{
		AvlTree* tmp = tree;
		tree = (tree->left != NULL) ? tree->left: tree->right;
		free(tmp);
	}
	return balance(tree); //balanceas el arbol despues de eliminar.
}
void* getElement(AvlTree* tree )
{
	return tree->element;
}

void printTree(AvlTree* tree)
{
	if(!tree)
		printf("None\n");
	printf("%d\n",tree->element);
	if(tree->left){
		printf("\t");
		printTree(tree->left);
	}
	if(tree->right){
		//printf("\t");
		printTree(tree->right);
	}
}
AvlTree* getPariente(AvlTree* tree1, AvlTree* tree2)
{
	while(tree1)
	{
		tree1->color = 1;
		tree1 = tree1->parent;
	}
	while(tree2)
	{
		if(tree2->color == 1)
		{
			return tree2;
		}
		tree2 = tree2->parent;
	}
}