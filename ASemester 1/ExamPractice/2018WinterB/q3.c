#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int inxedRow(int** mat, int rows, int cols);
void main()
{
	int mat[5][6] = { {0,0,0,1,1,1},{0,0,1,1,1,1},{0,1,1,1,1,1},{0,0,0,0,0,0},{0,0,1,1,1,1} };
	int* m[5] = { mat[0],mat[1],mat[2],mat[3],mat[4] };
	printf("%d", inxedRow(m, 5, 6));
	//printf("\n%d", Max_1(m, 5, 6));
	//int s[7][6] = { {7,1,3,0,4,6},{2,5,0,6,6,1},{6,1,7,2,4,0},{1,1,7,6,8,9},{5,5,6,1,5,3},{4,1,4,3,6,0},{4,6,1,7,4,3} };
	//int *mat[7]={s[0],s[1],s[2],s[3],s[4],s[5],s[6]};

}
int inxedRow(int** mat, int rows, int cols)
{
	int i, j, max = 0, count = 0,index=0;
	for (i = 0; i < rows; i++)
	{
		j = cols-1;
		while (mat[i][j] != 0)
		{
				count++;
				j = abs(j / 2);
		}
		if (count > max) {
			max = count;
			index = i;
		}
		count = 0;
	}
	return index;
}
