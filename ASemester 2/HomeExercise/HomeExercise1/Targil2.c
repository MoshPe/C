#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define MAX 150

typedef struct Department {
	char code[10];
	char* name;
	int soldItems;
}Depart;

void newDepart(Depart* depart);
void pointOrder(Depart** departP, Depart* depart);
void printWinLoseDepart(Depart** depart);
void CheckStrings(char* s, unsigned int size, char* name);
void NoMemory();

int main() {
	int i;
	Depart department[N];
	Depart* departmentP[N];

	for (i = 0; i < N; i++) {
		newDepart(&department[i]);	//collect information about every department
		departmentP[i] = &department[i]; //Add to the array pointer the adress of the every department
	}
	pointOrder(departmentP, department); //order the departments
	printWinLoseDepart(departmentP);	//print the best and wrost departments
	for (i = 0; i < N; i++)
		free(department[i].name);
	return 0;
}

//Function that collect the infromation about the department from the user
void newDepart(Depart* depart) {
	char name[MAX];
	printf("Enter class code: ");
	scanf("%s",depart->code);
	CheckStrings(depart->code, 10, "code");
	printf("Enter class name: ");
	rewind(stdin);
	scanf("%s",name);
	CheckStrings(name, 20, "name");
	depart->name = (char*)malloc((strlen(name)+1) * sizeof(char));
	if (depart->name == NULL)
	{
		free(depart->name);
		NoMemory();
	}
	strcpy(depart->name,name);
	printf("Enter amount of sold items: ");
	scanf("%d",&depart->soldItems);
}
/*checking if the string did not exceed the size limited to them*/
void CheckStrings(char* s, unsigned int size, char* name)
{
	while (strlen(s) > size)
	{
		printf("\ninvalid %s!-the %s is too long,please try again\n", name, name);
		printf("Please enter the %s (max %d): \n", name, size);
		rewind(stdin);
		scanf("%s",s);
	}
}
/*Function that change the order of the pointers by putting the best department on the
first place in the pointers array and putting the worst department on the second place
of the pointers array*/
void pointOrder(Depart** departP, Depart* depart) {
	int i;
	int bestSales = departP[0]->soldItems, badSales = departP[0]->soldItems;
	Depart** temp;

	for (i = 1; i < N; i++) {
		if (bestSales < departP[i]->soldItems) {
			bestSales = departP[i]->soldItems;
			temp = departP[0];
			departP[0] = departP[i];
			departP[i] = temp;
		}
	}
	for (i = 1; i < N; i++) {
		if (badSales > departP[i]->soldItems) {
			badSales = departP[i]->soldItems;
			temp = departP[1];
			departP[1] = departP[i];
			departP[i] = temp;
		}
	}
}
// Function that print the results
void printWinLoseDepart(Depart** depart) {
	printf("\nThe best class is %s with code number %s\n", depart[0]->name, depart[0]->code);
	printf("The wrost class is %s with code number %s\n", depart[1]->name, depart[1]->code);
}
void NoMemory()
{
	printf("\nError: not enough memory");
	exit(1);
}
