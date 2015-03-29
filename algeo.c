#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct punto
{
	int x;
	int y;
}punto;

punto* newPunto(int a, int b)
{
	punto* p = (punto*) malloc(sizeof(punto));
	p->x = a;
	p->y = b;
}
int distancia(punto* a, punto* b)
{
	return sqrt()
}


int main(int argc, char const *argv[])
{
	punto con[100000000];

	return 0;
}