#include <windows.h>
#include <math.h>
#include <stdio.h>
double piForinfinity(double n);
void main()
{
 double n = 1;
 long double sum = 0;
 long long i;
 char max[20000];
 //printf("%.50lf\n",4* piForinfinity(n));
 /*for (i = 0; i < 99999; i++)

	{

		sum = sum+ (pow((-1), n + 1) / (2 * n - 1));

		n++;

	}

	sum = sum * 4;

	//printf("%.50Lf\n", sum);*/
 _gcvt(M_PI, 20000, max);
 for (i = 0; i < 70; i++)
 {
  Sleep(500);
  putchar(max[i]);
 }
}
double piForinfinity(double n)
{
 if (n == 999)
  return (pow((-1), n + 1) / (2 * n - 1));
 return (pow((-1), n + 1) / (2 * n - 1)) + piForinfinity(n + 1);
}
