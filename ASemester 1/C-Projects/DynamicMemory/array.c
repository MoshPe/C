#include<stdio.h>
#define N 4
void main()
{
    int i,j;
    int a[N][N]={0};
    for (i = 0; i < N; i++)
    {
    for (j = 0; j < N; j++)
        a[i][j]=((i==j)||(i+j==N-1))?8:0;
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d  ",a[i][j]);
        }
        puts("\n");
    }
}