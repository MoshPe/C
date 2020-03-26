#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int removeCharacter(char* text, char c);
int removeCharacterRec(char* text, char c);
void moveLeft(char* text);
void main()
{
	char text[100] = { '\0' };
	char text1[100] = { '\0' };
	char ch;
	printf("Enter text: ");
	gets(text);
	printf("Enter characted to remove: ");
	scanf("%c", &ch);
	strcpy(text1, text);
	printf("\nThe Itrative method\n");
	printf("Removed %d letters %c\n", removeCharacter(text, ch), ch);
	puts(text);
	printf("\nThe Recursive method\n");
	printf("Removed %d letters %c\n", removeCharacterRec(text1, ch), ch);
	puts(text1);
}
/*
Function name: removeCharacter
Input: a pointer which point to the beginning of the text array and a char to match
Output: return the amount of ch been deleted from the array and outputing the array without the ch
Algoritem: we create a new array to copy our array in and sort and delete all the ch in the array + triming the ends
of the array because of excess copying.
*/

int removeCharacter(char* text, char c)
{
	int i, Count = 0, CpyIndx = 0;
	char* textCpy;
	textCpy = (char*)malloc((strlen(text) + 1) * sizeof(char));
	if (textCpy == NULL)
	{
		printf("Not enough memory\n");
		exit(1);
	}
	strcpy(textCpy, text);
	for (i = 0; i < strlen(text) + 1; i++)
	{

		if (textCpy[i] != c)
		{
			text[CpyIndx] = textCpy[i];
			CpyIndx++;
		}
		else Count++;
	}
	free(textCpy);
	if (CpyIndx < strlen(text) + 1)
		text[CpyIndx + 1] = '\0';
	return Count;
}
/*
Function name: removeCharacterRec(Recursive function)
Input:  a pointer which point to the beginning of the text array and a char to match
Output: return the amount of ch been deleted from the array and outputing the array without the ch
Algoritem: we check for every char in the array if it match the ch we move everything from that
			pointer to the left and we return 1 step we return 1 to the count for
			amount of deleted ch and calling the function again and move the array one step.
*/

int removeCharacterRec(char* text, char c)
{
	if (*text == 0)
		return 0;
	if (*text == c)
	{
		moveLeft(text);
		if (*text == c) 
			return 1 + removeCharacterRec(text, c);
		return 1 + removeCharacterRec(text + 1, c);
	}
	return removeCharacterRec(text + 1, c);
}
/*
Function name: moveLeft
Input: a pointer which point to the beginning of the text array
Output: it basically moves all the array left and cross the first place(exp:0-10>1-10)
Algoritem: we simply squashing the first place and putting the second one in its place and so on
			till the whole array moved 1 step left
*/

void moveLeft(char* text)
{
	if (*(text + 1) == '\0')
	{
		*text = '\0';
		return;
	}
	*text = *(text + 1);
	moveLeft(text + 1);
}