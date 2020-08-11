#include <stdio.h>
#include <stdlib.h>

int GB(int data, int b);

int main(void)
{
	FILE *fp;
	fp = fopen("file.txt", "rt");
	if (fp == NULL)
		printf("Error!");
	else
	{
		int sob = 0, n = 0, i;
		char tmp[2];
		while (fscanf(fp, "%s", tmp)!=EOF)
		{
			n++;
			for (i = 0; i<8; i++)
				if (GB(atoi(tmp), i))
					sob++;
		}
		if (n != 0)
			printf("%d and %d", sob, 8*n);
	}
	 
	return 0;
}


int GB(int data, int b)
{
	if (data & (1 << b))
		return 1;
	else
		return 0;
}
