#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

#define true 1
#define false 0

#define Max(a,b) ((a) > (b)? (a): (b)) 

typedef struct
{
	int key;
	float val;
} Data;

typedef struct TreeNode
{
	struct TreeNode* left;	 //left child
	struct TreeNode* right; //right child

	Data TreeNode_info;	 //info data in node
} TreeNode;

typedef struct ListNode
{
	struct ListNode* next;
	Data ListNode_info;	 //info data in node
} ListNode;


// TREE Handling prototypes
int treeHeight(TreeNode*); // returns the hight of a given tree
float sum_tree(TreeNode*); //returns the sum of values on all tree nodes
void empty_tree(TreeNode**); // frees all the allocated memory and sets the root to NULL
TreeNode* create_tree_node(Data);
void insert_info_by_key(TreeNode**, TreeNode**, Data);
TreeNode* create_search_tree();

// LIST Handling prototypes
void empty_list(ListNode**);// frees all the allocated memory and sets the head to NULL
ListNode* create_list_node(Data);
void print_list(ListNode*);   // Prints the elements of the list from head to tail
ListNode* append_lists(ListNode*, ListNode*);

// LIST <-> TREE conversions
ListNode* tree_to_inorder_list(TreeNode*);
ListNode* tree_to_preorder_list(TreeNode*);


int main()
{
	TreeNode* inputTree = NULL;
	ListNode* preList = NULL, * inList = NULL;

	printf("\n getting the input tree");
	inputTree = create_search_tree(); // get the tree from user
	printf("\nhight of tree is %d\n", treeHeight(inputTree)); // print hight
	printf("\nsum of values of tree is %f\n", sum_tree(inputTree));

	printf("\n printing input tree inorder");
	inList = tree_to_inorder_list(inputTree); // inorder traverse the tree
	print_list(inList);

	printf("\n printing input tree preorder");
	preList = tree_to_preorder_list(inputTree); // preorder traverse the tree
	print_list(preList);

	empty_tree(&inputTree);
	empty_list(&preList);
	empty_list(&inList);
	return 0;
}

//recursive function which returns the height of a given tree
int treeHeight(TreeNode* tree)
{
	int leftHeight, rightHeight;
	//checking if the list is empty and acts as end-break of the recursion
	if (tree == NULL)
		return -1;
	//counts the amount of nodes in the left side of the tree
	leftHeight = treeHeight(tree->left);
	//counts the amount of nodes in the right side of the tree
	rightHeight = treeHeight(tree->right);
	//returns the max height + the root(+1), to pay back the -1 from the if above
	return 1 + Max(leftHeight, rightHeight);
}

//returns the sum of values on all tree nodes
float sum_tree(TreeNode* tree)
{
	if (tree == NULL)
		return 0;
	return tree->TreeNode_info.val + sum_tree(tree->left) + sum_tree(tree->right);
}

// frees all the allocated memory and sets the root to NULL
void empty_tree(TreeNode** root)
{
	//going down to the tree nodes and checking if the tree isnt empty
	if (*root != NULL)
	{

		empty_tree(&(*root)->left);
		empty_tree(&(*root)->right);
		//free the tree from the end
		free(*root);
	}
	//setting the *root of the current place in the recursion to null and go back to the previous reursion caller
	*root = NULL;
}
TreeNode* create_tree_node(Data data)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newNode == NULL)
	{
		printf("\n Allocation memory error!\n");
		return NULL;
	}
	else
	{
		newNode->TreeNode_info = data;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
}
void insert_info_by_key(TreeNode** root, TreeNode** root_original, Data data)
{
	static int times;
	if (!(*root))
	{
		*root = create_tree_node(data);			//get new node for tree
		if (times == 0)
			*root_original = *root;
		if (*root == NULL)
		{
			printf("Allocation tree node failed");
			empty_tree(root_original);                    /*deleting the whole tree,since root_original is a pointer to the whole tree*/
			exit(1);
		}
	}
	else
	{
		if (data.key < (*root)->TreeNode_info.key)		//if the new node's key is smaller			
			insert_info_by_key(&((*root)->left), root_original, data); 	//call insert_node with the left child
		else
			insert_info_by_key(&((*root)->right), root_original, data);
	}
	times++;
}
TreeNode* create_search_tree()
{
	Data infoNode;
	char in_char;
	TreeNode* tree = NULL;

	do
	{
		printf("\n Do you want to enter another node? (y/n) :");
		in_char = _getche();
		if (in_char == 'y')
		{
			printf("\nEnter key and value: ");
			scanf("%d %f", &(infoNode.key), &(infoNode.val));
			insert_info_by_key(&tree, &tree, infoNode);     /*sending the same parameter twice for deleting a whole tree*/
		}
	} while (in_char == 'y');
	return tree;
}
// frees all the allocated memory and sets the head to NULL
void empty_list(ListNode** head)
{
	//checking if the list is empty and setting the end-break of the recursion
	if ((*head) == NULL)
		return;
	empty_list(&((*head)->next));
	//free the list from the end
	free(*head);
	//setting the *head of the current place in the recursion to null and go back to the previous reursion caller
	*head = NULL;
}
ListNode* create_list_node(Data data)
{
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));	//allocate new node in heap

	if (new_node == NULL)
		return NULL;
	else
	{
		new_node->ListNode_info = data;
		new_node->next = NULL;
		return new_node;		//returns intialized node
	}
}
void print_list(ListNode* head)
{
	if (head == NULL)
	{
		printf("\nThe list is EMPTY\n");
		return;
	}
	printf("\nThe list is:\n");
	while (head != NULL)
	{
		printf("\n (key=%d , val=%.01f)", head->ListNode_info.key, head->ListNode_info.val);
		head = head->next;
	}
	printf("\n\n");
}
ListNode* append_lists(ListNode* firstList, ListNode* secondList)
{
	ListNode* res;

	res = secondList;   /*if firstList is empty*/
	if (firstList)
	{
		res = firstList;
		while (firstList->next)
			firstList = firstList->next;
		firstList->next = secondList;
	}
	return res;
}
//the order should be Left->Root->Right
ListNode* tree_to_inorder_list(TreeNode* root)
{
	ListNode* curr = NULL, * left = NULL, * right = NULL;
	if (root)
	{
		left = tree_to_inorder_list(root->left);
		right = tree_to_inorder_list(root->right);
		curr = create_list_node(root->TreeNode_info);
		//setting the list to point to the right side of the root according the order
		curr->next = right;
		//point the curr and curr->next = right list to the end of the left list
		left = append_lists(left, curr);
	}
	//returning the head of the list(left = head)
	return left;
}
//the order should be Root->Left->Right
ListNode* tree_to_preorder_list(TreeNode* root)
{

	ListNode* curr = NULL, * left = NULL, * right = NULL;
	if (root)
	{

		left = tree_to_preorder_list(root->left);
		right = tree_to_preorder_list(root->right);
		//setting the first node to the root info
		curr = create_list_node(root->TreeNode_info);
		//setting the list to point to the left side of the root according the order
		curr->next = left;
		//point the right list to the end of the curr list
		curr = append_lists(curr, right);
	}
	//returning the head of the list(root = head)
	return curr;
}

