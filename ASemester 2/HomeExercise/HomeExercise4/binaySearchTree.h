#ifndef _binarySearchTree
#define _binarySearchTree

#define _CRT_SECURE_NO_WARNINGS

typedef struct treeNode *PTreeNode;
typedef struct Tree *PTree;

typedef enum boolean {FALSE,TRUE} boolean;
typedef void* PKEY;


void pop(PSTACKNODE*, void (*)(void*));



void addNewTreeNode(PTree root,PKEY key);
void printTreeKeys(PTree root);
int treeHeight(PTree root);
void printMaxKey(PTree root);
void printKeysBySize(PTree root,PKEY key);
PTreeNode getKeyBranchAddress(PTree root,PKEY key,)





#endif // !_binarySearchTree
