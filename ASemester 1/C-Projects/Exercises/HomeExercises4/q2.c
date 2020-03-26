#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int isSort1(int *ar,int n);
int isSort2(int *ar,int n);
void main()
{
  int ar[8] = {2,18,3,15,3,9,7,4};

   printf("%d",isSort1(ar+1,4));
   printf("%d",isSort2(ar,4));

}
int isSort1(int *ar,int n)
{
    if (n==0)
    return 1;
    return (*ar>=*(ar+2))?isSort1(ar+2,n-=2):0;
    
}
int isSort2(int *ar,int n)
{
    if (n==0)
    return 1;
    return (*ar<=*(ar+2))?isSort2(ar+2,n-=2):0;
    
}



