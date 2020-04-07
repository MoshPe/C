#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define Course_Name 3
#define Stud_ID 4
#define Stud_Full_Name 16
#define binary_ID 14

typedef struct student
{
	char Course[Course_Name + 1];
	char ID[Stud_ID + 1];
	char FullName[Stud_Full_Name + 1];
}student;



void Get_Lost(char*);
void Find(FILE*, char* course);

int main()
{
	char course[4];
	FILE* file;
	file = fopen("Stud.txt", "rt");
	if (file == NULL)
		Get_Lost("Cannot open file");
	printf("\nEnter the name of course,up to 3 letters;\n");
	scanf("%s", course);
	Find(file, course);
	fclose(file);
	return 0;
}
void Find(FILE* f, char* course)
{
	FILE* out;
	student s;
	int id;
	char Stud[Course_Name + Stud_Full_Name + Stud_ID + 1];
	char binary[binary_ID + 1];
	char Out_Course_Name[Course_Name + 5];
	strcpy(Out_Course_Name, course);
	strcat(Out_Course_Name, ".txt");
	out = fopen(Out_Course_Name, "wt");
	while (fgets(Stud, Course_Name + Stud_Full_Name + Stud_ID + 1, f)!=NULL)
	{
		strncpy(s.Course, Stud, Course_Name);
		s.Course[Course_Name] = '\0';
		if (strcmp(s.Course, course) == 0)
		{
			strncpy(s.ID, Stud + Course_Name, Stud_ID);
			s.ID[Stud_ID] = '\0';
			strncpy(s.FullName, Stud + Course_Name + Stud_ID, Stud_Full_Name);
			s.FullName[Stud_Full_Name] = '\0';
			id = atoi(s.ID);
			_itoa(id, binary, 2);
			fprintf(out, "%s, %s, %s\n", binary, s.FullName, s.Course);
		}
	}
	fclose(out);
}
void Get_Lost(char* s)
{
	puts(s);
	exit(1);
}