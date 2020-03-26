#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
/*הקלט הוא מספר ת.ז. והתוכנית מוציאה בעיקרון
פלט שהוא אומר מה הספרת ביקורת ואם הת.ז. נכון
*/
#define N 8
void main()
{
	int solution;
	int sum2 = 0;
	int ID = 0;
	int InspectionNum;
	int IDNum[N] = {};
	int sum1 = 0;
	int Multi;
	printf("Enter Your ID:");
	scanf("%d", &ID);
	InspectionNum = ID % 10;
	ID = ID / 10;
	for (int i = 0; i < N; i++)
	{
		IDNum[i] = ID % 10; // כאן לוקחים את המספר שנשאר לנו עושים שארית 10 ואז נשאר המספר עצמו
		if (i % 2 == 0)
		{
			if (IDNum[i] * 2 > 9)
			{
				Multi = IDNum[i] * 2;
				sum1 = sum1 + (Multi % 10 + Multi / 10);


			}
			else
			{
				sum1 = sum1 + IDNum[i] * 2;
			}
		}
		else
		{
			sum2 = sum2 + IDNum[i];
		}
		ID = ID / 10;
	}

	solution = sum1 + sum2 + InspectionNum;
	if (solution % 10 == 0)
	{
		printf("\nYour ID is valid\n");
		printf("Your Inspection Number is: %d\n", InspectionNum);
	}
	else
	{
		printf("Your ID is not valid!!\n\n");
	}

}