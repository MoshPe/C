#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define CRT_SECURE_NO_WARNINGS

void main()
{
    int NumUp,NumUp2 , BinaryUp=0 , rev = 0,t=0, DigAfterDot=0;
    double num , NumDown;
    //getting num from user
    printf("Enter floating number: ");
    scanf("%lf" , &num);
    //inputing the num's complete value(left from the dot)   
    NumUp = num;
    //creating 2 variables that contain the complete value of the num
    NumUp2 = NumUp;
    //finding the binary number of the num's complete value and counting the times the while worked
    while (NumUp != 0)
    {
        //checking if the complete num value divid by 2 without any leftovers so it adds 1        
        if (NumUp%2 != 0)
        {
            BinaryUp = BinaryUp*10 +1;
        }
        // if the term above doesnt apply so multiply the binaray variable by 10  
        else
        {
            BinaryUp=BinaryUp*10;
        }
        NumUp=NumUp/2;
        //counter for how much times the loop works
        t++;
    }
    // A loop the return the binary number in her right order, MSB first than LSB last
    for (int i = 0; i < t; i++)
    {
        rev = rev*10 + BinaryUp%10;
        BinaryUp=BinaryUp/10;
    }
    //Printing the complete value of num after converting it to binary and priting dot at the end for the fractional part
    printf("%d.",rev);
    //isolate the fractional part of the number from the num that the user typed
    NumDown = num - NumUp2 ;
    //A loop for converting the fractional part to binary and limiting it to 8 digits
    while (DigAfterDot<8)
    {
        NumDown=NumDown*2;
        //calculating if the fractional part multiply by 2 is bigger than 1
        if (NumDown > 1 || NumDown==1)
        {
            printf("1");
            NumDown=NumDown-1;
        }
        else
        {
            printf("0");
        }
        //adding 1 for the amount of digits after the dot from the fractional part side that the question allo which is 8 
         DigAfterDot++;
    }
}