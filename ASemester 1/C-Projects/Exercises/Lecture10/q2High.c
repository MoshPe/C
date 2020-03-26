#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define M 5
#define shiftNum 3
void shift(int ar[][M],int n,int m);
void main()
{
    int mat[N][M]={{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
    int i,j,k;
    //printf("Enter Mat: ");
    /*for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			scanf("%d",&mat[i][j]);
    }*/
    for (k = 0; k < shiftNum; k++)
    {
        printf("shift %d:\n",k+1);
        shift(mat,N,M);
     for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			printf("%7d", mat[i][j]);
		printf("\n");
	}
    }
}
void shift(int ar[][M],int n,int m)
{
   int i,j,temp;
   temp = ar[n - 1][m - 1];
   for (i = n-1; i >=0 ; i++)
   {
       for (j = m-1; j >=0; j++)
       {
           
       }
       
   }
   
}