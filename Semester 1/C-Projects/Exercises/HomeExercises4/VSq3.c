#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int baseToInt(char* str, int base);
int powst(int m, int n);
int countstr(char* str);
void intToBase(int val, char* buff, int base);
void replaceCh(char* buff);
void reset_Ar(char* buff);
void main()
{
	int base1;
	char str[32] = { 0 };
	char buff[32] = { '\0' };
	printf("*************************************************************************\n");
	printf("Select input format (2-binary, 8-octal, 10-decimal, 16-hexadecimal, 0-exit): ");
	rewind(stdin);
	scanf_s("%d", &base1);
	do 
	{
		rewind(stdin);
		printf("Enter value in the specified format: ");
		gets_s(str,32);
		printf("Entered value is %d ",baseToInt(str,base1));
		intToBase(baseToInt(str, base1), buff, 2);
		printf("\n\nBinary form: %s\n",buff);
		intToBase(baseToInt(str, base1), buff, 8);
		printf("Octal form: %s\n",buff);
		intToBase(baseToInt(str, base1), buff, 10);
		printf("Decimal form: %s\n",buff);
		intToBase(baseToInt(str, base1), buff, 16);
		printf("Hexadecimal form: %s\n",buff);
		printf("\n*************************************************************************");
		printf("\nSelect input format (2-binary, 8-octal, 10-decimal, 16-hexadecimal, 0-exit): ");
		scanf_s("%d", &base1);
	} while (base1 != 0);
	printf("\nFINISH");
}
int baseToInt(char* str, int base)
{
	int strlen;
	if (*str == '\0')
		return 0;
	strlen = countstr(str);
	return ((*str<58)?(*str)-48:(*str)-55) * powst(base, strlen-1) + baseToInt(str + 1, base);
}
int countstr(char* str)
{
	return (*str != '\0') ? 1 + countstr(str + 1) : 0;
}
int powst(int m, int n)
{
	return n != 0 ? m * (powst(m, n - 1)) : 1;

}
void intToBase(int val, char* buff, int base)
{
	reset_Ar(buff);
	if (val == 0)
		return;
	*buff = (val % base > 9) ? val % base + 55 : val % base+48;
	intToBase(val / base, buff+1, base);
	replaceCh(buff);
}
void replaceCh(char* buff)
{
	int temp;
	if (*buff == 0||*(buff+1)==0)
		return;
		temp = *(buff+1);
		*(buff+1) = *buff;
		*buff = temp;
		replaceCh(buff + 1);
}
void reset_Ar(char* buff)
{
	if (*buff == '\0')
	{
		return;
	}
	*buff = '\0';
	reset_Ar(buff + 1);
}
