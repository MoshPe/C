#include <stdio.h>
#include <math.h>
float func2(int x);
float func1(int x);
double sum_square(int m,int n,float(*f)(int a));//float/double
void main()
{   
    printf("The sum of func2:%.5f",sum_square(2,13,func2));
    printf("\nThe sum of func1:%.5f",sum_square(1,10000,func1));
}
double sum_square(int m,int n,float(*pfunc)(int a))//float/double
{
    int i;
    double sum = 0;
    for (i = m; i <= n; i++)
        sum += pow(pfunc(i),2);
    return sum;
}
float func1(int x)
{
    return 1.0f/x;
}
float func2(int x)
{
    return x/5.0f;
}
