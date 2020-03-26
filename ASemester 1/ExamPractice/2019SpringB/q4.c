#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void inAllRows(int **mat, int rows, int cols);
void main() {
	int i, j;
	int s[7][6] = { {7,1,3,0,4,6},{2,5,0,6,6,1},{6,1,7,2,4,0},{1,1,7,6,8,9},{5,5,6,1,5,3},{4,1,4,3,6,0},{4,6,1,7,4,3} };
	int *mat[7]={s[0],s[1],s[2],s[3],s[4],s[5],s[6]};
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 6; j++)
			printf("%7d", s[i][j]);
		printf("\n");
	}
	inAllRows(mat, 7, 6);
}
void inAllRows(int **mat, int rows, int cols)
{
	int i, j, max = 0, flag = 0;
	int a[10] = { 0 };
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++) {
			if (a[mat[i][j]]==i)
				a[mat[i][j]]++;
		}
	}

	for (i = 0; i < 10; i++)
	{
		if (a[i] == rows) {
			flag++;
			if (flag == 1)
				printf("\nCommon element(s): ");
			printf(" %d ", i);
		}
	}
	if (flag == 0)
		printf("No common elements");
}