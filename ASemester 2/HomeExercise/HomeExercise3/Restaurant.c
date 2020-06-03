#include "Restaurant.h"





boolean validation_Input(char* productName, int quantity, float price, PRestaurant steakHouse,FILE* outputFile)
{
	//cheking if the product name string length is the correct length
	if (CheckStringsLength(productName, 50, "product name", steakHouse,outputFile) == FALSE)
		return FALSE;
	//Checking the terms for the price that has to be positive 
	if (price < 0)
	{
		fprintf(stderr, "The new item price is incorrect\n");
		fprintf(outputFile, "The new item price is incorrect\n");
		return FALSE;
	}
	//Checking the terms for the price that has to be positive
	if (quantity < 0)
	{
		fprintf(stderr, "The new item quanntity is incorrect\n");
		fprintf(outputFile, "The new item price is incorrect\n");
		return FALSE;
	}
	return TRUE;
}
//return 1 if the fucntion succeed and 0 if didnt
boolean createProducts(FILE* inputFile, PRestaurant steakHouse, FILE* outputFile)
{
	char productName[MAX_CHARS];
	pProduct isExist;
	pProduct newNode = (pProduct)malloc(sizeof(Product));
	if (newNode == NULL)
	{
		fprintf(stderr, "Couldnt allocate memory for new item in the kitchen\n");
		return NO_MEMORY_ERROR;//! problem with the free in the main 
	}
	newNode->next = NULL;
	while (fscanf(inputFile, "%s %d %f", productName, &newNode->quantity, &newNode->price) != EOF)
	{
		if (validation_Input(productName, newNode->quantity, newNode->price,steakHouse,outputFile) == FALSE)
			return FALSE;
		newNode->productName = (char*)malloc((strlen(productName) + 1) * sizeof(char));
		if (newNode->productName == NULL)
		{
			fprintf(stderr, "Couldnt allocate memory for new item name");
			return NO_MEMORY_ERROR;//! problem with the free in the main 
		}
		strcpy(newNode->productName, productName);
		newNode->ordersCount = 0;
		if ((isExist = getProductAddress(productName, &steakHouse->mainKitchen)) != NULL)
			isExist->quantity += newNode->quantity;
		else
		{
			//checking if the list in empty
			if (steakHouse->mainKitchen.head == NULL && steakHouse->mainKitchen.tail == NULL)
			{
				steakHouse->mainKitchen.head = newNode;
				steakHouse->mainKitchen.tail = newNode;
			}
			else
			{
				steakHouse->mainKitchen.tail->next = newNode;
				steakHouse->mainKitchen.tail = newNode;
				steakHouse->mainKitchen.tail->next = NULL;
			}
			newNode = (pProduct)malloc(sizeof(Product));
			if (newNode == NULL)
			{
				fprintf(stderr, "Couldnt allocate memory for new item in the kitchen");
				return NO_MEMORY_ERROR;//! problem with the free in the main 
			}
		}
	}
	return TRUE;
}
//adding more to the stock of a certain item that exist in the kithen
void addItems(char* productNameToAdd, int itemAmount, FILE* outputFile, PKitchen mainKitchen)
{
	pProduct productAddress;
	//checking if the item is in the kitchen
	productAddress = getProductAddress(productNameToAdd, mainKitchen);
	if (productAddress == NULL)
	{
		fprintf(outputFile, "\nNo such item in the kitchen!!!");
		return;
	}
	productAddress->quantity += itemAmount;
	fprintf(outputFile, "\n%d %s were added to the kitchen", itemAmount, productNameToAdd);
}
//adding items to the table dishes list
boolean orderItems(char* productName, int tableIndex, int orderAmount, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct productKitchenAddress;
	pProduct getTableDishAddress;
	pProduct newProduct;
	if (orderAmount <= 0)
	{
		fprintf(outputFile, "\nincorrect order Amount");
		return FALSE;
	}
	if (!isTableExists(tableIndex, steakHouse->amountOfTables, outputFile))
		return FALSE;
	productKitchenAddress = getProductAddress(productName, &steakHouse->mainKitchen);
	if (productKitchenAddress == NULL)
	{
		fprintf(outputFile, "\nWe don't have %s, sorry!", productName);
		return FALSE;
	}
	if (productKitchenAddress->quantity < orderAmount)
	{
		fprintf(outputFile, "\nThe required product had sold out!");
		return FALSE;
	}
	//counting the amount of ordered dish
	productKitchenAddress->ordersCount += orderAmount;
	//checking if the table ordered the same dish
	getTableDishAddress = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
	if (getTableDishAddress != NULL)
	{
		getTableDishAddress->quantity += orderAmount;
		//updating the checkoutPrice price for the table
		steakHouse->tables[tableIndex - 1].checkoutPrice += (productKitchenAddress->price * orderAmount);
	}
	else
	{
		//making new node for input to table list
		newProduct = allocateNewProduct();
		if (newProduct == NULL)
		{
			fprintf(outputFile, "\nCouldnt allocate a new node for table number %d", tableIndex);
			return NO_MEMORY_ERROR;
		}
		//updating the kitchen stock
		productKitchenAddress->quantity -= orderAmount;
		newProduct->productName = (char*)malloc((strlen(productKitchenAddress->productName) + 1) * sizeof(char));
		if (newProduct->productName == NULL)
		{
			//FreeThemAll(steakHouse);
			fprintf(stderr, "\nCouldnt allocate memory for new item name");
			return NO_MEMORY_ERROR;
		}
		//TODO updating the new node
		updateNewNodeFields(newProduct,productKitchenAddress);
		insertNewNode(steakHouse,newProduct);
	}
	fprintf(outputFile, "\n%d %s were added to table number %d", orderAmount, productName, tableIndex);
	return TRUE;
}
//
void removeItem(char* productName, int tableIndex, int orderAmount, PKitchen mainKitchen, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct removeDishAddress;
	if (orderAmount < 0)
	{
		fprintf(outputFile, "incorrect quantities\n");
		return;
	}
	else
	{
		if (isTableExists(tableIndex, steakHouse->amountOfTables, outputFile) == 0)
			return;
		//brings back the dish location in the table list
		removeDishAddress = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
		if (removeDishAddress == NULL)
		{
			fprintf(outputFile, "\nThis table did not oredered %s, sorry!", productName);
			return;
		}
		if (removeDishAddress->quantity < orderAmount)
		{
			fprintf(outputFile, "\nThis table had ordered less then requaired to return the dish!");
			return;
		}
		//updating the checkoutPrice price after returning the dish
		steakHouse->tables[tableIndex - 1].checkoutPrice -= (removeDishAddress->price * orderAmount);
		//checking if we have to eliminate the whole node or just reduce the quantity
		if (removeDishAddress->quantity == orderAmount)
		{
			//checking if the dish is the head of the list
			if (removeDishAddress == steakHouse->tables[tableIndex - 1].dishes.head)
			{
				steakHouse->tables[tableIndex - 1].dishes.head = NULL;
				steakHouse->amountOfCheckedInTables--;
			}
				
			//checking if the dish is the tail of the list
			else if (removeDishAddress == steakHouse->tables[tableIndex - 1].dishes.tail)
				steakHouse->tables[tableIndex - 1].dishes.tail = removeDishAddress->prev;
			//the dish is int the list
			else
			{
				removeDishAddress->prev->next = removeDishAddress->next;
				removeDishAddress->next->prev = removeDishAddress->prev;
			}
			free(removeDishAddress);
		}
		else
			removeDishAddress->quantity -= orderAmount;
		fprintf(outputFile, "\n%d %s was returned to the kithcen form table number %d", orderAmount, productName, tableIndex);
	}
}
//
boolean removeTable(int tableIndex, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct deleteTable;
	Product popular;
	int i;
	//checking if there are any open tables
	if (steakHouse->amountOfTables == 0)
	{
		fprintf(outputFile, "\nThere are no open tables!");
		return FALSE;
	}
	//checking if the given table index had oredered anything
	else if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
	{
		fprintf(outputFile, "\nThe table number %d has not ordered yet!", tableIndex);
		return FALSE;
	}
	//checking if the table index is correct
	else if (isTableExists(tableIndex, steakHouse->amountOfTables, outputFile) == 0)
		return FALSE;
	if (steakHouse->amountOfCheckedInTables == 1)
	{
		//setting popular to the first node in the list of kithecn items
		popular.ordersCount = steakHouse->mainKitchen.head->ordersCount;
		deleteTable = steakHouse->mainKitchen.head;
		//looping thorough all the kithchen list to find the most popular item
		while (deleteTable != NULL)
		{
			if (deleteTable->ordersCount > popular.ordersCount)
			{
				popular.ordersCount = deleteTable->ordersCount;
				popular.productName = (char*)malloc(strlen(deleteTable->productName + 1) * sizeof(char));
				if (popular.productName == NULL)
				{
					//FreeThemAll(steakHouse);
					fprintf(stderr, "Couldnt allocate memory for popular name\n");
					return NO_MEMORY_ERROR;
				}
				strcpy(popular.productName, deleteTable->productName);
			}
			deleteTable = deleteTable->next;
		}
		//since its the only table in the Restaurant, head will be it
		//printing all the table data
		deleteTable = steakHouse->tables[tableIndex - 1].dishes.head;

		while (steakHouse->tables[tableIndex - 1].dishes.head != NULL)
		{
			fprintf(outputFile, "\n%d %s. %.2f nis,please!", deleteTable->quantity, deleteTable->productName, deleteTable->price * (float)(deleteTable->quantity));
			steakHouse->tables[tableIndex - 1].dishes.head = steakHouse->tables[tableIndex - 1].dishes.head->next;
		}
		fprintf(outputFile, "\nThe most popular dish today is %s! (was ordered %d times)", popular.productName, popular.ordersCount);
		//free the head's dishes list,since it had only 1 table open
		delete_list(steakHouse->tables[tableIndex - 1].dishes.head);
		//free all the Restaurant array
		//!free(steakHouse->tables);
		steakHouse->amountOfCheckedInTables--;
		return TRUE;
	}
	//if the table isnt the first and only table open,then free this table list
	deleteTable = steakHouse->tables[tableIndex - 1].dishes.head;
	while (steakHouse->tables[tableIndex - 1].dishes.head != NULL)
	{
		deleteTable = steakHouse->tables[tableIndex - 1].dishes.head;
		fprintf(outputFile, "\n%d %s. %.2f nis,please!", deleteTable->quantity, deleteTable->productName, deleteTable->price * (float)(deleteTable->quantity));
		free(deleteTable->productName);
		steakHouse->tables[tableIndex - 1].dishes.head = steakHouse->tables[tableIndex - 1].dishes.head->next;
		free(deleteTable);
	}
	//steakHouse->tables[tableIndex - 1].dishes.head = NULL;
	steakHouse->tables[tableIndex - 1].checkoutPrice = 0;
	return TRUE;
}
/////////
void insertNewNode(PRestaurant steakHouse,pProduct newProduct)
{
	//updating the checkoutPrice price for the table
	steakHouse->tables[tableIndex - 1].checkoutPrice += (newProduct->price * orderAmount);
	//checking if the list is empty updating the table list and table checkoutPrice
	if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
	{
		steakHouse->tables[tableIndex - 1].dishes.head = newProduct;
		steakHouse->tables[tableIndex - 1].dishes.tail = newProduct;
		steakHouse->amountOfCheckedInTables++;
	}
	//updating the table list and table checkoutPrice
	else
	{
		newProduct->next = steakHouse->tables[tableIndex - 1].dishes.head;
		steakHouse->tables[tableIndex - 1].dishes.head->prev = newProduct;
		steakHouse->tables[tableIndex - 1].dishes.head = newProduct;
	}
}
//////////////
void updateNewNodeFields(pProduct newProduct,pProduct productKitchenAddress)
	{
		strcpy(newProduct->productName, productKitchenAddress->productName);
		newProduct->price = productKitchenAddress->price;
		newProduct->quantity = orderAmount;
	}

