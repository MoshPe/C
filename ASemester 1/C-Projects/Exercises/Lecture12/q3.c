#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int isPalindrom(int arr[], int length);
void main()
{
	int* ar;
	int length, i;
	//input from user the length of the given array
    printf("Enter a length of an array, please: ");
	scanf("%d", &length);
	//loop for doing the action till the length of the array that the user entered is 0
    while(length>0)
    {
		/*using dynaminc memory allcation for the given array length
			and checking if we got the memory we needed*/
	    ar = (int*)malloc(length * sizeof(int));
	        if (ar == NULL)
	    {
	    	printf("No memory!!");
	    	exit(1);
	    }
		//inputing all the array values from the user
	    printf("Enter %d elements, please: ", length);
	    for (i = 0; i < length; i++)
	    	scanf("%d",&ar[i]);
		//printing if the array is polindrom or isnt
	    printf("The array is %sa palindrome.\n", isPalindrom(ar, length) == 1 ? "" : "not ");
	    //free the memory allocation
		free(ar);
        printf("\nEnter a length of an array, please: ");
	    scanf("%d", &length);
    }
    printf("\n\nThank you for exploring palindrom arrays.");
}
/*
Function name: isPalindrom
Input: a pointer which point to the beginning of the text array and its length
Output: 1 if the array is polindrom and 0 if it isnt 
Algoritem: the fucntion checks the array ends from both side for match
			if they aren't match return instant 0 else moving closer to the middle till the array ends
*/
int isPalindrom(int arr[], int length)
{
	if (length <= 0)
		return 1;
	return (*arr == arr[length - 1]) ? isPalindrom(arr + 1, length - 2) : 0;

}