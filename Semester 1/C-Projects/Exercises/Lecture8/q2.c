#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int inputThree(int* a, int* b, int* c);
void sortTwo(int* a, int* b);
void sortThree(int* a, int* b, int* c);
void main()
{
	int p, w, d;
	while (inputThree(&p,&w,&d)!=0)
	{
		sortThree(&p, &w, &d);
		printf("%d %d %d\n", p, w, d);
	}
	printf("\nFinish");
}
int inputThree(int* a, int* b, int* c)
{
	printf("Enter 3 integers: ");
	scanf("%d%d%d", a, b, c);
	return (*a == 0 && *b == 0 && *c == 0) ? 0 : 1;
}
void sortTwo(int* a, int* b)
{
	int temp;
	if (*a > * b)
	{
		temp = *b;
		*b = *a;
		*a = temp;
	}
}
void sortThree(int* a, int* b, int* c)
{
	sortTwo(a, b);
	sortTwo(a, c);
	sortTwo(b, c);
}
