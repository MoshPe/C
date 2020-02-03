#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void printMerge(int a[], int na, int b[], int nb);
void main()
{
	int a[6] = { 1,3,6,6,9,15 };
	int b[4] = { 3,3,5,6 };
	int n = 5;
	printMerge(a, 6, b, 4);
}
void printMerge(int a[], int na, int b[], int nb)
{
	int i = 0, j = 0, maxn;
	int* c;
	if (a[na-1] > b[nb-1])
		maxn = a[na-1];
	else
		maxn = b[nb-1];
	c = (int*)calloc(sizeof(int), maxn);
	while (i < na && j < nb)
	{
		if (a[i] < b[j] && c[a[i]] < 1)
		{
			printf("%d ", a[i]);
			c[a[i]]++;
			i++;
		}
		else if (c[b[j]] < 1)
		{
			printf("%d ", b[j]);
			j++;
			c[b[j]]++;
			
		}
		if (c[b[j]] != 0 && c[a[i]] !=0)
        {
			j++;
			i++;
		}

	}
	while (i < na)
		printf("%d ", a[i++]);
	while (j < nb)
		printf("%d ", b[j++]);
}