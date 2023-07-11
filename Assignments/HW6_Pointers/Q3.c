#include <stdio.h>
#include <string.h>


int main()
{
    char *ptr;
    

    char c[]="w3resource";
    ptr=c;
    int i=strlen(c);
    ptr=ptr+i;
    ptr--;
    
    while(i--)
    {
        printf("%c",*ptr--);
    }
    return 0;
}
