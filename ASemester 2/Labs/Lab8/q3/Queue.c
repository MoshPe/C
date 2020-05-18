#include"Queue.h"
#include<stdio.h>
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
/*
Function name: Enqueue
Input: Getting the queue and new value to enter the stack
*/
void Enqueue(PQue Q, int   new_elem) //add a new member to list of the queue  
{
	Item* temp;
	if (Q->size < NUM) // chekcing if the queue's number of items exceeds the NUM limit which has been defined in the header
	{
		temp = (Item*)malloc(sizeof(Item));
		if (temp == NULL)
		{
			Error_Msg("Couldnt allocate Memory");
			DeleteList(Q);
		}
		temp->num = new_elem;
		if (Q->size == 0) // checking if its the first time to be inserted
		{
			Q->head = temp;
			Q->tail = temp;
		}
		Q->tail->next = temp; //adding the new items temp from the tail
		Q->tail = temp;
		Q->size++;			  //increasing the amount of items in the queue
	}
	else
		printf("\n\nThe queue is full\n\n");
}
//deletes the entire list(free them All)
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
	Q->tail = NULL;
}
/*
Function name: Dequeue
Input: Getting the queue and the deleted valude pointer to return the pop
Output: returning the value of the dequeued item in the del_value pointer and return 1 if pop
		has succeeded, 0 if it did not.
Algoritem: extracting the item from out the head of the list,the head of the stack,
           putting his value in del_value, than free the item and decreasing the stack size by 1
*/
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