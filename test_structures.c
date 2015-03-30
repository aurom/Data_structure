#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

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
	printf("%s",string);
}

void testList(int * int_array, char* char_array, char* string_array[], int n)
{
	List* lista_int = newList(sizeof(int),print_int,compare_int);
	List* lista_ch = newList(sizeof(char),print_char,compare_char);
	List* lista_string = newList(sizeof(char*),print_string,compare_string);
	int i;
	for(i = 0; i < n; i++)
	{
		insert(lista_int,&int_array[i]);
		insert(lista_ch, &char_array[i]);
		insert(lista_string, &string_array[i]);
	}
	print_list(lista_int);
	printf("\n\n");
	print_list(lista_ch);
	printf("\n\n");
	print_list(lista_string);
	printf("\n");
}


int main()
{
	int size = 5;
	int arrint[] = {-1,3,4,-6,-9};
	char arrchar[] = {'p','e','r','r','o'};
	char* arrstring[5] = {"hola","halo","niño","vaca","peso"};
	int i;
	for(i = 0; i < 5; i++)
	{
		printf("%s\n",arrstring[i]);
	}
	testList(arrint,arrchar,arrstring,size);
	return 0;
}
//-Wall -lm -g