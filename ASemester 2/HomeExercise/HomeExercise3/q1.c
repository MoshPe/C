#include "Resturant.h"


void main()
{
	int instruction_guide;
	int tableIndex;
	char productName[MAX];
	int productAmount;
	Resturant steakHouse;
	int error_input = 0;
	int i;
	//
	FILE* instruction, * outPut, * dishes;
	if (!(outPut = fopen("outPut.txt", "w")))
		Error_Msg("\nThe input file is wrong");
	if (!(dishes = fopen("Manot.txt", "r")))
		Error_Msg("\nThe Manot file is wrong");
	if (!(instruction = fopen("Instructions.txt", "r")))
		Error_Msg("\nThe Instructions file is wrong");

	fscanf(instruction, "%d", &steakHouse.tablesAmount);
	if (steakHouse.tablesAmount > 0)
		Error_Msg("\nThe table amount inside instruction file is incorrect");
	//
	steakHouse.tables = (PTable)malloc(steakHouse.tablesAmount * sizeof(Table));
	if (steakHouse.tables == NULL)
		Error_Msg("Couldn't allocat memory for tables");
	for (i = 0; i < steakHouse.tablesAmount; i++)
	{
		steakHouse.tables[i].checkOut = 0;
		steakHouse.tables[i].dishes.head = NULL;
		steakHouse.tables[i].dishes.tail = NULL;
	}
	//
	fscanf(instruction, "%d", &instruction_guide);
	if (instruction_guide != 1)
		Error_Msg("\nNeed to input dishes to the kithchen first\noption 1 must be selected first!!!");
	if (createProducts(dishes, &steakHouse.mainKitchen, outPut) == 1)
		fprintf(outPut, "Success in extracting the kitchen data!!");
	else fprintf(outPut, "failt to extracting the kitchen data!!");

	while (fscanf(instruction, "%d", &instruction_guide) != EOF && error_input != 1)
	{
		switch (instruction_guide)
		{
		case '2':
			fscanf(instruction, "%s %d", productName, &productAmount);
			addItems(productName, productAmount, outPut, &steakHouse.mainKitchen);
			break;
		case '3':
			fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
			 if (orderItems(productName, tableIndex, productAmount, &steakHouse, outPut) != NO_MEMORY)
					break;
		case '4':
			fscanf(instruction, "%d %s %d", &tableIndex, productName, &productAmount);
			removeItem(productName, tableIndex, productAmount, &steakHouse.mainKitchen, &steakHouse, outPut);
			break;
		case '5':
			fscanf(instruction, "%d",&tableIndex);
			removeTable(tableIndex,&steakHouse, outPut);
			break;

		default:
			fprintf(outPut, "Wrong option, please fix the file!!!");
			for (i = 0; i < steakHouse.tablesAmount; i++)
				delete_list(&steakHouse.tables[i].dishes);
			delete_list(&steakHouse.mainKitchen);
			free(&steakHouse.tablesAmount);
			error_input = 1;
			break;
		}
	}
	fclose(instruction);
	fclose(outPut);
	fclose(dishes);
}