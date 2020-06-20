#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"

side isLeftOrRightInt(PKEY root, PKEY key)
{
	if (*(int*)root < *(int*)key)
		return RIGHT;
	return LEFT;
}
isEqual isEqualInt(PKEY a, PKEY b)
{
	if (*(int*)a == *(int*)b)
		return EQUAL;
	return NOT_EQUAL;
}
void printKeysInt(PKEY key, FILE* outPutFile, char* newNodePrintString)
{
	fprintf(outPutFile, "%d %s", *(int*)key, newNodePrintString);
}
/*free the data allocated for the char,
its a specific function and changes
in different uses like struct which we have more
things to free
*/

void freeInt(PKEY key)
{
	free((int*)key);
}

void main()
{
	FILE* instruction, * outPutFile;
	int instruction_guide;
	PTreeNode root = NULL;
	PTree treeManager = NULL;
	int printOnce = 1;
	// for sending the address to the functions
	int keyToInsert, * PkeyToInsert;
	int amountOfKeysToPrint;
	boolean memoryErrorAllocation = FALSE;

	if (!(outPutFile = fopen("output.txt", "w")))
		Error_Msg("\nThe output file is wrong");
	if (!(instruction = fopen("Instructions.txt", "r")))
	{
		fclose(outPutFile);
		Error_Msg("\nThe Instructions file is wrong\n");
	}
	/*reseting the treeManager structure with all the functions and the amount of nodes
	  and checking if the function was successful 
	*/
	if ((treeManager = initFunctionsStruct(isEqualInt, isLeftOrRightInt, printKeysInt)) == NULL)
	{
		fprintf(outPutFile, ALLOCATION_ERROR_TEMPLATE, "functions manager");
		memoryErrorAllocation = TRUE;
	}
	//extracting the instructions data from the instruction file 
	while (fscanf(instruction, "%d", &instruction_guide) != EOF && memoryErrorAllocation != TRUE)
	{
		switch (instruction_guide)
		{
		case 1:
			// for sending the key address to the functions
			PkeyToInsert = (int*)malloc(sizeof(int));
			//checking if allocation was successful
			if (PkeyToInsert == NULL)
			{
				fprintf(outPutFile,ALLOCATION_ERROR_TEMPLATE,"the new key!!");
				fprintf(stderr,ALLOCATION_ERROR_TEMPLATE, "the new key!!");
				memoryErrorAllocation = TRUE;
				break;
			}
			fscanf(instruction, " %d", &keyToInsert);
			//keeping the value of the key in the pointer and send it to the functions
			*PkeyToInsert = keyToInsert;
			//checking if there is already the same key in the tree
			if (!isKeyFree(root, PkeyToInsert, treeManager))
			{
				fprintf(outPutFile, "Error!\nThere is an existing node with the same key = %d\n",*PkeyToInsert);
				free(PkeyToInsert);
				break;
			}
			//checking if the memory allocation in the function was a successful
			if (addNewTreeNode(&root, PkeyToInsert, treeManager, outPutFile) == NO_MEMORY_ERROR)
				memoryErrorAllocation = TRUE;
			optionValidationCheck(instruction);
			break;
		case 2:
			printKeysByInorderWay(root, treeManager, &printOnce, outPutFile);
			printOnce = 1;
			fputc('\n', outPutFile);
			//checking if the rest of the instruction aren't incorrect
			optionValidationCheck(instruction);
			break;
		case 3:
			fprintf(outPutFile, "The height of your tree is %d\n", treeHeight(root));
			//checking if the rest of the instruction aren't incorrect
			optionValidationCheck(instruction);
			break;
		case 4:
			printMaxKey(root, treeManager, outPutFile);
			//checking if the rest of the instruction aren't incorrect
			optionValidationCheck(instruction);
			break;
		case 5:
			fscanf(instruction, "%d", &amountOfKeysToPrint);
			printGivenKeysAmount(root, treeManager,&amountOfKeysToPrint, &printOnce, outPutFile);
			if (!printOnce)
			{
				fputc('\n', outPutFile);
				printOnce = 1;
			}
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
	free(treeManager);
	fclose(outPutFile);
	fclose(instruction);
}