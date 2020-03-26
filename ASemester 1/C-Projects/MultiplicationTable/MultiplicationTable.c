#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define CRT_SECURE_NO_WARNINGS

void main()
{
    int i,j,N;
    printf("Enter Digit of table size(10=>): ");
    scanf("%d",&N);
    for (i = 1; i < N; i++)
    {
        for (j = 1; j < N; j++)
        {
            printf("%4d",i*j);
        }
        printf("\n");
    }
    
}