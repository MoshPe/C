#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void smallbig(char* a);
void main()
{
	char* b = "KfHTm";
	smallbig(b);
	puts(b);
}
void smallbig(char* a)
{
	char temp;
	int i=strlen(a)-1;
	while  (i/2!=0){
		if (*a < *(a+i-1))
		{
			temp = *a;
			*a = *(a + i - 1);
			*(a + i - 1) = temp;
			i--;
		}
		a++;
	}
}