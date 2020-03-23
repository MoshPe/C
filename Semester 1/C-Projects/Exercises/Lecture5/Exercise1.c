#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void main()
{
    int num,counter=0,i;
    printf("Enter an integer number , please: ");
    scanf("%d",&num);
    if(num == 0)
    {
        printf("Infinity\n");
    }
    else
    if (num == 1)
    {
        printf("count = %d",counter);
    }
    else
    {
    for (i = 1; i < abs(num); i++)
    {
        if(num%i ==0)
        {
            printf("%4d",i);
            counter++;
        }
    }
         if (num <0)
    {
        printf("%4d",abs(num));
        counter++;
        }
    printf("\ncount = %d",counter);
    }
}