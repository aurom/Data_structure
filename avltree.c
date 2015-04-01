#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "avltree.h"

AvlTree* newAvl(void* data,int elementsize)
{
	AvlTree* newtree = (AvlTree*) malloc(sizeof(AvlTree));
	assert(newtree != NULL);
	newtree->element = malloc(elementsize);
	newtree->element = data;
	newtree->father = NULL;
	newtree->left = NULL;
	newtree->right = NULL;
	newtree->color = 0;
	newtree->height = 0;
	return newtree;
}
void makeEmpty(AvlTree* tree)
{
	if(tree)
	{
		makeEmpty(tree->left);
		makeEmpty(tree->right);
		free(tree);
	}
	return;
}

AvlTree* find(AvlTree* tree ,void* data,compare comp)
{
	if(!tree)
	{
		puts("Empty tree");
		return NULL;
	}
	if(comp(data,tree->element) < 0)
		find(tree->left,data,comp);
	else if (comp(data,tree->element) > 0)
		find(tree->right,data,comp);
	else
		return tree;
}

AvlTree* findmin(AvlTree* tree)
{
	if(!tree->left)
		return tree;
	else return findmin(tree->left);
}
AvlTree* findmax(AvlTree* tree)
{
	if(!tree->right)
		return tree;
	else return findmax(tree->right);
}

int height(AvlTree* tree)
{
	if(!tree)
		return -1;
	else
		return tree->height;
}
int max(int a, int b)
{
	return a > b ? a: b;
}

AvlTree* srotationleft(AvlTree* tree)
{
	AvlTree* balance = tree->left;
	tree->left = balance->right;
	balance->right = tree;
	tree->height = max(height(tree->left),height(tree->right)) +1;
	balance->height = max(height(balance->left),tree->height) + 1;
	tree = balance;
	return tree;
}

AvlTree* srotationright(AvlTree* tree)
{
	AvlTree* balance = tree->right;
	tree->right = balance->left;
	balance->left = tree;
	tree->height = max(height(tree->left),height(tree->right)) + 1;
	balance->height = max(tree->height,height(balance->right)) +1;
	tree = balance;
	return tree;
}

AvlTree* drotationleft(AvlTree* tree)
{
	tree->left = srotationright(tree->left);
	return srotationleft(tree);
}

AvlTree* drotationright(AvlTree* tree)
{
	tree->right = srotationleft(tree->right);
	return srotationright(tree);
}

AvlTree* balance(AvlTree* tree)
{
	if(height(tree->left) - height(tree->right) > 1)
	{
		if(height(tree->left->left) >= height(tree->left->right))
			tree = srotationleft(tree);
		else
			tree = drotationleft(tree);
	}
	else if (height(tree->right) - height(tree->left) > 1)
	{
		if(height(tree->right->right) >= height(tree->right->left))
			tree = srotationright(tree);
		else
			tree = drotationright(tree);
	}
	else
		;
	tree->height = max(height(tree->left),height(tree->right)) + 1;
	return tree;
}

AvlTree* avl_insert(AvlTree* tree, void* data, int elementsize, compare comp)
{
	if(!tree)
	{
		tree =  newAvl(data,elementsize);
	}
	else
	{
		if(comp(data,tree->element) < 0){
			tree->left = avl_insert(tree->left,data,elementsize,comp);
			tree->left->father = tree;
		}
		else if (comp(data,tree->element) > 0){
			tree->right = avl_insert(tree->right,data,elementsize,comp); 
			tree->right->father = tree;
		}
		else
			;
	}
	tree = balance(tree);
	return tree;
}

AvlTree* avl_delete(AvlTree* tree,void* data, compare comp)
{
	if(!tree)
	{
		puts("Empty tree.");
		return NULL;
	}
	
	if(comp(data,tree->element) < 0)
		tree->left = avl_delete(tree->left,data,comp);
	else if (comp(data,tree->element) > 0)
		tree->right = avl_delete(tree->right,data,comp);
	else
	{
		if(tree->left && tree->right)
		{
			AvlTree* temp = findmin(tree->right);
			tree->element = temp->element;
			tree->right = avl_delete(tree->right,temp->element,comp);
			free (temp);
		}
		else
			tree = tree->left? tree->left: tree->right;
	}
	return tree;
}

void* getElement(AvlTree* tree)
{
	return tree->element;
}
void printTree(AvlTree* tree, int level,printData print)
{
	int i;
	if(!tree){
		printf("\n");
		return;
	}
	else
	{
		printTree(tree->right,level+1,print);
		for(i = 0; i < level;i++)
		{
			putchar('\t');
		}
		print(tree->element);
		printTree(tree->left,level+1,print);
	}
}

void printAVL(AvlTree* tree, printData print)
{
	printTree(tree,0,print);

}

AvlTree* getParent(AvlTree* tree1, AvlTree* tree2)
{
	while(tree1)
	{
		tree1->color = 1;
		tree1 = tree1->father;
	}
	while(tree2)
	{
		if(tree2->color == 1)
		{
			return tree2;
		}
		tree2 = tree2->father;
	}
}