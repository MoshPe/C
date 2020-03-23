#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
    int Weight, Height;
    float BMI;
    printf("Please enter weight (in kg) and height (in cm), respectively: ");
    scanf("%d%d", &Weight, &Height);
    BMI = (double)Weight/powf((double)Height/100,2);
    if(BMI < 18.5)
        {
            printf("Underweight");
        }
        else if (BMI >= 18.5 && BMI < 25 )
        {
            printf("Normal weight");
        }
         else if (BMI >= 25 && BMI < 30 )
        {
            printf("Increased weight");
        }
        
         else if (BMI >= 30 && BMI < 40 )
        {
            printf("Obese");
        }
         else if (BMI >= 40)
        {
            printf("Very high obese");
        }
        
        

}