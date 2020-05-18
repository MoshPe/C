// add_call.c

#include <stdio.h>

extern int add2Vecs( int v1[],  int v2[], int v1_plus_v2[], int n);


void main()
{
  int i, n=3, sum;
  int v1[10] = {1, 2, 3 };
  int v2[3] = {4, 5, 6 };
  int v1_plus_v2[3];

 sum=add2Vecs(v1, v2, v1_plus_v2, n);

 printf("v1+v2:\n");
 for(i=0; i < n; i++)
  printf("v1[%d]+v2[%d]=%d+%d=%d\n", i, i, v1[i], v2[i], v1_plus_v2 [i]);
 printf("sum of v1[i]+v2[i]= %d", sum);
 }
