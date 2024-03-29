#ifndef _stack
#define _stack

typedef struct node * PSTACKNODE;

void push(void*, PSTACKNODE*);
void pop(PSTACKNODE*, void (*)(void*));
int isEmpty(PSTACKNODE);
void* top(PSTACKNODE);

#endif // !_stack