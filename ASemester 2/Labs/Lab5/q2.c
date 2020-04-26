#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Bit_Count(unsigned int x);
void Bin_Print(unsigned int x);
void main()
{
	unsigned int x;
	printf("Enter a number: ");
	scanf("%d", &x);
	printf("There are %d bits equal to one in %d\n", Bit_Count(x), x);
	printf("The binary representation of %d is ", x);
	Bin_Print(x);
}
/*
Function name: Bin_Count
Input: Getting the integer that the user input
Output: returns number of times that a bit is "on"/"1"
Algoritem: using a mask and the bitwise action AND, it checks
			if the resoult it 1 and counts it, after it
			it shifts num one time to the right
*/
int Bit_Count(unsigned int x)
{
	int count = 0;
	unsigned int mask = 1;
	unsigned int num = x;
	while (num != 0)
	{
		count += mask & num;
		num = num >> 1;
	}
	return count;
}
/*
Function name: Bin_Print
Input: Getting the integer that the user input
Output: prints the binary form of the given char
Algoritem: using a mask the function move left the
		   the first bit to the msb location, using
		   the bitwise action AND, and it prints the
		   resoult
*/
void Bin_Print(unsigned int x)
{
	int i;
	int bit_size = (sizeof(int) * 8 - 1);
	unsigned int mask = 1;
	mask = mask << bit_size;
	while (mask != 0)
	{
		printf("%d", ((mask & x)!=0)?1:0);
		mask = mask >> 1;
	}
}



