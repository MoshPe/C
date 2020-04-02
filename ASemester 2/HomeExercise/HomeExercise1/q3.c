#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Clock
{
int hour, minute;
} clock_t;

void main()
{
    clock_t time;
    int minutes;
    printf("Enter time and minutes to add: ");
    scanf("%d%d%d",&time.hour,&time.minute,&minutes);
    printf("The time is %02d:%02d\n",time.hour,time.minute);
   
   if (time.minute+minutes>60)
    {
        if(time.hour+(time.minute+minutes)/60>=24)
            {
                time.hour+=(time.minute+minutes)/60-24;
            }
            else
                 time.hour+=(time.minute+minutes)/60;
        time.minute=(time.minute+minutes)%60;
    }
    else
        time.minute=time.minute+minutes;
    printf("The new time is is %02d:%02d",time.hour,time.minute);
    
    

}