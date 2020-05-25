#include <stdio.h>
#include <Windows.h>
void main()
{
	int i, j, k;
	char ch1, acode;
	char code_array[256];

	char msg[80] = "Hello World!";
	char encoded_msg[80], decoded_msg[80];

	k = 4;
	for (i = 0; i < 256; i++)
	{
		ch1 = i;
		acode = 'z';
		if ((i >= 'a') && (i <= 'z'))
		{
			ch1 = ch1 + k;
			if (ch1 > acode)
				ch1 = 'a' + (ch1 % acode);
		} // if

		acode = 'Z';
		if ((i >= 'A') && (i <= 'Z'))
		{
			ch1 = ch1 + k;
			if (ch1 > acode)
				ch1 = 'A' + (ch1 % acode) - 1;
		} // if

		code_array[i] = ch1;
        Sleep(500);
        printf("%c  , ",code_array[i]);

	} //for 
} // main
