#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"

side isLeftOrRightInt(PKEY root, PKEY key)
{
	if (*(char*)root < *(char*)key)
		return RIGHT;
	return LEFT;
}
isEqual isEqualInt(PKEY a, PKEY b)
{
	if (*(char*)a == *(char*)b)
		return EQUAL;
	return NOT_EQUAL;
}
void printKeysInt(PKEY key, FILE* outPutFile, char* newNodePrintString)
{
	fprintf(outPutFile, "%c %s", *(char*)key, newNodePrintString);
}
void freeInt(PTreeNode root,PKEY key)
{
	free(key);
	free(root);
}

void main()
{
	FILE* instruction, * outPutFile;
	int instruction_guide;
	PTreeNode root = NULL;
	PFunctions functionManager = NULL;
	int printOnce = 1;
	char keyToInsert, * PkeyToInsert;
	int amountOfNodes = 0, amountOfKeysToPrint;
	boolean memoryErrorAllocation = FALSE;
	//
	if (!(outPutFile = fopen("output.txt", "w")))
		Error_Msg("\nThe output file is wrong");
	if (!(instruction = fopen("Instructions.txt", "r")))
	{
		fclose(outPutFile);
		Error_Msg("\nThe Instructions file is wrong\n");
	}
	if ((functionManager = initFunctionsStruct(isEqualInt, isLeftOrRightInt, printKeysInt)) == NULL)
	{
		fprintf(outPutFile, ALLOCATION_ERROR_TEMPLATE, "functions manager");
		memoryErrorAllocation = TRUE;
	}
	while (fscanf(instruction, "%d", &instruction_guide) != EOF && memoryErrorAllocation != TRUE)
	{
		switch (instruction_guide)
		{
		case 1:
			PkeyToInsert = (char*)malloc(sizeof(char));
			if (PkeyToInsert == NULL)
			{
				fprintf(outPutFile,ALLOCATION_ERROR_TEMPLATE,"the new key!!");
				fprintf(stderr,ALLOCATION_ERROR_TEMPLATE, "the new key!!");
				memoryErrorAllocation = TRUE;
				break;
			}
			fscanf(instruction, " %c", &keyToInsert);
			*PkeyToInsert = keyToInsert;
			if (!isKeyFree(root, PkeyToInsert, functionManager))
			{
				fprintf(outPutFile, "Error!\nThere is an existing node with the same key = %c\n",*PkeyToInsert);
				free(PkeyToInsert);
				break;
			}
			if (addNewTreeNode(&root, PkeyToInsert, functionManager, outPutFile) == NO_MEMORY_ERROR)
				memoryErrorAllocation = TRUE;
			amountOfNodes++;
			optionValidationCheck(instruction);
			break;
		case 2:
			if (!amountOfNodes)
			{
				fprintf(outPutFile, "The tree is empty");
				break;
			}
			printKeysByInorder(root, functionManager, &printOnce, outPutFile);
			printOnce = 1;
			optionValidationCheck(instruction);
			break;
		case 3:
			fprintf(outPutFile, "The height of your tree is %d\n", treeHeight(root));
			optionValidationCheck(instruction);
			break;
		case 4:
			if (!amountOfNodes)
			{
				fprintf(outPutFile, "The tree is empty");
				break;
			}
			printMaxKey(root, functionManager, outPutFile);
			//checking if the rest of the instruction aren't incorrect
			optionValidationCheck(instruction);
			break;
		case 5:
			fscanf(instruction, "%d", &amountOfKeysToPrint);
			printGivenKeysAmount(&amountOfNodes, root, functionManager,&amountOfKeysToPrint, &printOnce, outPutFile);
			//fputc('\n', outPutFile);
			printOnce = 1;
			//checking if the rest of the instruction aren't incorrect
			optionValidationCheck(instruction);
			break;
		default:
			fprintf(outPutFile, "Wrong instruction option, please fix the file!!!\n");
			//moving the pointer to the next line in the instruction file
			optionValidationCheck(instruction);
			break;
		}
	}
	FreeThemAll(root, freeInt);
	free(functionManager);
	fclose(outPutFile);
	fclose(instruction);
}