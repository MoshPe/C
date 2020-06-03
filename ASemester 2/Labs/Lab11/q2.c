#include<stdio.h>

#define N 5


void Int_Sum(void *sum,void *num)
{
 *(int*)sum += *(int*)num;
}


void Int_Sub(void *sum ,void *num)
{
 *(int*)sum -= *(int*)num;
}


void Init(void *p)
{
 *(int*)p = 0;
}


int Int_Comp(void *a, void *b)
{
 if( *(int*)a == *(int*)b )
   return 1;
 return 0;
}

//return 1 if the funtion finds an item which the sum of his previous values ,returns 0 if it doesn't
int Do_It(void *sum,void** array,void (*p_Init)(void *),void(*p_Sum)(void*,void*),void(*p_Sub)(void*,void*),int(*p_Comp)(void*,void*))
{
    int i;
    //reseting the sum element
    p_Init(sum);
    for (i = 0; i < N-1; i++)
    {
        //checking if the index is even
        if (i%2 == 0)
            p_Sum(sum,array[i]);
        else//the index is odd
            p_Sub(sum,array[i]);
        //checking if the sum is equal to the next value in the array
        if (p_Comp(sum,array[i+1]))
            return 1;
    }
    return 0;
}

int main()
{
 int num[] = {5,8,23,20,23}, i, answer;
 void *p_num[N];
 //placing the num addresses in the p_num array
for (i = 0; i < N; i++)
    p_num[i] = &num[i]; 
 answer = Do_It(&answer,p_num,Init,Int_Sum,Int_Sub,Int_Comp);
 if(answer == 1)
   printf("The answer is 'Yes'");
 else
   printf("The answer is 'No'");
return 0;
}

