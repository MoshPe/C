#include<stdio.h>
#include<stdlib.h>

#define N 5

typedef struct Item
{
	int num;
	struct Item* next;
}*PItem;

void Error_Msg(char*);
void CreateListFromArray(PItem*,PItem*,int *);
void DeleteList(PItem *);
void ListDisplay(PItem );
int ListLength(PItem);

int main()
{
	int Arr[N]={3,4,1,0,8};

	PItem list=NULL,tail=NULL;

	CreateListFromArray(&list,&tail,Arr);
	printf("The length of the list is %d members\n",ListLength(list));
	printf("\nThe list is:\n");
	ListDisplay(list);
		
	DeleteList(&list);
        tail=NULL;
	return 0;
}

void Error_Msg(char*msg)
{
	printf("\n%s",msg);
	exit(1);
}


void CreateListFromArray(PItem* head,PItem* tail,int *Arr)
{
	int i;
	PItem temp;
	for(i=0;i<N;i++)
	{
		temp=(PItem)malloc(sizeof(struct Item));
		if(temp == NULL)
                {
                  DeleteList(head);
                  Error_Msg("Memmory!");
		}
		temp->num=Arr[i];
		temp->next=NULL;
		if(*head==NULL)
			*head=temp;
		else
			(*tail)->next=temp;
		*tail=temp;
	}
}


void DeleteList(PItem *head)
{
	PItem tmp=*head;
	while(*head)
        {
		tmp=*head;
		*head=(*head)->next;
		free(tmp);
	}
}
int ListLength(PItem L)
{
	return (L->next == NULL)?1:1 + ListLength(L->next);
}
void ListDisplay(PItem L)
{
	if (L == NULL)
	return;
	printf("%d --> ",L->num);
	ListDisplay(L->next);
}