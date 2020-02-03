#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

int indexReturn(int a[], int n);
void SortA(int a[], int c);
void main()
{
	int i;
	int a[10] = { 10,11,16,20,-5,-3,0,5,6,9 };
	printf("The index is %d\n", indexReturn(a, 10));
	SortA(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d, ", a[i]);
			
}
int indexReturn(int a[], int n)
{
	int b = n;
	int i=0;
	while (b>i)
	{
		if (a[i] < a[b - 1])
			b = b - abs(i / 2);
		else if (b - 1 != i)
			i = abs(b / 2);
		else
			return i-1;
	}
}
void SortA(int a[], int c)
{
	int i,b=0;
	int* p;
	p = (int*)malloc(c * sizeof(int));
	assert(p);
	for (i = indexReturn(a, c); i < c; i++,b++)
		p[b] = a[i];
	for (i = 0; i < indexReturn(a, c); i++,b++)
		p[b] = a[i];
	for (i = 0; i < c; i++)
		a[i] = p[i];
	free(p);
}