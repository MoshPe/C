#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define CRT_SECURE_NO_WARNINGS

void push(node_ID* head);
typedef struct node
	{
		int val;
		struct node* next;

	}
	node_ID;
void push(int a);
void main()
{
	int ID = 0;
	
	node_ID* head = NULL;
	head = malloc(sizeof(node_ID));
	if (head == NULL)
	{
		exit(1);
	}
	printf("Enter Your ID: ");
	scanf_s("%d", &ID);
	int InspectionNum = ID % 10;
	ID = ID / 10;
	head->val = ID % 10;
	int next = push(*head);
	
	
	/*void print_list(node_ID* head);
	{
		node_ID* current = head;
		while (current != NULL) {
			printf("%d\n", current);
			current = current->next;
		}
	}*/



}
void push(node_ID* head)
	{
		while (head->next != NULL)
		{
			node_ID* new_node;
			new_node = malloc(sizeof(node_ID));
			head->next->val = ID % 10;
			//head->next = *head;
			head->next = ID % 10;
			ID = ID / 10;
		}
	}