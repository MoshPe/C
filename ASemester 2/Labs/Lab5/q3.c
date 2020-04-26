#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


unsigned char change_bit(unsigned char, int size);
void BinPrint(unsigned char ch);
unsigned char check_ms(unsigned char);

void main()
{
	unsigned char num1 = 102,num2 = 58;
	int n;

	printf("\nThe first part :");
	printf("\nThe number is %d   ", num1);
	BinPrint(num1);
	num1 = check_ms(num1);
	printf ("\nThe new number is: %d   ", num1);
	BinPrint(num1);

	printf("\n\nThe second part :");
	printf("\nThe number is %d   ", num2);
	BinPrint(num2);
	printf ("\nEnter a number of the bit to change(1-8)");
	scanf ("%d",&n);
	num2 = change_bit(num2, n);
	printf ("\nThe new number is: %d   ", num2);
	BinPrint(num2);     /*Binary representation of number*/

}


/*
Function name: BinPrint
Input: Getting the char that the user input
Output: prints the binary form of the given char
Algoritem: using a mask the function move left the 
		   the first bit to the msb location, using 
		   the bitwise action AND, and it prints the 
		   resoult
*/
void BinPrint(unsigned char ch)
{
	int i;
	int bit_size = (sizeof(char) * 8 - 1);
	unsigned char mask = 1;
	mask = mask << bit_size;
	while (mask!=0)
	{
		printf("%u", (mask & ch) ? 1 : 0);
		mask = mask >> 1;
	}
}
/*
Function name: check_ms
Input: Getting the char that the user input
Output: return the char after checking and changing the MSB bit to 1
Algoritem: using a mask the function move left the 
		   the first bit to the msb location, using 
		   the bitwise action OR, and it returns the 
		   resoult
*/
unsigned char check_ms(unsigned char ch)
{
    unsigned char mask=1;
    int bit_size = (sizeof(char)*8-1);
    mask = mask<<bit_size;
    if ((mask & ch )== 0)//checking if msb equal to 0
		ch = ch|mask;//change the bit to 1
    return ch;
}
/*
Function name: change_bit
Input: Getting the char that the user input and the bit location
Output: return the char after checking and changing the MSB bit to 1
Algoritem: using a mask the function move left the 
		   the first bit the amount of time given by size
		   and use a bitwise action XOR to change the bit
*/
unsigned char change_bit(unsigned char ch, int size)
{
    unsigned char mask=1;
    mask = mask << 8-size;
    ch = ch^mask;
    return ch;
}