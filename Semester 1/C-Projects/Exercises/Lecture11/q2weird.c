#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int hiddenStr(char *st1,char *st2);
void is_in(char *st1,char *st2);
void reverse(char* x, int begin, int end);
void main()
{
    char st1[]={"optic"};
    char st2[]={"nirto"};
    char st3[]={"option"};
    char st[]={"Computer Science"};
    is_in(st,st1);
    is_in(st,st2);
    is_in(st,st3);
}
/*
Input: gets the substring st1 and the string st
algoritem: the function checks if the string st2 is in st1
output: the function return 0 if the string isnt in st1 and return 1 if it is
*/
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
/*
Input: gets the substring st1 and the string st
algoritem: the function checks if the string st2 is in st1
output: the function just prints if the st2 is hidden in st1 or not
*/
void is_in(char *st1,char *st2)
{
    int i=0,temp=0,was=0;
  while (i!=strlen(st1))
    {
        if (st1[i]==st2[0])
        {
            if (hiddenStr(st1,st2)==1)
            {
                printf("\"%s\" is hidden in \"%s\"\n",st2,st1);
                temp=1;
                break;
            }
        }
            else if (st1[i]==st2[strlen(st2)-1])
            {
                reverse(st2, 0, (strlen(st2) - 1));
               if (hiddenStr(st1,st2)==1)
               {
                     reverse(st2, 0, (strlen(st2) - 1));
                     printf("\"%s\" is hidden in \"%s\"\n",st2,st1);
                     temp=1;
                     break;
                } 
            } 
            i++;
    }
     if (temp==0)
     {
        reverse(st2, 0, (strlen(st2) - 1));
        printf("\"%s\" is not hidden in \"%s\"\n",st2,st1);
     }
}
/*
Input: gets the string, the index of the beginning and the end
algoritem: the function calculates the factorial of a certain num in recorsivi
output: the factorial of a certain num
*/
void reverse(char* x, int begin, int end)
{
	char c;
	if (begin >= end)
		return;
	c = *(x + begin);
	*(x + begin) = *(x + end);
	*(x + end) = c;
	reverse(x, ++begin, --end);
}