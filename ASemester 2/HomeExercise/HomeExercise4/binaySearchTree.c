#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"
/////////////////
typedef struct treeNode
{
	struct treeNode* right;
	struct treeNode* left;
	PKEY key;
}treeNode;
/////////////////
typedef struct functions
{
	isKeysEqual isEqualFunc;
	isLeftOrRight isLeftOrRightFunc;
	printKeys printKeysFunc;
}functions;
/////////////////
PFunctions initFunctionsStruct(isKeysEqual isEqualFunc, isLeftOrRight isLeftOrRightFunc, printKeys printKeysFunc)
{
	PFunctions temp = (PFunctions)malloc(sizeof(functions));	
	if (temp != NULL)
	{
		temp->isEqualFunc = isEqualFunc;
		temp->isLeftOrRightFunc = isLeftOrRightFunc;
		temp->printKeysFunc = printKeysFunc;
	}
		return temp;
}
/////////////////
PTreeNode getAllocatedMemoryAddress()
{
	PTreeNode allocatedAddressToReturn = (PTreeNode)malloc(sizeof(treeNode));
	if (allocatedAddressToReturn != NULL)
	{
		allocatedAddressToReturn->right = NULL;
		allocatedAddressToReturn->left = NULL;
	}
	return allocatedAddressToReturn;
}
//The function checks if the given keys are already exist in the tree
isFree isKeyFree(PTreeNode root, PKEY key, PFunctions functionManager)
{
	if (root == NULL)
		return FREE;
	if (functionManager->isEqualFunc(key, root->key))
		return NOT_FREE;
	else
	{
		if (functionManager->isLeftOrRightFunc(root->key, key))
			return isKeyFree(root->right, key, functionManager);
		else
			return isKeyFree(root->left, key, functionManager);
	}
}
/*
Function name: CheckStringsLength
Input: A string to check, the size required,the name of the string, the string name, the retaurant
	   ,steakHouse,the output file for printing
Algoritem: It checks the length of the string by strlen() function, if it is above the required length
		   the function pulls outputFile a message and terminate the program
*/
boolean addNewTreeNode(PTreeNode* root,PKEY keyToInsert, PFunctions functionManager,FILE* outPutFile)
{
	PTreeNode newNodeToInsert;
	if (*root == NULL)
	{
		newNodeToInsert = getAllocatedMemoryAddress();
		if (newNodeToInsert == NULL)
		{
			fprintf(outPutFile,ALLOCATION_ERROR_TEMPLATE,"new node");
			return NO_MEMORY_ERROR;
		}
		newNodeToInsert->key = keyToInsert;
		(*root) = newNodeToInsert;
	}
	else
	{
		if (functionManager->isLeftOrRightFunc((*root)->key, keyToInsert))
			return addNewTreeNode(&(*root)->right, keyToInsert, functionManager,outPutFile);
		else
			return addNewTreeNode(&(*root)->left, keyToInsert, functionManager, outPutFile);
	}
	functionManager->printKeysFunc(keyToInsert, outPutFile, DEFAULT_NEW_NODE_PRINT);
	return TRUE;
}
//the function prints the keys by Inorder way recursivly
void printKeysByInorder(PTreeNode root, PFunctions functionManager,int* printOnce, FILE* outPutFile)
{
	if (*printOnce == 1)
	{
		fprintf(outPutFile, "The keys by inorder way are: ");
		(*printOnce)--;
	}
	if (root != NULL) 
	{
		printKeysByInorder(root->left, functionManager, printOnce, outPutFile);
		functionManager->printKeysFunc(root->key, outPutFile, DEFAULT_KEY_PRINT);
		printKeysByInorder(root->right, functionManager, printOnce, outPutFile);
	}
}
//recursive function which returns the height of a given tree
int treeHeight(PTreeNode root)
{
	int leftHeight, rightHeight;
	//checking if the list is empty and acts as end-break of the recursion
	if (root == NULL)
		return -1;
	//counts the amount of nodes in the left side of the tree
	leftHeight = treeHeight(root->left);
	//counts the amount of nodes in the right side of the tree
	rightHeight = treeHeight(root->right);
	//returns the max height + the root(+1), to pay back the -1 from the if above
	return 1 + Max(leftHeight, rightHeight);
}
//function ro print the max key in the tree unrecursivly
void printMaxKey(PTreeNode root, PFunctions functionManager, FILE* outPutFile)
{
	PTreeNode getMaxKeyAddress = root;
	while (getMaxKeyAddress->right)
		getMaxKeyAddress = getMaxKeyAddress->right;
	functionManager->printKeysFunc(getMaxKeyAddress->key, outPutFile, DEFAULT_MAX_KEY_PRINT);
}
/*
Function name: printGivenKeysAmount
Input: A string to check, the size required,the name of the string, the string name, the retaurant
	   ,steakHouse,the output file for printing
Algoritem: It checks the length of the string by strlen() function, if it is above the required length
		   the function pulls outputFile a message and terminate the program
*/
void printGivenKeysAmount(int* amountOfNodes,PTreeNode root, PFunctions functionManager, int* amountOfKeysToPrint,int* printOnce, FILE* outPutFile)
{
	if (*amountOfNodes < *amountOfKeysToPrint)
	{
		fprintf(outPutFile, "There are no %d elements in this tree\n", *amountOfKeysToPrint);
		return;
	}
	else if (*printOnce == 1)
	{
		fprintf(outPutFile, "There are %d elements in this tree: ", *amountOfKeysToPrint);
		(*printOnce)--;
	}
	if (root == NULL)
		return;
	printGivenKeysAmount(amountOfNodes,root->left, functionManager, amountOfKeysToPrint, printOnce, outPutFile);
	if (*amountOfKeysToPrint == 0)
		return;
	functionManager->printKeysFunc(root->key, outPutFile, DEFAULT_KEY_PRINT);
	(*amountOfKeysToPrint)--;
	printGivenKeysAmount(amountOfNodes,root->right, functionManager, amountOfKeysToPrint, printOnce, outPutFile);
}
//The function deletes the tree
void FreeThemAll(PTreeNode root,Free freeFunc)
{
	//going down to the tree nodes and checking if the tree isnt empty
	if (root != NULL)
	{

		FreeThemAll(root->left, freeFunc);
		FreeThemAll(root->right, freeFunc);
		//free the tree from the end
		freeFunc(root,root->key);
	}
	//setting the *root of the current place in the recursion to null and go back to the previous reursion caller
	root = NULL;
}
void Error_Msg(char* msg)
{
	fprintf(stderr, "\n%s", msg);
	exit(1);
}
//The function goes down a line to avoid any incorrect instructions
void optionValidationCheck(FILE* instruction)
{
	char optionValidationCheck = getc(instruction);
	while (optionValidationCheck != '\n' && optionValidationCheck != EOF)
		optionValidationCheck = getc(instruction);
}
