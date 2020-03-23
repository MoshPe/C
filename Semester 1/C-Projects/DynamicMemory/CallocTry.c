#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
    int n,i;
    int *c;
    printf("Enter Calloc size: ");
    scanf("%d",&n);
    c = (int*)calloc(sizeof(int),n);
    printf("Enter Calloc array numbers: ");
    for (i = 0; i < n-1; i++)
        scanf("%d",&c[i]);
    for (i = 0; i < n; i++)
        printf("%d  " , c[i]);
    
    
	

}

