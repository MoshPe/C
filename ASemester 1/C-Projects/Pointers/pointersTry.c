#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<conio.h>


void main()
{
    int** z;
    int x;
    int* y;
    x=3;
    y=&x;
    //y=&x;
    z=&y;
    printf("%d", **z);
}