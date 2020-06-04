#ifndef _Restaurant
#define _Restaurant
////
#define MAX_CHARS 200
#define _CRT_SECURE_NO_WARNINGS
////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////
typedef enum boolean { FALSE, TRUE, NO_MEMORY_ERROR} boolean;
typedef enum functionName { addItemsValidation, orderItemsValidation, removeItemValidation, removeTableValidation} functionName;
////
#define DEFAULT_TABLE_INDEX 1
#define DEFAULT_ITEM_AMOUNT 1
#define ALLOCATION_ERROR_TEMPLATE "\n Couldnt allocate memory for %s"
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
boolean validation_Input(char*, int, float, PRestaurant, FILE*);
boolean CheckStringsLength(char*, unsigned int, char*, PRestaurant, FILE*);
boolean createProducts(FILE*, PRestaurant, FILE*);
boolean isFunctionValid(PRestaurant, int, int, int, pProduct, FILE*);
void addItems(char*, int, FILE*, PRestaurant);
boolean orderItems(char*, int, int, PRestaurant, FILE*);
void removeItem(char*, int, int, PKitchen, PRestaurant, FILE*);
boolean removeTable(int, PRestaurant, FILE*);
pProduct getPopularDish(PRestaurant);
void printTableCheckOut(PRestaurant, int, FILE*);
boolean isTableExists(int, int, FILE*);
pProduct getProductAddress(char*, PKitchen);
pProduct allocateNewProduct();
void delete_list(pProduct);
void Error_Msg(char*);
void FreeThemAll(PRestaurant);
void tableReset(PRestaurant);
void updateNewNodeFields(pProduct, pProduct, int);
void insertNewNode(PRestaurant, pProduct,int,int);

#endif // ! _Restaurant
