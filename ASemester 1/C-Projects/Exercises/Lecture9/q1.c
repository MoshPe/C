#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void main()
{
    int *arr;
    int arLength,i,max=0,maxIndex=0;
    do
    {
        //inputing the length of the string     
    printf("Enter the number of integers: ");
    scanf("%d",&arLength);
    //length = 0 is the term for finishing the loop
    if (arLength == 0)
        break;
    else
    {
        /*creating an array using dynamic memory with
        the length that we got from user*/ 
    arr = (int*)malloc(arLength*sizeof(int));
    /*checking if we got the memory size that we wanted
    if not the program shuts herself and free the memory*/
    if (arr == NULL)
    {
        free(arr);
        exit(1);
    }
    //inputing numbers into the array
    printf("Enter %d integers: ",arLength);
    for (i = 0; i < arLength; i++)
        scanf("%d",&arr[i]);
        //getting the max number out of the array
    for (i = 0; i < arLength; i++)
    {
        if (arr[i]>max)
        {
            max = arr[i];
            maxIndex=i;
        }
    }
    //printing the index of the max number
    printf("The maximum is at place: %d\n",maxIndex+1);
    }
    } while (arLength>0);
    printf("Bye Bye...");
    free(arr);
}
