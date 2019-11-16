#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{

	float x;
	float SumX, In;
	printf("Enter x please: ");
	scanf("%f", &x);
	In = ((double)pow(x, 4)/3) + (2 * sqrt(x));
	SumX = x + pow(In, 0.2);
	printf("x + (1/3x^4 + 2x^(1/2))^(1/5)) = %g + (1/3*%g^4 + 2*%g^(1/2))^(1/5) = %f ",x, x, x, SumX);
	



}