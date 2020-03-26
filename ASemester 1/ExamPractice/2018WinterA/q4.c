#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
int canBePali(char* s);
char* pelindromBuild(char* s);
void main()
{
	char* a = "aabbx";
	puts(pelindromBuild(a));
}
int canBePali(char* s)
{
	int count[26] = {0}, i, odd = 0;

	for (i = 0; s[i]; i++)
		count[s[i] - 'a']++;

	for (i = 0; i < 26; i++)
	{
		if (count[i] % 2 == 1)
			odd++;

		if (odd > 1)
			return 0;
	}
	return 1;

}
char* pelindromBuild(char* s)
{
	int sLen = strlen(s), i, j, k = 0, cnt[26] = { 0 };
	int middle = sLen / 2;
	char  midChar = 0;
	
	char* spali= (char*)malloc((sLen+1)*sizeof(char));
	
	if (*spali)
	  if (!canBePali(s)) return NULL;
  else {
		for (i = 0; s[i]; i++)
			cnt[s[i] - 'a']++;

		for (i = 0; i < 26; i++)
			if (cnt[i] % 2 != 0)
				midChar = 'a' + i;

		//left half of the palindrom
		for (i = 0; i < 26;i++)
			for (j = 0; j < cnt[i] / 2; j++)
				spali[k++] = 'a' + i;

		// if there exists char with odd count put it in the middle
		if (midChar)
			spali[k++] = midChar;

		//right half of the palindrom
		for (i = 1; i <= sLen / 2; i++)
			spali[k++] = spali[sLen / 2 - i];

		spali[k] = '\0';
	}
	return spali;
}
