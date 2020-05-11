#ifndef _StackQueue
#define _StackQueue

#define NUM 5

typedef struct Item{
int num;
struct Item* next;
}Item;
//
typedef struct Stack{
Item* head;
int size;         //a current number of items
}Stack,*PStack;
//
void DeleteList(PStack s);
void Error_Msg(char* msg);
void Push(PStack s, int   new_elem);    
int Pop(PStack s, int * del_value);          

#endif // !_StackQueue

