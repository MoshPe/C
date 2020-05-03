#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct node
{
	char code[11];
	char *name;
	char Dep[4];
	int marks[3];
	float avg;
	struct node* next;
}std;

void Error_Msg(char* str);
std* FromFileToList(std* head,FILE *in);
std* Delete_Stud(std* toDel,std* head);
std* DeleteList(std* head);
void PrintList(std* head);
std* FindMax(std* head);
void FreeThemAll(std* head);
void CheckStrings(char* s, unsigned int size, char* name);

int main()
{
	int i;
	FILE *f;
	std *Head=NULL, *temp;
	if((f=fopen("List.txt","rt")) == NULL)
           Error_Msg("input error");
	Head=FromFileToList(Head,f);

	printf("\nThe list is:");
	PrintList(Head);
	
	temp = FindMax(Head);
        printf("\n\nthe student with max average:\n");
	printf("%s %s %s ",temp->code,temp->name,temp->Dep);
        for(i=0;i<3;i++)
          printf(" %d ",temp->marks[i]);

	printf("\n\nThe list after change:");
	Head=Delete_Stud(FindMax(Head),Head);
	PrintList(Head);
	Head = DeleteList(Head);
        return 0;
}
std* FromFileToList(std* head,FILE *in)
{
    char name[MAX];
    std temp;
    int i;
    while (fscanf(in,"%s%s%s%d%d%d",temp.code,name,temp.Dep,&temp.marks[0],&temp.marks[1],&temp.marks[2])!=EOF)
    {
      CheckStrings(name,256,"name");
      std* ptr= (std*)malloc(sizeof(std));
      if (ptr == NULL)
      {
        FreeThemAll(head);
        Error_Msg("Memory allocation error\n");
      }
      temp.name = (char*)malloc((strlen(name)+1)*sizeof(char));
      if (temp.name == NULL)
      {
          ////////////////////////////////////////free check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        FreeThemAll(head);
        Error_Msg("Memory allocation error\n");
      }
      temp.avg = (temp.marks[0] + temp.marks[1] + temp.marks[2])/3.0f;
      ptr = &temp;
      ptr->next=head;
      head=ptr;
    }
    return head;
}
std* FindMax(std* head)
{
    std* temp = head, * max=head;
    while (temp->next!= NULL)
    {
        temp = temp->next;
        if (temp->avg > max->avg)
            max = temp;
    }
    return max;
}

void Error_Msg(char* str)
{
	printf("\n%s",str);
    exit(1);
}
std* DeleteList(std* head)
{
    std* temp;
    while (head != NULL)
    {
        temp = head;
        head = head -> next;
        free(temp->name);
        free(temp);
    }
    return head;
}
std* Delete_Stud(std* toDel,std* head)
{
    std* temp = head;
    if(head == NULL)
        return NULL;

    if(toDel==temp)
    {
        temp = temp ->next;
        free(toDel->name);
        free(toDel);
    }
    else
    {
        while (temp != NULL && temp->next != toDel)
        temp = temp->next;
        //delete toDel node
        if(temp != NULL && temp->next == toDel)
        {
        temp -> next = toDel -> next;
        free(toDel->name);
        free(toDel);
        }
    }
  return head;
}
void CheckStrings(char* s, unsigned int size, char* name)
{
	while (strlen(s) > size)
	{
		printf("\ninvalid %s!-the %s is too long,please try again\n", name, name);
		printf("Please enter the %s again (max %d): \n", name, size);
		rewind(stdin);
		scanf("%s",s);
	}
}
void FreeThemAll(std* head)
{
   std *temp = head;
    while(head != NULL){
        temp = head;
        head = head ->next;
        free(temp->name);
        free(temp);
	} 
}
void PrintList(std* head)
{
    std* temp = head;
    while(temp != NULL){
		printf("%s %s %s %d %d %d \n ",temp->code,temp->name,temp->Dep,temp->marks[0],temp->marks[1],temp->marks[2]);
        temp = temp->next;
	}
}