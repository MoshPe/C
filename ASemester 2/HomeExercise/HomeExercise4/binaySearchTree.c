#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"

typedef struct treeNode
{
	struct treeNode* right;
	struct treeNode* left;
	PKEY key;
}treeNode;
//A struct to save all the specific function addresses
typedef struct Tree
{
	isKeysEqual isEqualFunc;
	isLeftOrRight isLeftOrRightFunc;
	printKeys printKeysFunc;
	int amountOfNodes;
}Tree;
//////
//The function allocate memory for a functions structure  and save all the specific functions addresses in it
PTree initFunctionsStruct(isKeysEqual isEqualFunc, isLeftOrRight isLeftOrRightFunc, printKeys printKeysFunc)
{
	PTree temp = (PTree)malloc(sizeof(Tree));	
	if (temp != NULL)
	{
		temp->isEqualFunc = isEqualFunc;
		temp->isLeftOrRightFunc = isLeftOrRightFunc;
		temp->printKeysFunc = printKeysFunc;
		temp->amountOfNodes = 0;
	}
	return temp;
}
//The function allocate memory for a new node,reseting its left and right pointers and return its address
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
//The function checks if the given key are already exist in the tree
isFree isKeyFree(PTreeNode root, PKEY key, PTree treeManager)
{
	if (root == NULL)
		return FREE;
	if (treeManager->isEqualFunc(key, root->key))
		return NOT_FREE;
	else
	{
		if (treeManager->isLeftOrRightFunc(root->key, key))
			return isKeyFree(root->right, key, treeManager);
		else
			return isKeyFree(root->left, key, treeManager);
	}
}
/*
Function name: addNewTreeNode
Input: The root of the tree, the new key to insert, 
	   the functions structure and the file to print out to
Output: returns NO_MEMORY_ERROR if the new node allocation failed and TRUE if the function succeeded 
*/
boolean addNewTreeNode(PTreeNode* root,PKEY keyToInsert, PTree functionManager,FILE* outPutFile)
{
	PTreeNode newNodeToInsert;
	//Checks that we got to the required root
	if (*root == NULL)
	{
		newNodeToInsert = getAllocatedMemoryAddress();
		//checking if the allocation succeeded
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
		//checking on which side of the root should we go, based on the value of the root->key and the given key
		if (functionManager->isLeftOrRightFunc((*root)->key, keyToInsert))
			return addNewTreeNode(&(*root)->right, keyToInsert, functionManager,outPutFile);
		else
			return addNewTreeNode(&(*root)->left, keyToInsert, functionManager, outPutFile);
	}
	//Prints the newNode key value
	functionManager->amountOfNodes++;
	functionManager->printKeysFunc(keyToInsert, outPutFile, DEFAULT_NEW_NODE_PRINT);
	return TRUE;
}
//the function prints the keys by Inorder way recursivly
void printKeysByInorderWay(PTreeNode root, PTree functionManager,int* printOnce, FILE* outPutFile)
{
	if (!functionManager->amountOfNodes)
	{
		fprintf(outPutFile, "The tree is empty");
		return;
	}
	//Makes sure that this phrase will be printed only once 
	if (*printOnce == 1)
	{
		fprintf(outPutFile, "The keys by inorder way are: ");
		(*printOnce)--;
	}
	if (root != NULL) 
	{
		printKeysByInorderWay(root->left, functionManager, printOnce, outPutFile);
		functionManager->printKeysFunc(root->key, outPutFile, DEFAULT_KEY_PRINT);
		printKeysByInorderWay(root->right, functionManager, printOnce, outPutFile);
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
void printMaxKey(PTreeNode root, PTree functionManager, FILE* outPutFile)
{
	//checking if the tree is empty
	if (!functionManager->amountOfNodes)
	{
		fprintf(outPutFile, "The tree is empty");
		return;
	}
	PTreeNode getMaxKeyAddress = root;
	while (getMaxKeyAddress->right)
		getMaxKeyAddress = getMaxKeyAddress->right;
	functionManager->printKeysFunc(getMaxKeyAddress->key, outPutFile, DEFAULT_MAX_KEY_PRINT);
}
/*
Function name: printGivenKeysAmount
Input: The root of the tree, the amount of keys to print(k),string to print once 
	   the functions structure and the file to print out to 
*/
void printGivenKeysAmount(PTreeNode root, PTree functionManager, int* amountOfKeysToPrint,int* printOnce, FILE* outPutFile)
{
	//checking if the amount of nodes in the tree is less than the required keys to print
	if (functionManager->amountOfNodes < *amountOfKeysToPrint)
	{
		fprintf(outPutFile, "There are no %d elements in this tree\n", *amountOfKeysToPrint);
		return;
	}
	//makes sure that the string below will be printed only once during the recursion
	else if (*printOnce == 1)
	{
		fprintf(outPutFile, "There are %d elements in this tree: ", *amountOfKeysToPrint);
		(*printOnce)--;
	}
	if (root == NULL)
		return;
	printGivenKeysAmount(root->left, functionManager, amountOfKeysToPrint, printOnce, outPutFile);
	if (*amountOfKeysToPrint == 0)
		return;
	//printing the key
	functionManager->printKeysFunc(root->key, outPutFile, DEFAULT_KEY_PRINT);
	//reducing the amount of keys to print
	(*amountOfKeysToPrint)--;
	printGivenKeysAmount(root->right, functionManager, amountOfKeysToPrint, printOnce, outPutFile);
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
		freeFunc(root->key);
		free(root);
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
