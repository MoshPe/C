#include<iostream>

int main()
{
	__asm
	{
		mov al, 5;
		mov bl, 2;
		add al, bl;
	}
	std::cout << "Hello World!\n";
}