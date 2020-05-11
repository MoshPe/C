#include"Queue.h"
#include<stdio.h>
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}

void Enqueue(PQue Q, int   new_elem) //add a new member to list of the queue  
{
	Item* temp;
	if (Q->size < NUM)
	{
		temp = (Item*)malloc(sizeof(Item));
		if (temp == NULL)
		{
			Error_Msg("Couldnt allocate Memory");
			DeleteList(Q);
		}
		temp->num = new_elem;
		if (Q->size == 0)
		{
			Q->head = temp;
			Q->tail = temp;
		}
		Q->tail->next = temp;
		Q->tail = temp;
		Q->size++;
	}
	else
		printf("\n\nThe queue is full\n\n");
}
void DeleteList(PQue Q)
{
	Item* temp;
	while (Q->head != NULL)
	{
		temp = Q->head;
		Q->head = Q->head->next;
		free(temp);
	}
	Q->size = 0;
}
int Dequeue(PQue Q, int* del_value)//delete member from the queue and  return the deleted value  using int *del_value       
{
	Item* temp;
	if (Q->size > 0)
	{
		temp = Q->head;
		Q->head = temp->next;
		*del_value = temp->num;
		free(temp);
		Q->size--;
		return 1;
	}
	else
		printf("\n\nThe queue is empty\n\n");
	return 0;
}