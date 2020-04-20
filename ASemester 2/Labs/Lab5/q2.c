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
    scanf("%d",&x);
    printf("There are %d bits equal to one in %d\n", Bit_Count(x),x);
	printf("The binary representation of %d is ",x); 
	Bin_Print(x);
}
int Bit_Count(unsigned int x)
{
	int count = 0;
	int mask = 1;
	unsigned int num = x;
	while (num != 0)
	{
		count += (mask&num) ? 1 : 0;
		num = num >> 1;
	}
	return count;
}
void Bin_Print(unsigned int x)
{
	int i;
	int bit_size = (sizeof(int) * 8 - 1);
	unsigned int mask = 1;
	mask = mask << bit_size;
	while (mask!=0)
	{
		printf("%u", (mask & x) ? 1 : 0);
		mask = mask >> 1;
	}
}