#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
int consecSame(int **mat,int rows,int cols);
int isConsec(int *ar,int n);
#define M 6
void main()
{
    //int ar[6]={15,17,18,20,19,16};
    int s[5][6] = {{12,13,17,15,14},{7,3,5,8,10},{5,2,7,4,3,6},{2,6,3,4,7,5},{11,12,13,15,10,14}};
    int *mat[5]={s[0],s[1],s[2],s[3],s[4]};
    printf("%d ",consecSame(mat,5,6));
}
int isConsec(int *ar,int n)
{
    int i,max=0,isConseCheck=0;
    for (i = 0; i < n; i++)
    {
        if (ar[i]>max)
            max=ar[i];
    }
    for (i = 0; i < n; i++)
    {
        if (ar[i]>=max-n+1&&ar[i]<max)
            isConseCheck++;
    }
    if (isConseCheck==n-1)
        return max;
    return -1;
}
int consecSame(int **mat,int rows,int cols)
{
   int i,j,count=0;
   int *a;
   a=(int*)calloc(rows,sizeof(int));
   assert(a);
   for (i = 0; i < rows; i++)
            a[i]=isConsec(mat[i],cols);
    for (i = 0; i < rows; i++)
    {
        if (a[i]!=-1)
        {
            for (j = i+1; j < rows; j++)
            {
                if (a[i]==a[j])
                    return 1;
            }
        }
    }
    return 0;
}