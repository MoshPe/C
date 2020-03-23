#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define A 11
int gradeConv(int n);
int MaxGrade(int GradeFrequent[], int n);
int print_frequnt(int GradeFrequent[],int n, int max);
void main()
{
	int GradeFrequent[A] = { 0 };
	int i, maxgrade = 0,num;
	int grade;
	//inputing grades from 0 to 100
	printf("Enter grade: ");
	do
	{
		scanf("%d", &grade);
		//loop for sorting the grades to 0 to 10
		for (i = 0; i < A; i++)
		{
			//if grade is -1 so it just break out of the loop for not wasting time
			if (grade != -1)
			{
				//its actually round up or down the num and put + 1 if the index is equal to it
				if (gradeConv(grade) == i)
				{
					GradeFrequent[i] = GradeFrequent[i] + 1;
				}
			}
			else
				break;
		}
	} while (grade >= 0 && grade <=100);

	maxgrade = MaxGrade(GradeFrequent, A);
	printf("            grade     frequency\n");
	//prints all the grades from 1 to 10 in a table and prints the frequent of these grades as well
	for (i = 0; i < A; i++)
		printf("%15d    %8d\n", i, GradeFrequent[i]);
	printf("The most frequent grades are: ");
	print_frequnt(GradeFrequent,A, maxgrade);
}
int gradeConv(int n)
{
	int gradeCon;
	gradeCon = (int)round(n/ 10.0);
	return gradeCon;		
}
//getting an GradeFrequent and its length and outputing the max number in the GradeFrequent
int MaxGrade(int GradeFrequent[], int n)
{
	int i, max = 0;
	for (i = 0; i < n; i++)
	{
		if (GradeFrequent[i] > max)
			max = GradeFrequent[i];
	}
	return max;
}
//the function get an GradeFrequent, its length and max and output to the screen the range that was matched to the max
int print_frequnt(int GradeFrequent[],int n, int max)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (GradeFrequent[i] == max)
		printf("%d to %d  ", ((i * 10 - 5)<0)?0: (i * 10 - 5), ((i * 10 + 4)>100)?100:(i * 10 + 4));
	}
}

