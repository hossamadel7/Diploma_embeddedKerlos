#include <stdio.h>
#include <string.h>

struct complex
{
    float real;
    float img;
};

int main()
{
    printf("Enter real and img for complex1:\n");
    struct complex s1;
    scanf("%f %f",&s1.real,&s1.img);
    printf("Enter real and img for complex2:\n");
    struct complex s2;
    scanf("%f %f",&s2.real,&s2.img);

    printf("\nThe sum:");
    printf("%f %fi \n",s1.real+s2.real,s1.img+s2.img);
    return 0;
}
