#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void matbuild(int **mat,int r,int c);
void sum(int **mat,int **mat1,int **mat2,int r,int c);
void main()
{
    int **mat1;
    int **mat2;
    int **mat3;
    int r,c;
    printf("Enter Rows and Columns of the Matrix: ");
	scanf("%d%d",&r,&c);
	matbuild(mat1,r,c);
    matbuild(mat2,r,c);
    matbuild(mat1,r,c);
    sum(mat1,mat2,mat3,r,c);


	/*for (i = 0; i < r; i++)
		free(mat[i]);
	free(mat);*/
}
void matbuild(int **mat,int r,int c)
{
    int i;
    mat = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		mat[i] = (int*)malloc(c*sizeof(int));
}
void sum(int **mat,int **mat1,int **mat2,int r, int c)
{
    int i,j;
    for (i = 0; i < r; i++)
    {
        for (i = j; j < c; j++)
            mat2[i][j]=mat[i][j] + mat1[i][j];
    }
}