//checking if the product exist in the kitchen menu 
pProduct getProductAddress(char* productName, PKitchen stock)
{
	pProduct temp = stock->head;
	while (temp != NULL)
	{
		if (strcmp(temp->productName, productName) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
//checking if the given table index is correct
boolean isTableExists(int index, int amountOfTables, FILE* outputFile)
{
	if (index > amountOfTables || index < 0)
	{
		fprintf(outputFile, "The table index is incorrect\n");
		return FALSE;
	}
	return TRUE;
}
// adding new node to a list
pProduct allocateNewProduct()
{
	pProduct temp;
	temp = (pProduct)malloc(sizeof(Product));
	temp->next = NULL;
	temp->prev = NULL;
	//the test if allocated is in the function
	return temp;
}
void Error_Msg(char* msg)
{
	fprintf(stderr, "\n%s", msg);
	exit(1);
}
/*
Function name: CheckStringsLength
Input: A string, the size required,the name of the string, the University to free before exit(1)
Algoritem: It checks the length of the string by strlen() function, if it is above the required length
		   the function pulls outputFile a message and terminate the program
*/
boolean CheckStringsLength(char* stringInput, unsigned int requiredSize, char* stringName, PRestaurant steakHouse,FILE* outputFile)
{
	if (strlen(stringInput) > requiredSize)
	{
		fprintf(stderr, "\ninvalid %s!-the %s is too long.\nPlease fix the input file and try again!!!\n\n", stringName, stringName);
		fprintf(outputFile, "\ninvalid %s!-the %s is too long.\nPlease fix the input file and try again!!!\n\n", stringName, stringName);
		return FALSE;
	}
	return TRUE;
}
void FreeThemAll(PRestaurant steakHouse)
{
	int i;
	for (i = 0; i < steakHouse->amountOfTables; i++)
	{
		if (steakHouse->tables[i].dishes.head != NULL)
			delete_list(steakHouse->tables[i].dishes.head);
	}
	delete_list(steakHouse->mainKitchen.head);
	free(steakHouse->tables);
}
//deleting a list
void delete_list(pProduct head)
{
	pProduct temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->productName);
	}
	head = NULL;
}
void tableReset(PRestaurant steakHouse)
{
	int i;
	for (i = 0; i < steakHouse->amountOfTables; i++)
	{
		steakHouse->tables[i].checkoutPrice = 0;
		steakHouse->tables[i].dishes.head = NULL;
		steakHouse->tables[i].dishes.tail = NULL;
	}
}
/////
	boolean functionValidations(name)
	{
		int flag;
		if(!NULL)
		flag =0;
		if (!flag)
		{
				switch (expression)
			{
			case "orderItems":
						printf("%s %d %c",print[0]);
				break;
			
			default:
				break;
			}

		}
		
		
	return TRUE;
	}
////////
//TODO list/array of all the strings according to the if's
//TODO array of flags every index is in relation to the error messages, in the case run on all the flags array 
//TODO if array == flash/true and print my printf according to the index of the error messages


char[2000] error;
strcpy(error,'skdjdghjfghjlsghlskgd');
flags - 		    [1]		[0]		[1]		[0]
error messages - [string][string][string][string]

if(!flag[i])
	strcpy(errorMessage,"");


error.

