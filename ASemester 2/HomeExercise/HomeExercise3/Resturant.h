#ifndef  _Resturant
#define _Resturant

#define NO_MEMORY_ERROR -1
#define TRUE 1
#define FALSE 0
#define MAX_CHARS 200
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product
{
	char* productName;
	float price;
	int quantity;
	int ordersCount;       ////////////////////////////////////////////////array                                                     
	struct Product* next, * prev;      
}Product, * pProduct;                                               

typedef struct Kitchen
{
	struct Product* head, * tail;
}Kitchen, * PKitchen, tableDishes;

typedef struct Table
{
	float checkoutPrice;
	tableDishes dishes;
}Table, * PTable;

typedef struct Resturant
{
	Kitchen mainKitchen;
	PTable tables;
	int amountOfTables;
}Resturant, * PResturant;


int createProducts(FILE*, PResturant, FILE*);
void addItems(char*, int, FILE*, PKitchen);
int orderItems(char*, int, int, PResturant, FILE*);
void removeItem(char*,int,int,PKitchen, PResturant, FILE*);
int removeTable(int, PResturant, FILE*);
int isTableExists(int, int, FILE*);
pProduct getProductAddress(char*, PKitchen);
void CheckStringsLength(char*, unsigned int, char*, PResturant);
pProduct addNewItem(PResturant);
void delete_list(pProduct);
void Error_Msg(char*);
void FreeThemAll(PResturant);
void tableReset(PResturant);
int validation_Input(char*,int,float,PResturant);


#endif // ! _Resturant
