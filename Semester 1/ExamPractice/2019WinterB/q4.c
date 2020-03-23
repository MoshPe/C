#include<stdio.h>
#include<stdlib.h>
int is_ranked (int **m, int rows, int cols);
void main()
{
    int m[2][2]={{9,4},{5,3}};
    int *mat[2]={m[0],m[1]};
    printf("%d",is_ranked (mat, 2, 2));

}
int is_ranked (int **m, int rows, int cols)
{
    int i,j,sum=1;
    for (i = 0; i < rows-1; i++)
    {
        for (j = 0; j < cols-1; j++)
        {
            if (m[i][j]>m[i][j+1]&&m[i][j]>m[i+1][j]&&m[i][j]>m[i+1][j+1])
                sum++;
        }
    }
   for (i = 0; i < rows-1; i++)
    {
        if (m[i][cols-1]>m[i+1][cols-1])
            sum++;
    }
    for (j = 0; j < cols-1; j++)
    {
        if (m[rows-1][j]>m[rows-1][j+1])
            sum++;
    }
    if (sum==cols*rows)
        return 1;
    else
    return 0;
    
    
}