#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    int **z;
    int x;
    int *y;
    x=0;
    y=&x;
    //y=&x;
    z=&y;
    printf("%d", **z);
}