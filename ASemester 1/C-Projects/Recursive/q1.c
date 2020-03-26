#include<stdio.h>
int long long m(int n);
void main()
{
   printf("%d",m(78451264));
}
int long long m(int n)
{
    int sum=0;
    m(n/10);
    return n==0?0:(n%10)%2!=0?sum+=n%10:0;
}