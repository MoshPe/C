#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	char name[20];
	int grades[3];
}student;

void Error_Msg(char*);
int InputData(student**, FILE*);
void OutputData(int, student*, FILE*);
int Avg(student*, int);

int main()
{
	FILE* fp;
	student* arr;
	int size;
	if (!(fp = fopen("Students.txt", "r")))
		Error_Msg("The input file is wrong");
	size = InputData(&arr, fp);
	fclose(fp);
	if (!(fp = fopen("Students.txt", "w")))
		Error_Msg("The output file is wrong");
	OutputData(size, arr, fp);
	fclose(fp);
	return 0;
}

/*
Function name: InputData
Input: getting double pointer from type struct student and a pointer to the file fp
Output: outputting the number of the student that the function read from the txt file
Algoritem: it checks if there are any name and 3 grades following him until he reaches the end 
            of the file,if he finds a name so he adds the grades and resizing the students array
*/
int InputData(student** p_array, FILE* fp)
{
	student* arr;
	int i = 1;
	arr = (student*)malloc(sizeof(student));
	if (arr == NULL)
		Error_Msg("No memory allocated for arr");
	while (fscanf(fp, "%s %d %d %d", arr[i - 1].name, &arr[i - 1].grades[0], &arr[i - 1].grades[1], &arr[i - 1].grades[2]) != EOF)
	{
        //increase number of students
		i++;
        //putting is an other array to not lose it while we're tying to reallocing 
		student* Test=arr;
		arr= (student*)realloc(arr,i*sizeof(student));
		if (arr == NULL)
		{
			free(Test);
			Error_Msg("No memory allocated for arr");
		}
	}
    //giving the array back to the main that sent the pointer
	*p_array = arr;
	return i - 1;       /*return the number of students*/
}
/*prints all the names and their avg to a new file
  StudentsHigh.txt*/ 
void OutputData(int arr_size, student* arr, FILE* fp)
{
	int i;
	for (i = 0; i < arr_size; i++)
	{
		fprintf(fp, "%s %d\n", arr[i].name, Avg(arr + i, 3));
	}
}
/*calculates and returning the student avg to the right
  place in the Student struct
  */
int Avg(student* s, int size)
{
	int i,max=0;
	for (i = 0; i < size; i++)
	{
		if (s->grades[i] > max)
			max = s->grades[i];
	}
	return max;
}

void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}