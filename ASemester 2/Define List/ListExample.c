#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 10
#define N 5

typedef struct item
{
   int code;
   char name[NAME+1];
   struct item *next;
}Item;

int main()
{
	int i;
	Item *Head=NULL, *temp;
	//creating the list
    for(i=1;i<=N;i++)
    {		
        temp = (Item*)malloc(sizeof(Item));
        if (temp == NULL)
        {
            //free all the previous nodes if exist
            while (Head != NULL)
            {
                temp = Head;
                Head = Head->next;
                free(temp);
            }
            printf("Memory allocation error!!!\n");
            exit(1);
        }
        temp ->next=Head;
        Head = temp;
        //getting input data from the user
        printf("Enter a new code and name: ");
        scanf("%d%s",&Head->code,Head->name);
        rewind(stdin);
	}
	printf("\n\nThe List is:  ");
	//printing all the list from last to first
    temp = Head;
    while(temp != NULL){
		printf("%d %s --> ",temp->code,temp->name);
        temp = temp->next;
	}
    //deleting all the list
    temp = Head;
    while(Head != NULL){
        temp = Head;
        Head = Head ->next;
        free(temp);
	}
        return 0;
}