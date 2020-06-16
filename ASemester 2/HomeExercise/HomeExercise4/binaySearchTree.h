#ifndef _binaySearchTree
#define _binaySearchTree


#define DEFAULT_NEW_NODE_PRINT "was added to the tree\n" 
#define DEFAULT_KEY_PRINT ", "
#define DEFAULT_MAX_KEY_PRINT "is the max key in the tree\n"
#define ALLOCATION_ERROR_TEMPLATE "\n Couldnt allocate memory for %s"

#define Max(a,b) ((a) > (b)? (a): (b)) 

typedef struct treeNode* PTreeNode;
typedef struct functions* PFunctions;
// Some necessary type definitions
typedef enum boolean { FALSE, TRUE, NO_MEMORY_ERROR } boolean;
typedef enum side { LEFT, RIGHT } side;
typedef enum isEqual { NOT_EQUAL, EQUAL } isEqual;
typedef enum isFree { NOT_FREE, FREE } isFree;
typedef void* PKEY;

// Function types
typedef side(*isLeftOrRight)(PKEY, PKEY);
typedef isEqual(*isKeysEqual)(PKEY, PKEY);
typedef void(*printKeys)(PKEY, FILE*, char*);
typedef void(*Free)(PTreeNode,PKEY);

// Interface functions 
PFunctions initFunctionsStruct(isKeysEqual, isLeftOrRight, printKeys);
isFree isKeyFree(PTreeNode, PKEY, PFunctions);
PTreeNode getAllocatedMemoryAddress();
boolean addNewTreeNode(PTreeNode*, PKEY, PFunctions, FILE*);
void printKeysByInorder(PTreeNode, PFunctions,int*,FILE*);
int treeHeight(PTreeNode);
void printMaxKey(PTreeNode, PFunctions, FILE*);
void printGivenKeysAmount(int*,PTreeNode, PFunctions, int*,int*, FILE*);
void FreeThemAll(PTreeNode, Free);
void Error_Msg(char*);
void optionValidationCheck(FILE*);

#endif // !_binarySearchTree
