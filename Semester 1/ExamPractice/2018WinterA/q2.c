#include<stdio.h>
#include<stdlib.h>
void Smax1(int a[],int n,int Smax);
void main()
{
    int ar[8]={60,-7,-310,14,50,9,1,7};
    int Smax=0;
    Smax1(ar,8,Smax);

}
void Smax1(int a[],int n,int Smax)
{
    int i,sum=0;
    mergesort(a,n);
    for (i = 0; i < n; i++)
    {
        if (sum+a[i]<=Smax){
            sum+=a[i];
            printf("%d",a[i]);
        }
    }
    
}