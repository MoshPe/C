#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void main()
{
    char operator;
    float num1;
    float num2;
    char option;
    do
    {
    printf("\nWelcom to our Amazing calculator! \n");
    printf("\nPick an Operator (+ ,- ,* ,/ ,^): \n");
    rewind(stdin);
    scanf("%c", &operator);
    printf("Enter Num1: \n");
    scanf("%f", &num1);
    printf("Enter Num2: \n");
    scanf("%f", &num2);
    switch (operator)
    {
    case '+':
        printf("%.2f + %.2f = %.2f ",num1,num2,num1+num2);
        break;
        
    case '-':
        printf("%.2f - %.2f = %.2f ",num1,num2,num1-num2);
        break;
        
    case '/':
        printf("%.2f / %.2f = %.2f ",num1,num2,num1/num2);
        break;
        
    case '*':
        printf("%.2f * %.2f = %.2f ",num1,num2,num1*num2);
        break;
   
    case '^':
        printf("%.2f ^ %.2f = %.2f ",num1,num2,pow(num1,num2));
        break;
        default:
    printf("\nError! Operator is not valid!\n");
    }
    printf("\nDo you want to use the calculator again? Y/N?\n");
    option = getche();
    //scanf("%f",&option);   
    }
    while (option == 'Y' || option=='y');
    {
        getche();
    }
    printf("\nThank you for Using our amazing calculator!");
    
}