#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int hiddenStr(char *st1,char *st2);
void main()
{
    char st1[100];
    char st2[100];
    int i=0,temp=0;
    printf("Enter text: ");
	gets(st1);
	printf("Enter substring: ");
	gets(st2);
    while (i!=strlen(st1))
    {
        if (st1[i]==st2[0])
        {
            if (hiddenStr(st1,st2)==1)
            {
                printf("\"%s\" is hidden in \"%s\"",st2,st1);
                temp=1;
                break;
            }
        }
            else if (st1[i]==st2[strlen(st2)-1])
            {
                //Reverse(st2);
               if (hiddenStr(st1,strrev(st2))==1)
               {
                printf("\"%s\" is hidden in \"%s\"",strrev(st2),st1);
                temp=1;
                break;
                } 
            } 
            i++;
    }
     if (temp==0)
            printf("\"%s\" is not hidden in \"%s\"",st2,st1);
}
int hiddenStr(char *st1,char *st2)
{
    int i,k=strlen(st2),j=0,count=0;
    for (i = 0; i < strlen(st1); i++)
    {
        if (st1[i]==st2[j]&&j<=k)
        {
            count++;
            j++;
        }
        if (count == k)
            return 1;
    }
    return 0;
    
}