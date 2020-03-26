#include <stdio.h>
#include <stdlib.h>
unsigned R_howManyLetters(char *str);
void main()
{
    char arr[10];
    printf("Enter something: ");
    gets(arr);
    printf("%d",R_howManyLetters(arr));


}
unsigned R_howManyLetters(char *str)
{
    if ((*str >= 'A' && *str <= 'Z')||(*str >='a' && *str <= 'z'))
        return 1 + R_howManyLetters(str+1);
    
    return R_howManyLetters(str+1);
}