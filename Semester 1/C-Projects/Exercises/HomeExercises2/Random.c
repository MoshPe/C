#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    int a,b,c;
    for (int i = 0; i < 20; i++)
    {
        a = rand() % 20;
        printf("%d  " ,a);
    }
    
}