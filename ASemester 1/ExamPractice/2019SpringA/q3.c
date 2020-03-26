#include<stdio.h>
#include<stdlib.h>
long int LargestNum(char** mat, int rows, int cols);

void main()
{
	char s[4][5] = { {'7','X','*','#','a'},{'1','T','P','X','#'},{'#','M','5','@','2'},{'@','*','k','2','b'} };
	char* mat[5] = { s[0],s[1],s[2],s[3],s[4] };
	printf("The largest num is %d ", LargestNum(mat, 4, 5));
}
long int LargestNum(char** mat, int rows, int cols)
{
	int a[10] = { 0 };
	int i, j, num=0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (mat[i][j] <= '9' && mat[i][j] >= '0')
				a[(int)mat[i][j] - '0']++;
		}
	}

	for (i = 9; i >= 0; i--)
	{
		if (a[i] == 1)
			num = num * 10 + i;
		if(a[i] > 1)
			while (a[i]!=0)
			{
				num = num * 10 + i;
				a[i]--;
			}
			
	}
	return num;
}







