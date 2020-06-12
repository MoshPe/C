#include "Restaurant.h"

void main()
{
	int instruction_guide;
	int tableIndex;
	char productName[MAX_CHARS];
	int productAmount;
	Restaurant steakHouse;
	boolean memoryErrorAllocation = FALSE;
	FILE* instruction, * outputFile, * dishes;

	if (!(outputFile = fopen("output.txt", "w")))
		Error_Msg("\nThe input file is wrong");
	if (!(dishes = fopen("Manot.txt", "r")))
	{
		fclose(outputFile);
		Error_Msg("\nThe Manot file is wrong\n");
	}
	if (!(instruction = fopen("Instructions.txt", "r")))
	{
		fclose(dishes);
		fclose(outputFile);
		Error_Msg("\nThe Instructions file is wrong\n");
	}
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
	// in case that the amount of tables is below or equal 0
	else
	{
		fprintf(outputFile, "The table amount inside instruction file is incorrect\n");
		fclose(instruction);
		fclose(outputFile);
		fclose(dishes);
		free(steakHouse.tables);
		exit(1);
	}
	//reseting all the tables checkoutputFilePrice and list
	tableReset(&steakHouse);
	//gettint the first instruction
	fscanf(instruction, "%d", &instruction_guide);
	//Checking if the first instruction is to extract data from the kitchen
	if (instruction_guide != 1)
	{
		fprintf(outputFile, "Need to input dishes to the kithchen first\noption 1 must be selected first!!!\n");
		fclose(instruction);
		fclose(outputFile);
		fclose(dishes);
		exit(1);
	}
	//reseting the kitchen list to start receiving items
	steakHouse.mainKitchen.head = NULL;
	steakHouse.mainKitchen.tail = NULL;
	//checking if successfully extracted data from Manot file(dishes) to the kitchen list
	if (createProducts(dishes, &steakHouse, outputFile) == TRUE)
	{
		fprintf(outputFile, "Success in extracting the kitchen data!!\nThe kitchen was created\n");
		//extracting the instructions data from the instruction file 
		while (fscanf(instruction, "%d", &instruction_guide) != EOF && memoryErrorAllocation != TRUE)
		{
			switch (instruction_guide)
			{
			case 1:
				fprintf(outputFile, "Extracting data to the kitchen is avilable only once!!!\n");
				//checking if the rest of the instruction aren't incorrect
				optionValidationCheck(instruction);
				break;
			case 2:
				fscanf(instruction, "%s %d", productName, &productAmount);
				addItems(productName, productAmount, outputFile, &steakHouse);
				//checking if the rest of the instruction aren't incorrect
				optionValidationCheck(instruction);
				break;
			case 3:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				//checking if the allocation memory succeeded in function,orderItems
				if (orderItems(productName, tableIndex, productAmount, &steakHouse, outputFile) == NO_MEMORY_ERROR)
					memoryErrorAllocation = TRUE;
				//checking if the rest of the instruction aren't incorrect
				optionValidationCheck(instruction);
				break;
			case 4:
				fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
				removeItem(productName, tableIndex, productAmount, &steakHouse, outputFile);
				//checking if the rest of the instruction aren't incorrect
				optionValidationCheck(instruction);
				break;
			case 5:
				fscanf(instruction, "%d", &tableIndex);
				removeTable(tableIndex, &steakHouse, outputFile);
				//checking if the rest of the instruction aren't incorrect
				optionValidationCheck(instruction);
				break;
			default:
				fprintf(outputFile, "Wrong instruction option, please fix the file!!!\n");
				//moving the pointer to the next line in the instruction file
				optionValidationCheck(instruction);
				break;
			}
		}
	}
	//in case that the program couldnt extract the data to the kitchen
	else fprintf(outputFile, "fail to extracting the kitchen data!!\n");
	FreeThemAll(&steakHouse);
	fclose(instruction);
	fclose(outputFile);
	fclose(dishes);
}
