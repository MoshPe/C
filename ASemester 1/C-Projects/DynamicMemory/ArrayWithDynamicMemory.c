#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

void main()
{
    srand (time(NULL));
    int *arr, n,i;
    printf("Enter array size: ");
    scanf("%d",&n);
    arr = (int*)malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        arr[i] = rand()%n;
    }
    for (i = 0; i < n; i++)
    {
        printf("%d,",arr[i]);
    }
    free(arr);
}