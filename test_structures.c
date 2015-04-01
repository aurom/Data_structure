#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "list.h"
#include "queue.h"
#include "avltree.h"
#include "rbtree.h"




typedef enum
{
		list,
		stack,
		queue,
		avltree,
		rbtree
}Data;

int compare_int(void* a, void* b)
{
	int num1 = *(int*)a;
	int num2 = *(int*)b;
	return num1 - num2;
}

int compare_char(void* a, void* b)
{
	char ch1 = *(char*)a;
	char ch2 = *(char*)b;
	return (int)ch1 - ch2;
}

int compare_double(void*a, void* b)
{
	double d1 = *((double *) a);
	double d2 = *((double*) a);
	return d1 - d2;
}
int compare_string(void* a,void*b)
{
	char * s1 = (char*)a;
	char * s2 = (char*)b; 
	return strcmp(s1,s2);
}

void print_int(void* num)
{
	int n = *((int*)num);
	printf("%d",n);
}

void print_char(void* ch)
{

	printf("%c",(*(char*)ch));
}

void print_string(void* str)
{
	char *string = (char*)str;
	int i = 0;
	while(*(string+i) != '\0'){
		printf("%c",*(string+i));
		i++;
	}
}

void testList()
{
	int size = 5;
	int int_array[] = {-1,3,4,-6,-9};
	char char_array[] = {'p','e','r','r','o'};
	char* string_array[5] = {"hola","halo","niño","vaca","peso"};
	printf("List testing ....\n\n");
	List* lista_int = newList(sizeof(int),print_int,compare_int);
	List* lista_ch = newList(sizeof(char),print_char,compare_char);
	List* lista_string = newList(sizeof(char*),print_string,compare_string);
	int i;
	for(i = 0; i < size; i++)
	{
		insert(lista_int,&int_array[i]);
		insert(lista_ch, &char_array[i]);
		insert(lista_string, string_array[i]);
	}
	printf("List with integers:\n");
	print_list(lista_int);
	int m = *((int*)list_max(lista_int));
	printf("The max element : %d\n",m );
	int mim = *((int*)minim(lista_int));
	printf("The minimun element : %d\n",mim);
	printf("The list inverse:\n");
	print_list(inverse(lista_int));
	printf("\n");
	printf("List with chars:\n");
	print_list(lista_ch);
	char macha = *((char*)list_max(lista_ch));
	printf("The max element : %c\n",macha );
	char mimch = *((char*)minim(lista_ch));
	printf("The minimun element : %c \n",mimch);
	printf("The list inverse:\n");
	print_list(inverse(lista_ch));
	printf("\n");
	printf("List with strings:\n");
	print_list(lista_string);
	char* smax = (char*)list_max(lista_string);
	printf("The max element : %s\n",smax);
	char* smin = (char*)minim(lista_string);
	printf("The minimun element : %s\n",smin);
	printf("The list inverse: \n");
	print_list(inverse(lista_string));
	list_destroy(lista_int);
	list_destroy(lista_ch);
	list_destroy(lista_string);
}

void testStack()
{
	int size = 5;
	int int_array[] = {-1,3,4,-6,-9};
	char char_array[] = {'p','e','r','r','o'};
	char* string_array[5] = {"hola","halo","niño","vaca","peso"};
	printf("Stack testing .... \n");
	Stack* stack_int = newStack(sizeof(int),print_int);
	Stack* stack_char = newStack(sizeof(char),print_char);
	Stack* stack_str = newStack(sizeof(char*),print_string);
	int i;
	for(i = 0; i < size; i++)
	{
		push(stack_int,&int_array[i]);
		push(stack_char, &char_array[i]);
		push(stack_str, string_array[i]);
	}
	printf("Stack with integers\n");
	printStack(stack_int);
	printf("\nStack with chars\n");
	printStack(stack_char);
	printf("\nStack with strings \n");
	printStack(stack_str);
	printf("\nRemove stacks..\n\n");
	for(i =0; i < size; i++)
	{
		int n = *((int*)pop(stack_int));
		char ch = *((char*)pop(stack_char));
		char* str = ((char*)pop(stack_str));
		printf("%d\n",n );
		printf("%c\n", ch);
		printf("%s\n",str);
	}
	printf("Ok..\n");
}

void testQueue()
{
	int size = 5;
	int int_array[] = {-1,3,4,-6,-9};
	char char_array[] = {'p','e','r','r','o'};
	char* string_array[5] = {"hola","halo","niño","vaca","peso"};
	Queue* qint = newQueue(sizeof(int),print_int);
	Queue* qchar = newQueue(sizeof(char),print_char);
	Queue* qstr = newQueue(sizeof(char*),print_string);
	int i;
	for(i = 0; i < size; i++)
	{
		enqueue(qint,&int_array[i]);
		enqueue(qchar,&char_array[i]);
		enqueue(qstr,string_array[i]);
	}
	printf("Queue with integers.\n");
	printQueue(qint);
	printf("This queue has %d elements.\n",q_length(qint));
	printf("\nQueue with chars. \n");
	printQueue(qchar);
	printf("This queue has %d elements.\n",q_length(qchar));
	printf("\nQueue with strings. \n");
	printf("This queue has %d elements.\n",q_length(qstr));
	printQueue(qstr);
	printf("\nDeleting queues....\n");
	for(i = 0; i < size; i++)
	{
		printf("%d\n",*((int*)dequeue(qint)));
		printf("%c\n",*((char*)dequeue(qchar)));
		printf("%s\n",((char*)dequeue(qstr)));
	}
	printf("ok!\n");
}

