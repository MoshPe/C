#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#define  N  5
#define  LENGTH 30

typedef enum { FALSE, TRUE } BOOL;


int CurrentCount = 0;   /*global variable - only for the first ADT lab!Please,don't use!*/


void Insert(BOOL(*f)(void*, void*), void* Element, void** Parray);
BOOL Str_Comp(void* FirstElement, void* SecondElement);
BOOL IsFull();


int main()
{
	char* Array[N];
	void* PArray[N];
	int i;
	char TempStr[LENGTH];
    //placing the PArray to point the Array addresses
	for (i = 0; i < N; i++)
		PArray[i] = &Array[i];

	printf("Enter strings with space between them,'end' to finish  ");
	scanf("%s", TempStr);

	while (strcmp(TempStr, "end"))
	{

		if (!IsFull())
		{
			Array[CurrentCount] = (char*)malloc(strlen(TempStr) + 1); /*allocate the string memory*/
			assert(Array[CurrentCount]);
			strcpy(Array[CurrentCount], TempStr);
			Insert(Str_Comp, Array[CurrentCount], PArray);    /*call the general function*/
			scanf("%s", TempStr);
		}
		else
		{
			printf("The array is full");
			break;
		}
	}
	printf("\nYour sorted array is:\n");
	for (i = 0; i < CurrentCount; i++)
		printf(" %s ", (char*)PArray[i]);

	for (i = 0; i < CurrentCount; i++)
		free(Array[i]);

	return 0;
}
BOOL IsFull()
{
	if (CurrentCount == N)
		return TRUE;
	return FALSE;
}
BOOL Str_Comp(void* FirstElement, void* SecondElement)
{
	if (strcmp((char*)FirstElement, (char*)SecondElement) > 0)
		return TRUE;
	return FALSE;
}
void Insert(BOOL(*f)(void*, void*), void* Element, void** Parray)
{
	int i = CurrentCount++;
    //loop for searching the place that the element should be
	while (i > 0 && f(Parray[i - 1], Element) == TRUE)
	{
		Parray[i] = Parray[i - 1];
		i--;
	}
    //placing the element in the right position
	Parray[i] = Element;
}


