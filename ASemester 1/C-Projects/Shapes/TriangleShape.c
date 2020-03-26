#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define CRT_SECURE_NO_WARNINGS
//The program gets an char and a num and output a 90 degree angle Equilateral triangle triangle.
void main()
{
    int i,j,N;
    char ch;
    // getting input of the char and the num for the triangle size
    printf("Enter a character and integer, please: ");
    scanf("%c%d",&ch,&N);
    //loop for the triangle row
    for ( i = 0; i <= N-1; i++)
    {//loop for the triangle column
        for (j = 0; j <=N-i-1; j++)
        {
            //printing the char for the making of the triangle
            printf("%c",ch);
        }
        //just going one line down to the second row
        putch('\n');
        
    }
    
}