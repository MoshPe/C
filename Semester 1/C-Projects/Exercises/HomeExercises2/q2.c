#include <stdio.h>
#include <stdlib.h>
void print_Pos(int[], unsigned);
void main()
{
 int A[9] = { -13,-2,3,1,8,-5,5,1,2};
 int B[10] = { 1,2,3,0,1,8,12,7,3,5};
 int C[12] = { 1,0,3,1,0,8,12,7,4,5,1,1};
 int D[1] = { 100 };
 print_Pos(A, 9);
 print_Pos(B, 10);
 print_Pos(C, 12);
 print_Pos(D, 1);
}
void print_Pos(int ar[], unsigned n)
{
 int i = 0, p = 0, q = 0, counterOne = 0, counterTwo = 0, max = 0,One = 0, Two = 0;
 do
 {
    do
    {
        while (ar[i] > 0)
        {
             counterOne++;
   i++;
   p = i;
  }
  if (counterOne != 0)
  {
   i = n;
  }
  else
  {
   i++;
  }
  One = counterOne;
 } while (i != n && i < n);
 i = p+1;
 do
 {
  while (ar[i] > 0)
  {
   counterTwo++;
   i++;
   q = i;
  }
  if (counterTwo != 0)
  {
   i = n;
  }
  else
  {
   i++;
   q = i;
  }
  Two = counterTwo;
 } while (i != n && i < n);
 i = q+1;
 if (counterOne>counterTwo && counterOne>max)
 {
  max = counterOne;
 }
 else if (counterTwo > max)
 {
  max = counterTwo;
 }
 counterOne = 0;
 counterTwo = 0;
 } while (i < n);
 printf("%d,\n",max);
}
