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
	fraction* p = &Fractions[0];
	outputInfo(p, 9);
}
/*
Function name: calculate
Input: getting the fraction struct and the quatity of the fractions
Output: outputting the smallest fraction possible  
Algoritem: first it counts the mone and the mechane together by the rules
			to one fraction, then the fucntion finds the highest number that
			divide them both
*/
void calculate(fraction* s, int size)
{
	int i, count = 0;
	long int t,mechaneX,moneX;
	long int mechane = s[0].b;
	long int mone = 0;
	for (i = 1; i < size; i++)
		mechane = mechane * s[i].b;
	for (i = 0; i < size; i++)
		mone = mone + s[i].a * (mechane / s[i].b);
	for (i = 0; i < size; i++)
		printf(" %d/%d %c", s[i].a, s[i].b, (i == size - 1) ? '=' : '+');
		//for not losing the original number
		moneX = mone;
		mechaneX = mechane;
		//calculates the highest number that divide both mone and mechane
	do {
		t = moneX % mechaneX;
		if (2 * t > mechaneX)
			t = mechaneX - t;
		moneX = mechaneX;
		mechaneX = t;
	} while (moneX != 0 && mechaneX != 0);
	mone = mone / moneX;
	mechane = mechane / moneX;
	while (mone>mechane)
	{
		mone = mone - mechane;
		count++;
	}
	if (count > 0)
		printf("%ld and", count);
	printf(" %ld/%ld", mone, mechane);
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