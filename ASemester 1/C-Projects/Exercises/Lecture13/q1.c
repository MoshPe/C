#include <stdio.h>
#include <string.h>
#define N 4
void printReversedFromTo(char *text, int start, int End);
int main(){
	char *text = "Experimental text to print reversed fragment.";
	int i, len = strlen(text);
	int From_Vec[4] = { 0, 0, 10, 22 },
		To_Vec[N] = { len - 1, len / 2, len - 1, 33 };
	for (i = 0; i < N; i++){
		printf("*** Reversed from %d to %d:\n", From_Vec[i], To_Vec[i]);
		printReversedFromTo(text, From_Vec[i], To_Vec[i]);
		printf("\n");
	}
	printf("\n*** Finish.\n");
	return 0;
}
void printReversedFromTo(char *text, int start, int End)
{
    if (End == start)
    {
        printf("%c",*(text+start));  
        return;
    }
        printf("%c",*(text+End));
        printReversedFromTo(text,start,End-1);
}