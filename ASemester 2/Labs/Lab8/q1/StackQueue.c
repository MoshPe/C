#include"StackQueue.h"
#include<stdio.h>
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
/*
Function name: Push
Input: Getting the stack and new value to enter the stack
*/
void Push(PStack s, int   new_elem)    
{
    Item* temp;
    int count=0;
   if(s->size < NUM) // chekcing if the stack's number of items exceeds the NUM limit which has been defined in the header
     {
        temp = (Item*)malloc(sizeof(Item));
            if (temp==NULL)
            {
                Error_Msg("Couldnt allocate Memory");
                DeleteList(s);
            }
            temp->num = new_elem;
            temp->next = s->head; //adding the new items temp from the head
            s->head = temp;
            s->size++; //increasing the amount of items in the stack
     }
     else
        printf("\n\nThe stack is full\n\n");
}
//deletes the entire list(free them All)
void DeleteList(PStack s)
{
	Item* temp;
	while (s->head != NULL)
	{
		temp = s->head;
		s->head = s->head->next;
		free(temp);
	}
	s->size = 0;
}
/*
Function name: Pop
Input: Getting the stack and the deleted valude pointer to return the pop
Output: returning the value of the poped item in the del_value pointer and return 1 if pop
		has succeeded, 0 if it did not.
Algoritem: extracting the item from out the head of the list,the head of the stack,
           putting his value in del_value, than free the item and decreasing the stack size by 1
*/
int Pop(PStack s, int * del_value)       
{
   Item* temp;
	
   if (s->size > 0) // checking if the stack is empty
   {
	   temp = s->head;              
	   s->head = temp->next;
	   *del_value = temp->num;
	   free(temp);
	   s->size--;
	   return 1;
   }
   else
	   printf("\n\nThe stack is empty\n\n");
    return 0;
}