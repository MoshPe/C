#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 4
typedef struct Complex
{
	float real;
	float image;
}Complex;

float CRadius(Complex*);
void Error_Msg(char* str);
void InputAndWriteToFile(FILE* f);
int CheckFile(FILE* f, float m);
void OutputData(Complex* arr, FILE* fp);

int main()
{

	FILE* f;
    /*opening a new file to write only and checking if its
      opened*/
	if (!(f = fopen("Complex_Number.txt", "wt")))
		Error_Msg("The input file is wrong");
	InputAndWriteToFile(f);
	fclose(f);
    /*opening the complex_number.txt file to read only and
     checking if its opened*/
	if (!(f = fopen("Complex_Number.txt", "rt")))
		Error_Msg("The input file is wrong");
	printf("\nThere are %d big numbers\n", CheckFile(f, 4));
	fclose(f);
	return 0;
}
/*
the function receiving the real and image parts of the complex 
and printing them on the f file together with the radius 
*/
void InputAndWriteToFile(FILE* f)
{
	int i;
	Complex c;
	printf("Enter %d complex numbers: \n", N);
	for (i = 0; i < N; i++)
	{
		scanf("%f%f", &c.real, &c.image);
		fprintf(f, "%.1f %.1f %.1f\n", c.real, c.image, CRadius(&c));
	}
}
//calculate the radius of the complex number
float CRadius(Complex* s)
{
	return sqrt(pow(s->real, 2) + pow(s->image, 2));
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}
/*reading all the radius and checking if its
  greater than m, if it is it counts it
  */
int CheckFile(FILE* f, float m)
{
	int count = 0;
	float radius;
	while (fscanf(f, "%f %f %f ",&radius, &radius, &radius) != EOF)
	{
		if (radius > m)
			count++;
	}
	return count;
}