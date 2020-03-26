#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    unsigned a,b,c;
    printf("Enter 3 triangle edges: ");
    scanf("%u%u%u",&a,&b,&c);
    if ((a+b>c) && (a+c>b) && (b+c>a))
    {
        if (a==b && b==c)
        {
            printf("The triangle edges are all equal");
        }
        else if (a==b || b==c || a==c)
        {
            printf("The 2 triangle edges are equal");
        }
        else
        {
            printf("The triangle edges are not equal");
        }
        
        
        
        


    }






}