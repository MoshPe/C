#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 9
typedef struct fraction
{
	int a;
	int b;
}fraction;

void calculate(fraction* s, int size);
void inputInfo(fraction* s, int size);
void main()
{
	fraction Fractions[MAX];
	fraction* p = &Fractions[0];
	inputInfo(p, MAX);
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
	long int t, mehaneX, moneX, moneY, mehaneY;
	long int mehane = s[0].b;
	long int mone = 0;
	for (i = 1; i < size; i++)//calculates the common division
		mehane = mehane * s[i].b;
	for (i = 0; i < size; i++)// calculates the entire fraction
		mone = mone + s[i].a * (mehane / s[i].b);
	for (i = 0; i < size; i++)
		printf(" %d/%d %c", s[i].a, s[i].b, (i == size - 1) ? '=' : '+');
	//for not losing the original number
	moneX = abs(mone);
	mehaneX = abs(mehane);
	/*calculates the highest number that divides both mone and mehane
	  and put it in moneX  */
	do {
		t = moneX % mehaneX;
		if (2 * t > mehaneX)
			t = mehaneX - t;
		moneX = mehaneX;
		mehaneX = t;
	} while (moneX != 0 && mehaneX != 0);
	mone = mone / moneX;//reduction the mone and mehane by the highest common number
	mehane = mehane / moneX;
	printf(" %ld/%ld = ", mone, mehane);
	moneY = abs(mone);
	mehaneY = abs(mehane);
	while (moneY > mehaneY)//count the quantities of the integers 
	{
		moneY = moneY - mehaneY;
		count++;
	}
	mehane = mehaneY;
	if (mone < 0) {
		moneY = moneY * -1;
		count = count * -1;
	}
	if (abs(count) > 0)
		printf("%ld and", count);
	printf(" %ld/%ld\n", moneY, abs(mehane));
}
/*
Function name: outputInfo
Input: getting the fraction struct and the quatity of the fractions
Output: outputting the smallest fraction possible
Algoritem: it first getting input all the fraction from the user and put them
			into the structure array and send the array to the calculate function
*/
void inputInfo(fraction* s, int size)
{
	int i, index;
	printf("Enter fractions(max 9) by pairs of integers(0 0 to finish):\n");
	for (i = 0, index = 0; i < size; i++, index++)
	{
		printf("%d (mone mehane): ", i + 1);
		scanf("%d%d", &s[i].a, &s[i].b);
		//checking if the fraction is correct and valid
		while (s[i].a != 0 && s[i].b == 0)
		{
			printf("invalid denominator,please try again!\n");
			scanf("%d%d", &s[i].a, &s[i].b);	
		}
		if ((s[i].a == 0) && (s[i].b == 0))
			i = size;
	}
	if (index < i)
		calculate(s, index - 1);
	else
		calculate(s, i);
}