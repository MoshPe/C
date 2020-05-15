#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define MAX 200
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
void FreeThemAll(University* inputUniv);
void input_HWGrade(University* inputUniv);
double finalGradeAvg(float grade, char ExercisesGradeCount);
void CheckStrings(char* s, unsigned int size, char* name, University* inputUniv);
int HWCount(char* binary);
void checkLabGrades(char* grade, University* inputUniv);
void Error_Msg(char* msg);

void main()
{
	int flag = 0, secondTry = 1, finish = 0;
	char MenuChoice;
	FILE* in, * out;
	University Univ;
	if (!(in = fopen("input.txt", "r")))
		Error_Msg("The input file is wrong");
	if (!(out = fopen("OutPut.txt", "w")))
		Error_Msg("The OutPut file is wrong");
	do
	{
		//execute the second try in the default option
		if (secondTry == 1)
		{
			printf("\n*************************************************************************\n");
			printf("Select option: \na - Extract data from input file\nb - OutPut data to output file\nc - Calculate final grade\nd - OutPut statistics data to output file\ne - Black List\nf - Exit \n");
			if (flag == 0)
				printf("!!! Please pay attention! first time using the program, option a must be selected before other options to proceed  !!!\n");
			printf(">>>: ");
			rewind(stdin);
			scanf("%c", &MenuChoice);
		}
		else
			secondTry = 1;
		//checking if the option is == 'a'
		if (MenuChoice == 'a' && flag == 0)
		{
			InputData(&Univ, in);
			input_HWGrade(&Univ);
			flag = 1;
		}
		//check if f is the first input or a
		else if (flag == 1 || MenuChoice == 'f')
		{
			switch (MenuChoice)
			{
			case 'a':
				printf("\n\nInput data can be execute one per run!!!\n\n");
				break;
			case 'b':
				fprintf(out, "\nOption B\n");
				fprintf(out, "Print OutPut.file\n\n");
				OutPutData(&Univ, out);
				break;
			case 'c':
				fprintf(out, "\nOption C\n");
				fprintf(out, "FinalGradeCalc\n\n");
				finalGradePrint(&Univ, out);
				break;
			case 'd':
				fprintf(out, "\nOption D\n");
				fprintf(out, "Statistics\n\n");
				Statistics(&Univ, out);
				break;
			case 'e':
				fprintf(out, "\nOption E\n");
				fprintf(out, "BlackList\n\n");
				BlackList(&Univ, out);
				break;
			case 'f':
				fprintf(out, "\nOption F\n");
				fprintf(out, "End Of Program");
				//if f was selected before 'a' (stud not crated) no need for free
				if (flag == 1)
					FreeThemAll(&Univ);
				fclose(in);
				fclose(out);
				finish = 1;
				break;
			default:
				//check if the letter entered isn't an option of the list
				while (MenuChoice != 'a' && MenuChoice != 'b' && MenuChoice != 'c' && MenuChoice != 'd' && MenuChoice != 'e' && MenuChoice != 'f')
				{
					printf("\n Invalid input, Please try again!!! \n>>>: ");
					rewind(stdin);
					scanf("%c", &MenuChoice);
					secondTry = 0;
				}
				break;
			}
		}
		else //first input wasn't a nor f
			printf("\n!!!  Invalid input(in first use, choose option a first, otherwise try again)  !!!\n");
	} while (finish != 1);
}
/*
Function name: CheckStrings
Input: A string, the size required,the name of the string, the University to free before exit(1)
Algoritem: It checks the length of the string by strlen() function, if it is above the required length
		   the function pulls out a message and terminate the program
*/
void CheckStrings(char* s, unsigned int size, char* name, University* inputUniv)
{
	while (strlen(s) > size)
	{
		fprintf(stderr, "\ninvalid %s!-the %s is too long.\nPlease fix the input file and try again!!!\n\n", name, name);
		FreeThemAll(inputUniv);
		exit(1);
	}
}
/*
Function name: checkLabGrades
Input: A string and the University to free before exit(1)
Algoritem: In a recursive way it checks if all the string is assembled
		   by '1' and '0' and not other chars, if it not the function
		   it pulls out a message and terminate the program
*/
void checkLabGrades(char* grade, University* inputUniv)
{
	if (*grade == '\0')
		return;
	else
	{
		if (*grade != '1' && *grade != '0')
		{
			FreeThemAll(inputUniv);
			Error_Msg("\nInvalid grades!-The grades is incorect.\nPlease fix the input file and try again!!!\n");
		}
	}
	checkLabGrades(grade + 1, inputUniv);
}
/*
Function name: InputData
Input: Getting the University pointer and the input file
Output: Creates an array of students inside the struct inputUniv with all the data that
		the function inputs
*/
void InputData(University* inputUniv, FILE* inputFile)
{
	int gradeCount = 0;
	char name[MAX];
	char grade[MAX];
	int i = 0;
	inputUniv->Stud = (Student*)malloc(sizeof(Student));
	if (inputUniv->Stud == NULL)
		Error_Msg("No memory allocated for arr");
	while (fscanf(inputFile, "%s%ld%f%s", name, &inputUniv->Stud[i].id, &inputUniv->Stud[i].MtmGrade, grade) != EOF)
	{
		inputUniv->students = i;
		//checking if there are '1' and '0' in the lab grades array
		checkLabGrades(grade, inputUniv);
		//cheking if the name string length is the correct length
		CheckStrings(name, 99, "name", inputUniv);
		//cheking if the lab grades string length is the correct length
		CheckStrings(grade, 5, "Lab Grades", inputUniv);
		strcpy(inputUniv->Stud[i].Grade, grade);
		inputUniv->Stud[i].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (inputUniv->Stud[i].name == NULL)
		{
			FreeThemAll(inputUniv);
			Error_Msg("No memory allocated for name");
		}
		strcpy(inputUniv->Stud[i].name, name);
		//Checking the terms for the id that has to be between 10000 to 99999
		if (inputUniv->Stud[i].id > 99999 || inputUniv->Stud[i].id < 10000)
		{
			FreeThemAll(inputUniv);
			Error_Msg("\nInvalid id!-The id is incorect.\nPlease fix the input file and try again!!!\n\n");
		}
		//Checking the terms for the mtm grade that has to be between 0 to 100
		if (inputUniv->Stud[i].MtmGrade > 100 || inputUniv->Stud[i].MtmGrade < 0)
		{
			FreeThemAll(inputUniv);
			Error_Msg("\nInvalid Mtm Grade!-The Mtm Grade is incorect.\nPlease fix the input file and try again!!!\n\n");
		}
		//increase number of students
		i++;
		//putting is an other array to not lose it while we're tying to reallocing so we can free
		Student* Test = inputUniv->Stud;
		inputUniv->Stud = (Student*)realloc(inputUniv->Stud, (i+1) * sizeof(Student));
		if (inputUniv->Stud == NULL)
		{
			for (i = i - 1; i >= 0; i--)
				//free the address that we saved earlier because realloc failed abd inputUniv->Stud == NULL
				free(Test[i].name);
			free(Test);
			Error_Msg("No memory allocated for inputUniv->Stud");
		}
	}
	inputUniv->students++;
}
/*
Function name: input_HWGrade
Input: Getting the University array
Output: it puts '1' or '0' in every student final grade
Algoritem: the function counts the amount number of '1' in the labGrade string
*/
void input_HWGrade(University* inputUniv)
{
	int i, gradeCount;
	for (i = 0; i < inputUniv->students; i++)
	{
		gradeCount = HWCount(inputUniv->Stud[i].Grade);
		inputUniv->Stud[i].HWfinalGrade = (gradeCount >= 3) ? '1' : '0';
	}
}
//prints out the data to the output file
void OutPutData(University* inputUniv, FILE* outputFile)
{
	int i;
	for (i = 0; i < inputUniv->students; i++)
		fprintf(outputFile, "Student %d : %s %ld %.2f %c\n", i + 1, inputUniv->Stud[i].name, inputUniv->Stud[i].id, inputUniv->Stud[i].MtmGrade, inputUniv->Stud[i].HWfinalGrade);
}
/*
Function name: finalGradeAvg
Input: Getting the MtmGrade and the HW final grade
Output: it returns the finalGrade avg of mtm grade and hw grade
Algoritem: the function checks if the student passed the exam>55
		   if he did it calculates the final grade
*/
double finalGradeAvg(float mtmGrade, char ExercisesGradeCount)
{
	if (mtmGrade > 55.0)
	{
		double gradeFinal;
		double ExercisesFinal;
		gradeFinal = mtmGrade * 0.85;
		ExercisesFinal = ((ExercisesGradeCount - '0') * 15.0);
		return ExercisesFinal + gradeFinal;
	}
	return mtmGrade;
}
/*
The function prints out the data to the output file before adding the final grade and after
	getting the final grade
*/
void finalGradePrint(University* inputUniv, FILE* outputFile)
{
	fprintf(outputFile, "BEFORE\n");
	OutPutData(inputUniv, outputFile);
	fprintf(outputFile, "\nAFTER\n");
	int i;
	float finalGrade;
	for (i = 0; i < inputUniv->students; i++)
	{
		finalGrade = (float)finalGradeAvg(inputUniv->Stud[i].MtmGrade, inputUniv->Stud[i].HWfinalGrade);
		fprintf(outputFile, "Student %d : %s %ld %.2f %c final: %.2f\n", i + 1, inputUniv->Stud[i].name, inputUniv->Stud[i].id, inputUniv->Stud[i].MtmGrade, inputUniv->Stud[i].HWfinalGrade, finalGrade);
	}
}
/*
Function name: Statistics
Input: Getting the University pointer and the output file
Output: prints out to the data file the statistics of the students
Algoritem: the function calculates the avg grade,the standard deviation,
		   the amount of students and the range of the students grades from max
		   grade to min grade by given formulas
*/
void Statistics(University* inputUniv, FILE* outputFile)
{
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
//prints out to the output file the students id and name whi got '0' in their final hw grade
void BlackList(University* inputUniv, FILE* outputFile)
{
	int i, j;
	for (i = 0, j = 1; i < inputUniv->students; i++)
	{
		//checks if the final hw grade == '0'
		if (inputUniv->Stud[i].HWfinalGrade == '0')
		{
			fprintf(outputFile, "Student %d: %s %ld\n", j, inputUniv->Stud[i].name, inputUniv->Stud[i].id);
			j++;
		}
	}
}
//free all the allocations
void FreeThemAll(University* inputUniv)
{
	int i;
	for (i = 0; i < inputUniv->students; i++)
		free(inputUniv->Stud[i].name);
	free(inputUniv->Stud);
}
//the function returns the amounts of '1' in the string
int HWCount(char* binary)
{
	return (*binary == '\0') ? 0 : (*binary == '1') ? 1 + HWCount(binary + 1) : HWCount(binary + 1);
}
//prints an error message and terminate the program
void Error_Msg(char* msg)
{
	fprintf(stderr, "\n%s", msg);
	exit(1);
}
