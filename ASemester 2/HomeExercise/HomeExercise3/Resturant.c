#include "Resturant.h"




void Error_Msg(char* msg)
{
	fprintf(stderr, "\n%s", msg);
	exit(1);
}
/*
Function name: CheckStrings
Input: A string, the size required,the name of the string, the University to free before exit(1)
Algoritem: It checks the length of the string by strlen() function, if it is above the required length
		   the function pulls out a message and terminate the program
*/
void CheckStrings(char* stringInput, unsigned int size, char* stringName, PResturant steakHouse)
{
	if (strlen(stringInput) > size)
	{
		fprintf(stderr, "\ninvalid %s!-the %s is too long.\nPlease fix the input file and try again!!!\n\n", stringName, stringName);
		FreeThemAll(steakHouse);
		exit(1);
	}
}
//return 1 if the fucntion succeed and 0 if didnt
int createProducts(FILE* inputFile, PResturant steakHouse, FILE* out)
{
	int gradeCount = 0;
	char productName[MAX];
	Product temp;
	temp.next = NULL;
	while (fscanf(inputFile, "%s %d %d", productName, &temp.quantity, &temp.price) != EOF)
	{
		//cheking if the product name string length is the correct length
		CheckStrings(productName, 50, "product name", steakHouse);
		temp.productName = (char*)malloc((strlen(productName) + 1) * sizeof(char));
		if (temp.productName == NULL)
		{
			FreeThemAll(steakHouse);//
			Error_Msg("No memory allocated for name");//
			return 0;
		}
		strcpy(temp.productName, productName);
		//Checking the terms for the price that has to be positive
		if (temp.price < 0)
		{
			FreeThemAll(steakHouse);
			Error_Msg("\ninvaldd id!-the id is incorect.\nPlease fix the input file and try again!!!\n\n");
			return 0;
		}
		//Checking the terms for the price that has to be positive
		if (temp.quantity < 0)
		{
			FreeThemAll(steakHouse);
			Error_Msg("\ninvaldd Mtm Grade!-the Mtm Grade is incorect.\nPlease fix the input file and try again!!!\n\n");
			return 0;
		}
		temp.orderCount = 0;
		//checking if the list in empty
		if (steakHouse->mainKitchen.head == NULL && steakHouse->mainKitchen.tail == NULL)
		{
			steakHouse->mainKitchen.head = &temp;
			steakHouse->mainKitchen.tail = &temp;
		}
		else
		{
			steakHouse->mainKitchen.tail->next = &temp;
			steakHouse->mainKitchen.tail = &temp;
		}
	}
	return 1;
}
//adding more to the stock of a certain item that exist in the kithen
void addItems(char* add_productName, int itemAmount, FILE* out, PKitchen mainKitchen)
{
	pProduct temp;
	//checking if the item is in the kitchen
	if (temp = productAvailable_check(add_productName, mainKitchen) == NULL)
	{
		fprintf(out, "No such item in the kitchen!!!");
		return;
	}
	temp->quantity += itemAmount;
}
//adding items to the table dishes list
int orderItems(char* productName, int tableIndex, int orderAmount, PResturant steakHouse, FILE* out)
{
	pProduct temp;
	pProduct if_exist_dish;
	pProduct newNode;
	if (orderAmount < 0)
	{
		fprintf(out, "incorrect order Amount");
		return 0;
	}
	else
	{
		if (tableIndexCheck(tableIndex, steakHouse->tablesAmount, out) == 0)
			return 0;
		if (temp = productAvailable_check(productName, &steakHouse->mainKitchen) == NULL)
		{
			fprintf(out, "We don't have %s, sorry!", productName);
			return 0;
		}
		if (temp->quantity < orderAmount)
		{
			fprintf(out, "The required product had sold out!");
			return 0;
		}
		//counting the amount of ordered dish
		temp->orderCount += orderAmount;
		//checking if the table ordered the same dish
		if (if_exist_dish = productAvailable_check(productName, steakHouse->tables[tableIndex - 1].dishes.head, out) == NULL)
		{
			if_exist_dish->quantity += orderAmount;
				//updating the checkout price for the table
				steakHouse->tables[tableIndex - 1].checkOut += (temp->price * orderAmount);
		}
		//making new node for input to table list
		newNode = addNode();
		if (newNode == NULL)
			return NO_MEMORY;
		//updating the kitchen stock
		temp->quantity -= orderAmount;
		//updating the new node
		strcpy(newNode->productName, temp->productName);
		newNode->price = temp->price;
		newNode->quantity = orderAmount;
		//updating the checkout price for the table
		steakHouse->tables[tableIndex - 1].checkOut += (newNode->price * orderAmount);
		//checking if the list is empty updating the table list and table checkout
		if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
		{
			steakHouse->tables[tableIndex - 1].dishes.head = newNode;
			steakHouse->tables[tableIndex - 1].dishes.tail = newNode;
		}
		//updatit the table list and table checkout
		else
		{
			newNode->next = steakHouse->tables[tableIndex - 1].dishes.head;
			steakHouse->tables[tableIndex - 1].dishes.head->prev = newNode;
			steakHouse->tables[tableIndex - 1].dishes.head = newNode;
		}
	}
	return 1;
}
//
void removeItem(char* productName, int tableIndex, int orderAmount, PKitchen mainKitchen, PResturant steakHouse, FILE* out)
{
	pProduct temp;
	if (orderAmount < 0)
	{
		fprintf(out, "incorrect quantities");
		return;
	}
	else
	{
		if (tableIndexCheck(tableIndex, steakHouse->tablesAmount, out) == 0)
			return;
		if (temp = productAvailable_check(productName, &steakHouse->mainKitchen, out) == NULL)
		{
			fprintf(out, "We don't have %s, sorry!", productName);
			return;
		}
		if (temp = productAvailable_check(productName, &steakHouse->tables[tableIndex - 1].dishes) == NULL)
		{
			fprintf(out, "This table did not oredered %s, sorry!", productName);
			return;
		}
		if (temp->quantity < orderAmount)
		{
			fprintf(out, "This table had ordered less then requaired to return the dish!");
			return;
		}
		//updating the checkOut price after returning the dish
		steakHouse->tables[tableIndex - 1].checkOut -= (temp->price * orderAmount);
		//checking if the dish is the head of the list
		if (temp == steakHouse->tables[tableIndex - 1].dishes.head)
			steakHouse->tables[tableIndex - 1].dishes.head = temp->next;
		//checking if the dish is the tail of the list
		else if (temp == steakHouse->tables[tableIndex - 1].dishes.tail)
			steakHouse->tables[tableIndex - 1].dishes.tail = temp->prev;
		//the dish is int the list
		else
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		free(temp);
	}
}
//
void removeTable(int tableIndex, PResturant steakHouse, FILE* out)
{
	pProduct temp;
	Product popular;
	int i;
	int openTalbes = 0;
	//checking if there are any open tables
	if (steakHouse->tablesAmount == 0)
	{
		fprintf(out, "\nThere are no open tables!");
		return;
	}
	//checking if the given table index had oredered anything
	else if (steakHouse->tables[tableIndex - 1].dishes.head == NULL)
	{
		fprintf(out, "\nThere are no orders for this table!");
		return;
	}
	//checking if the table index is correct
	else if (tableIndexCheck(tableIndex, steakHouse->tablesAmount, out) == 0)
		return;
	//counting the amount of open tables
	for (i = 0; i < steakHouse->tablesAmount - 1; i++)
	{
		if (steakHouse->tables[i].dishes.head != NULL)
			openTalbes++;
	}
	if (openTalbes == 1)
	{
		//setting max to the first node in the list of kithecn items
		popular.orderCount = steakHouse->mainKitchen.head->orderCount;
		temp = steakHouse->mainKitchen.head;
		//looping thorough all the kithchen list to find the most popular item
		while (temp != NULL)
		{
			if (temp->orderCount > popular.orderCount)
			{
				popular.orderCount = temp->orderCount;
				strcpy(popular.productName, temp->productName);
			}
			temp = temp->next;
		}
		//since its the only table in the resturant, head will be it
		//printing all the table data
		int i = tableIndex - 1;
		temp = steakHouse.tables[i]->dishes.head;
		while (temp != NULL)
		{
			fprintf(out, "\n%d %s. %f nis,please!", temp->quantity, temp->productName, temp->price);
			temp = temp->next;
		}
		fprintf(out, "The most popular dish today is %s! (was ordered %d times)", popular.productName, popular.orderCount);
		//free the head's dishes list,since it had only 1 table open
		delete_list(steakHouse->tables->dishes.head);
		//free all the resturant array
		free(steakHouse->tables);
		return;
	}
	//if the table isnt the first and only table open,then free this table list
	temp = steakHouse->tables[tableIndex - 1]->dishes.head;
	while (temp != NULL)
	{
		fprintf(out, "\n%d %s. %f nis,please!", temp->quantity, temp->productName, temp->price);
		temp = temp->next;
	}
	delete_list(steakHouse->tables[tableIndex - 1]->dishes.head);
}
//checking if the product exist in the kitchen menu 
pProduct productAvailable_check(char* productName, PKitchen stock)
{
	pProduct temp = stock->head;
	while (temp != NULL)
	{
		if (strcmp(temp->productName, productName) == 1)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
//checking if the given table index is correct
int tableIndexCheck(int index, int tablesAmount, FILE* out)
{
	if (index > tablesAmount || index < 0)
	{
		fprintf(out, "The table index is incorrect");
		return 0;
	}
	return 1;
}
// adding new node to a list
pProduct addNode()
{
	pProduct temp;
	temp = (pProduct)malloc(sizeof(Product));
	if (temp == NULL)
		Delete_List();
	return temp;
}
//deleting a list
void delete_list(pProduct head)
{
	pProduct temp;
	while (head != NULL)
	{
		temp = head;
		free(temp->productName);
		free(temp);
		head = head->next;
	}
}