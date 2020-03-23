#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
void inputRanNum(int arr[], int n, int a);
void inputNum(int arr[], int n);
int is_in(int arr[], int n, int a);
void putinArr3(int arr3[], int arr[], int arr1[], int n,int *p);
void printArr(int arr[], int n);
void printArr3(int arr[],int n);
#define N 7
void main()
{
	int arr1[N] = { 0 }, arr2[N] = { 0 }, arr3[N];
	int maxValue,num=0,*p;
	p = &num;
	inputNum(arr1, N);
	printf("Enter max value greater than zero: ");
	scanf("%d", &maxValue);
	while (maxValue <= 0)
	{
		printf("Error input!");
		printf("Enter max value greater than zero : ");
		scanf("%d", &maxValue);
	}
	inputRanNum(arr2,N,maxValue);
	putinArr3(arr3, arr2, arr1, N,p);
	printf("\nArray3: ");
	printArr3(arr3,num);
	printf("\nArray2: ");
	printArr(arr2,N);
	printf("\nArray1: ");
	printArr(arr1,N);
	puts("\n");
}
void inputRanNum(int arr[], int n, int a)
{
	srand(time(NULL));
	int i;
	for (i = 0; i < n; i++)
		arr[i] = (rand()%a);
}
void inputNum(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("Enter arr[%d]: ", i);
		scanf("%d", &arr[i]);
	}
}
void putinArr3(int arr3[],int arr[], int arr1[], int n,int *p)
{
	int i, j, k = 0, num, count=0;
	for (i = 0; i <n; i++)
	{
		for ( j = 0; j < n; j++)
		{
			if (arr1[i] != arr[j]) 
				count=count +1;
		}
		if (count == n)
		{
			num = arr1[i];
			if (is_in(arr3, num, n) == 1)
			{
				arr3[k] = num;
				k++;
				*p=*p+1;
			}
		}
		count = 0;
	}
}
int is_in(int arr[], int n, int a)
{
	int i, count = 1;
	for (i = 0; i < a; i++)
	{
		if (arr[i] == n)
		{
			count = 0;
			break;
		}
	}
	return count;
}
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
}
void printArr3(int arr[], int n)
{
	int i;
	if (n > 0)
	{
		for (i = 0; i < n; i++)
			printf("%d ", arr[i]);
	}
	else
		printf("The array 1 and array 2 are alike");
}
