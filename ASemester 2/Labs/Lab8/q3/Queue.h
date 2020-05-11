#ifndef _StackQueue
#define _StackQueue

#define NUM 5

typedef struct Item{
int num;
struct Item* next;
}Item;
//
typedef struct Que{
Item* head,*tail;
int size;      //a current number of items
}Queue,*PQue;
//
void DeleteList(PQue Q);
void Error_Msg(char* msg);
void Enqueue(PQue Q, int   new_elem);   //add a new member to list of the queue 
int Dequeue(PQue Q, int * del_value);     //delete member from the queue and  return the deleted value  using int *del_value

#endif // !_StackQueue

