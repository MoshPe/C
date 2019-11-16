#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
/*בעצם כאן התכנית מקבלת קלט מספר בעל 3 ספרות ומחזירה כפלט 
את סכום ספרותיו, הפרש המיספרים עם היפוכו, מספר ההפוך וכמות האי זוגיים במספר
*/
void main ()
{
    int Units,Dozens,Hundreds;
    int DigitSum,SumDiff,BackNum,OddSum;
    int ThreeDigitNum;
printf("Enter 3 digit number: ");
scanf("%d", &ThreeDigitNum);
Units = ThreeDigitNum%10;
Dozens = ThreeDigitNum/10%10;
Hundreds = ThreeDigitNum/100;
DigitSum = Units + Dozens + Hundreds;
BackNum = Units*100 + Dozens*10 + Hundreds;
SumDiff = ThreeDigitNum-BackNum;
OddSum = Units%2 + Dozens%2 + Hundreds%2;
printf("\nsum of digits is : %d\n",DigitSum);
printf("\n reversed is : %d\n",BackNum);
printf("\nDiff between the number and the reversed is : %d\n",SumDiff);
printf("\nNumber of odd digits is : %d\n",OddSum);
system("pause");
}