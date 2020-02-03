#include<stdio.h>
#include<stdlib.h>
char *chLoc (char *st,int n,char ch);

void main()
{
    char *ch="bbbcccccdgggkkkkkmmmmmz";
    printf("%c",*chLoc(ch,23,'k'));
}
char *chLoc (char *st,int n,char ch)
    {
        //char *p=0;
    //int b = n;
	int i=0;
	while (n>i)
	{
		if (ch>st[i])
            i+=i+abs((n-i)/2);
        else 
			n = n-abs((n-i)/2);
	}
    p=i;
    return *st[i];
}