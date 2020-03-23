#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
void set_2d(float** a, int m, int n);
void print_2d(float** a, int m, int n);

void main()
{
	int m, n, i;
	float** a;
	printf("\nenter m and n, for m*n array: \n");
	scanf_s("%d %d", &m, &n);
	puts("\n");
	a = (float**)malloc(m * sizeof(float*));
	assert(a);
	for (i = 0; i < m; i++)
	{
		a[i] = (float*)malloc(n * sizeof(float));
		assert(a[i]);
	}
	set_2d(a, m, n);
	print_2d(a, m, n);
	for (i = 0; i < m; i++)
		free(a[i]);
	free(a);

}
void set_2d(float** a, int m, int n)
{
	int i, j, k = 1;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i][j] = k++;
}
void print_2d(float** a, int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%7.1f ", a[i][j]);
		puts("\n");
	}
}
