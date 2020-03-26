#include <stdio.h>
#include <stdlib.h>

void main()
{
char ch;
printf("Enter an English lower case letter, please: ");
scanf("%c", &ch);
printf("The ascii code of '%c' is %d.\n",ch,ch);
printf("The ascii code of '%c' is %d.",ch-32,ch-32);




}