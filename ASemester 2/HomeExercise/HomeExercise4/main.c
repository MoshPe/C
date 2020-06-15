#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"

side isLeftOrRightInt(PKEY root, PKEY key)
{
	if (*(int*)root > * (int*)key)
		return left;
	return right;
}
boolean isEqualInt(PKEY a, PKEY b)
{
	if (*(int*)a == *(int*)b)
		return TRUE;
	return FALSE;
}
void printKeysInt(PKEY key, FILE* outPutFile, char* newNodePrintString)
{
	fprintf(outPutFile, "%d %s", *(int*)key, newNodePrintString);
}

void main()
{
	FILE* instruction, * outputFile;
	int instruction_guide;
	PTree tree;
	PTreeNode root;
	int key;
	boolean memoryErrorAllocation = FALSE;
	if (!(outputFile = fopen("output.txt", "w")))
		Error_Msg("\nThe input file is wrong");
	if (!(instruction = fopen("Instructions.txt", "r")))
	{
		fclose(outputFile);
		Error_Msg("\nThe Instructions file is wrong\n");
	}
	while (fscanf(instruction, "%d", &instruction_guide) != EOF && memoryErrorAllocation != TRUE)
	{
		switch (instruction_guide)
		{
		case 1:
			fscanf(instruction, "%d",&key);
			if (addNewTreeNode(tree, root, &key, isLeftOrRightInt, isEqualInt, outputFile) == NO_MEMORY_ERROR)
				memoryErrorAllocation = TRUE;
			break;
		case 2:
			printKeysByInorder(root, printKeysInt, outputFile);
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
	FreeThemAll(&tree);/////////////////////////////////////////
	fclose(outputFile);
	fclose(instruction);
}