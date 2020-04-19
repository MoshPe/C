#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
/*Clock Struct*/
typedef struct Clock
{
	int hour;
	int	minute;
} clock_t;

void TimeAdd(clock_t* a, int minsadd, clock_t* b);
void ClockPrint(clock_t* a);
int main()
{
	int minsadd;
	clock_t clock, newclock;
	printf("Enter time and minutes to add: ");
	scanf("%d%d%d",&clock.hour, &clock.minute, &minsadd);
	while (clock.hour > 24 || clock.minute >= 60)
	{
		printf("Input error\n");
		printf("Enter time and minutes to add: ");
		scanf("%d%d%d",&clock.hour, &clock.minute, &minsadd);
	}
	printf("\nThe time is: ");
	ClockPrint(&clock);
	TimeAdd(&clock, minsadd, &newclock);
	printf("\nThe new time is: ");
	ClockPrint(&newclock);
	return 0;
}

/*Function that add time to the clock and update it */
void TimeAdd(clock_t* clock, int minsadd, clock_t* newclock)
{
	newclock->minute = clock->minute + minsadd;
	newclock->hour = clock->hour + newclock->minute / 60;
	newclock->minute %= 60;
	newclock->hour %= 24;
}
/*Function that print the clock*/
void ClockPrint(clock_t* a)
{
	if (a->hour < 10)
		printf("0");
	printf("%d:", a->hour);
	if (a->minute < 10)
		printf("0");
	printf("%d", a->minute);

}