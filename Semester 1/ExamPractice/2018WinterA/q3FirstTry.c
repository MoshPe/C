#include<stdio.h>
#include<stdlib.h>
void insert(int a[],int n,int new);
void move(int a[],int n);
void main()
{
    int a[7]={1,1,2,3,5,7};
    int new=13;
    insert(a,7,new);
    for (int i = 0; i < 7; i++)
        printf("%d, ",a[i]);
    

}
void insert(int a[],int n,int new)
{
    if (n==1)
    {
        a[n-1]=new;
        return;
    }
    if (*a>new)
    {
        move(a,n);
        *a=new;
        return;
    }
    insert(a+1,n-1,new);   
}
void move(int a[],int n)
{
    int i;
    for (i = n-1; i >0 ; i--)
        a[i]=a[i-1];
}