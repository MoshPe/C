#include "Restaurant.h"
//The fuction checks the perfection of the given parameters
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
/*
Function name: createProducts
Input: The Manot inputFile, the restaurant pointer and the output file
Output: The function returns TRUE if it succeeded extracting data FALSE if it didnt successfuly extract the data
		and NO_MEMORY_ERROR if the malloc of the new node returned NULL
Algoritem: The function each time creates a new node by allocating memory, and then it puts the new data into that node
			and place the node in the list from the tail(Without using the prev pointer field in the product) 
*/
boolean createProducts(FILE* inputFile, PRestaurant steakHouse, FILE* outputFile)
{
	char productName[MAX_CHARS];
	pProduct isExist;
	//creating new node
	pProduct newNode = (pProduct)malloc(sizeof(Product));
	if (newNode == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item in the kitchen");
		return NO_MEMORY_ERROR;//! problem with the free in the main 
	}
	//reseting the next value in the new node
	newNode->next = NULL;
	while (fscanf(inputFile, "%s %d %f", productName, &newNode->quantity, &newNode->price) != EOF)
	{
		//Checking the perfecting of the given data
		if (validation_Input(productName, newNode->quantity, newNode->price,steakHouse,outputFile) == FALSE)
			return FALSE;
		//creating a new string to the new node by allocating memory with the size of the given string
		newNode->productName = (char*)malloc((strlen(productName) + 1) * sizeof(char));
		if (newNode->productName == NULL)
		{
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item name");
			return NO_MEMORY_ERROR;//! problem with the free in the main 
		}
		strcpy(newNode->productName, productName);
		//reseting the amount of orders for the most popular dish
		newNode->amountOfOrders = 0;
		//Checking if the kitchen already hold that item in the kitchen
		if ((isExist = getProductAddress(productName, &steakHouse->mainKitchen)) != NULL)
			isExist->quantity += newNode->quantity;
		else
		{
			//checking if the kitchen list in empty and putting the new item in the head and tail
			if (steakHouse->mainKitchen.head == NULL && steakHouse->mainKitchen.tail == NULL)
			{
				steakHouse->mainKitchen.head = newNode;
				steakHouse->mainKitchen.tail = newNode;
			}
			//if the list isnt empty, inputing the new item to the list from the tail
			else
			{
				steakHouse->mainKitchen.tail->next = newNode;
				steakHouse->mainKitchen.tail = newNode;
				steakHouse->mainKitchen.tail->next = NULL;
			}
			//creating a new node for the next item
			newNode = (pProduct)malloc(sizeof(Product));
			if (newNode == NULL)
			{
				fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item in the kitchen");
				return NO_MEMORY_ERROR;
			}
		}
	}
	return TRUE;
}
/*
Function name: addItems
Input: The product name to add to the kitchen, it's amount, the output file for printing and the retaurant, steakHouse
Output: The programs prints the product's name and quantity added to an exsisting item, else it prints that the kitchen
		doesn't hold that item
Algoritem: First the function checks the validation of the given product name and quantities, after that we get the 
			item address we add the amount given to the item quantity
*/
void addItems(char* productNameToAdd, int addItemAmount, FILE* outputFile, PRestaurant steakHouse)
{
	pProduct productAddressToAdd;
	//checking if the item exist in the kitchen, return null if doesnt and its address if it does
	productAddressToAdd = getProductAddress(productNameToAdd, &steakHouse->mainKitchen);
	//Checking if the item available in the kitchen
	if (productAddressToAdd == NULL)
	{
			fprintf(outputFile, "The kitchen doesn't hold %s!!!\n", productNameToAdd);
			return;
	}
	if (!isFunctionValid(steakHouse, addItemsValidation, DEFAULT_TABLE_INDEX, addItemAmount, productAddressToAdd, outputFile))
		return;
	//adding the quantities to an existing item in the kitchen
	productAddressToAdd->quantity += addItemAmount;
	fprintf(outputFile, "%d %s were added to the kitchen\n", addItemAmount, productNameToAdd);

}
/*
Function name: orderItems
Input: The product name to add to the table,the table index ,the amount of product, 
		the output file for printing and the retaurant, steakHouse,
Output: returns TRUE if the fucntion succeeded in creating a new node and insert it to the table list 
		FALSE if the product name or table index or the order amount is incorrect
		NO_MEMORY_ERROR if the fucntion failed to allocate memory
Algoritem: First the function checks the validation of the given product name,table index and the order amount
			, after that the fucntion checks if the items is exist in the kitchen.
			After all the test the fucntion creates a new node mallocly and transer the correct data to it,
			and insert it to the table list
*/
boolean orderItems(char* productName, int tableIndex, int orderAmount, PRestaurant steakHouse, FILE* outputFile)
{

	pProduct productKitchenAddress;
	pProduct getTableDishAddress;
	pProduct newProduct;
	//checking if the item exist in the kitchen, returns null if doesnt and its address if it does
	productKitchenAddress = getProductAddress(productName, &steakHouse->mainKitchen);
	//Checking if the item available in the kitchen
	if (productKitchenAddress == NULL)
	{
		fprintf(outputFile, "We don't have %s, sorry!\n", productName);
		return FALSE;
	}
	if(!isFunctionValid(steakHouse, orderItemsValidation, tableIndex, orderAmount, productKitchenAddress, outputFile))
		return FALSE;
	//counting the amount of the ordered dish and saving it for the popular dish of the day
	productKitchenAddress->amountOfOrders += orderAmount;
	//checking if the table ordered the same dish
	getTableDishAddress = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
	//counting the number of open tables
	if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
		steakHouse->amountOfCheckedInTables++;
	//if the items exist in the table, the function just adds the quantities to the same item
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
		//checking if the allocation memory succeeded
		if (newProduct == NULL)
		{
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE," new node for table order");
			//the main program(in the switch) checks if the allocation succeeded, if not the program ends
			return NO_MEMORY_ERROR;
		}
		//updating the kitchen item quantity
		productKitchenAddress->quantity -= orderAmount;
		//allocating memory for the new name in the same length of the given name
		newProduct->productName = (char*)malloc((strlen(productKitchenAddress->productName) + 1) * sizeof(char));
		//checking if the allocation memory succeeded
		if (newProduct->productName == NULL)
		{
			fprintf(stderr, ALLOCATION_ERROR_TEMPLATE,"new item name");
			//the main program(in the switch) checks if the allocation succeeded, if not the program ends
			return NO_MEMORY_ERROR;
		}
		//updating the new node data(fields)
		updateNewNodeFields(newProduct, productKitchenAddress,orderAmount);
		//inserting the new item in the table list
		insertNewNode(steakHouse, newProduct,tableIndex);
		//updating the checkOutPrice price for the table
		steakHouse->tables[tableIndex - 1].checkoutPrice += (productKitchenAddress->price * orderAmount);
	}
	fprintf(outputFile, "%d %s were added to table number %d\n", orderAmount, productName, tableIndex);
	return TRUE;
}
//The function inserts the new giving node to the table list
void insertNewNode(PRestaurant steakHouse, pProduct newProduct, int tableIndex)
{
	//checking if the list is empty and updating the table list 
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
//The fucntion updats the new giving node fields from the kitchen existing node
void updateNewNodeFields(pProduct newProduct, pProduct productKitchenAddress, int orderAmount)
{
	strcpy(newProduct->productName, productKitchenAddress->productName);
	newProduct->price = productKitchenAddress->price;
	newProduct->quantity = orderAmount;
}
/*
Function name: removeItem
Input: The product name to remove from the table,the table index ,the amount of product,
		the output file for printing and the retaurant, steakHouse,
Output: printf if the dish returned to the kitchen or that the table didnt ordered the dish 
Algoritem: First the function checks the validation of the given product name,table index and the return amount
			, after that the fucntion checks if the items is exist in the table.
			After all the tests the fucntion remove the item from the list is the qunatity or the returned item
			and the existing item is identical ,if not the functions just reduces the order amount
*/
void removeItem(char* productName, int tableIndex, int itemAmountToReturn, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct dishAddressToRemove;
	dishAddressToRemove = getProductAddress(productName, &steakHouse->tables[tableIndex - 1].dishes);
	//checking if the item exist in the table, returns null if doesnt and its address if it does
	if (dishAddressToRemove == NULL)
	{
		fprintf(outputFile, "This table did not ordered %s, sorry!\n", productName);
		return;
	}
	if (!isFunctionValid(steakHouse, removeItemValidation, tableIndex, itemAmountToReturn, dishAddressToRemove, outputFile))
			return;
	//updating the checkOutPrice price after returning the dish
	steakHouse->tables[tableIndex - 1].checkoutPrice -= (dishAddressToRemove->price * itemAmountToReturn);
	//checking if we have to eliminate the whole node or just reduce the quantity
	if (dishAddressToRemove->quantity == itemAmountToReturn)
	{
		//checking if the dish is the only dish int the table list
		if (dishAddressToRemove == steakHouse->tables[tableIndex - 1].dishes.head && dishAddressToRemove == steakHouse->tables[tableIndex - 1].dishes.tail)
		{
			steakHouse->tables[tableIndex - 1].dishes.head = NULL;
			steakHouse->tables[tableIndex - 1].dishes.tail = NULL;
			steakHouse->amountOfCheckedInTables--;
		}
		//checking if the dish is the tail of the list and there isnt only 1 dish in the table
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
	fprintf(outputFile, "%d %s was returned to the kitchen from table number %d\n", itemAmountToReturn, productName, tableIndex);
}
/*
Function name: removeTable
Input: The table index,the output file for printing and the retaurant, steakHouse,
Output: if the table is the last table, it prints the popular dish,otherwise,it only prints the 
		table checkoutPrice and the dishes
Algoritem: First the function checks the validation table index,after that the fucntion checks if the item
			exist in the table.
			After all the tests the fucntion free the table list and prints the table checkoutPrice and 
			its dished that the table had
*/
void removeTable(int tableIndex, PRestaurant steakHouse, FILE* outputFile)
{
	pProduct tableAddressToDelete;
	tableAddressToDelete = steakHouse->tables[tableIndex - 1].dishes.head;
	if(!isFunctionValid(steakHouse, removeTableValidation, tableIndex, DEFAULT_ITEM_AMOUNT, tableAddressToDelete, outputFile))
		return;
	//checking if there is only 1 table open then prints the popular dish
	if (steakHouse->amountOfCheckedInTables == 1)
	{
		// prints the table dishes and checkoutPrice
		printTableCheckOut(steakHouse, tableIndex, outputFile);
		//getting the popular dish address
		tableAddressToDelete = getPopularDish(steakHouse);
		//prints the most popular dish
		fprintf(outputFile, "The most popular dish today is %s! (was ordered %d times)\n", tableAddressToDelete->productName, tableAddressToDelete->amountOfOrders);
	}
	//if the table isn't the first and the table open,then free this table list
	else
		printTableCheckOut(steakHouse, tableIndex, outputFile);
}
//The function returns the item address from the kitchen or null if it doesnt exist in the kitchen
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
//Allocating a new memory for product node and reseting its next and prev pointers
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
Input: A string to check, the size required,the name of the string, the string name, the retaurant
	   ,steakHouse,the output file for printing
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
//Free all the table lists and the main kitchen list and the steakHouse->tables product array
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
//deletes the list and free the name in the same node
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
//resets all the tables lists and the checkoutPrice 
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
//The fucntion checks the main functions cases
boolean isFunctionValid(PRestaurant steakHouse, int functionName, int tableIndex, int itemAmountByAction, pProduct productAddress, FILE* outputFile)
{
	if (!isTableExists(tableIndex, steakHouse->amountOfTables, outputFile))
		return FALSE;
	else
	{
		switch (functionName)
		{
		case addItemsValidation:
				//checks if the item quantity to add is correct
				if (itemAmountByAction <= 0)
					{
						fprintf(outputFile, "The item quantity to add is incorrect!\n");
						return FALSE;
					}
				break;
			case orderItemsValidation:
				//checks the amount of ordered items to the quantities available in the kitchen of the same item
				if (productAddress->quantity < itemAmountByAction)
					{
						fprintf(outputFile, "The required product had sold out!\n");
						return FALSE;
					}
				//checks if the item quantity to add is correct
				if (itemAmountByAction <= 0)
					{
						fprintf(outputFile, "Incorrect order amount!!\n");
						return FALSE;
					}
				break;
			case removeItemValidation:
				//checks if the item quantity to add is correct
				if (itemAmountByAction <= 0)
					{
						fprintf(outputFile, "incorrect quantities\n");
						return FALSE;
					}
				//checks the amount of returned items to the quantities available in the table of the same item
				if (productAddress->quantity < itemAmountByAction)
					{
						fprintf(outputFile, "This table had ordered less then required to return the dish!\n");
						return FALSE;
					}
				break;
			case removeTableValidation:
					//checking if there are any open tables
					if (steakHouse->amountOfTables == 0)
						{
							fprintf(outputFile, "There are no open tables!\n");
							return FALSE;
						}
					//checking if the given table index had ordered anything
					if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
						{
							fprintf(outputFile, "The table number %d has not ordered yet!\n", tableIndex);
							return FALSE;
						}
				break;
		}
	}
	return TRUE;
}
//prints the table dishes and the checkoutPrice for the table and reseting the table list
void printTableCheckOut(PRestaurant steakHouse,int tableIndex,FILE* outputFile)
{
	pProduct tableAddressToDelete;
	while (steakHouse->tables[tableIndex - 1].dishes.head != NULL)
	{
		tableAddressToDelete = steakHouse->tables[tableIndex - 1].dishes.head;
		fprintf(outputFile, "%d %s.", tableAddressToDelete->quantity, tableAddressToDelete->productName);
		free(tableAddressToDelete->productName);
		steakHouse->tables[tableIndex - 1].dishes.head = steakHouse->tables[tableIndex - 1].dishes.head->next;
		free(tableAddressToDelete);
	}
	fprintf(outputFile, "%.0f nis,please!\n", steakHouse->tables[tableIndex - 1].checkoutPrice);
	steakHouse->tables[tableIndex - 1].checkoutPrice = 0;
	steakHouse->amountOfCheckedInTables--;
}
//searching for the most popular dish with the max orders in the kitchen and return its address
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
		if (dishAddressIterator->amountOfOrders > popularDishAddress->amountOfOrders)
			popularDishAddress = dishAddressIterator;
		dishAddressIterator = dishAddressIterator->next;
	}
	return popularDishAddress;
}
//The function goes down a line to avoid any incorrect instructions
void optionValidationCheck(FILE* instruction)
{
	char optionValidationCheck = getc(instruction);
	while (optionValidationCheck != '\n' && optionValidationCheck != EOF)
		optionValidationCheck = getc(instruction);
}
