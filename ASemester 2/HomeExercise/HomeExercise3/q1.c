#include "Restaurant.h"

//TODO Care about the malloc free problem, bcuz you free twice and you cant xD
void main()
{
	int instruction_guide;
	int tableIndex;
	char productName[MAX_CHARS];
	int productAmount;
	Restaurant steakHouse;
	boolean errorInput = FALSE;
	//////////////////
	FILE* instruction, * outputFile, * dishes;
	if (!(outputFile = fopen("blablablabla.txt", "w")))
		Error_Msg("\nThe input file is wrong");
	if (!(dishes = fopen("TestManot.txt", "r")))
		Error_Msg("\nThe Manot file is wrong");
	if (!(instruction = fopen("TestInstructions.txt", "r+")))
		Error_Msg("\nThe Instructions file is wrong");
	//getting the tables amount
	fscanf(instruction, "%d", &steakHouse.amountOfTables);
	//reseting the amount of open tables
	steakHouse.amountOfCheckedInTables = 0;
	if (steakHouse.amountOfTables > 0)
	{
		//creating an array of tables with the given tables amount
		steakHouse.tables = (PTable)malloc(steakHouse.amountOfTables * sizeof(Table));
		if (steakHouse.tables == NULL)
		{
			fclose(instruction);
			fclose(outputFile);
			fclose(dishes);
			Error_Msg("Couldn't allocate memory for tables");
		}
	}
	else
	{
		fprintf(outputFile, "\nThe table amount inside instruction file is incorrect");
		fclose(instruction);
		fclose(outputFile);
		fclose(dishes);
		exit(1);
	}
	//reseting all the tables checkoutputFilePrice and list
	tableReset(&steakHouse);
	//gettint the first instraction
	fscanf(instruction, "%d", &instruction_guide);
	if (instruction_guide != 1)
		Error_Msg("\nNeed to input dishes to the kithchen first\noption 1 must be selected first!!!");
	//reseting the kitchen list to start receiving items
	steakHouse.mainKitchen.head = NULL;
	steakHouse.mainKitchen.tail = NULL;
	//checking if successfully extracted data to kitchen list
	if (createProducts(dishes, &steakHouse, outputFile) == TRUE)
	{
		fprintf(outputFile, "Success in extracting the kitchen data!!\nThe kitchen was created");
		while (fscanf(instruction, "%d", &instruction_guide) != EOF && errorInput != TRUE)
		{
			switch (instruction_guide)
			{
			case 1:
				fprintf(outputFile, "Extracting data to the kitchen is aviable to do only once!!!");
				break;
			case 2:
				fscanf(instruction, "%s %d", productName, &productAmount);
				addItems(productName, productAmount, outputFile, &steakHouse);
				break;
			case 3:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				if (orderItems(productName, tableIndex, productAmount, &steakHouse, outputFile) == NO_MEMORY_ERROR)
					errorInput = TRUE;
				break;
			case 4:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				removeItem(productName, tableIndex, productAmount, &steakHouse.mainKitchen, &steakHouse, outputFile);
				break;
			case 5:
				fscanf(instruction, "%d", &tableIndex);
				if (removeTable(tableIndex, &steakHouse, outputFile) == NO_MEMORY_ERROR)
					errorInput = TRUE;
				break;
			default:
				fprintf(outputFile, "\nWrong option instruction, please fix the file!!!");
				while (getc(instruction) != '\n')
					fseek(instruction, 1, SEEK_CUR);
				break;
			}
		}
	}
	else fprintf(outputFile, "fail to extracting the kitchen data!!\n");
	FreeThemAll(&steakHouse);
	fclose(instruction);
	fclose(outputFile);
	fclose(dishes);
}
