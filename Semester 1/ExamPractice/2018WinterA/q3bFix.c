#include<stdio.h>
#include<stdlib.h>
void checkMat(int** mat, int a, int b);
void makeItOne(int** mat, int row, int col);
#define N 3
#define M 4
void main()
{
	int a[M][N] = { {0,1,0},{0,0,0},{0,0,0},{0,1,1} };
	int* m[M] = { a[0],a[1],a[2],a[3] };
	checkMat(m, M, N);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d, ", a[i][j]);
		printf("\n");
	}
}
void checkMat(int** mat, int a, int b)
{
	int i, j, rows[M]={0}, cols[N]={0};;
	for( i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(mat[i][j]==1)
				rows[i]=cols[j]=1;
	for( i=0; i<M; i++)
		if(rows[i])
			for(j=0; j<N; j++)
				mat[i][j]=1;

	for( j=0; j<N; j++)
		if(cols[j])
			for(i=0; i<M; i++)
				mat[i][j]=1;		
		
}
