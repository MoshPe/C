#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
char* addStrings(char* str1, char* str2);
void replaceString(char* buff);
void main()
{
	char s1[] = "989909", s2[] = "998", * sx;
	char s3[] = "", s4[] = "1";
	char s5[] = "900262188172", s6[] = "199025514231";
	sx = addStrings(s1, s2);
    printf("%s + %s = %s", s1, s2, sx); 
    free(sx);
	sx = addStrings(s3, s4); 
    printf("%s + %s = %s", s3, s4, sx); 
    free(sx);
	sx = addStrings(s5, s6); 
    printf("%s + %s = %s", s5, s6, sx); 
    free(sx);
	_getch();
}
char* addStrings(char* str1, char* str2)
{
	char* sum = {0};
	if (strlen(str1) > strlen(str2))
		addStrings(str1 + 1, str2);
	if (strlen(str1) < strlen(str2))
		addStrings(str1, str2 + 1);
	if ((strlen(str1) == strlen(str2)) && (*str1 != '\0'))
		addStrings(str1 + 1, str2 + 1);
	if (strlen(str1) == 0 && strlen(str2) == 0)
	{
		sum = (char*)malloc((strlen(str1) + strlen(str2)) * sizeof(char));
		return (char*)sum;
	}
	sum = (char*)realloc(sum, (strlen(str1) + strlen(str2)) * sizeof(char));
	if ((int)*str1 + (int)*str2 <= 9)
		*sum = ((int)*str1 + (int)*str2)+48;
	else
	{
		*sum = (((int)*str1 + (int)*str2) % 10)+48;
		*(sum + 1) = (((int)*str1 + (int)*str2) / 10)+48;
	}
	if (strlen(str2) + strlen(str1) == strlen(sum))
		replaceString(sum);
	return (char*)sum;
}
void replaceString(char* buff)
{
	int temp;
	if (*buff == 0 || *(buff + 1) == 0)
		return;
	temp = *(buff + 1);
	*(buff + 1) = *buff;
	*buff = temp;
	replaceString(buff + 1);
}