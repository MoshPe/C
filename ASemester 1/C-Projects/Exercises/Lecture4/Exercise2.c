#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    int num;
    printf("Please enter a positive 4 digits number: ");
    scanf("%d", &num);
    if (num )
    {
        /* code */
    }
    
    int units = num %10;
    int tens = (num/10)%10;
    int hund = (num/100)%10;
    int tho = num/1000;
    if (num >= 1000 && num <9999)
    {
        if (units <= tens && tens <= hund && hund<= tho)
        {
            if ((units - tens) == (hund - tho) && (units - tens)<0)
            {
                printf("Decreasing arithmetic sequence <from left to right>");
            }
            else if ((units - tens) != (hund - tho))
            {
                printf("Decreasing sequence <from left to right>.");
            }
            else 
            {
                printf("all 4 digits are the same");
            }
            
        }
        else if (units > tens && tens > hund && hund > tho)
        {
            if ((units - tens) == (hund - tho) && (units - tens)>0)
            {
               printf("Increasing arithmetic sequence <from left to right>");
            }
            else
            {
                printf("Increasing sequence <from left to right>");
            }
            
        }else
        {
            printf("Nondecreasing and nonicreasing sequence");
        }
        
        
        
    }
    else
    {
        if (num > 9999)
        {
            printf("%d is not a 4 digits number. Bye Bye", num);

        }
        else if (num < 1000 && num > 0)
        {
            printf("%d is not a 4 digits number" , num);
        }
        else
        {
            printf("%d is  a negetive number" , num);
        }
        
        
    }
    
    

    
    


}