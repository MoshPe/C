#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
    {
        float result;
        float a,b;
        printf("Given the equation a^x=b\n");
        printf("Enter a and b, repectively please: ");
        scanf("%f%f", &a,&b);
        result = log(b)/log(a);
        printf("x is: %g", result);
    }
