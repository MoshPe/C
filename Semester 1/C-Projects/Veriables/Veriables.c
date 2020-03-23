#include <stdio.h>
#include <stdlib.h>

int main ()
{
char characterName [] = "John";
int characterAge = 35;
printf("There was a young man named %s\n" ,characterName);
printf("and he was like %d years old.\n" ,characterAge);
characterAge = 45;
printf("but he decided to change his name to %s\n" , characterName);
printf("just because he thought that it was beautiful beacause he was %d\n" ,characterAge);
    return (0);
}