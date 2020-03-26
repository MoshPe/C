#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define N 5
#define M 6
//int drivercount(int bus[][M], int a, int n, int m);
void matprint(int bus[][M], int n);
void noCollectionStation(int bus[][M], int n);
void twomoreStation(int bus[][M], int n);
void moreThreeHr(int bus[][M], int n);
int is_in(int bus[][M], int j, int m, int n);
void main()
{
	int bus[N][M] = { {6,3,8,0,0,5},{6,6,5,7,8,4},{4,5,6,6,1,7},{0,4,3,2,5,0},{0,8,7,3,2,8} };
	matprint(bus, N);
	printf("The station with no collection for more than two hours are: \n");
	noCollectionStation(bus, N);
	printf("The drivers that have two or more stations in one hour are: \n");
	twomoreStation(bus, N);
	printf("The drivers that drive three hours in a row are: \n");
	moreThreeHr(bus, N);
}
/*
Input: gets the matrix, and the number of rows
algoritem: the function uses 2 arrays to print
output: prints the matrix
*/
void matprint(int bus[][M], int n)
{
	int i, j;
	printf("             10:00  11:00  12:00  13:00  14:00  15:00\n");
	for (i = 0; i < n; i++)
	{
		printf("station%d:", i + 1);
		for (j = 0; j < M; j++)
			printf("%7d", bus[i][j]);
		printf("\n");
	}
}
/*
Input: gets the matrix, and the number of rows
algoritem: the function seek for a station with no collection at all, its just count the number 0 that follow in the same row
output: the function prints the number of the station that has more than 2hrs
*/
void noCollectionStation(int bus[][M], int n)
{
	int i, j, firstEmpLoc = 0, lastEmpLoc = 0, Emptycount = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (bus[i][j] == 0 && firstEmpLoc == 0)
				firstEmpLoc = j;
			else if (bus[i][j] == 0)
			{
				lastEmpLoc = j;
				Emptycount++;
			}
		}
		if (firstEmpLoc != 0 && ((Emptycount + firstEmpLoc) == lastEmpLoc))
		{
			printf("station number %d\n", i + 1);
		}
		firstEmpLoc = 0;
		lastEmpLoc = 0;
		Emptycount = 0;
	}
}
/*
Input: gets the matrix, and the number of rows
algoritem: the function counts the number of station that a certain driver has to be at
output: the function prints out the driver number that has to be in 2 or more stations at once
*/
void twomoreStation(int bus[][M], int n)
{
	int countstation = 0, i, j;
	int temp = bus[0][0];
	for (j = 0; j < M; j++)
	{
		for (i = 0; i < n; i++)
		{
			if (temp == bus[i][j])
				countstation++;
			if (countstation >= 2 && bus[i][j] != temp)
			{
				printf("driver number %d\n", bus[i - 1][j]);
				countstation = 0;
			}
			temp = bus[i][j];
		}
		countstation = 0;
	}
}
/*
Input:gets the matrix, and the number of rows
algoritem: the function check for a sequence of 3 in the matrix col, by using a loop to check each number
output: the function prints out the driver number thaat drive 3 hrs and more
*/
void moreThreeHr(int bus[][M], int n)
{
	int countHr = 1, k, i, j;
	for (k = 9; k > 0; k--)
	{
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < n-2; j++)
			{
				if (bus[i][j] == k && is_in(bus, j + 1, k, n) == 1&& is_in(bus, j + 2, k, n) == 1)
					countHr+=2;
			}
		}
		if (countHr >= 3)
			printf("driver number %d\n", k);
		countHr = 1;
	}
}
/*
Input: gets the matrix, its specific col index,the k which goes from 1-9 and its col size
algoritem: the function check if the same number that was on col j is also in j+1
output: the function return 1 if it is in the next col and prints 0 if it doesnt
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
