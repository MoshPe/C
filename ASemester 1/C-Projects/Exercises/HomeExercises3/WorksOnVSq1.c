#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void strCompress(char* str, char* dest);
int destLength(char* str);
void strRestore(char* compressed, char* dest);
int restoredLength(char* compressed);
void main()
{
	char str[100];
	char* dest;
	char* compressed;
	int i, num, strlen1;
	printf("Enter string to compress:\n");
	gets(str);
	strlen1 = destLength(str);
	dest = (char*)malloc((strlen1) * sizeof(char));
	if (dest == NULL)
	{
		printf("Not enough memory\n");
		free(dest);
		exit(1);
	}
	else
	{
		strCompress(str, dest);
		printf("Compressed string length is: %d\n", destLength(str));
		printf("Compressed string is:");
		num = destLength(str);
		for (i = 0; i < num; i += 2)
			printf("%c%d", dest[i], dest[i + 1]);
		compressed = (char*)malloc((strlen1)*sizeof(char));
		strcpy(compressed,dest);
		printf("\nRestored string length is: %d\n", restoredLength(compressed));
		dest = (char*)realloc(NULL, (strlen(str)*sizeof(char)));
		if (dest == NULL)
		{
			free(dest);
			exit(1);
		}
	}
	printf("Restored string is:");
	strRestore(compressed, dest);
	num = strlen(str);
	for (i = 0; i < num; i++)
		printf("%c",dest[i]);
	free(compressed);
	free(dest);

}
void strCompress(char* str, char* dest)
{
	int i, j = 0, count = 1, k = 0, num;
	num = strlen(str);
	for (i = 0; i < num; i++)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] == str[i + 1])
			{
				count++;
				dest[k] = str[i];
				dest[k + 1] = count;
			}
			else
			{
				dest[k] = str[i];
				dest[k + 1] = count;
				count = 1;
				k = k + 2;
			}
		}
	}
}
int destLength(char* str)
{
	int i, j = 0, destLen = 0, num;
	num = strlen(str);
	for (i = 0; i < num; i++)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] != str[i + 1])
				destLen += 2;
		}
	}
	return destLen;
}
void strRestore(char* compressed, char* dest)
{
	int i, j = 0, num, num1 = 0, num3;
	num3 = strlen(compressed);
	for (i = 0; i < num3; i = i + 2)
	{
		num = (int)compressed[i + 1];
		for (; j < num + num1; j++)
			dest[j] = compressed[i];
		num1 = j;
	}
}
int restoredLength(char* compressed)
{
	int i = 1, sum = 0, num = 0;
	while ((int)compressed[i] > 0)
	{
		if (compressed[i] == '\0')
			break;
		sum = sum + compressed[i];
		i += 2;
	}
	return sum;
}
