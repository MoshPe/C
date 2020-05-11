#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
	int num;
	struct Item* next;
}Item;

typedef struct List
{
	struct Item* head;
	struct Item* tail;
	int count;
}List;

void Error_Msg(char*);
void AddAsFirst(Item*, List*);
void AddAsLast(Item*, List*);
void MoveToAnotherList(List*, List*, List*);
void CreateList(List*, FILE*);
void PrintItem(Item*);
void PrintList(List*, char*);
void DeleteList(List*);

int main()
{
	List L, Posit, Negat;
	FILE* in = fopen("ThreeLists.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	L.head = NULL;
	L.tail = NULL;
	L.count = 0;

	Posit.head = NULL;
	Posit.tail = NULL;
	Posit.count = 0;

	Negat.head = NULL;
	Negat.tail = NULL;
	Negat.count = 0;

	CreateList(&L, in);
	PrintList(&L, "\nMy List:\n");
	MoveToAnotherList(&L, &Posit, &Negat);
	PrintList(&Posit, "\n\nThe Positive List:\n");
	PrintList(&Negat, "\n\nThe Negative List:\n\n");

	fclose(in);
	DeleteList(&Posit);
	DeleteList(&Negat);
	return 0;
}



void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}

void CreateList(List* L, FILE* f)
{
	int value;
	Item* temp;
	while (fscanf(f, "%d", &value) == 1)
	{
		temp = (Item*)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(L);
			Error_Msg("Memmory!");
		}

		temp->num = value;
		temp->next = NULL;
		if (L->head == NULL)
			L->head = temp;
		else
			L->tail->next = temp;
		L->tail = temp;
		L->count++;
	}
}


void PrintItem(Item* node)
{
	printf("%d--> ", node->num);
}


void PrintList(List* L, char* title)
{
	Item* temp = L->head;
	printf("%s", title);
	while (temp)
	{
		PrintItem(temp);
		temp = temp->next;
	}
	printf("\nThere are %d items in the list", L->count);
}
//Addint a node to the head of the list every time
void AddAsFirst(Item* A, List* L)
{
	if (L->head == NULL)
		L->head = A;
	else
	{
		A->next = L->head;
		L->head = A;
		if (L->count == 0)
			L->tail = A;
		L->count++;
	}
}
void AddAsLast(Item* A, List* L)
{
	A->next = NULL;
	if (L->tail != NULL)
		L->tail->next = A;
	else
		L->head = A;
	L->tail = A;
	L->count++;
}

void DeleteList(List* L)
{
	Item* temp;
	while (L->head != NULL)
	{
		temp = L->head;
		L->head = L->head->next;
		free(temp);
	}
	L->tail = L->head;
	L->count = 0;
}
void MoveToAnotherList(List* L, List* Posit, List* Negat)
{
	Item* temp;
	while (L->head != NULL)
	{
		temp = L->head;
		L->head = temp->next;
		L->count--;
		if (temp->num >= 0)
			AddAsLast(temp, Posit);
		else
			AddAsLast(temp, Negat);
	}
	L->tail= L->head;
}
