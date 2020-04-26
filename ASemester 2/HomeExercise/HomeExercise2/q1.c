#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_NAME 150
#define GRADE 5


typedef struct Student
{
	char* name;
	long int id;
	float MtmGrade;
	char Grade[GRADE + 1];
	char HWfinalGrade;
}Student;
typedef struct University
{
	Student* Stud;
	int students;
}University;
void Error_Msg(char* msg);
void InputData(University* inputUniv, FILE* inputFile);
void CheckStrings(char* s, unsigned int size, char* name);
void OutPutData(University* inputUniv, FILE* outputFile);
void finalGradePrint(University* inputUniv, FILE* outputFile);
int HWCount(char* binary);
float finalGradeAvg(float grade, int ExercisesGradeCount);



void main()
{
	int flag = 0;
	char MenuChoice;
	FILE* in;
	FILE* out;
	University Univ;
	if (!(in = fopen("input.txt", "r")))
		Error_Msg("The input file is wrong");
	if (!(out = fopen("OutPut.txt", "w")))
		Error_Msg("The OutPut file is wrong");
	printf("*************************************************************************\n");
	printf("Select option (a - input.file, b - OutPut.file, c - finalGradeCalc, d - Stastistics.file,e - Black List, f - Exit): \n");
	printf("!!! Please attention! first time using the program, input must be selected before other options to proceed  !!!\n");
	rewind(stdin);
	scanf("%c",&MenuChoice);
	do
	{
		switch (MenuChoice)
		{
		case 'a':
			InputData(&Univ, in);
			flag = 1;
			break;
			case 'b':
					if (flag == 0)
						break;
				OutPutData(&Univ, out);
				break;
			case 'c' :
					if (flag == 0)
						break;
					finalGradePrint(&Univ, out);
				break;
			case 'd' :
					if (flag == 0)
						break;
				break;
			case 'e' :
					if (flag == 0)
						break;
				break;
			case 'f' :
					if (flag == 0)
						break;
				break;
		}
		if (flag == 0)
			printf("!!!Please select input first in order to proceed  !!!\n");
		printf("*************************************************************************\n");
		printf("Select option (a - input.file, b - OutPut.file, c - finalGradeCalc, d - Stastistics.file,e - Black List, f - Exit): \n");
		rewind(stdin);
		scanf("%c", &MenuChoice);
	} while (MenuChoice != 'f');
	//////////////////////////////////////FREEEEEEEEEEEEEEEEEEEEEEEEE/////////////////////////////
	
	fclose(in);
	fclose(out);
}
void InputData(University* inputUniv, FILE* inputFile)
{
	char name[MAX_NAME];
	Student* arr;
	int i = 1;
	arr = (Student*)malloc(sizeof(Student));
	if (arr == NULL)
		Error_Msg("No memory allocated for arr");
	while (fscanf(inputFile, "%s %ld %f %s", name, &arr[i - 1].id, &arr[i - 1].MtmGrade, arr[i - 1].Grade) != EOF)
	{
		//increase number of students
		i++;
		//putting is an other array to not lose it while we're tying to reallocing 
		Student* Test = arr;
		arr = (Student*)realloc(arr, i * sizeof(Student));
		if (arr == NULL)
		{
			free(Test);
			Error_Msg("No memory allocated for arr");
		}
		CheckStrings(name, 99, "name");
		arr[i].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (arr[i].name == NULL)
		{
			free(arr[i].name);
			Error_Msg("No memory allocated for name");
		}
		strcpy(arr[i].name, name);
	}
	//giving the array back to the main that sent the pointer
	inputUniv->Stud = arr;
	inputUniv->students = i - 1;
}
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
void CheckStrings(char* s, unsigned int size, char* name)
{
	while (strlen(s) > size)
	{
		printf("\ninvalid %s!-the %s is too long, please try again\n", name, name);
		printf("Please enter the %s (max %d): \n", name, size);
		rewind(stdin);
		scanf("%s", s);
	}
}
void OutPutData(University* inputUniv, FILE* outputFile)
{
	int i;
	int count = inputUniv->students;
	for (i = 0; i < count; i++)
		fprintf(outputFile, "Student %d : %s %ld %.2f %d\n", i + 1, *inputUniv->Stud[i].name, inputUniv->Stud[i].id, inputUniv->Stud[i].MtmGrade, (HWCount(*inputUniv->Stud[i].Grade) >= 3) ? 1 : 0);
}
int HWCount(char* binary)
{
	return (*binary == '\0') ? 0 : (*binary == 1) ? 1 + HWCount(binary + 1) : HWCount(binary + 1);
}
void finalGradePrint(University* inputUniv, FILE* outputFile)
{
	int i;
	int count = inputUniv->students;
	int gradeCount;
	fseek(outputFile, 28, SEEK_SET);
	for (i = 0; i < count; i++)
	{
		gradeCount = HWCount(*inputUniv->Stud[i].Grade);
		fprintf(outputFile," final: %.2f\n", finalGradeAvg(inputUniv->Stud[i].MtmGrade, gradeCount));
		fseek(outputFile, 28, SEEK_CUR);
	}
}
float finalGradeAvg(float grade, int ExercisesGradeCount)
{
	float gradeFinal;
	float ExercisesFinal;
	gradeFinal = grade * 0.85;
	ExercisesFinal = (ExercisesGradeCount * 15.0);
		return ExercisesFinal + gradeFinal;
}