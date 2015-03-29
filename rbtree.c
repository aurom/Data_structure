#include "rbtree.h"
#define FALSE 0
#define True 1


RBTree* newRB(int data){
	RBTree* tree = (RBTree*) malloc(sizeof(RBTree));
	assert(tree != NULL);
	tree->element = data;
	tree->color = BLACK;
	tree->father = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->height = 0;
	tree->coloration = 0;
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


int is_red(RBTree* tree)
{
	if(!tree)
		return FALSE;
	else
		return tree->color == RED;
}

RBTree* srotationleft(RBTree* tree)
{
	RBTree* balanceado = tree->left;
	tree->left = balanceado->right;
	balanceado->right = tree;
	tree->color = RED;
	balanceado->color = BLACK;
	return balanceado;
}

RBTree* srotationright(RBTree* tree)
{
	RBTree* balanceado = tree->right;
	tree->right = balanceado->left;
	balanceado->left = tree;
	tree->color = RED;
	balanceado->color = BLACK;
	return balanceado;
}

RBTree* drotationleft(RBTree* tree)
{
	tree->left = srotationright(tree->left);
	return srotationleft(tree);
}

RBTree* drotationright(RBTree* tree)
{
	tree->right = srotationleft(tree->right);
	return srotationright(tree);
}

RBTree* balance(RBTree* tree)
{
	if(!tree->father || !tree->father->father)
		return tree;

	while(tree->father->color == RED)
	{
		RBTree* grandfa = tree->father->father;
		if(tree->father == grandfa->left)
		{
			RBTree* uncle = grandfa->right;
			if(uncle->color == RED)
			{
				uncle->color = tree->father->color = BLACK;
				grandfa->color = RED;
				tree = grandfa;
			}
			else if(tree == tree->father->right)
			{
				tree = tree->father
				tree = srotationright(tree);
			}
		}
	}
}



int height(RBTree* tree)
{
	if(!tree)
		return -1;
	return tree->height;	
}



int afirm(RBTree* tree )
{
	if(!tree)
		return TRUE;

	if(is_red(tree))
	{
		if(is_red(tree->left) || is_red(tree->right))
		{
			puts("Red violation");
			return FALSE;
		}
	}
	afirm(tree->left);
	afirm(tree->right);

}

RBTree* rbinsert(RBTree* tree, int data)
{
	RBTree* newtree = newRB(data);
	if(!tree)
		tree = newtree;
	else
	{
		while (tree)
		{
			if(data < tree->element)
				tree = tree->left;
			else if(data > tree->element)
				tree = tree->right;
			else
				return tree;
		}
		newtree->father = tree;
		if(data < tree->element)
			tree->left = newtree;
		else if (data > tree->element)
			tree->right = newtree;
	}
	return balance(tree);
}