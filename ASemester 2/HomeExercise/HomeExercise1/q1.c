#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fraction
{
	int a;
	int b;
}fraction;
void calculate(fraction* s, int size);
void outputInfo(fraction* s, int size);
void main()
{
	fraction Fractions[9];
	fraction* p= &Fractions[0];
	outputInfo(p, 9);
}
void calculate(fraction* s, int size)
{
	int i,count=0;
	int mul = s[0].b;
	int sum = 0;
	for (i = 1; i < size; i++)
		mul = mul * s[i].b;
	for (i = 0; i < size; i++)
		sum =sum+ s[i].a * (mul / s[i].b);
	for (i = 0; i < size; i++)
		printf(" %d/%d %c", s[i].a, s[i].b,(i==size-1)?'=':'+');
	do
	{
		count = 0;
		for (i = 1; i < 8; i++)
		{
			if (sum % i == 0 && mul % i == 0)
			{
				sum = sum / i;
				mul = mul / i;
			}
			else
				count++;
		}
	} while (count != 5);
	printf(" %d/%d %c", sum, mul,(sum>mul)?'=':' ');
	count = 0;
	while (sum>mul)
	{
		sum = sum - mul;
		count++;
	}
	printf(" %d and %d/%d", count, sum, mul);
}
void outputInfo(fraction* s, int size)
{
	int i, index;
	printf("Enter fractions(max 9) by pairs of integers(0 0 to finish):\n");
	for (i = 0, index = 0; i < size; i++, index++)
	{
		printf("%d (mone mehane): ", i + 1);
		scanf("%d%d", &s[i].a, &s[i].b);
		if (s[i].a != 0 && s[i].b == 0)
		{
			printf("invalid denominator,please try again!\n");
			i--;
		}
		if ((s[i].a == 0) && (s[i].b == 0))
			i = 9;
	}
	if (index < i)
		calculate(s, index - 1);
	else
		calculate(s, i);
}