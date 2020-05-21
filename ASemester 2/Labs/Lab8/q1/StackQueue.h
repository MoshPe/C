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
int size;         //a current number of itemss
}Stack,*PStack;
//
void Error_Msg(char* msg);
void Push(PStack s, int   new_elem);  //add a new member to list of the stack
int Pop(PStack s, int * del_value);  //delete member from the stack and  return the deleted value  using  int * del_value
        

#endif // !_StackQueue

