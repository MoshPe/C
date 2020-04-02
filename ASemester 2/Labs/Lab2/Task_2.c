#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct stud
{
	char* name;
	int marks[4];
	float avg;
}student;


student* Create_Class(int);
void Avg_Mark(student*);
void Print_One(student*);
void FreeThemAll(student*, int);
void NoMemory();

int main()
{
	int size, i;
	student* arr;
	printf("\nEnter the number of students:");
	scanf("%d", &size);
	
	arr = Create_Class(size);
	puts("\n");
	for (i = 0; i < size; i++)
	{
		if (arr[i].avg >= 85.0)
			Print_One(&arr[i]);
	}
	FreeThemAll(arr, size);
	return 0;
}

/*
Function name: Create_Class From type struct student
Input: size of the array that should be created dynamically
Output: return the address of the new array that made form struct student
Algoritem: creating an array dynamically and inserting the info in the fields place:
	.name, .marks, .avg
*/
student* Create_Class(int size)
{
	int i, j;
	student* newStudent;
	char nameCheck[50];
	//creating an array type of struct student
	newStudent = (student*)malloc(size * sizeof(student));
	assert(newStudent);
	for (i = 0; i < size; i++)
	{
		printf("\nEnter your name: ");
		rewind(stdin);
		gets(nameCheck);
		//creating and string in size of the nameCheck 
		newStudent[i].name = (char*)malloc((strlen(nameCheck) + 1) * sizeof(char));
		if (newStudent[i].name == NULL)
		{
			FreeThemAll(newStudent, i);
			NoMemory();
		}
		strcpy(newStudent[i].name, nameCheck);
		printf("\nEnter your marks: ");
		for (j = 0; j < 4; j++)
			scanf("%d", &newStudent[i].marks[j]);
		Avg_Mark(&newStudent[i]);
	}
	//return the address of the struct student array
	return newStudent;
}
/*
Function name: Avg_Mark
Input: a pointer struct from type student
Output: just inputing the avg in the avg field 
*/
void Avg_Mark(student* s)
{
	float avr = 0;
	int i;
	for (i = 0; i < 4; i++)
		avr += s->marks[i];
	avr = avr / 4;
	s->avg = avr;
}
void Print_One(student* s)
{
	printf("The average of %s is %.1f\n", s->name, s->avg);
}
void FreeThemAll(student* s, int index)
{
	int i;
	for (i = 0; i < index; i++)
		free(s[i].name);
	free(s);
}
void NoMemory()
{
	printf("\nError: not enough memory");
	exit(1);
}