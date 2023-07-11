#include <stdio.h>
#include <string.h>


int main()
{
    char *ptr;
    

    char alph[27];
    int i;
    for ( i = 0; i < 26; i++)
    {
        alph[i]='A'+i;
    }

    ptr=alph;
    while(*ptr!='\0')
    {
        printf("%c ",*ptr);
        ptr++;
    }
    return 0;
}
