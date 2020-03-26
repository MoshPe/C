#define N 20
#include <stdio.h>

int addNums(int  array[ ], int);  
int main()
{
	//creating new array with a size of defined N
	int i, array[N];  /*1*/
	// getting 20 number from user
	printf("Enter %d integers, please: ", N);
	//loop for inputing the numbers into an array
	for(i=0 ; i<N ; i++) 
scanf("%d", &array[i]); /*2*/
//printing the sum of all number by using the function,addNums	
	printf("\n The sum is:%d\n", 	addNums(array , N));/*3*/
  	return 0;
}
//sum all the array numbers and return their sum 
int addNums (int array[], int n)/*4*/
{  
	int i, sum =0;
//loop for summing the value of the index in the array 
	for (i=0 ; i<n ; i++) 
		//sum all the array values
		sum = sum +array[i];    /*5*/
            //return the sum to the previous printf 
	return sum; /*6*/ 
}
