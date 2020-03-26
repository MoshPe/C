#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS
//definig prototypes for the functions
float deg2rad(int a);
float horizontal(float v, int a, float t);
float height(float v, int a, float t);
//defining a constant variable
#define PI 3.14159265
#define G 9.81

void main()
{
	float v;
	int a;
	float t;
	float h, s;
	//making a do while loop to repeat the printing action
	do
	{
		//input a v for speed and a for the angle
		printf("Enter v <0.0 - 100.0 m/s and a <0-90 degrees>: ");
		scanf("%f",&v);
		//checking if the speed if above 100 or below 0
		if (v >= 0.0 && v <= 100.0)
		{
				scanf("%d", &a);
				//checking if the angle is above 0 degrees and below 90 degrees
				if (a >= 0 && a <= 90)
				{
					//setting t to 0.1 because that at 0 the while go out because the height is 0
					t = 0.1;
					//building a loop for the calculation and printing the height and horizontal at any given time 
					while (height(v, a, t) >= 0)
					{
						// printing and calculating the time, horizontal and height of the object
						printf("Time: %.1f....S=%.2f  H=%.2f\n", t, horizontal(v, a, t), height(v, a, t));
						//adding 0.1 to the time
						t = t + 0.1;
					}
					//printing Fallen in case the object had fallen down
					printf("Time: %.1f....S=%.2f  H=%.2f\n", t, horizontal(v, a, t), height(v, a, t));
					printf("\nFallen!\n");
				}
		}
		//repeating the inputing and calculating as long as the speed and the angle are in range of 0<v<100 and 0<a<90
	} while (v >= 0 && v<=100 && a >= 0 && a <= 90);
	printf("Finish\n");
}

	


//converint the angle from degree to rad
float deg2rad(int a)
{
	float RadAngle;
	RadAngle = (a * 2.0 * PI) / 360;
	return RadAngle;
}
//calculating the horizontal of an object at a certain time and speed
float horizontal(float v, int a, float t)
{
	float s;
	s = (v * cos(deg2rad(a))) * t;
	return s;
}
//calculating the height of an object at a certain time and speed
float height(float v, int a, float t)
{
	float h;
	h = (v * sin(deg2rad(a))) * t - (G * pow(t, 2)) / 2.0;
	return h;
}