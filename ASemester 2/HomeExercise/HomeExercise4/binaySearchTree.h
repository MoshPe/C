#ifndef _binaySearchTree
#define _binaySearchTree


#define DEFAULT_NEW_NODE_PRINT "was added to the tree" 
#define DEFAULT_KEY_PRINT "= key"
#define DEFAULT_MAX_KEY_PRINT "is the max key in the tree"
#define _CRT_SECURE_NO_WARNINGS
#define Max(a,b) ((a) > (b)? (a): (b)) 

typedef struct treeNode* PTreeNode;
typedef struct Tree* PTree;

typedef enum boolean { FALSE, TRUE, NO_MEMORY_ERROR } boolean;
typedef enum side { left, right } side;

typedef void* PKEY;

typedef boolean(*isLeftOrRight)(PKEY, PKEY);
typedef boolean(*isEqual)(PKEY, PKEY);
typedef void(*printKeys)(PKEY, FILE*, char*);

boolean addNewTreeNode(PTree,PTreeNode,PKEY, isLeftOrRight, isEqual, FILE*);
PTreeNode getAllocatedMemoryAddress();
boolean isKeyFree(PTreeNode, PKEY, isEqual, isLeftOrRight);
void printKeysByInorder(PTreeNode, printKeys, FILE*);
int treeHeight(PTreeNode);
void printMaxKey(PTreeNode, printKeys, FILE*);
void printK_KeysBySize(PTree,PTreeNode, FILE*, printKeys, int);
PTreeNode getNewNodeBranchToInsert(PTreeNode, PKEY, isLeftOrRight);
void Error_Msg(char*);


#endif // !_binarySearchTree
