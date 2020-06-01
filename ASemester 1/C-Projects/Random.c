#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

#define max 500
int main()
{
	int *arr;
	arr = (int*)malloc(0*sizeof(int));
	if (arr == NULL)
		printf("Problem");
	return 0;

}
