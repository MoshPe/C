#include <stdio.h>
#include <stdlib.h>



//TODO Change to ADT file
typedef struct node
{
    char data;                        /* Store the keystroke by the user */
    struct node *next;                /* Pointer to the next node */
} STACKNODE;

void push(char key, STACKNODE **stack);
void pop(STACKNODE **stack);
int isempty(STACKNODE *stack);
char top(STACKNODE *stack);

int main()
{
    STACKNODE *stack = NULL;
    char key;
     puts("Enter characters, separated by space. Press enter to stop\n");
    do
    {
	   key = getchar();
	   _flushall();
	   push(key, &stack);
    } while (key != '\n');

    puts("Here are the characters in reverse order:\n");

    while (!isempty(stack))
    {
	  printf(" %c ",top(stack));
          pop(&stack);
    }
      
   return 0;
}

char top(STACKNODE *stack)
{
    return stack->data;
}



void push(char key, STACKNODE **stack)
{
    STACKNODE *newnode;
    newnode=(STACKNODE *)malloc(sizeof(STACKNODE));
    newnode->data = key;
    newnode->next = (*stack);
    (*stack) = newnode;
}

void pop(STACKNODE **stack)
{
    STACKNODE *oldnode;
    oldnode = (*stack);
    (*stack) = (*stack)->next;
    free(oldnode);
}

int isempty(STACKNODE *stack)
{
    return (stack==NULL);
}

