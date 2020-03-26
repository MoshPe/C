#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6
int drivercount(int bus[][M], int a, int n, int m);
int is_in(int bus[][M], int j, int m, int n);
void main()
{
	int i, j, count = 0, count1 = 0, count2 = 0, temp = 0, k;
	int bus[N][M] = { {6,3,8,0,0,5},{6,6,5,7,8,4},{4,5,6,6,1,7},{0,4,3,2,5,0},{0,8,7,3,2,8} };
	printf("             10:00  11:00  12:00  13:00  14:00  15:00\n");
	for (i = 0; i < N; i++)
	{
		printf("station%d:", i + 1);
		for (j = 0; j < M; j++)
			printf("%7d", bus[i][j]);
		printf("\n");
	}
	printf("The station with no collection for more than two hours are: \n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (bus[i][j] == 0 && count == 0)
				count = j;
			else if (bus[i][j] == 0)
			{
				count1 = j;
				count2++;
			}
		}
		if (count != 0 && ((count2 + count) == count1))
		{
			printf("station number %d\n", i + 1);
		}
		count = 0;
		count1 = 0;
		count2 = 0;
	}
	printf("The drivers that have two or more stations in one hour are: \n");
	count = 0;
	temp = bus[0][0];
	for (j = 0; j < M; j++)
	{
		for (i = 0; i < N; i++)
		{
			if (temp == bus[i][j])
				count++;
			if (count >= 2 && bus[i][j] != temp)
			{
				printf("driver number %d\n", bus[i - 1][j]);
				count = 0;
			}
			temp = bus[i][j];
		}
		count = 0;
	}
	printf("The drivers that drive three hours in a row are: \n");
	count = 1;
	for (k = 9; k > 0; k--)
	{
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (bus[i][j] == k && is_in(bus, j + 1, k, N) == 1)
					count++;
			}
		}
		if (count >= 3)
			printf("driver number %d\n", k);
		count = 0;
	}
}
/*
Input: gets the matrix, its specific col index,the k which goes from 1-9 and its col size
algoritem: the function check if the same number that was on
output: the function just prints if the st2 is hidden in st1 or not
*/
int is_in(int bus[][M], int j, int m, int n)
{
	int i, flag = 0;
	for (i = 0; i < n; i++)
	{
		if (bus[i][j] == m)
			flag = 1;
	}
	return flag;
}