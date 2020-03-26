#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main ()
{

    int a, b , c;
    float x1, x2; 
    float Delta = 0;
    printf("Please Enter A: \n");
    scanf("%d", &a);
    printf("Please Enter B: \n");
    scanf("%d", &b);
    printf("Please Enter C: \n");
    scanf("%d", &c);
    Delta = pow(b,2) - (4*a*c);
    //printf("Delta is: %d" , Delta);
    if (Delta == 0)
    {
    printf ("There will be only one result\n");
    x1 = (-b + sqrt(Delta)) / (2 * a);
	x2 = (-b - sqrt(Delta)) / (2 * a);
    if (x1 == x2)
    {
        printf("Your X is: %.2f ", x1);
    }
     
    }
    else if (Delta < 0)
    {
        printf("There wont be any results");
    }
    else
    {
        printf("There will be 2 results\n");
        x1 = (-b + sqrt(Delta)) / (2 * a);
		x2 = (-b - sqrt(Delta)) / (2 * a);
        printf("x1 is: %.2f\n" , x1);
        printf("x2 is: %.2f\n" , x2); 
    }
    
    printf("\nThe Delta is: %d", Delta);
    

}