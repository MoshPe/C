#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void main()
{
	char *name;
	name = (char*)malloc(50*sizeof(char));
	printf("Enter your name: ");
	gets(name);
	printf("%s,,,",name);




}