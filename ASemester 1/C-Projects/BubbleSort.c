#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void single_bubble(int *arr, int size);
void bubbleSort(int *arr, int size);
void main() 
{ 
    int a[10]={5,8,45,9,1,6,3,5,8,10};
	bubbleSort(a, 10);
    for (int i = 0; i < 10; i++)
		printf("%d, ",a[i]);
}
void single_bubble(int *arr, int size){
	if (size == 1)
		return;
	if(arr[0]>arr[1]){
		arr[0]=arr[0]+arr[1];
		arr[1]=arr[0]-arr[1];
		arr[0]=arr[0]-arr[1];}
	single_bubble(arr+1,size-1);}
void bubbleSort(int *arr, int size){
	if (size == 1)
		return;
	single_bubble(arr,size);
	bubbleSort(arr,size-1);}