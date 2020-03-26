#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct point
{
	float x;
	float y;
}point;
typedef struct circle
{
	point Cp;
	int R;
}circle;
int is_in(point p, circle c);
void main()
{
	point p;
	circle c;
	printf("Enter the coordinates of your point: ");
	scanf("%f%f", &p.x,&p.y);
	rewind(stdin);
	printf("Enter the radius and the center of your circle: ");
	scanf("%d%f%f", &c.R,&c.Cp.x,&c.Cp.y);
	if (is_in(p,c))
		printf("The point is included in the circle");
	else
		printf("The point is not included in the circle");


}
int is_in(point p, circle c)
{
	int d,x,y;
	x = pow((p.x) - (c.Cp.x), 2);
	y = pow((p.y) - (c.Cp.y), 2);
	d = sqrt(x+y);
	if (abs(d) > c.R)
		return 0;
	return 1;
}