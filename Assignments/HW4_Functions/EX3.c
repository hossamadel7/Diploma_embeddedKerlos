#include <stdio.h>
#include <string.h>

void reverse (char *c)
{ 
    if(*c!='\0')
    {
        reverse(c+1);
        printf("%c",*c);
    }
    else return;
}

int main()
{
    
    printf("The sentence: ");
    char c[100]="margorp emosewa";
    reverse(c);

}
