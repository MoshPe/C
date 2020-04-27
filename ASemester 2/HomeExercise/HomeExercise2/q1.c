#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

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

void InputData(University* inputUniv, FILE* inputFile);
void OutPutData(University* inputUniv, FILE* outputFile);
void finalGradePrint(University* inputUniv, FILE* outputFile);
void Statistics(University* inputUniv, FILE* outputFile);
void BlackList(University* inputUniv, FILE* outputFile);
void FreeThemAll(University* inputUniv, FILE* outputFile);
void input_HWGrade(University* inputUniv);
double finalGradeAvg(float grade, char ExercisesGradeCount);
void CheckStrings(char* s, unsigned int size, char* name);
int HWCount(char* binary);
void Error_Msg(char* msg);

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
	do
	{	
		printf("*************************************************************************\n");
		printf("Select option: \na - Extract data from input file\nb - OutPut data to output file\nc - finalGradeCalc\nd - Stastistics.file\ne - Black List\nf - Exit \n");
		printf("!!! Please attention! first time using the program, input must be selected before other options to proceed  !!!:\n>>>: ");
		rewind(stdin);
		scanf("%c", &MenuChoice);
		if (MenuChoice == 'a' && flag == 0)
		{
			InputData(&Univ, in);
			input_HWGrade(&Univ);
			flag = 1;
		}
		elseif (flag == 1){	
			switch (MenuChoice)
			{
			case 'a':
				printf("Input data can be execute one per run!!!");
				break;
			case 'b':
				OutPutData(&Univ, out);
				break;
			case 'c':
				finalGradePrint(&Univ, out);
				break;
			case 'd':
				Statistics(&Univ, out);
				break;
			case 'e':
				BlackList(&Univ, out);
				break;
			case 'f':
				FreeThemAll(&Univ, out);
				fclose(in);
				fclose(out);
				break;
			default:
				printf("\n invalid input please try again \n>>>: ");
				rewind(stdin);
				scanf("%c", &MenuChoice);
				break;
			}
		}
		else //flag == 0
			printf("!!!Please select input first in order to proceed  !!!\n");
	} while (MenuChoice != 'f');
}
void CheckStrings(char* s, unsigned int size, char* name)
{
	while (strlen(s) > size)
	{
		fprintf(stderr,"\ninvalid %s!-the %s is too long.\nPlease fix the input file and try again!!!\n", name, name);
		exit(1);
	}
}
void InputData(University* inputUniv, FILE* inputFile)
{
	int gradeCount = 0;
	char name[MAX_NAME];
	//Student* arr;
	int i = 1;
	inputUniv->Stud = (Student*)malloc(sizeof(Student));
	if (inputUniv->Stud == NULL)
		Error_Msg("No memory allocated for arr");
	while ( fscanf(inputFile, "%s%ld%f%s", name, &inputUniv->Stud[i - 1].id, &inputUniv->Stud[i - 1].MtmGrade, inputUniv->Stud[i - 1].Grade) != EOF)
	{
		CheckStrings(name, 99, "name");
		inputUniv->Stud[i - 1].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (inputUniv->Stud[i - 1].name == NULL)
		{
			free(inputUniv->Stud);
			Error_Msg("No memory allocated for name");
		}
		strcpy(inputUniv->Stud[i - 1].name, name);
		//increase number of students
		i++;
		//putting is an other array to not lose it while we're tying to reallocing 
		Student* Test = inputUniv->Stud;
		inputUniv->Stud = (Student*)realloc(inputUniv->Stud, i * sizeof(Student));
		if (inputUniv->Stud == NULL)
		{
			for (i=i-1;i>=0; i--)
				free(inputUniv->Stud[i].name);
			free(inputUniv->Stud);			
			Error_Msg("No memory allocated for inputUniv->Stud");
		}
	}
		inputUniv->students = i - 1;
}
void input_HWGrade(University* inputUniv)
{
	int i,gradeCount;
	for (i = 0; i < inputUniv->students; i++)
	{
		gradeCount = HWCount(inputUniv->Stud[i].Grade);
		inputUniv->Stud[i].HWfinalGrade = (gradeCount >= 3) ? '1' : '0';
	}
}
void OutPutData(University* inputUniv, FILE* outputFile)
{
	fprintf(outputFile, "\nOption B\n");
	fprintf(outputFile, "Print OutPut.file\n\n");
	int i;
	for (i = 0; i < inputUniv->students; i++)
		fprintf(outputFile, "Student %d : %s %ld %.2f %c\n", i + 1, inputUniv->Stud[i].name, inputUniv->Stud[i].id, inputUniv->Stud[i].MtmGrade, inputUniv->Stud[i].HWfinalGrade);
}
double finalGradeAvg(float grade, char ExercisesGradeCount)
{
	if (grade > 55.0)
	{
		double gradeFinal;
		double ExercisesFinal;
		gradeFinal = grade * 0.85;
		ExercisesFinal = ((ExercisesGradeCount-'0') * 15.0);
		return ExercisesFinal + gradeFinal;
	}
	return grade;
}
void finalGradePrint(University* inputUniv, FILE* outputFile)
{
	fprintf(outputFile, "\nOption C\n");
	fprintf(outputFile, "finalGradeCalc\n\n");
	int i;
	float FinalAvg;
	for (i = 0; i < inputUniv->students; i++)
	{
		FinalAvg = finalGradeAvg(inputUniv->Stud[i].MtmGrade,inputUniv->Stud[i].HWfinalGrade);
		fprintf(outputFile, "Student %d : %s %ld %.2f %c final: %.2f\n", i + 1, inputUniv->Stud[i].name, inputUniv->Stud[i].id, inputUniv->Stud[i].MtmGrade,inputUniv->Stud[i].HWfinalGrade,FinalAvg);
	}
}
void Statistics(University* inputUniv, FILE* outputFile)
{
	fprintf(outputFile, "\nOption D\n");
	fprintf(outputFile, "Statistics\n\n");
	int i;
	float avg = 0;
	double sd = 0;//Standard Deviation
	float max = inputUniv->Stud[0].MtmGrade;
	float min = inputUniv->Stud[0].MtmGrade;
	for (i = 0; i < inputUniv->students; i++)
	{
		avg += inputUniv->Stud[i].MtmGrade;
		if (inputUniv->Stud[i].MtmGrade > max)
			max = inputUniv->Stud[i].MtmGrade;
		if (inputUniv->Stud[i].MtmGrade < min)
			min = inputUniv->Stud[i].MtmGrade;
	}
	avg = avg / (float)inputUniv->students;
	for (i = 0; i < inputUniv->students; i++)
		sd += pow((inputUniv->Stud[i].MtmGrade - avg), 2);
	fprintf(outputFile, "The Average is: %.2f\n", avg);
	fprintf(outputFile, "The Standard Deviation is: %.2f\n", sqrt(sd / (float)inputUniv->students));
	fprintf(outputFile, "The Amount of students is: %d\n", inputUniv->students);
	fprintf(outputFile, "The range is %.2f - %.2f\n", max, min);
}
void BlackList(University* inputUniv, FILE* outputFile)
{
	fprintf(outputFile, "\nOption E\n");
	fprintf(outputFile, "BlackList\n\n");
	int i,j;
	for (i = 0,j=1; i < inputUniv->students; i++)
	{
		if (inputUniv->Stud[i].HWfinalGrade == '0')
			{
				fprintf(outputFile, "Student %d: %s %ld\n", j, inputUniv->Stud[i].name, inputUniv->Stud[i].id);
				j++;
			}
	}
}
void FreeThemAll(University* inputUniv, FILE* outputFile)///////free
{
	fprintf(outputFile,"\nOption F\n");
	fprintf(outputFile,"End Of Program");
	int i;
	for (i = 0; i < inputUniv->students; i++)
		free(inputUniv->Stud[i].name);
	free(inputUniv->Stud);
}
int HWCount(char* binary)
{
	return (*binary == '\0') ? 0 : (*binary == '1') ? 1 + HWCount(binary + 1) : HWCount(binary + 1);
}
void input_HWGrade(University* inputUniv)
{
	int i,gradeCount;
	for (i = 0; i < inputUniv->students; i++)
	{
		gradeCount = HWCount(inputUniv->Stud[i].Grade);
		inputUniv->Stud[i].HWfinalGrade = (gradeCount >= 3) ? '1' : '0';
	}
}
void Error_Msg(char* msg)
{
	fprintf(stderr,"\n%s", msg);
	exit(1);
}
