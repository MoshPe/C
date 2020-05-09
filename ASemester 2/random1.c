#include<STDIO.H>
extern int findNum(int arr[],int size,int num);
void main()
{
    int arr[6]={7,7,6,6,5,5};
    int res,i;
    res = findNum(arr,6,7);
    printf("There were %d 7 in the array\n",res);
    printf("The array is: \n");
    for (i = 0; i < 6; i++)
        printf("%d",arr[i]);
    return;
}