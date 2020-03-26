#include <stdio.h>
#include <stdlib.h>
int findSumZRec(int *arr,int size, int z);
void main()
{
    int arr[]={1,2,3,4,5,6,7,8,9};
    int z =5;
    printf("%d",findSumZRec(arr,9,z));

}







//arr is sorted
int findSumZ(int *arr,int size, int z)
{
    int left = 0, right = size-1,i;
    while (left <right)
    {
        if (arr[left]+arr[right]>z)
            right--;
        else if (arr[left]+arr[right]<z)
            left++;
          else  return 1;
    }
    return 0;
}
int findSumZRec(int *arr,int size, int z)
{
    if (*arr>*(arr+size-1))
        return 0;
        if (*arr+*(arr+size-1)==z)
            return 1;
        else if (*arr+*(arr+size-1)>z)
                findSumZRec(arr,size-1,z);
                else if (*arr+*(arr+size-1)<z)
                    findSumZRec(arr+1,size,z);
}