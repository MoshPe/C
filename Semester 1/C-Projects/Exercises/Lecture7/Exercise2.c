#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N 10
float avg(float array[], int n);

void main()
{
	float RunTime[N],avg1;
	int i,count = 0;
	printf("Enter times, please: ");
	for (i = 0; i < N; i++)
	{
		scanf("%f", &RunTime[i]);
	}
	avg1 = avg(RunTime, N);
	for ( i = 0; i < N; i++)
	{
		if (RunTime[i] < avg1)
			count++;
	}
	printf("The number of runners, running below the average time is %d", avg1);
}
float avg(float array[], int n)
{
	int i;
	float avg1;
	for (i = 0; i < n; i++)
	{
		avg1 = avg1 + array[i];
	}
	avg1 = avg1 / n;
	return avg1;
}