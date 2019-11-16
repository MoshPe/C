#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
    //int DeltaCalculate = "RootsDeltaCalculate.exe";
    int a,b,c;
    float x1, x2; 
    printf("Please Enter A: ");
    scanf("%d", &a);
    printf("Please Enter B: ");
    scanf("%d", &b);
    printf("Please Enter C: ");
    scanf("%d", &c);
    int Delta;
    Delta = (b*b) - (4*a*c);
    x1 = (-b+sqrt(Delta))/2*a;
    x2 = (-b-sqrt(Delta))/2*a;
    printf("x1 is %.2f\n" , x1);
    printf("x2 is %.2f\n" , x2); 
}