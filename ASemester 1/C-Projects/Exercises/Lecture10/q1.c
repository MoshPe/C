#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5
#define M 5
int rowEqualRow(int ar[][N],int row, int n);
int mainsland(int ar[][N],int row, int n);
void main()
{
    int ar[M][N] = {0};
    int i,j,flag=1,flag1;
    printf("Please enter 5x5 matrix elements:\n");
    for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
			scanf("%d",&ar[i][j]);
    }
    for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
			printf("%7d", ar[i][j]);
		printf("\n");
	}
     for (i = 0; ((i < M&&flag==1)); i++)
        flag=rowEqualRow(ar,i,N);
    if (flag==0)
        {
            printf("isn't OK");
            exit(1);
        }
    else
    {
    flag1=mainsland(ar,M,N); 
    printf("is%s OK",(flag1==1)?"":"n't");
    }
}
int rowEqualRow(int ar[][N],int row, int n)
{
    int i,sum=0;
    for (i = 0; i < n; i++)
        sum+=ar[row][i];
    return(sum==row?1:0);
}
int mainsland(int ar[][N],int row, int n)
{
    int i,flag=1;
    for (i = 0; i < n&&flag==1; i++)
    {
        if(ar[i][i]<0)
        flag=0;
    }
    return(flag==1?1:0);
}