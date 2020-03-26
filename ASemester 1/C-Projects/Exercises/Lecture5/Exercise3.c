#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void main()
{
    char num1,num2;
    char ch;

    do{
        
        printf("Pick an Operator (a or A,* ,m ,M ,^) or Q/q to finish:");
        rewind(stdin);
        ch = getche();
        //scanf("%c",&ch);
        if (ch == 'q' || ch =='Q')
        break;
        else
        {
        printf("\nEnter 2 digits: ");
        scanf("%d%d",&num1,&num2);
        switch (ch)
        {
        case 'A': case 'a':
        
            printf("\nThe Average is %sinteger\n", ((num1+num2)/2.0) ? "" : "not ");
            printf("\nThe Average %d\n", ((num1+num2)/2.0));
            break;
        case '*':
            printf("\nThe multiply is %d\n",num1*num2);
            break;
        case 'm':
            printf("\nThe minimum number is %d\n", num1>num2 ? num2:num1);
            break;
        case 'M':
            printf("\nThe maximun4m number is %d\n", num1>num2 ? num1 :num2);
            break;
        case '^':
        {
        if (pow(num1,num2) == (int)pow(num1,num2))
        {
            printf("\nThe power of the 2 numbers and is an integer ans is %.4f\n",pow(num1,num2));
        }
        else
        {
            printf("\nThe power of the 2 numbers and is not an integer and is %.4f\n",pow(num1,num2));
        }
        }
            break;
        default:
            printf("Error\n");
        }
        
        }
    }
    
    while (ch != 'q' || ch !='Q');
    {
       getche();
    }
    printf("\nFinish");
    
}
