#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void main()
{
    int i,j,R,C;
    printf("Enter number of table rows: ");
    scanf("%d%d",&R,&C);
    for (i = 1; i <= R; i++)
    {
        for (j = 1; j <= C; j++)
        {
            printf("%6d",i*j);
        }
        printf("\n");
    }
    
}