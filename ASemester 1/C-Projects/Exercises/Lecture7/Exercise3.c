#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10
void main()
{
	int array[N] = { 0 }, i,max = 0,count = 0;
	long long int num,num1;
	printf("Enter an integer number, please: ");
	scanf("%lld", &num);
	num = llabs(num);
	do
	{
		while (num != 0)
		{
			array[num % 10]++;
			num = num / 10;
		}
		if (num==0)
		{
			array[0]++;
		}
		for (i = 0; i < N; i++)
		{
			if (array[i] > 0)
			{
				printf("the digit %d appears %d times.\n", i, array[i]);
			}
			if (array[i] > max)
				max = array[i];
		}
		printf("The most frequent digit/s is/are: ");
		for (i = 0; i < N; i++)
		{
			if (array[i] == max)
			{
				printf("%d ", i);
			}
		}
		printf("\n");
	} while (num!=0);
}