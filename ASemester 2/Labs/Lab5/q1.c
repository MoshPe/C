#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define GRADE 3
#define NAME 6
#define DIV 4

typedef struct CompStud {
	char name[GRADE + 1];
	char division[DIV + 1];
	char grade1[GRADE + 1];
	char grade2[GRADE + 1];
}CompStud;


void Error_Msg(char* str);
void CompStudents(FILE* in, FILE* out);
void main()
{
	FILE* in, * out;
	if (!(in = fopen("Students.txt", "r")))Error_Msg("The input file is wrong");
	if (!(out = fopen("StudentsNew.txt", "w")))Error_Msg("The output file is wrong");
	CompStudents(in, out);
	fclose(in);
	fclose(out);
}
/*
Function name: CompStudents
Input: Getting an address of a file and the name of the course
Output: Outputting in an out file and students name and they avg grade
Algoritem: The function takes the entire first student data and checks his course,
			if it matches to what the user input so the function prints his name
			and his grade avg
*/
void CompStudents(FILE* in, FILE* out)
{
	int gradeNum1, gradeNum2;
	char studstats[GRADE+GRADE + NAME + DIV + 1];
	CompStud Student;
	while (fgets(studstats, GRADE + GRADE + NAME + DIV + 1, in) != NULL)
	{
		strncpy(Student.division, studstats + NAME, DIV);
		Student.division[DIV] = '\0';
		//checking if the student div matches to comp div
		if (strcmp(Student.division, "Comp") == 0)
		{
			strncpy(Student.name, studstats, NAME);
			Student.name[NAME] = '\0';
			strncpy(Student.grade1, studstats + NAME + DIV, GRADE);
			Student.grade1[GRADE] = '\0';
			strncpy(Student.grade2, studstats + NAME + DIV + GRADE, GRADE);
			Student.grade2[GRADE] = '\0';
			gradeNum1 = atoi(Student.grade1);
			gradeNum2 = atoi(Student.grade2);
			fprintf(out, "%s %.2f\n", Student.name, (gradeNum1 + gradeNum2) / 2.0);
		}
	}
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}