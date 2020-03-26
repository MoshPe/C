#include<stdio.h>
#include<stdlib.h>
#include<math.h>
char* chLoc(char* st, int n, char ch);
int letRec(char* st, int n);
void main()
{
	char* ch = "bbbcccccdgggkkkkkmmmmmz";
	char c = 'k';
	printf("|%c|", *chLoc(ch, 23, c));
	printf(",,,%d", letRec(ch, 23));
}
char* chLoc(char* st, int n, char ch)
{
	//char* p = 0;
	int b = 0;
	int i = 0;
	while (n >= i)
	{
		b = (i + n) / 2;
		if (ch < st[b])
			n = b - 1;
		else
			if (ch > st[b])
				i = b + 1;
			else
				if (st[b] == st[b - 1])
					n = b - 1;
				else
					return &st[b];
	}
	return NULL;
}

int letRec(char* st, int n)
{
	if (n == 0)
		return 0;
	if (*st!=*(st+1))
	{
		printf("%c", *st);
		return 1 + letRec(st + 1, n - 1);
	}
	return 0+ letRec(st + 1, n - 1);
}