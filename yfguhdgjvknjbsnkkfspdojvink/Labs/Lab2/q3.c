#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

typedef struct Complex
{
	float real;
	float image;
	double R;
}Complex;
Complex* Cmax(Complex*, int);
float CRadius(Complex*);
void main()
{
	int num, i;
	Complex* c;
	printf("Enter amount of complex numbers: \n");
	scanf("%d",&num);
	c = (Complex*)malloc(num * sizeof(Complex));
	assert(c);
	printf("Enter %d Complex numbers: \n",num);
	for (i = 0; i < num; i++)
		scanf("%f%f", &c[i].real, &c[i].image);
	for (i = 0; i < num; i++)
		c[i].R = CRadius(&c[i]);
	printf("\nThe max complex numer is: %.2f + %.2fi", Cmax(c, num)->real, Cmax(c, num)->image);
	printf("\nThe radius of the max number is %.2f", Cmax(c, num)->R);
}
Complex* Cmax(Complex* s, int size)
{
	int i;
	double max = s[0].R;
	Complex* p=s;
	for (i = 1; i < size; i++)
	{
		if (s[i].R > max)
		{
			max = p[i].R;
			p = s+i;
		}
	}
	return p;
}
float CRadius(Complex* s)
{
	return sqrt(pow(s->real, 2) + pow(s->image, 2));
}