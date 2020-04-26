#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<math.h>

void main()
{
	int i;
	float arr[4]={99.80,77.89,50.34,49.78};
	float avg;
	float hey;
	float sd = 0;//Standard Deviation
	float max = arr[0];
	float min = arr[0];
	for (i = 0; i < 4; i++)
	{
		avg += arr[i];
		if (arr[i]>max)
			max = arr[i];
			if (arr[i]<min)
			min = arr[i];	
	}
	avg = avg/4;
	for (i = 0; i < 4; i++)
	{
		hey = (arr[i] - avg);
		printf("\n%.2f\n",hey);
		sd= sd + pow(hey,2.0);
		printf("\n%.2f\n",sd);
	}
	printf(" the avg is %f the max is %.2f min %.2f sd %f",avg,max,min,sqrt(sd/4.0));
}

