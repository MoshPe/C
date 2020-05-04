#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct node
{
	char id[11];
	char* name;
	char Dep[4];
	int marks[3];
	float avg;
	struct node* next;
}std;

void Error_Msg(char* str);
std* FromFileToList(std* head, FILE* in);
std* Delete_Stud(std* toDel, std* head);
std* DeleteList(std* head);
void PrintList(std* head);
std* FindMax(std* head);
void FreeThemAll(std* head);
void CheckStrings(char* s, unsigned int size, char* name, std* head);

int main()
{
	int i;
	FILE* f;
	std* Head = NULL, * temp;
	if ((f = fopen("List1.txt", "rt")) == NULL)
		Error_Msg("input error");
	Head = FromFileToList(Head, f);
	printf("\nThe list is:\n");
	PrintList(Head);
	temp = FindMax(Head);
	printf("\n\nthe student with max average:\n");
	printf("%s %s %s ", temp->id, temp->name, temp->Dep);
	for (i = 0; i < 3; i++)
		printf(" %d ", temp->marks[i]);
	printf("\n\nThe list after change:\n");
	Head = Delete_Stud(temp, Head);
	PrintList(Head);
	Head = DeleteList(Head);
	fclose(f);
	return 0;
}
/*
Function name: FromFileToList
Input: Getting head of the list and the input file
Output: returning the list back to the head
Algoritem: It dynamically creates a temp every time and puts the file values in it
           and push the head value to the temp->next and change the head address to the
           head of the list which is temp
*/
std* FromFileToList(std* head, FILE* in)
{
	char name[MAX];
    char id[MAX];
    char dep[MAX];
    int i;
	std* temp = (std*)malloc(sizeof(std));
	if (temp == NULL)
		Error_Msg("Memory allocation error\n");
	while (fscanf(in, "%s%s%s%d%d%d", id, name, dep, &temp->marks[0], &temp->marks[1], &temp->marks[2]) != EOF)
	{
        //Checking the input data if they stand in the correct standart
		CheckStrings(name, 256, "name", head);
        CheckStrings(id, 10, "id", head);
        CheckStrings(dep, 3, "Dep", head);
        for (i = 0; i < 3; i++)
        {
            if (temp->marks[i] > 100 || temp->marks[i] < 0)
		    {
			FreeThemAll(head);
			Error_Msg("\ninvalid Grade!-the Grade is incorect.\nPlease fix the input file and try again!!!\n\n");
		    }
        }
		//allocating for the name in the node
		temp->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (temp->name == NULL)
		{
			FreeThemAll(head);
			Error_Msg("Memory allocation error\n");
		}
		strcpy(temp->name, name);
        strcpy(temp->id, id);
        strcpy(temp->Dep, dep);
		temp->avg = (temp->marks[0] + temp->marks[1] + temp->marks[2]) / 3.0f;
        //add the new node to the list
		temp->next = head;
		head = temp;
		temp = (std*)malloc(sizeof(std));
		//creating a new node
		if (temp == NULL)
		{
			FreeThemAll(head);
			Error_Msg("Memory allocation error\n");
		}
	}
	return head;
}
/*
Function name: FindMax
Input: Getting head of the list
Output: return the address of the max average
Algoritem: go through all the list and find the max avg and put
           its address in the max pointer. At the end it returns
           the max address.
*/
std* FindMax(std* head)
{
	std* temp = head, * max = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->avg > max->avg)
			max = temp;
	}
	return max;
}
//prints the error message and exit from program with a warning in the error log
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}
//free all the nodes and head of the list
std* DeleteList(std* head)
{
	std* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
	return head;
}
/*
Function name: Delete_Stud
Input: Getting head of the list and the address of the max avg student
Output: returning the list after the function deletes the max avg student
*/
std* Delete_Stud(std* toDel, std* head)
{
	std* temp = head;
    //checking if there is a list and return NULL to the head
	if (head == NULL)
		return NULL;
    //if the max avg student address is the same address as the head
	if (toDel == temp)
	{
        //deletes the head of the list
		temp = temp->next;
		free(toDel->name);
		free(toDel);
		head = temp;
	}
	else
	{
        //searching for the max avg student in the list
		while (temp != NULL && temp->next != toDel)
			temp = temp->next;
		//delete toDel node 
		if (temp != NULL && temp->next == toDel)
		{
			temp->next = toDel->next;
			free(toDel->name);
			free(toDel);
		}
	}
	return head;
}
//check if the string in the file is in the correct length
void CheckStrings(char* s, unsigned int size, char* name, std* head)
{
	while (strlen(s) > size)
	{
		printf("\ninvalid %s!-the %s is too long,\n", name, name);
		printf("Please fix the file!!!");
		FreeThemAll(head);
		exit(1);
	}
}
//its free all the list when an error occur
void FreeThemAll(std* head)
{
	std* temp = head;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
}
// printing all the data that FromFileToList function has extracted
void PrintList(std* head)
{
	std* temp = head;
	while (temp != NULL) {
		printf("%s %s %s %d %d %d \n", temp->id, temp->name, temp->Dep, temp->marks[0], temp->marks[1], temp->marks[2]);
		temp = temp->next;
	}
}