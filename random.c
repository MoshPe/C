#include <stdio.h>
#include<stdlib.h>
#include<windows.h>

int* allocateNewProduct()
{
	return (int*)malloc(sizeof(int));
}

void main()
{
	int x = 5;
	int* y;
	y = allocateNewProduct();
	*y = 24;
	// y=&x;
	// *y= *y +5;
	printf("%d %p \n",*y,y);
	printf("%d %p",x,&x);

}