#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
void main()
{
    char string[N];
    int i,j;
    do
    {
    printf("Enter a string, please: ");
    gets(string);
    for ( i=0; string[i]!=0;)
    {
        if (string[i]=='\t'||string[i]==' ')
        i++;
        else
        {
           printf("%c",string[i]);
           if (string[i+1]=='\t'||string[i+1]==' '|| string[i+1]=='\0')
           printf("\n");
           i++;
        }
    }
     } while (strlen(string)!=0);
     printf("\nFinish.");
}