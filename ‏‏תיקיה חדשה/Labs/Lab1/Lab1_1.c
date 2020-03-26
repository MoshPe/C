#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define SIZE 10

void main()
{
	int i, Arr[SIZE] = { 3,5,10,1,2,7,6,9,0,8 };
	int** Parr;
	Parr = (int**)malloc(SIZE * sizeof(int*));
	assert(Parr);
	for (i = 0; i < SIZE; i++)
		Parr[i] = Arr+i;
	printf("My Array is: ");
	for (i = SIZE-1; i >= 0; i--)
		printf("%d, ", *Parr[i]);
	free(Parr);
}

