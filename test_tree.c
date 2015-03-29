#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "avltree.h"

int compareChar(void* a, void* b)
{
	char ch1 = *((char*)a);
	char ch2 = *((char*)b);
	return ch1 - ch2;
}
int compareInt(void* a,void* b)
{
	int num1 = *((int*)a);
	int num2 = *((int*)b);
 	return num1 - num2;

}
/*sint compareString(char* a, char* b)
{
	if()
}*/
int main()
{
	int arr[] = {-4,-3,-2,0,1,20,50,-7,-11,11};
	char arr2[] = {'a','p','e','r','r','o','i','t','o','o','t','r','o'};
	AvlTree* tree_int = NULL;
	AvlTree* tree_char = NULL;
	int i;
	for(i = 0; i < 10; i++)
	{
		tree_int = insert(tree_int,(void*)arr[i], compareInt);
	}
	for(i = 0; i <13; i++)
		tree_char = insert(tree_char,(void*)arr2[i], compareChar);
	printTree(tree_int);
	printf("\n");
	printTree(tree_char);
	printf("\n");
	printf("%d\n",height(tree_int));
	tree_int = delTree(tree_int,-4,compareInt);
	printf("\n");
	printTree(tree_int);
	printf("\n");
	printf("%d\n",height(tree_int));
	makeEmpty(tree_int);
	return 0;
}

//-Wall -lm -g