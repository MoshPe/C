#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";
    int a,j;
    double b;
    char c[100000];
    scanf("%d",&a);
    scanf("%lf",&b);
    rewind(stdin);
    gets(c);
    for (j=0; j<strlen(c); j++) {
    printf("%c",c[j]);
    }
    printf("%d\n",a+i);
    printf("%.1lf\n",b+d);
    printf("%s",s);
    printf("%s",c);

    
    // Declare second integer, double, and String variables.
    
    // Read and save an integer, double, and String to your variables.
    
    // Print the sum of both integer variables on a new line.
    
    // Print the sum of the double variables on a new line.
    
    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.

    return 0;
}