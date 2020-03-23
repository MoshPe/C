#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int rec_prefix(char *s,char *pref);
void main()
{
    char s[]={"abc"};
    char pref[]={"abcy"};
    printf("Amount of alike chars %d",rec_prefix(s,pref));
}
int rec_prefix(char *s,char *pref)
{
    return (*s==*pref)?1+rec_prefix(s+1,pref+1):0;   
}