void testAVL()
{
	int size = 5;
	int int_array[] = {-1,3,4,-6,-9};
	char char_array[] = {'p','e','r','r','o'};
	char* string_array[5] = {"hola","halo","niño","vaca","peso"};
	AvlTree* avlint = NULL; //newAvl(sizeof(int),print_int,compare_int);
	AvlTree* avlchar = NULL; //newAvl(sizeof(char),print_char,compare_char);
	AvlTree* avlstr = NULL; //newAvl(sizeof(char*),print_string,compare_string);
	int i;
	for(i = 0; i < size; i++)
	{
		avlint = avl_insert(avlint,&int_array[i],sizeof(int),compare_int);
		avlchar = avl_insert(avlchar,&char_array[i],sizeof(char),compare_char);
		avlstr = avl_insert(avlstr,*(string_array+i),sizeof(char*),compare_string);
	}
	printf("AvlTree with integers.\n");
	printAVL(avlint,print_int);
	printf("\nThe max element: %d\n",*((int*)getElement(findmax(avlint))));
	printf("The minimun element: %d\n",*((int*)getElement(findmin(avlint))));
	printf("Height of tree: %d\n",height(avlint));
	printf("AvlTree with chars.\n");
	printAVL(avlchar,print_char);
	printf("\nThe max element: %c\n",*((char*)getElement(findmax(avlchar))));
	printf("The minimun element: %c\n",*((char*)getElement(findmin(avlchar))));
	printf("Height of tree: %d\n",height(avlchar));
	printf("AvlTree with strings.\n");
	printAVL(avlstr,print_string);
	printf("\nThe max element: %s\n",((char*)getElement(findmax(avlstr))));
	printf("The minimun element: %s\n",((char*)getElement(findmin(avlstr))));
	printf("Height of tree: %d\n",height(avlstr));
	printf("Deleting AvlTrees...\n");
	makeEmpty(avlint);
	makeEmpty(avlchar);
	makeEmpty(avlstr);
	printf("ok!\n");
}

void testRB()
{
	int size = 5;
	int int_array[] = {-1,3,4,-6,-9};
	char char_array[] = {'p','e','r','r','o'};
	char* string_array[5] = {"hola","halo","niño","vaca","peso"};
	RBTree* rbint = newRB(sizeof(int),print_int,compare_int);
	RBTree* rbchar =newRB(sizeof(char),print_char,compare_char);
	RBTree* rbstr = newRB(sizeof(char*),print_string,compare_string);
	int i;
	for(i = 0; i < size; i++)
	{
		rb_insert(rbint,&int_array[i],sizeof(int),rbint->print,rbint->comp);
		rb_insert(rbchar,&char_array[i],sizeof(char),rbchar->print,rbchar->comp);
		rb_insert(rbstr,string_array[i],sizeof(char*),rbstr->print,rbstr->comp);
	}

	printf("RBTree with integers.\n");
	print_rb(rbint);
	printf("\nThe max element: %d\n",*((int*)get_element(find_max(rbint))));
	printf("The minimun element: %d\n",*((int*)get_element(find_min(rbint))));
	printf("Height of tree: %d\n",rb_height(rbint));
	printf("RBTree with chars.\n");
	print_rb(rbchar);
	printf("\nThe max element: %c\n",*((char*)get_element(find_max(rbchar))));
	printf("The minimun element: %c\n",*((char*)get_element(find_min(rbchar))));
	printf("Height of tree: %d\n",rb_height(rbchar));
	printf("RBTree with strings.\n");
	print_rb(rbstr);
	printf("\nThe max element: %s\n",((char*)get_element(find_max(rbstr))));
	printf("The minimun element: %s\n",((char*)get_element(find_min(rbstr))));
	printf("Height of tree: %d\n",rb_height(rbstr));
	printf("Deleting AvlTrees...\n");
	make_empty(rbint);
	make_empty(rbchar);
	make_empty(rbstr);
	printf("ok!\n");	
}
void tester(int select)
{
	switch(select)
	{
		case 1:
			testList();
			break;
		case 2:
			testStack();
			break;
		case 3:
			testQueue();
			break;
		case 4:
			testAVL();
			break;
		case 5:
			testRB();
			break;
		case 0:
			break;
	}
}
int main()
{
	int select;
	int status;
	printf("This is a tester, please select your data structure: \n");
	printf("1) Double Linked List. \n");
	printf("2) Stack.\n");
	printf("3) Queue.\n");
	printf("4) AVL Tree.\n");
	printf("5) Red Black Tree.\n");
	printf("0) Exit \n");
	status = scanf("%d", &select);
	tester(select);
	return 0;
}
//-Wall -lm -g