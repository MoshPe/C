#include <stdio.h>
#include <stdlib.h>
#include "binaySearchTree.h"
#define _CRT_SECURE_NO_WARNINGS

typedef struct treeNode
{
	struct treeNode* right;
	struct treeNode* left;
	PKEY key;
}treeNode;

typedef struct Tree
{
	PTreeNode root;
	int amountOfNodes;
}Tree;
//////
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
/////////////
PTreeNode getNewNodeBranchToInsert(PTreeNode root, PKEY key, isLeftOrRight isLeftOrRightFunc)
{
	if (root == NULL)
		return root;
	if (isLeftOrRightFunc(root->key, key))
	{
		if (root->right == NULL)
			return root;
		getNewNodeBranchToInsert(root->right, key, isLeftOrRightFunc);
	}
	else
	{
		if (root->left == NULL)
			return root;
		getNewNodeBranchToInsert(root->left, key, isLeftOrRightFunc);
	}
}
///////////////
boolean isKeyFree(PTreeNode root, PKEY key, isEqual isEqualFunc, isLeftOrRight isLeftOrRightFunc)
{
	if (root == NULL)
		return TRUE;
	if (isEqualFunc(key, root->key))
		return FALSE;
	else
	{
		if (isLeftOrRightFunc(root->key, key))
			isKeyFree(root->right, key, isEqualFunc, isLeftOrRightFunc);
		else
			isKeyFree(root->left, key, isEqualFunc, isLeftOrRightFunc);
	}
}
////////////
boolean addNewTreeNode(PTree* tree,PTreeNode* root,PKEY key, isLeftOrRight isLeftOrRightFunc, isEqual isEqualFunc, printKeys newNodeInsertPrint, FILE* outPutFile)
{
	PTreeNode newNodeToInsert;
	PTreeNode nodePlaceToInsert;
	if (*tree == NULL)
	{
		*tree = (PTree)malloc(sizeof(Tree));
		if (*tree == NULL)
		{
			fprintf(outPutFile, "Error!\nCouldnt allocate memory for new tree");
			return NO_MEMORY_ERROR;
		}
		(*tree)->root = NULL;
		(*tree)->amountOfNodes = 0;
	}
	if (!(isKeyFree((*tree)->root, key, isEqualFunc, isLeftOrRightFunc)))
	{
		fprintf(outPutFile, "Error!\nThere is an existing node with the same key");
		return FALSE;
	}
	newNodeToInsert = getAllocatedMemoryAddress();
	if (newNodeToInsert == NULL)
	{
		fprintf(outPutFile, "Error!\nCouldnt allocate memory for new node");
		return NO_MEMORY_ERROR;
	}
	newNodeToInsert->key = key;
	nodePlaceToInsert = getNewNodeBranchToInsert((*tree)->root, key, isLeftOrRightFunc);
	if ((*tree)->root == NULL)
		(*tree)->root = newNodeToInsert;
	else
	{
		if (isLeftOrRightFunc(nodePlaceToInsert->key, key))
			nodePlaceToInsert->right = newNodeToInsert;
		nodePlaceToInsert->left = newNodeToInsert;
	}
	newNodeInsertPrint(key, outPutFile, DEFAULT_NEW_NODE_PRINT);
	(*tree)->amountOfNodes++;
	(*root) = (*tree)->root;
}
void printKeysByInorder(PTreeNode root, printKeys printKeys, FILE* outPutFile)
{
	if (root == NULL)
		return;
	printKeysByInorder(root->left, printKeys, outPutFile);
	printKeys(root->key, outPutFile, DEFAULT_KEY_PRINT);
	printKeysByInorder(root->right, printKeys, outPutFile);
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
void printMaxKey(PTreeNode root, printKeys printMaxKey, FILE* outPutFile)
{
	PTreeNode getMaxKeyAddress = root;
	while (getMaxKeyAddress->right)
		getMaxKeyAddress = getMaxKeyAddress->right;
	printMaxKey(getMaxKeyAddress->key, outPutFile, DEFAULT_MAX_KEY_PRINT);
}
////the error msg is in the main
void printK_KeysBySize(PTree tree,PTreeNode root, FILE* outPutFile, printKeys printSmallestKeys, int* k)
{
	if (tree->amountOfNodes < *k)
	{
		fprintf(outPutFile, "There are no %d elements in this tree\n", *k);
		return;
	}
	if (*k == 0 || root == NULL)
		return;
	printK_KeysBySize(tree,root->left, outPutFile, printSmallestKeys, k);
	if (*k == 0)
		return;
	printSmallestKeys(root->key, outPutFile, DEFAULT_KEY_PRINT);
	*k--;
	printK_KeysBySize(tree,root->right, outPutFile, printSmallestKeys, k);
}
void FreeThemAll(PTreeNode root)
{
	//going down to the tree nodes and checking if the tree isnt empty
	if (root != NULL)
	{

		FreeThemAll(root->left);
		FreeThemAll(root->right);
		//free the tree from the end
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

