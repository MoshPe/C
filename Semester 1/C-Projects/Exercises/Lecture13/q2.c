#include <stdio.h>
unsigned build(unsigned num, unsigned mask);
void main()
{
    int mask,num;
    printf("Give us the number and the mast ");
    scanf("%d%d",&num,&mask);
    printf("After applying mask %d onto %d we got %u",mask,num,build(num,mask));

}
/*unsigned build(unsigned num, unsigned mask)
{
    if (num==0||mask==0)
        return 0;
    return num%10*mask%10 + unsigned build(num/10,mask/10);
}*/
unsigned build(unsigned num, unsigned mask)
{
    int sum=0;
    if (num==0||mask==0)
        return 0;
    sum = num%10*mask%10;
    return sum + 10 * build(num/10,mask/10);
}