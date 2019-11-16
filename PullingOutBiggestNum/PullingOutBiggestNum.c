#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#define N 10
void main()
{
	float max;
	float array[N];
	int i;
	//max = array[0];
	for (i = 0; i < N; i++)
	{
		printf("Enter a digit: ");
		scanf("%f", &array[i]);
		if (array[i] < max)
		{

		}
		else
		{
			max = array[i];
		}
	}
	printf("%f", max);
}










