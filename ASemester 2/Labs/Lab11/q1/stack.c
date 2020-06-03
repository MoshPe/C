
#include "stack.h"

typedef struct node
{
	void* data; /* Store the keystroke by the user */
	struct node* next; /* Pointer to the next node */
}STACKNODE;


void* top(PSTACKNODE stack)
{
	return stack->data;
}

void push(void* key, PSTACKNODE* stack)
{
	PSTACKNODE newNode;
	newNode = (PSTACKNODE)malloc(sizeof(STACKNODE));
	newNode->data = key;
	newNode->next = (*stack);
	(*stack) = newNode;
}

void pop(PSTACKNODE* stack, void (*free_func)(void*))
{
	PSTACKNODE oldnode;
	oldnode = (*stack);
	(*stack) = (*stack)->next;
	free_func(oldnode->data);
	free(oldnode);
}

int isEmpty(PSTACKNODE stack)
{
	return (stack == NULL);
}