#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avltree.h"

AvlTree* newAvl(int elementsize, printData print, compare comp){
	AvlTree* tree = (AvlTree*) malloc(sizeof(AvlTree));
	assert(tree != NULL);
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->element = malloc(elementsize);
	tree->print = print;
	tree->comp = comp;
	tree->e_size = elementsize;
	tree->color = 0;
	tree->height = 0;
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
	if(tree->comp(data,tree->element) < 0)
		return find(tree->left,data);
	if(tree->comp(data,tree->element) > 0)
		return find(tree->right,data);
	else
		return tree;
}

AvlTree* findmin(AvlTree* tree){
	if(tree->left == NULL)
		return tree;
	return findmin(tree->left);
}

AvlTree* findmax(AvlTree* tree)
{
	if(tree->right == NULL)
		return tree;
	return findmax(tree->right);
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
	return a > b ? a : b;
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
		if(height(tree->left->left) >= height(tree->left->right))
			tree = srotationleft(tree);
		else
			tree = drotationleft(tree);
	}
	else if(height(tree->right)-height(tree->left) > 1){ //si esta desbalanceado por la derecha
			if(height(tree->right->right) >= height(tree->right->left))
				tree = srotationright(tree);
			else
				tree = drotationright(tree);
	}
	else
		;
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

void avl_insert(AvlTree* tree, void* data, printData print, compare comp)
{
	if(!tree->parent)//first avl_insertion.
	{
		tree = newAvl(sizeof(data),print,comp);
		return;
	}		
	if(!tree)
		tree = newAvl(sizeof(data),print,comp);
	if(tree->comp(data,tree->element) < 0 ){
		avl_insert(tree->left,data,print,comp);
		tree->left->parent = tree;
	}
	else if(tree->comp(data,tree->element) > 0){
		avl_insert(tree->right,data,print, comp);
		tree->right->parent = tree;
	}
	else
		return;
	balance(tree);

}

void avl_delete(AvlTree* tree ,void* data)
{
	if(!tree){
		puts("Empty tree.");
		return;
	}
	if(tree->comp(data, tree->element))
		avl_delete(tree->left, data);
	else if(tree->comp(data,tree->element))
		avl_delete(tree->right, data);
	else if(tree->left && tree->right)
	{
		tree->element = findmin(tree->right)->element;
		avl_delete(tree->right, tree->element);
	}
	else
	{
		AvlTree* tmp = tree;
		tree = (tree->left != NULL) ? tree->left: tree->right;
		free(tmp);
	}
	balance(tree);
}
void* getElement(AvlTree* tree )
{
	return tree->element;
}

void printTree(AvlTree* tree, int level)
{
	int i;
	if(!tree){
		printf("None\n");
		return;
	}
	else
	{
		printTree(tree->left,level+1);
		for(i = 0; i < level;i++)
		{
			putchar('\t');
		}
		tree->print(tree->element);
		printf("\n");
		printTree(tree->right,level+1);
	}
}

void printAVL(AvlTree* tree)
{
	printTree(tree,0);
}

AvlTree* getParent(AvlTree* tree1, AvlTree* tree2)
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