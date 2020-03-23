#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h> 

void main()
{
	int num, RevNum, DigCount, NoSE = 0, t1 = 0, LastDigNum, MidNumOdd,RevBigDig,t2;
	//input num by user and put it in variable 'num'
    printf("Enter positive number (2-8 digits): ");
	scanf("%d", &num);
    //checking if the num digits below 2 or above 8 and prints if it is.
    if (num < 10 || num > 99999999)
	{
		printf("Incorrect number.");
	}
	else
	{
    //counting the digits that we have in the num
	DigCount = num;
	while (DigCount != 0)
	{
		DigCount = DigCount / 10;
		t1++;
	}
        //i want here to have 2 nums, one that l get the digit from left and one from the right
		RevNum = num;
		//if the digits num are odd so we check where the middle is placed to cancel it
        if (t1%2 != 0)
		{
			 MidNumOdd = round(t1 / 2.0);
		}
        t2 = t1;
        //loop for checking each digits from left to right and right to left
		for (int i = 0; i < t2; i++)
		{
            //we take the number from the left
			RevBigDig = RevNum / pow(10, t1 - 1);
            //we take the number from the right +the number from the left
			LastDigNum = num % 10 + RevBigDig;
            //checking if there is an odd digits num so we can cancel the middle one
			if (MidNumOdd == t1)
			{
				RevBigDig = 0;
				LastDigNum = 0;
			}
            //checking if the sum of the right and left equivalent by 3
			if (LastDigNum % 3 == 0)
			{
                //we're taking one off the right
				num = num / 10;
                //we're taking the left number out
				RevNum = RevNum - (RevNum / (int)pow(10, t1 - 1) * (int)pow(10, t1 - 1));
				t1--;
			}
			else
			{
                /*this shows that if we have an unSymmetric-Equivalent-3 
                we count the times that it isnt Symmetric-Equivalent-3*/
				NoSE++;
			}

		}
        //check if there was any sum of digits that were not Symmetric-Equivalent-3
		if (NoSE > 0)
		{
			printf("Not Symmetric - Equivalent-3\n");
		}
		else
		{
			printf("Symmetric - Equivalent - 3\n");
		}
	}
}