#include "stack.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	void* data; /* Store the keystroke by the user */
	struct node* next; /* Pointer to the next node */
}STACKNODE;

void* top(PSTACKNODE stack)
{
	return stack->data;
}
//creating a new node and put it in the top of the stack
void push(void* key, PSTACKNODE* stack)
{
	PSTACKNODE newNode;
	newNode = (PSTACKNODE)malloc(sizeof(STACKNODE));
	newNode->data = key;
	newNode->next = (*stack);
	(*stack) = newNode;
}
//pop the top item from the stack and free it's place
void pop(PSTACKNODE* stack, void (*free_func)(void*))
{
	PSTACKNODE oldnode;
	oldnode = (*stack);
	(*stack) = (*stack)->next;
	free_func(oldnode->data);
	free(oldnode);
}
//check if the stack is empty
int isEmpty(PSTACKNODE stack)
{
	return (stack == NULL);
}
