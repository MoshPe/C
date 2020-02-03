#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cntMaxSub(char* s, char* pref);
void main()
{
	char s[] = { "uabacad" };
	char sub[] = { "abcdefg" };
	printf("Amount of alike chars %d", cntMaxSub(s, pref));
}
int cntMaxSub(char* s, char* sub)
{
	int max1 = 0,j=0,i;
	int max2 = 0;
	for (i = 0; i < (strlen(s) - 1); i++)
	{
		if (s[i] == sub[j])
		{
			max1++;
			j++;
		}
		else
		{
			max1 = 0;
			j = 0;
		}

		if (max2 < max1)
		{
			max2 = max1;
		}
	}

	return max2;
}
	
