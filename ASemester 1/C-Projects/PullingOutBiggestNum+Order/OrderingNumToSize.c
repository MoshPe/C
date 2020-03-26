#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#define t1 10
void main()
{
	int num, num1=0;
	int i = 0, j = 0, b = 0, max = 0,k=0;
	printf("Please enter 10 digits num: ");
	scanf("%d", &num);
	num1 = num;
	/*while (num1 != 0)
	{
		num1 = num1 / 10;
		t1++;
	}*/
	int arrayA[] = { t1 };
	int arrayB[] = { t1 };
	int max1[] = { t1 };
	for (;i < t1; i++)
	{
		arrayA[i] = num % 10;
		num = num / 10;
		arrayB[i] = arrayA[i];
	}
	for (j = 0; j < t1; j++);
	{
		for (i = 0; i <t1; i++)
		{
			if (arrayB[j] > arrayA[i])
			{
				max = arrayB[j];

			}
			else
			{
				max = arrayA[i];
			}
			for ( i = 0; i < t1; i++)
			{
				if (max1[i] != max)
				{
					max1[k] = max;
				    k++;
				}
			}
		}
	}
	for (i = 0; i < t1; i++)
	{
		printf("%d",max1[i]);
	}
	
}

