#include <stdio.h>
#include <stdlib.h>
int recSeriesElem(unsigned n);
void main()
{
    int i,n=12;
    printf("The first %d elements in the series are: \n", n);
    //loop for the series from 0 till the number n which was given in the question and is 12 and prints theri value
    for (i = 0; i < n; i++)
       printf("%d   ",recSeriesElem(i));
}
/*
Function name: recSeriesElem
Input: an unsigned number which indicates the place in a series
Output: the value of the place in the series
Algoritem: the function follow the series algoritem(3*a(n-1)-4*a(n-2)) and out its value
*/
int recSeriesElem(unsigned n)
{
    if (n<3)
        return n;
        return 3*recSeriesElem(n-1)-4*recSeriesElem(n-2);
}