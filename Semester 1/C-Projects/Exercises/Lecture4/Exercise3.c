#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    int child, salary;
    float Mortage;
    char MiliServ;
    printf("Enter number of children: ");
    scanf("%d", &child);
    printf("Enter your monthly salary: ");
    scanf("%d" , &salary);
    printf("Military service?\n");
    printf("For YES enter 'y', otherwise any other character:");
    rewind(stdin);
    scanf("%c" , &MiliServ);
    if ((MiliServ == 'y' && salary >= 5000) || (child >= 4 && salary >= 4000))
         {
             Mortage = salary*0.2;
             printf("Mortage is approved at amount of : %.2f", Mortage);
         }
    else if (salary > 7500)
    {
        Mortage = salary * 0.3;
        printf("Mortage is approved at amount of : %.2f", Mortage);
    }
    else
    {
        printf("The mortage is not approved.");
    }  
}