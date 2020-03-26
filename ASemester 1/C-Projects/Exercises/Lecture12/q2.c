#include <stdio.h>
#include <stdlib.h>
#define LEN 256
int recursiveHasPrefix(char *str, char *prefix);
int main (){
	char str[LEN+1];
	char pre[LEN+1];
	int isPrefix=1;
	while(isPrefix){/* As long as pre is a predix of str */
		printf("Please enter a string: "); /*input two strings*/
		gets_s(str, LEN);
		printf("Please enter a prefix string: ");
		gets_s(pre, LEN);
		isPrefix = recursiveHasPrefix(str, pre);/*check whether pre is a prefix of str.*/
		if(isPrefix) printf("The specific text has the prefix.\n\n");
		else printf("No prefix.\n\n");
	}
	return 0;
}
