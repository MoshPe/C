#include "Stack_Header_Array.h"
#include <stdio.h>
#include <stdlib.h>

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
/*
Function name: InitStack
Input: Getting the stack and the stack size
*/
void InitStack(PStack s, int size)//initialization of a new stack with capacity of size elements
{
	s->size = size;
	s->Array = (int*)malloc(size * sizeof(int));
	if (s->Array == NULL)
		Error_Msg("Couldn't allocate memory");
	s->top = 0; //initialize the top index of the stack
	s->count = 0; //initialize the the amount of items in the stack
}
/*
Function name: Push
Input: Getting the stack and new value to enter the stack
*/
void Push(PStack s, int new_elem)  //add a new member to array of the stack 
{
	if (s->count < s->size) //checking the amount of the existing items in the stack in comparison to the stack size
	{
		s->Array[s->count] = new_elem;
		s->count++;
		s->top = s->count - 1;
	}
	else // means the stack if stack is full and no more room to enter
		printf("\n\nThe stack is full\n");
}
/*
Function name: Pop
Input: Getting the stack and the deleted valude pointer to return the pop
Output: returning the value of the poped item in the del_value pointer and return 1 if pop
		has succeeded, 0 if it did not.
*/
int Pop(PStack s, int* del_value) //delete member from the array of the stack and  return the deleted value  using  int * del_value
{
	if (s->count > 1) // checking if the stack has more than one item
	{
		*del_value = s->Array[s->top];//using s->top value as index of the top item in the stack
		s->top--;//decreasing the higher item index
		s->count--;//decreasing the number of items in the stack
	}
	else if (s->count == 1) // checking if there is only one item in the stack so we return this item
	{
		*del_value = s->Array[s->top];//using s->top value as index of the top item in the stack
		s->count--;
	}
	else // in case the stack is empty,also returns 0
	{
		printf("\nThe stack is empty,nothing to pop!!\n");
		return 0;
	}

	return 1;
}