#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 31
void main()
{
    int i,count=0,temp=0;
    char ar[N]={'\0'};
    do{
    printf("String: ");
    gets(ar);
    for (i = 0; i < N-1; i++)
    {
        if (ar[i]==ar[i+1])
        {
            count++;
            temp=1;
        }
        else if (count>=3)
        {
            printf(" there is \"%c%c%c\"",ar[i],ar[i],ar[i]);
            count=0;
            break;
        }   
    }
    puts("\n");
    //ar[N]={'\0'};
    if (temp==0)
       printf("there is NO Triple!");
      } while (ar[0]!='\0');       
}