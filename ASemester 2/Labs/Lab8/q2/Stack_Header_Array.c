#include "hello.h"
#include <stdio.h>
#include <stdlib.h>

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}

void InitStack(PStack s, int size)    //initialization of a new stack with capacity of size elements
{
	s->size = size;
	s->Array = (int*)malloc(size * sizeof(int));
	if (s->Array == NULL)
		Error_Msg("Couldn't allocate memory");
	s->top = 0;
	s->count = 0;
}

void Push(PStack s, int new_elem)  //add a new member to array of the stack 
{
	if (s->count < s->size)
	{
		s->Array[s->count] = new_elem;
		s->count++;
		s->top = s->count - 1;
	}
	else
		printf("\n\nThe stack is full\n");
}

int Pop(PStack s, int* del_value) //delete member from the array of the stack and  return the deleted value  using  int * del_value
{
	if (s->count > 1)
	{
		*del_value = s->Array[s->top];
		s->top--;
		s->count--;
	}
	else if (s->count == 1)
	{
		*del_value = s->Array[s->top];
		s->count--;
	}
	else
	{
		printf("\nThe stack is empty,nothing to pop!!\n");
		return 0;
	}

	return 1;
}