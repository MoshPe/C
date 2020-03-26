#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
int factorial(int n);
int is_in_row(int** mat, int n, int i, int j);
//int is_in_col(int** mat, int n);
void freeMatrix(int **m,int size);
void checkAllocation(int *mat);
void main()
{
	int c, i, j;
	int** t;
	printf("Enter n please:\n ");
	scanf("%d", &c);
	t = (int**)malloc(c * sizeof(int*));
	if (t==0)
	{
		printf("Memory allocation error.\n");
		exit(1);
	}
	for (i = 0; i < c; i++)
	{
		t[i] = (int*)malloc(c * sizeof(int));
		checkAllocation(t[i]);
	}
		
	do
	{
		printf("Enter %dx%d matrix elements, please: \n", c, c);
		for (i = 0; i < c; i++)
		{
			for (j = 0; j < c; j++)
				scanf("%d", &t[i][j]);
		}
		printf("Matrix\n");
		for (i = 0; i < c; i++)
		{
			for (j = 0; j < c; j++)
				printf("%5d ", t[i][j]);
			puts("\n");
		}
		if (is_in_row(t, c,i,j) == 1 && is_in_row(t, c,j,i) == 1)
			printf("is perfect");
		else
			printf("isn't perfect");
		printf("\nEnter n please:\n ");
		scanf("%d", &c);
		t = (int**)realloc(NULL,(c * sizeof(int*)));
		if (t==0)
		{
		printf("Memory allocation error.\n");
		exit(1);
		}
		for (i = 0; i < c; i++)
		{
			t[i] = (int*)realloc(NULL,(c * sizeof(int)));
			checkAllocation(t[i]);
		}
	} while (c != 0);
	printf("Thank you for exploring perfect matrices.");
	freeMatrix(t,c);
}


int is_in_row(int** mat, int n, int i, int j)
{
	int sum = 1,num;
	num =factorial(n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (mat[i][j] <= n)
				sum = sum * mat[i][j];
			else
				return 0;
		}
		if (sum != num)
			return 0;
		sum = 1;
	}  
	return 1;
}
int factorial(int n)
{
	if (n == 1)
		return 1;
	else
		return n * factorial(n - 1);
}
void freeMatrix(int **m,int size)
{
	int i;
	for (i = 0; i < size; i++)
		free(m[i]);
	free(m);
}
void checkAllocation(int *mat)
{
	if (mat==0)
	{
		printf("Memory allocation error.\n");
		exit(1);
	}
}