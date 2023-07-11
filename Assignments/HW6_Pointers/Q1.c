#include <stdio.h>
#include <string.h>


int main()
{
    int *pm;
    int m=29;

    printf("Adress of m=%p and its value=%d \n",&m,m);
    pm=&m;
    printf("Adress of pointer pm=%p and its content=%d \n",&pm,*pm);
    m=34;
    printf("Adress of pointer pm=%p and its content=%d\n",&pm,*pm);
    *pm=7;
    printf("Adress of m=%p and its value=%d",&m,m);
    return 0;
}
