#include<stdio.h>
#include<stdlib.h>
char* LongestWord(char* ch);
void main()
{
	char *a = "ab cdefg a hijj    ";
	a = LongestWord(a);
	while (*a != ' ') {
		printf("%c", *a);
		a++;
	}
}
char* LongestWord(char* ch)
{
	char* p=0;
	int max = 0, count = 0;
	while (*ch != '\0')
	{
		if (*ch >='a'&&*ch<='z')
			count++;
		if (*ch == ' ') {
			if (max < count)
			{
				max = count;
				p = ch - max;
			}
			count = 0;
		}
		ch++;
	}
	//printf("%d", max);
	return p;
}