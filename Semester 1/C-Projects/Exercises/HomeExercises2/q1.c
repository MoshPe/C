#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS
int randArr(int array[], int b);
int printArr(int array[], int n);
int countPeaks(int array[], int n);
int peaksLocation(int array[], int n);
#define LEN 15

void main()
{
    srand (time(NULL));
    int i;
    int Arr[LEN];
    randArr(Arr,LEN);
    printArr(Arr,LEN);
    printf("\nNum of peakes are %d\n",countPeaks(Arr,LEN));
    printf("The location/s of the peaks is/are ");
    peaksLocation(Arr,LEN);
    

}
int randArr(int array[], int b)
{
    int i;
    for (i = 0; i < b; i++)
    {
        array[i] = (rand()%41) + 10;
    }
    return array[b];
}
int printArr(int array[], int n)
{
    int i;
   for ( i = 0; i < n; i++)
    {
        printf("%d, ", array[i]);
    }
    return 0;
}
int countPeaks(int array[], int n)
{
    int i,sum=0;
    for (i = 1; i < n-1; i++)
    {
        if (array[i] > array[i+1] && array[i] > array[i-1])
        {
            sum+=1;
        }
    }
    return sum;
}
int peaksLocation(int array[], int n)
{
    int i;
    for (i = 1; i < n-1; i++)
    {
        if (array[i] > array[i+1] && array[i] > array[i-1])
        {
            printf("%d,",i);
        }   
    }
}
