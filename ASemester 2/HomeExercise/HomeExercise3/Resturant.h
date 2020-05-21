#ifndef  _Resturant
#define _Resturant

#define NO_MEMORY -1
#define MAX 200
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product
{
	char* productName;
	float price;
	int quantity;
	int orderCount;
	struct Product* next, * prev;
}Product, * pProduct;

typedef struct Table
{
	float checkOut;
	tableDishes dishes;
}Table, * PTable;

typedef struct Kitchen
{
	struct Product* head, * tail;
}Kitchen, * PKitchen, tableDishes;

typedef struct Resturant
{
	Kitchen mainKitchen;
	PTable tables;
	int tablesAmount;
}Resturant, * PResturant;


int createProducts(FILE*, PKitchen, FILE*);
void addItems(char*, int, FILE*, PKitchen);
int orderItems(char*, int, int, PResturant, FILE*);
void removeItem(char*,int,int,PKitchen, PResturant, FILE*);
void removeTable(int, PResturant, FILE*);
int tableIndexCheck(int, int, FILE*);
pProduct productAvailable_check(char*, PKitchen);
void CheckStrings(char*, unsigned int, char*, PResturant);
pProduct addNode();
void delete_list(pProduct);
void Error_Msg(char*);

#endif // ! _Resturant
