#include<stdio.h>
#include<math.h>



int* sortedSquares(int* A, int ASize, int* returnSize);
void main()
{
    int*A = {-4,-1,0,3,10};
    int*hi;
    int i;
    hi = sortedSquares(A,5,hi);
    for (i = 0; i < 5; i++)
        printf("%d,",hi[i]);
    
}
int* sortedSquares(int* A, int ASize, int* returnSize)
{
    int i;
    int* afterit;
    afterit = (int*)malloc(ASize*sizeof(int));
    assert(returnSize);
for(i=0;i<ASize-1;i++)
{
    if(abs(A[ASize-i-1])>abs(A[i]))
        afterit[ASize-i-1] = pow(A[ASize-i-1],2);
    else
        afterit[i] = pow(A[i],2);       
}
    return afterit;
}