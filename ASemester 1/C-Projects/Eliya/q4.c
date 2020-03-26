#include <stdio.h>
#include <stdlib.h>
  /* To sort the given numbers in ascending order */
  void bubbleSort(int *data, int n) {
        int i, temp;
        if (n > 0) {
                for (i = 1; i < n; i++) {
                        if (data[i - 1] > data[i]) {
                                temp = data[i];
                                data[i] = data[i - 1];
                                data[i - 1] = temp;
                        }
                }
                bubbleSort(data, n - 1);
        }
        return;
  }
  int main() {
  int i, n, *data;
        /* Enter the numbers of inputs which is to be sorted */
        printf("Enter the number of inputs:");
        scanf("%d", &n);
        /* To store input values, it allocates dynamic memory */
        data = (int *) malloc(sizeof(int) * n);
        /* Enter the input data */
        for (i = 0; i < n; i++) {
                printf("data[%d]: ", i);
                scanf("%d", &data[i]);
        }
        /* sorts the given numbers */
        bubbleSort(data, n);
        /* print the sorted numbers */
        printf("Sorted array:\n");
        for (i = 0; i < n; i++) {
                printf("%d ", data[i]);
        }
        printf("\n");
        return 0;
  }