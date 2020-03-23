#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void intEnter(int* a, int n);
void sortedArr(int* a, int n);
void memoryAllocation(int* a, int n);
void main()
{
	int* arr;
	int size, i,j=0;
	do
	{
		printf("Enter the number of integers: ");
		scanf("%d", &size);
		arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL)
	{
		printf("No memory!");
		exit(1);
	}
	    printf("Enter %d integers: ", size);
	     for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
		//sortedArr(arr,size);
        		for (i = 0; i < size; i++)
			printf("%d ", arr[i]);
		sortedArr(arr, size);


		free(arr);
	} while (size > 0);
	printf("Bye Bye....");

}
void memoryAllocation(int* a, int n)
{
	a = (int*)malloc(n * sizeof(int));
	if (a == NULL)
	{
		printf("No memory!");
		exit(1);
	}
}
void intEnter(int* a, int n)
{
	int i;
	printf("Enter %d integers: ", n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);

}
/*void sortedArr(int *a, int n)
{
	int i;
	int temp;
	min = 0;
	for (i = 0; i < n; i++)
	{
		if (a[i]<min)
			min=a[i];
	}

}*/
void sortedArr(int* a, int n)
{
	int i;
	int temp;
	if (n>0)
    {
    for (i = 1; i < n; i++)
	{
		if (a[i-1] > a[i])
		{
			temp = a[i];
			a[i] = a[i - 1];
			a[i - 1] = temp;
        }
	}
        sortedArr(a, n-1);
    }		
}

