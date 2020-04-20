#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


char change_bit(unsigned char, int size);
void BinPrint(unsigned char ch);
char check_ms(unsigned char);

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

void BinPrint(unsigned char ch)
{
	int i;
	int bit_size = (sizeof(char) * 8 - 1);
	unsigned int mask = 1;
	mask = mask << bit_size;
	while (mask!=0)
	{
		printf("%u", (mask & ch) ? 1 : 0);
		mask = mask >> 1;
	}
}
char check_ms(unsigned char ch)
{
    int mask=1;
    int bit_size = (sizeof(char)*8-1);
    mask = mask<<bit_size;
    ch = ch|mask;
    return ch;
}
char change_bit(unsigned char ch, int size)
{
    int mask=1;
    mask = mask <<size-1;
    ch = ch^mask;
    return ch;
}