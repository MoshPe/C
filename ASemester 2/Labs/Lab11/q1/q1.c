#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*free the data allocated for the char,
its a specific function and changes
in different uses like struct which we have more
things to free
*/

void free_char(void* freeMallocked)
{
	free(freeMallocked);
}

int main()
{
	PSTACKNODE stack = NULL;
	char key;
	// for sending the address to the functions
	char* temp;
	puts("Enter characters, separated by space. Press enter to stop\n");
	do
	{
		key = getchar();
		_flushall();
		//we're assuming that the malloc will always work
		temp = (char*)malloc(sizeof(char));
		//keeping the value of the key in the pointer and send it to the functions
		*temp = key;
		push(temp, &stack);
	} while (key != '\n');

	puts("Here are the characters in reverse order:\n");

	while (!isEmpty(stack))
	{
		//*(char) casting beacuse its a specific program
		//char* printChar = top(stack);
		printf("%c", *(char*)top(stack));
		pop(&stack, free_char);
	}
	return 0;
}
