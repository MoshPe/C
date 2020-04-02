#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Person
{
	char ID[10];
	char F_name[11];
	char L_name[16];
	int Age;
	char Addr[51];
}Person;

void Error_Msg(char*);

int main()
{
	Person temp;
	FILE* in, * out;
	in = fopen("the_first.txt", "r");
	if (in == NULL)
		Error_Msg("Unable to open file the_first.txt");
	out = fopen("the_second.txt", "wt");
	if (in == NULL)
		Error_Msg("Unable to open file the_second.txt");
	fscanf(in, "%s%s%s%d%s", temp.ID, temp.F_name, temp.L_name, &temp.Age, temp.Addr);
	fprintf(out, "ID:%s\nFull name:%s %s\nAge:%d\nAddress:%s", temp.ID, temp.F_name, temp.L_name, temp.Age, temp.Addr);
	fclose(in);


	return 0;
}



void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}