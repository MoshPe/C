#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define N 4
void main()
{
	int num;
	int square;
	int cube;
	int array[N];
	printf("Enter Number: ");
	scanf("%d", &num);
	printf("Number    Square     Cube\n");
	printf("%4d%10d%11d\n", num, num * num, num * num * num);
	for (int i = 0; i < N; i++)
	{
		//num1=num;
		array[i] = num + 1;
		square = array[i] * array[i];
		cube = array[i] * array[i]*array[i];
		printf("%4d%10d%11d\n", array[i],square, cube);
		num=num +1;
		
	}

}