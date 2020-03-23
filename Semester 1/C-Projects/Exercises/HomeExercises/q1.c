#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define CRT_SECURE_NO_WARNINGS

void main ()
{
    int min_counter = 60;
    int hr_counter = 24;
    int counterMin, counterHr;
    int hr1,hr2,min1,min2;
    printf("Please enter the first time (hh:mm): ");
    scanf("%d:%d" , &hr1 , &min1);
    printf("Please enter the second time (hh:mm): ");
    scanf("%d:%d" , &hr2 , &min2);
    if (min2-min1 <0 && hr2 - hr1 <0)
    {
        counterMin = abs(min2 - min1);
        counterHr = abs(hr2 - hr1);
        printf("Difference of times is -%02d:%02d" ,counterHr,counterMin);
    }
    else if (min2 - min1 <0)
    {
        counterMin = min_counter + (min2 - min1);
        counterHr = hr2 - hr1 -1;
        printf("Difference of times is %02d:%02d" ,counterHr,counterMin);
    }
   else
   {
       printf("Difference of times is %02d:%02d" , hr2 - hr1,abs(min2 - min1));
   }
    
}
