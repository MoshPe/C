#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define N 3
#define BUFFER 100 //used to check length of string user entered
#define LEN_NAME 20

typedef struct division
{
	char code[11];
	char* name_div; //string len <=20
	int sold_items;

}division;

void ScanDivision(division* d);
void Best_Worst_Sales(division* d, int* i_best, int* i_worst);

void main()
{
	int i, i_best, i_worst;
	division d[N];
	division* pointerD[N];
	ScanDivision(d);		//scan from user the details of each division
	for (i = 0; i < N; i++)		//make every pointer in the array-pointerD to point the array D in place i
		pointerD[i] = &d[i];
	Best_Worst_Sales(d, &i_best, &i_worst); //Updates the best and worst divisions indexes
	if (i_best == i_worst)		//In case all divisions sold an equal amount
		printf("All divisions sold the exact same quantity");
	else
	{
		pointerD[0] = &d[i_best]; //Updates the first place int the arry of pointers in to point the best division
		pointerD[i_best] = &d[0];

		pointerD[1] = &d[i_worst]; //Updates the second place int the arry of pointers in to point the worst division
		pointerD[i_worst] = &d[1];

		printf("\nThe best division is:\nName: %sCode: %s", pointerD[0]->name_div, pointerD[0]->code);
		printf("\n\nThe worst division is:\nName: %sCode: %s", pointerD[1]->name_div, pointerD[1]->code);
	}

	for (i = 0; i < N; i++)
		free(d[i].name_div);
	
}
/*function:ScanDivision
input: array of struct-division -d
output: void
algorithm: The function receives an array of division and enter into the array data from user */
void ScanDivision(division* d)
{
	char name_temp[BUFFER];//using 'BUFFER' to check if user entered 20 or less characters 
	int i;
	printf("Please enter %d dvision data:\n", N);
	for (i = 0; i < N; i++)
	{
		printf("division %d:\n", i + 1);
		printf("	Code (10 digits): ");
		scanf("%s", d[i].code);
		while ((strlen(d[i].code) > 10))//check if the code that enter is more then 10 digits then ask from user to enter a correct code
		{
			printf("\tError: Enter code (10 digits!): ");
			scanf("%s", d[i].code);
		}
		printf("\tName (max 20 char): ");
		rewind(stdin);		// reset the input so fgets dosent scan enter/space
		fgets(name_temp, BUFFER, stdin);
		while (strlen(name_temp) > LEN_NAME)//Checks if the length of the division name is less than or equal to 20 if not, then asks the user for a new input
		{
			printf("\tError: enter Name (max 20 char): ");
			rewind(stdin);		// reset the input so fgets dosent scan enter/space
			fgets(name_temp, BUFFER, stdin);
		}
		d[i].name_div = (char*)malloc((strlen(name_temp) + 1) * sizeof(char));
		if (d[i].name_div == NULL)
		{
			printf("NO MEMORY!!");
			_getch();
			exit(1);
		}
		strcpy(d[i].name_div, name_temp);
		printf("\tAmount of products sold today: ");
		scanf("%d", &(d[i].sold_items));
	}
}
/*function:Best_Worst_Sales
input: array of struct division-d, two pointers integers -index best and worst
output: void
algorithm: The function gets a pointer of array division and the function updates
	the Pointers- indexes of the array which  dvision with the best and worst sales */
void Best_Worst_Sales(division* d, int* i_best, int* i_worst)
{
	int i;
	*i_best = 0;
	*i_worst = 0;
	for (i = 0; i < N; i++)
	{
		if ((d[i].sold_items) > (d[*i_best].sold_items))
			*i_best = i;
		if ((d[i].sold_items) < (d[*i_worst].sold_items))
			*i_worst = i;
	}
}
