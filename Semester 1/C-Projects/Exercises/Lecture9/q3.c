#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
void replaceSubstring(char* str, char* substr);
#define N 100
void main()
{
	int i, length, j, counter = 1;
	char ar[N], SubAr[N];
	do 
	{
	printf("Enter text: ");
	gets(ar);
	if (ar[0]==0)
		break;
	printf("Enter substring: ");
	gets(SubAr);
	if (SubAr[0]==0)
		break;
	replaceSubstring(ar, SubAr);
	puts(ar);
	} while (ar[0]&&SubAr[0]);
	printf("Finish!\n");
}
void replaceSubstring(char* str, char* substr)
{
	int i, j, length, counter = 1,k;
	length = strlen(substr);
	for (i = 0; str[i]; i++)
	{
		if (str[i] == substr[0])
		{
			for (j = 1; j < length && str[i + j]; j++)
			{
				if (str[i + j] == substr[j])
					counter++;
			}
			if (counter == length)
				for (k = 0; k < length; k++)
				{
					if(str[i+k]>=97)
						str[i + k] = str[i + k] - 32;
				}
			counter = 1;
		}
	}
}
