#include "Restaurant.h"

boolean validation_Input(char* productName, int quantity, float price,PRestaurant steakHouse,FILE* outputFile)
{
	//cheking if the product name string length is the correct length
	if (CheckStringsLength(productName, 50, "product name", steakHouse, outputFile) == FALSE)
		return FALSE;
	//Checking the terms for the price that has to be positive 
	if (price < 0)
	{
		//fprintf(stderr, "The new item price is incorrect\n");
		fprintf(outputFile, "The new item price is incorrect\n");
		return FALSE;
	}
	//Checking the terms for the price that has to be positive
	if (quantity < 0)
	{
		//fprintf(stderr, "The new item quantity is incorrect\n");
		fprintf(outputFile, "The new item amount is incorrect\n");
		return FALSE;
	}
	return TRUE;
}
//return 1 if the function succeed and 0 if didn't
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
				fprintf(outputFile, "Couldnt allocate memory for new item in the kitchen");
				return NO_MEMORY_ERROR;//! problem with the free in the main 
			}
		}
	}
	return TRUE;
}
//adding more to the stock of a certain item that exist in the kithen
void addItems(char* productNameToAdd, int addItemAmount, FILE* outputFile, PRestaurant steakHouse)
{
	pProduct productAddress;
	productAddress = functionValidations(steakHouse, addItemsTwo, noTableIndexNeeded, addItemAmount, productNameToAdd, outputFile);
	if (productAddress == NULL)
		return;
	productAddress->quantity += addItemAmount;
	fprintf(outputFile, "\n%d %s were added to the kitchen", addItemAmount, productNameToAdd);

}
//adding items to the table dishes list
boolean orderItems(char* productName, int tableIndex, int orderAmount, PRestaurant steakHouse, FILE* outputFile)
{

	pProduct productKitchenAddress;
	pProduct getTableDishAddress;
	pProduct newProduct;
	//todo
	productKitchenAddress = functionValidations(steakHouse, orderItemsThree, tableIndex, orderAmount, productName, outputFile);
	if (productKitchenAddress == NULL)
		return FALSE;
	//counting the amount of ordered dish
	productKitchenAddress->ordersCount += orderAmount;
	//checking if the table ordered the same dish
	getTableDishAddress = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
	//counting the number of open tables
	if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
		steakHouse->amountOfCheckedInTables++;
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
			//todo FreeThemAll(steakHouse);
			fprintf(stderr, "\nCouldnt allocate memory for new item name");
			return NO_MEMORY_ERROR;
		}
		//TODO updating the new node
		updateNewNodeFields(newProduct, productKitchenAddress,orderAmount);
		insertNewNode(steakHouse, newProduct,tableIndex,orderAmount);
	}
	fprintf(outputFile, "\n%d %s were added to table number %d", orderAmount, productName, tableIndex);
	return TRUE;
}
/////////
void insertNewNode(PRestaurant steakHouse, pProduct newProduct, int tableIndex, int orderAmount)
{
	//updating the checkoutPrice price for the table
	steakHouse->tables[tableIndex - 1].checkoutPrice += (newProduct->price * orderAmount);
	//checking if the list is empty updating the table list and table checkoutPrice
	if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
	{
		steakHouse->tables[tableIndex - 1].dishes.head = newProduct;
		steakHouse->tables[tableIndex - 1].dishes.tail = newProduct;
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
void updateNewNodeFields(pProduct newProduct, pProduct productKitchenAddress, int orderAmount)
{
	strcpy(newProduct->productName, productKitchenAddress->productName);
	newProduct->price = productKitchenAddress->price;
	newProduct->quantity = orderAmount;
}

//
void removeItem(char* productName, int tableIndex, int itemReturnAmount, PKitchen mainKitchen, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct removeDishAddress;
	removeDishAddress = functionValidations(steakHouse, removeItemFour, tableIndex, itemReturnAmount, productName, outputFile);
	if (removeDishAddress == NULL)
		return;
		//updating the checkoutPrice price after returning the dish
		steakHouse->tables[tableIndex - 1].checkoutPrice -= (removeDishAddress->price * itemReturnAmount);
	//checking if we have to eliminate the whole node or just reduce the quantity
	if (removeDishAddress->quantity == itemReturnAmount)
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
		removeDishAddress->quantity -= itemReturnAmount;
	fprintf(outputFile, "\n%d %s was returned to the kitchen from table number %d", itemReturnAmount, productName, tableIndex);
}
//
boolean removeTable(int tableIndex, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct deleteTableAddress;
	Product popular;
	pProduct findPopularDish;
	deleteTableAddress = functionValidations(steakHouse, removeTableFive, tableIndex, noOrderAddRemoveItemAmountNeeded, noProductNameNeeded, outputFile);
	if (deleteTableAddress == NULL)
		return FALSE;
	if (steakHouse->amountOfCheckedInTables == 1)
	{
		//setting popular to the first node in the list of kitchen items
		popular.ordersCount = steakHouse->mainKitchen.head->ordersCount;
		findPopularDish = steakHouse->mainKitchen.head;
		//looping thorough all the kithchen list to find the most popular item
		while (findPopularDish != NULL)
		{
			if (findPopularDish->ordersCount > popular.ordersCount)
			{
				popular.ordersCount = findPopularDish->ordersCount;
				popular.productName = (char*)malloc(strlen(findPopularDish->productName + 1) * sizeof(char));
				if (popular.productName == NULL)
				{
					//FreeThemAll(steakHouse);
					fprintf(stderr, "Couldnt allocate memory for popular name\n");
					return NO_MEMORY_ERROR;
				}
				strcpy(popular.productName, findPopularDish->productName);
			}
			findPopularDish = findPopularDish->next;
		}
		checkOutTablePrint(deleteTableAddress, steakHouse, tableIndex, outputFile);
		fprintf(outputFile, "The most popular dish today is %s! (was ordered %d times)\n", popular.productName, popular.ordersCount);
	}
	//if the table isn't the first and the table open,then free this table list
	else
		checkOutTablePrint(deleteTableAddress, steakHouse, tableIndex, outputFile);
	return TRUE;
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
	if (index > amountOfTables || index < 1)
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
boolean CheckStringsLength(char* stringInput, unsigned int requiredSize, char* stringName, PRestaurant steakHouse, FILE* outputFile)
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
pProduct functionValidations(PRestaurant steakHouse, int functionName, int tableIndex, int actionToItemAmount, char* productName, FILE* outputFile)
{
	//reseting the new validationCheck 
	pProduct validationCheck = NULL;
	if (!isTableExists(tableIndex, steakHouse->amountOfTables, outputFile))
		return NULL;
	else
	{
		switch (functionName)
		{
		case addItemsTwo:
			validationCheck = getProductAddress(productName, &steakHouse->mainKitchen);
				if (validationCheck == NULL)
					{
					fprintf(outputFile, "\nNo such item in the kitchen!!!");
					return NULL;
					}
				if (actionToItemAmount <= 0)
					{
					fprintf(outputFile, "\nThe item quantity to add is incorrect!");
					return NULL;
					}
				break;
			case orderItemsThree:
				validationCheck = getProductAddress(productName, &steakHouse->mainKitchen);
				if (validationCheck == NULL)
					{
					fprintf(outputFile, "\nWe don't have %s, sorry!", productName);
					return NULL;
					}
				if (validationCheck->quantity < actionToItemAmount)
					{
					fprintf(outputFile, "\nThe required product had sold out!");
					return NULL;
					}
				if (actionToItemAmount <= 0)
					{
					fprintf(outputFile, "\nIncorrect order amount!!");
					return NULL;
					}
				break;
			case removeItemFour:
					if (actionToItemAmount <= 0)
						{
						fprintf(outputFile, "incorrect quantities\n");
						return NULL;
						}
				//brings back the dish location in the table list
					validationCheck = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
					if (validationCheck == NULL)
						{
						fprintf(outputFile, "\nThis table did not ordered %s, sorry!", productName);
						return NULL;
						}
					if (validationCheck->quantity < actionToItemAmount)
						{
						fprintf(outputFile, "\nThis table had ordered less then required to return the dish!");
						return NULL;
						}
				break;
			case removeTableFive:
					//checking if there are any open tables
					if (steakHouse->amountOfTables == 0)
						{
						fprintf(outputFile, "\nThere are no open tables!");
						return NULL;
						}
					//checking if the given table index had ordered anything
					if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
						{
						fprintf(outputFile, "\nThe table number %d has not ordered yet!", tableIndex);
						return NULL;
						}
					else
						validationCheck = steakHouse->tables[tableIndex - 1].dishes.head;
					break;
		}
	}
	return validationCheck;
}
void checkOutTablePrint(pProduct deleteTableAddress, PRestaurant steakHouse,int tableIndex,FILE* outputFile)
{
	fprintf(outputFile, "\nThe dishes that table number %d ordered: ", tableIndex);
	deleteTableAddress = steakHouse->tables[tableIndex - 1].dishes.head;
	while (steakHouse->tables[tableIndex - 1].dishes.head != NULL)
	{
		deleteTableAddress = steakHouse->tables[tableIndex - 1].dishes.head;
		fprintf(outputFile, "\n%d %s. %.1f nis,please!", deleteTableAddress->quantity, deleteTableAddress->productName, deleteTableAddress->price * (float)(deleteTableAddress->quantity));
		free(deleteTableAddress->productName);
		steakHouse->tables[tableIndex - 1].dishes.head = steakHouse->tables[tableIndex - 1].dishes.head->next;
		free(deleteTableAddress);
	}
	steakHouse->tables[tableIndex - 1].checkoutPrice = 0;
	steakHouse->amountOfCheckedInTables--;
}
////////
