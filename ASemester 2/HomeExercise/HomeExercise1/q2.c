#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Section {
	char Code[10];
	char* SeqName;//max 20 chars
	int NumberOfItemsSold;
}Section;
#define N 3

void CheckStrings(char* s, unsigned int size, char* name, int index);
void Inputing_Data(Section* s, int size);
void Greater_Worse(Section* s, Section** p, int size);
void NoMemory();


void main()
{
	Section s[N];
	Section* pi[N];
	Section* ps;
	int i;
	ps = &s[0];
	for (i = 0; i < N; i++)
		pi[i] = &s[i];
	Inputing_Data(ps, N);
	Greater_Worse(ps, pi, N);
	printf("\nThe best Section is %s code: %s\n", pi[0]->SeqName, pi[0]->Code);
	printf("\nThe worse Section is %s code: %s\n", pi[1]->SeqName, pi[1]->Code);
	for (i = 0; i < N; i++)
		free(s[i].SeqName);
}

void Inputing_Data(Section* s, int size)
{
	int i;
	char name[20];
	for (i = 0; i < size; i++)
	{
		rewind(stdin);
		printf("Please enter the code for the Section number %d (max 10): \n", i+1);
		gets(s[i].Code);
		CheckStrings(s[i].Code, 10, "code", i);
		printf("Please enter the name for the Section number %d (max 20): \n", i+1);
		gets(name);
		CheckStrings(&name[0], 20, "name", i);
		s[i].SeqName = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (s[i].SeqName == NULL)
		{
			free(s[i].SeqName);
			NoMemory();
		}
		strcpy(s[i].SeqName, name);
		printf("Please enter the quantities of items sold in Section number %d : \n", i+1);
		scanf("%d", &s[i].NumberOfItemsSold);
	}
}
void CheckStrings(char* s, unsigned int size, char* name, int index)
{
	while (strlen(s) > size)
	{
		printf("\ninvalid %s!-the %s is too long,please try again\n", name, name);
		printf("Please enter the %s for the Section number %d (max %d): \n", name, index, size);
		gets(s);
	}
}
void NoMemory()
{
	printf("\nError: not enough memory");
	exit(1);
}
void Greater_Worse(Section* s, Section** p, int size)
{
	Section* temp;
	int i, max = s[0].NumberOfItemsSold, min = s[0].NumberOfItemsSold;
	int indexMax=0, indexMin=0;
	for (i = 0; i < size; i++)
	{
		if (s[i].NumberOfItemsSold > max)
		{
			max = s[i].NumberOfItemsSold;
			indexMax = i;
		}
		else if (s[i].NumberOfItemsSold < min)
		{
			min = s[i].NumberOfItemsSold;
			indexMin = i;
		}
	}
	temp = p[0];
	p[0] = p[indexMax];
	p[indexMax] = temp;
	temp = p[1];
	p[1] = p[indexMin];
	p[indexMin] = temp;
}