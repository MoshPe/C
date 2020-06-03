#ifndef  _Restaurant
#define _Restaurant

//#define NO_MEMORY_ERROR 2
//#define TRUE 1
//#define FALSE 0

typedef enum {FALSE,TRUE,NO_MEMORY_ERROR,}boolean;

#define MAX_CHARS 200
#define _CRT_SECURE_NO_WARNINGS
////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////
typedef struct error
{
	char[200] name1;
	char[200] name2;
	char[200] name3;
	char[200] name4; 
}error;
////
typedef struct Product
{
	char* productName;
	float price;
	int quantity;
	int ordersCount; 
	struct Product* next, * prev;
}Product, * pProduct;
////
typedef struct Kitchen
{
	struct Product* head, * tail;
}Kitchen, * PKitchen, tableDishes;
////
typedef struct Table
{
	float checkoutPrice;
	tableDishes dishes;
}Table, * PTable;
////
typedef struct Restaurant
{
	Kitchen mainKitchen;
	PTable tables;
	int amountOfTables;
	int amountOfCheckedInTables;  
}Restaurant, * PRestaurant;
////
boolean createProducts(FILE*, PRestaurant, FILE*);
void addItems(char*, int, FILE*, PKitchen);
boolean orderItems(char*, int, int, PRestaurant, FILE*);
void removeItem(char*, int, int, PKitchen, PRestaurant, FILE*);
boolean removeTable(int, PRestaurant, FILE*);
boolean isTableExists(int, int, FILE*);
pProduct getProductAddress(char*, PKitchen);
boolean CheckStringsLength(char*, unsigned int, char*, PRestaurant,FILE*);
pProduct allocateNewProduct();
void delete_list(pProduct);
void Error_Msg(char*);
void FreeThemAll(PRestaurant);
void tableReset(PRestaurant);
boolean validation_Input(char*, int, float, PRestaurant,FILE*);
void updateNewNodeFields(pProduct,pProduct);
void insertNewNode(PRestaurant,pProduct);


#endif // ! _Restaurant
