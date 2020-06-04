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
		fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item in the kitchen");
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
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item name");
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
				fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item in the kitchen");
				return NO_MEMORY_ERROR;//! problem with the free in the main 
			}
		}
	}
	return TRUE;
}
//adding more to the stock of a certain item that exist in the kitchen
void addItems(char* productNameToAdd, int addItemAmount, FILE* outputFile, PRestaurant steakHouse)
{
	pProduct productAddress;
	productAddress = getProductAddress(productNameToAdd, &steakHouse->mainKitchen);
	if (!isFunctionValid(steakHouse, addItemsValidation, DEFAULT_TABLE_INDEX, addItemAmount, productAddress, outputFile))
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
	productKitchenAddress = getProductAddress(productName, &steakHouse->mainKitchen);
	if (productKitchenAddress == NULL)
	{
		fprintf(outputFile, "\nWe don't have %s, sorry!", productName);
		return FALSE;
	}
	if(!isFunctionValid(steakHouse, orderItemsValidation, tableIndex, orderAmount, productKitchenAddress, outputFile))
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
		//updating the checkOutPrice price for the table
		steakHouse->tables[tableIndex - 1].checkoutPrice += (productKitchenAddress->price * orderAmount);
	}
	else
	{
		//making new node for input to table list
		newProduct = allocateNewProduct();
		if (newProduct == NULL)
		{
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE," new node for table number");
			return NO_MEMORY_ERROR;
		}
		//updating the kitchen stock
		productKitchenAddress->quantity -= orderAmount;
		newProduct->productName = (char*)malloc((strlen(productKitchenAddress->productName) + 1) * sizeof(char));
		if (newProduct->productName == NULL)
		{
			//todo FreeThemAll(steakHouse);
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item name");
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
	//updating the checkOutPrice price for the table
	steakHouse->tables[tableIndex - 1].checkoutPrice += (newProduct->price * orderAmount);
	//checking if the list is empty updating the table list and table checkOutPrice
	if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
	{
		steakHouse->tables[tableIndex - 1].dishes.head = newProduct;
		steakHouse->tables[tableIndex - 1].dishes.tail = newProduct;
	}
	//updating the table list and table checkOutPrice
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
void removeItem(char* productName, int tableIndex, int itemAmountToReturn, PKitchen mainKitchen, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct dishAddressToRemove;
	dishAddressToRemove = getProductAddress(productName, &steakHouse->mainKitchen);
	if(!isFunctionValid(steakHouse, removeItemValidation, tableIndex, itemAmountToReturn, dishAddressToRemove, outputFile))
		return;
		//updating the checkOutPrice price after returning the dish
		steakHouse->tables[tableIndex - 1].checkoutPrice -= (dishAddressToRemove->price * itemAmountToReturn);
	//checking if we have to eliminate the whole node or just reduce the quantity
	if (dishAddressToRemove->quantity == itemAmountToReturn)
	{
		//checking if the dish is the head of the list
		if (dishAddressToRemove == steakHouse->tables[tableIndex - 1].dishes.head)
		{
			steakHouse->tables[tableIndex - 1].dishes.head = NULL;
			steakHouse->tables[tableIndex - 1].dishes.tail = NULL;
			steakHouse->amountOfCheckedInTables--;
		}
		//checking if the dish is the tail of the list
		else if (dishAddressToRemove == steakHouse->tables[tableIndex - 1].dishes.tail)
			steakHouse->tables[tableIndex - 1].dishes.tail = dishAddressToRemove->prev;
		//the dish is in the list
		else
		{
			dishAddressToRemove->prev->next = dishAddressToRemove->next;
			dishAddressToRemove->next->prev = dishAddressToRemove->prev;
		}
		free(dishAddressToRemove->productName);
		free(dishAddressToRemove);
	}
	else
		dishAddressToRemove->quantity -= itemAmountToReturn;
	fprintf(outputFile, "\n%d %s was returned to the kitchen from table number %d", itemAmountToReturn, productName, tableIndex);
}
//
boolean removeTable(int tableIndex, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct tableAddressToDelete;

	tableAddressToDelete = steakHouse->tables[tableIndex - 1].dishes.head;
	if(!isFunctionValid(steakHouse, removeTableValidation, tableIndex, DEFAULT_ITEM_AMOUNT, tableAddressToDelete, outputFile))
		return FALSE;
	if (steakHouse->amountOfCheckedInTables == 1)
	{
		tableAddressToDelete = getPopularDish(steakHouse);
		printTableCheckOut(steakHouse, tableIndex, outputFile);
		fprintf(outputFile, "The most popular dish today is %s! (was ordered %d times)\n", tableAddressToDelete->productName, tableAddressToDelete->ordersCount);
	}
	//if the table isn't the first and the table open,then free this table list
	else
		printTableCheckOut(steakHouse, tableIndex, outputFile);
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
boolean isFunctionValid(PRestaurant steakHouse, int functionName, int tableIndex, int itemAmountByAction, pProduct productAddress, FILE* outputFile)
{
	if (!isTableExists(tableIndex, steakHouse->amountOfTables, outputFile))
		return FALSE;
	else
	{
		switch (functionName)
		{
		case addItemsValidation:
				if (productAddress == NULL)
					{
					fprintf(outputFile, "\nNo such item in the kitchen!!!");
					return FALSE;
					}
				if (itemAmountByAction <= 0)
					{
					fprintf(outputFile, "\nThe item quantity to add is incorrect!");
					return FALSE;
					}
				break;
			case orderItemsValidation:
				if (productAddress->quantity < itemAmountByAction)
					{
					fprintf(outputFile, "\nThe required product had sold out!");
					return FALSE;
					}
				if (itemAmountByAction <= 0)
					{
					fprintf(outputFile, "\nIncorrect order amount!!");
					return FALSE;
					}
				break;
			case removeItemValidation:
					if (itemAmountByAction <= 0)
						{
						fprintf(outputFile, "incorrect quantities\n");
						return FALSE;
						}
					//brings back the dish location in the table list
					//productAddress = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
					if (productAddress == NULL)
						{
						fprintf(outputFile, "\nThis table did not ordered %s, sorry!", productAddress->productName);
						return FALSE;
						}
					if (productAddress->quantity < itemAmountByAction)
						{
						fprintf(outputFile, "\nThis table had ordered less then required to return the dish!");
						return FALSE;
						}
				break;
			case removeTableValidation:
					//checking if there are any open tables
					if (steakHouse->amountOfTables == 0)
						{
						fprintf(outputFile, "\nThere are no open tables!");
						return FALSE;
						}
					//checking if the given table index had ordered anything
					if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
						{
						fprintf(outputFile, "\nThe table number %d has not ordered yet!", tableIndex);
						return FALSE;
						}
				break;
		}
	}
	return TRUE;
}
void printTableCheckOut(PRestaurant steakHouse,int tableIndex,FILE* outputFile)
{
	pProduct tableAddressToDelete;
	fprintf(outputFile, "\nThe dishes that table number %d ordered: ", tableIndex);
	while (steakHouse->tables[tableIndex - 1].dishes.head != NULL)
	{
		tableAddressToDelete = steakHouse->tables[tableIndex - 1].dishes.head;
		fprintf(outputFile, "\n%d %s. %.1f nis,please!", tableAddressToDelete->quantity, tableAddressToDelete->productName, tableAddressToDelete->price * (float)(tableAddressToDelete->quantity));
		free(tableAddressToDelete->productName);
		steakHouse->tables[tableIndex - 1].dishes.head = steakHouse->tables[tableIndex - 1].dishes.head->next;
		free(tableAddressToDelete);
	}
	steakHouse->tables[tableIndex - 1].checkoutPrice = 0;
	steakHouse->amountOfCheckedInTables--;
}

pProduct getPopularDish(PRestaurant steakHouse)
{
	pProduct popularDishAddress;
	pProduct dishAddressIterator;

	//setting popular to the first node in the list of kitchen items
	popularDishAddress = steakHouse->mainKitchen.head;
	dishAddressIterator = steakHouse->mainKitchen.head;
	//looping thorough all the kithchen list to find the most popular item
	while (dishAddressIterator != NULL)
	{
		if (dishAddressIterator->ordersCount > popularDishAddress->ordersCount)
			popularDishAddress = dishAddressIterator;
		dishAddressIterator = dishAddressIterator->next;
	}
	return popularDishAddress;
}