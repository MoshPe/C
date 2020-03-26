#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
void main()
{
	srand(time(NULL));
	int r, c, i, j;
	int** t;
	printf("Enter Rows and Columns of the Matrix: ");
	scanf("%d%d",&r,&c);
	t = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		t[i] = (int*)malloc(c*sizeof(int));
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
			t[i][j] = rand()%10;
	}
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
			printf("%d ",t[i][j]);
		puts("\n");
	}
	for (i = 0; i < r; i++)
		free(t[i]);
	free(t);
}