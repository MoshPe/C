#include<stdio.h>
#include<stdlib.h>
void changeAr(int* ar, int n);
int maxCnt(int* ar, int n);
#define N 4
void main()
{
	int i;
	int a[N] = {1,7,7,12};
	changeAr(a, N);
	for (i = 0; i < N; i++)
	    printf("%d , ", a[i]);
	printf("\n%d,", maxCnt(a, N));

}
void changeAr(int* ar, int n)
{
    int temp;
	if (n <=1)
		return;
	temp = *ar;
	*ar = *(ar + n - 1);
	*(ar + n - 1) = temp;
	changeAr(ar + 1, n - 2);
}
int maxCnt(int* ar, int n)
{
	if (n <= 1)
		return 0;
	if (*(ar + 1) > *ar&&*(ar + 1) > *(ar + 2))
		return 1 + maxCnt(ar + 2, n - 3);
	else
		return 0 + maxCnt(ar + 1, n - 1);
}