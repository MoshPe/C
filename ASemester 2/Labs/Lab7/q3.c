#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
	int num;
	float price;
	struct Item* next;
}*PItem;

void Error_Msg(char*);
void AddNewItem(PItem*, PItem*, int, int, float);
void CreateList(PItem*, PItem*, FILE*);
void PrintItem(PItem);
void PrintList(PItem, char*);
void WriteListToFile(PItem, FILE*);
void DeleteList(PItem*);

int main()
{
	int a, n;
	float b;
	PItem head = NULL, tail = NULL;
	FILE* in = fopen("input_price.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	CreateList(&head, &tail, in);
	PrintList(head, "\nThe Old List:\n");
	printf("\n\nEnter a number and the price\n");
	scanf("%d%f", &a, &b);
	printf("\nEnter a place for the new item:");
	scanf("%d", &n);
	do
	{
		if(n<1)
		{
			printf("\nplace for the new item is wrong,please try again:\n");
			scanf("%d", &n);
		}
		else if (n>=1)
			AddNewItem(&head, &tail, n, a, b);
	}
	while (n < 1);
	PrintList(head, "\nThe New List:\n");
	fclose(in);
	WriteListToFile(head, in);
	fclose(in);
	DeleteList(&head);
	tail = NULL;
	return 0;
}


void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}


void CreateList(PItem* head, PItem* tail, FILE* f)
{
	int a;
	float b;
	PItem temp;
	while (fscanf(f, "%d %f", &a, &b) == 2)
	{
		temp = (PItem)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(head);
			Error_Msg("Memmory!");
		}
		temp->num = a;
		temp->price = b;
		temp->next = NULL;
		if (*head == NULL)
			*head = temp;
		else
			(*tail)->next = temp;
		*tail = temp;
	}
}


void PrintItem(PItem node)
{
	printf("%d,%.1f-->", node->num, node->price);
}



void PrintList(PItem head, char* title)
{
	printf("%s", title);
	while (head)
	{
		PrintItem(head);
		head = head->next;
	}
}


void DeleteList(PItem* head)
{
	PItem tmp = *head;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}
void AddNewItem(PItem* head, PItem* tail, int n, int a, float b)
{
	PItem temp;
	PItem ptrHead = *head;
	PItem ptrTail = *tail;
	int count = 1;
	int flag = 0;
	int secondTry;
	temp = (PItem)malloc(sizeof(struct Item));
	if (temp == NULL)
	{
		DeleteList(head);
		Error_Msg("Couldnt Allocate memory");
	}
	temp->num = a;
	temp->price = b;
	if (n == 1 || *head == NULL)
	{
		temp->next = *head;
		*head = temp;
		if(*tail == null)
			*tail = temp;
		flag = 1;
	}
	while (ptrHead != ptrTail && count != n)
	{
		count++;
		if (count == n)
		{
			temp->next = ptrHead->next;
			ptrHead->next = temp;
			flag = 1;
		}
		ptrHead = ptrHead->next;
	}
	if (flag == 0 && n != 1 && count+1 == n)
	{
		temp->next = ptrTail->next;
		ptrTail->next = temp;
		ptrTail = temp;
		flag = 1;
	}
	else if (flag == 0)
	{
		printf("invalid place, please try again:\n");
		scanf("%d", &secondTry);
		AddNewItem(head, tail, secondTry, a, b);
	}
	return;
}
void WriteListToFile(PItem head, FILE* in)
{
	if (!(in = fopen("input_price.txt", "w")))
		Error_Msg("input file is wrong");
	PItem temp = head;
	while (temp != NULL)
	{
		fprintf(in, "%d %.2f ", temp->num, temp->price);
		temp = temp->next;
	}
}
