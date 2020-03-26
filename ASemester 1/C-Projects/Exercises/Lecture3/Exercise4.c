#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

void main()
{
	float a;
	float Angle;
	float V;
	float height, baseEdge;
	printf("Enter the pyramid base edge <in centimeters> , please: ");
	scanf("%f", &a);
	printf("Enter the angle <in degrees> between the pyramid side edge and its height, please: ");
	scanf("%f", &Angle);
	baseEdge = (sqrt(a * a + a * a) / 2);
	height = (baseEdge / tan(Angle *PI/180));
	V = (a * a * height) / 3;
	printf("The volume <in cubic centimeters> of the pyramid is %.3f\n", V);


}