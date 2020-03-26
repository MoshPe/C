#include<stdio.h>
#include<stdlib.h>
void SortAr(int* a, int n);
void main()
{
	int a[9] = { -2,3,10,7,9,5,12,17,23 };
	int i;
	SortAr(a, 9);
	for (i = 0; i < 9; i++)
		printf("%d ", a[i]);

}
void SortAr(int* a, int n)
{
	int i, num = 0, flag = 0;
	for (i = 0; i < n - 1 && flag == 0; i++)
	{
		if (a[i] > a[i + 1])
		{
			flag = 1;
			num = i;
		}
	}
	for (i=num+1; i < n - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			flag = a[i + 1];
			a[i + 1] = a[num];
			a[num] = flag;
		}
	}
}