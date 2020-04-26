#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 256
#define Code_Book_Len 10

typedef struct Book {
	char Code[Code_Book_Len + 1];
	char* BookName;
}Book;
typedef struct Library
{
	char LibName[MAX + 1];
	int num_books;
	Book* bk;

}Library;
void Get_Lost(char* str);
void input_book(Book* B, FILE* in);
void input_library(Library* L, FILE* in);
void output_book(Book* B, FILE* out);
void output_library(Library* L, FILE* out);

int main()
{
	FILE* in, * out;
	Library Libr;
	int i;
	in = fopen("input.txt", "rt");
	if (in == NULL)
		Get_Lost("Cannot open file");
	input_library(&Libr, in);
	fclose(in);
	out = fopen("output.txt", "wt");
	if (out == NULL)
		Get_Lost("Cannot open file");
	output_library(&Libr, out);
	fclose(out);
	for (i = 0; i < Libr.num_books; i++)
		free(Libr.bk[i].BookName);
	free(Libr.bk);
	return 0;
}
void input_library(Library* L, FILE* in)
{
	int i;
	fscanf(in, "%s%d", L->LibName, &L->num_books);
	L->bk = (Book*)malloc(L->num_books * sizeof(Book));
	if (L->bk == NULL)
	{
		free(L->bk);
		Get_Lost("Cannot Allocate Memory");
	}
	for (i = 0; i < L->num_books; i++)
		input_book(L->bk + i, in);

}
void input_book(Book* B, FILE* in)
{
	char BookName[MAX + 1];
	fscanf(in, "%s%s", B->Code, BookName);
	B->BookName = (char*)malloc((strlen(BookName) + 1) * sizeof(char));
	if (B->BookName == NULL)
	{
		free(B->BookName);
		Get_Lost("Cannot Allocate Memory");
	}
	strcpy(B->BookName, BookName);
}
void output_library(Library* L, FILE* out)
{
	int i;
	fprintf(out, "%s\n", L->LibName);
	for (i = 0; i < L->num_books; i++)
		output_book(L->bk + i, out);

}
void output_book(Book* B, FILE* out)
{
	fprintf(out, "%-10s",B->Code);
	fprintf(out,"%s\n",B->BookName);
}
void Get_Lost(char* str)
{
	printf("\n%s", str);
	exit(1);
}

