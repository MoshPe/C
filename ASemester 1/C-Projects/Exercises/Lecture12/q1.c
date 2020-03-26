#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int lengthOfString(char *s);

int main(){
    char *text = "Experimental text to test recursive function.";
    printf("Length of string: \n%s\nis %d.\n", text, lengthOfString(text));
    return 0;
}
int lengthOfString(char *s)
{
    return (*s=='\0')?0:1+lengthOfString(s+1);
}
