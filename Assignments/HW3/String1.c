#include <stdio.h>
#include <string.h>
int main()
{
    char arr[100];
    printf("Enter a string: ");
    gets(arr);

    printf("Enter a character to finde freq: ");
    char cc;
    int sum=0;
    scanf("%c",&cc);
    for (int i = 0; i < sizeof(arr) && arr[i]!=0; i++)
    {
        if(arr[i]==cc) sum++;
    }
    printf("sum====>%d",sum);
    

    
}
