#include<stdio.h>
#include<stdlib.h>
int isMirror(char* ch, int n, int k);
int isMirrorRec(char* ch, int n, int k);
void main()
{
	char a[] = "bamygymxb";
	char* b = { a };
	printf("%d ", isMirror(a, 9, 2));
}
int isMirrorRec(char* ch, int n, int k)
{
	if (k == 0)
		return 1;
	if (n == 0)
		return 0;
	if (*ch == *(ch + n - 1))
		return isMirror(ch + 1, n - 2, k - 1);
	else return isMirror(ch + 1, n - 2, k - 1);

}
int isMirror(char* ch, int n, int k)
{
	int i = 0, sum = 0;
	while (n > i+1)
	{
		if (ch[i] == ch[n - 1])
			sum++;
		i++;
		n--;
	}
	if (sum >= k)
		return 1;
	return 0;
}