#include "Resturant.h"

//TODO Care about the malloc free problem, bcuz you free twice and you cant xD
void main()
{
	int instruction_guide;
	int tableIndex;
	char productName[MAX_CHARS];
	int productAmount;
	Resturant steakHouse;
	int error_input = 0;
	//
	FILE* instruction, * outputFile, * dishes;
	if (!(outputFile = fopen("outputFile.txt", "w")))
		Error_Msg("\nThe input file is wrong");
	if (!(dishes = fopen("Manot.txt", "r")))
		Error_Msg("\nThe Manot file is wrong");
	if (!(instruction = fopen("Instructions.txt", "r")))
		Error_Msg("\nThe Instructions file is wrong");
	//getting the tables amount
	fscanf(instruction, "%d", &steakHouse.amountOfTables);
	if (steakHouse.amountOfTables > 0)
	{
		//creating an array of tables with the given tables amount
		steakHouse.tables = (PTable)malloc(steakHouse.amountOfTables * sizeof(Table));
		if (steakHouse.tables == NULL)
		{
			fclose(instruction);
			fclose(outputFile);
			fclose(dishes);
			Error_Msg("Couldn't allocat memory for tables");
		}
	}
	else
	{
		fprintf(outputFile, "\nThe table amount inside instruction file is incorrect");
		error_input = 1;
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
	if (createProducts(dishes, &steakHouse, outputFile) == 1)
	{
		fprintf(outputFile, "Success in extracting the kitchen data!!\nThe kitchen was created");
		while (fscanf(instruction, "%d", &instruction_guide) != EOF && error_input != 1)
		{
			switch (instruction_guide)
			{
			case 1:
				fprintf(outputFile, "Extracting data to the kitchen is aviable to do only once!!!");
				break;
			case 2:
				fscanf(instruction, "%s %d", productName, &productAmount);
				addItems(productName, productAmount, outputFile, &steakHouse.mainKitchen);
				break;
			case 3:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				if (orderItems(productName, tableIndex, productAmount, &steakHouse, outputFile) == NO_MEMORY_ERROR)
					error_input = 1;
				break;
			case 4:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				removeItem(productName, tableIndex, productAmount, &steakHouse.mainKitchen, &steakHouse, outputFile);
				break;
			case 5:
				fscanf(instruction, "%d", &tableIndex);
				if (removeTable(tableIndex, &steakHouse, outputFile) == NO_MEMORY_ERROR)
					error_input = 1;
				break;

			default:
				fprintf(outputFile, "\nWrong option instruction, please fix the file!!!");
				fseek(instruction, 65, SEEK_SET);
				break;
			}
		}
	}
	else fprintf(outputFile, "fail to extracting the kitchen data!!\n");
	//FreeThemAll(&steakHouse);
	fclose(instruction);
	fclose(outputFile);
	fclose(dishes);
}
