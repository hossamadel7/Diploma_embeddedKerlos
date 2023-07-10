#include <stdio.h>
#include <string.h>

#define Pi 3.14
#define Area(r) Pi*r*r
int main()
{
    int r;
    float area;

    printf("Enter the radius:");
    scanf("%d",&r);
    area=Area(r);
    printf("Area=%f",area);
    return 0;
}
