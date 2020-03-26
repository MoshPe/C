#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void printNonRepeat(int a[], int na);
void main()
{
	int a[7] = {1,1,3,6,6,9,15};
    printNonRepeat(a,7);
}
void printNonRepeat(int a[], int na)
{
    if (na==0)
        return;
    if (*a!=*(a+1))
       printf("%d ",*a);
    printNonRepeat(a+1,na-1);
}

