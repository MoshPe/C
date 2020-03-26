#include<stdio.h>
#include<stdlib.h>
void merge(int* a, int na, int* b, int nb, int* c);
#define N 5
void main()
{
	int a[5] = { 1,23,45,46,87 }, b[5] = {11,22,42,65,89};
	int c[10] = { 0 };
	merge(a, N, b, N, c);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", c[i]);
	}







}
void merge(int* a, int na, int* b, int nb, int* c)
{
	if (nb == 0 || na == 0) 
		return;
	if (*a > * b)
	{
		*c = *b;
		merge(a, na, b + 1, nb - 1, c + 1);
	}
	else
	{
		*c = *a;
		merge(a + 1, na - 1, b, nb, c + 1);
	}
}
