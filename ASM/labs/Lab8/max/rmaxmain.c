/* rmax1.c - Find the maximum of array elements,
                     iterative, recursive.     */
#include <stdio.h>
#define ARRSIZE 40

/* Find maximum of x[0] ... x[n] */
extern int rmax(int arr[], int n);

 void main()
   {
     int n, x[ARRSIZE];

     printf("Enter up to %d integers, any number per line,\n", ARRSIZE);
     puts("Signal EOF by ctrl-Z\n");

     n = 0;
     while( scanf("%d",&x[n]) != EOF )
                n++;

     printf("The maximum of the %d elements is: %d \n", n, rmax(x, n-1));

   } /* main */
