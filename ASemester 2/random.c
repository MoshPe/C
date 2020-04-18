#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void func(int *a);
int main() {
    int* i;
    *i=4;
    func(i);
    return 0;
}
void func(int *a)
{
    printf("%d",*a);
}