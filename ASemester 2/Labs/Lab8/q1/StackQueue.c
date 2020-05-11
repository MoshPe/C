#include"StackQueue.h"
#include<stdio.h>
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
void Push(PStack s, int   new_elem)    
{
    Item* temp;
    int count=0;
   if(s->size<NUM)
     {
        temp = (Item*)malloc(sizeof(Item));
            if (temp==NULL)
            {
                Error_Msg("Couldnt allocate Memory");
                DeleteList(s);
            }
            temp->num = new_elem;
            temp->next = s->head;
            s->head = temp;
            s->size++;
     }
     else
        printf("\n\nThe stack is full\n\n");
}
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
int Pop(PStack s, int * del_value)       
{
   Item* temp;
	
   if (s->size > 0)
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