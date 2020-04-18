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
Algoritem: first it counts the mone and the mehane together by the rules
			to one fraction, then the fucntion finds the highest number that
			divide them both
*/
void calculate(fraction* s, int size)
{
	int i, count = 0;
	long int t,mehaneX,moneX;
	long int mehane = s[0].b;
	long int mone = 0;
	for (i = 1; i < size; i++)
		mehane = mehane * s[i].b;
	for (i = 0; i < size; i++)
		mone = mone + s[i].a * (mehane / s[i].b);
	for (i = 0; i < size; i++)
		printf(" %d/%d %c", s[i].a, s[i].b, (i == size - 1) ? '=' : '+');
		//for not losing the original number
		moneX = mone;
		mehaneX = mehane;
		/*calculates the highest number that divide both mone and mehane
		  and put it in moneX  */
	do {
		t = moneX % mehaneX;
		if (2 * t > mehaneX)
			t = mehaneX - t;
		moneX = mehaneX;
		mehaneX = t;
	} while (moneX != 0 && mehaneX != 0);
	mone = mone / moneX;
	mehane = mehane / moneX;
	while (mone>mehane)
	{
		mone = mone - mehane;
		count++;
	}
	if (count > 0)
		printf("%ld and", count);
	printf(" %ld/%ld", mone, mehane);
}
/*
Function name: outputInfo
Input: getting the fraction struct and the quatity of the fractions
Output: outputting the smallest fraction possible  
Algoritem: it first getting input all the fraction from the user and put them
			into the structure array and send the array to the calculate function
*/
void outputInfo(fraction* s, int size)
{
	int i, index;
	printf("Enter fractions(max 9) by pairs of integers(0 0 to finish):\n");
	for (i = 0, index = 0; i < size; i++, index++)
	{
		printf("%d (mone mehane): ", i + 1);
		scanf("%d%d", &s[i].a, &s[i].b);
		//checking if the fraction is correct and valid
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