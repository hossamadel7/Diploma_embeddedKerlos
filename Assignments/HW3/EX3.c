#include <stdio.h>

int main()
{
    int a[2][3];
    printf("Enter the elements of 1st matrix \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Enter a%d%d: ",i+1,j+1);
            scanf("%d",&a[i][j]);
        } 
    }
    
     printf("Entered Matrix\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d  ",a[i][j]); 
        } 
        printf("\n");
    }
    printf("Transpose Matrix\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d  ",a[j][i]); 
        } 
        printf("\n");
    }
    

    
}