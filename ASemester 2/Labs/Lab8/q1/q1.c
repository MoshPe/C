#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "StackQueue.h"

void main()
{
	Stack Test;
	int arr[NUM + 1] = { 1,2,3,4,5,6 }; //creating an array of numbers for testing
	int del_value, flag, i;
	int size_before;
	Test.size = 0;// init the Stack size before pushing
	for (i = 0; i < NUM + 1; i++)
	{
		size_before = Test.size; // for always check if the push function has pushed the number
		Push(&Test, arr[i]);
		if (Test.size > size_before) // checking which numbers has been inserted and which were not
			printf("\n%d has been inserted ", arr[i]);
		else
			printf("\n%d has NOT been inserted ", arr[i]);
	}
	puts("\n");
	for (i = 0; i < NUM + 1; i++)
	{
		flag = Pop(&Test, &del_value);
		if (flag == 1) // checking if a certain item was removed 
			printf("\n%d has been removed", del_value);
		else
			printf("\nAn element has NOT been removed\n");
	}
	puts("\n");
}