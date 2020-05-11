#include <stdio.h>
#include "StackQueue.h"

void main()
{
	Stack Test;
	int arr[5 + 1] = { 1,2,3,4,5,6 };
	int del_value, flag, i;
	int size_before;
	Test.size = 0;
	for (i = 0; i < 5 + 1; i++)
	{
		size_before = Test.size;
		Push(&Test, arr[i]);
		if (Test.size > size_before)
			printf("\n%d has been inserted ", arr[i]);
		else
			printf("\n%d has NOT been inserted ", arr[i]);
	}
	puts("\n");
	for (i = 0; i < 5 + 1; i++)
	{
		flag = Pop(&Test, &del_value);
		if (flag == 1)
			printf("\n%d has been removed", del_value);
		else
			printf("\nAn element has NOT been removed\n");
	}
	puts("\n");
}
