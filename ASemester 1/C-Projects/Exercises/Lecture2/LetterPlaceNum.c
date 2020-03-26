#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
//תכנית הקולטת תו שהוא אות קטנה ומחזירה את מיקומה

void main ()
{
char SmallLetter;
int Place;
printf("Enter small case letter:" );
scanf("%c",&SmallLetter);
Place = SmallLetter -'a' + 1;
printf("\nThe %c is placed at %d\n", SmallLetter,Place);
system("pause");
}