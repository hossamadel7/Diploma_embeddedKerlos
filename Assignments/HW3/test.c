#include <stdio.h>
#include <string.h>
int main()
{
    char arr[100];
    printf("Enter a string: ");
    gets(arr);
    printf("Reverse of string:");
    for (int i = strlen(arr)-1 ; i >=0; i--)
    {
        printf("%c",arr[i]);
    }
    
    

    
}