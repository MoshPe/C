#include<stdio.h>
void astering(int n);
void main()
{
    astering(5);
}
void astering (int n)
{
    if (n==0)
    {
        printf("\n");
        return;
    }
     else
        printf("*");
    astering(--n);
}