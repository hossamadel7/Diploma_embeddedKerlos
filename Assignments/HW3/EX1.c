#include <stdio.h>

int main()
{
    int a[2][2];
    int b[2][2];
    printf("Enter the elements of 1st matrix \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Enter a%d%d: ",i+1,j+1);
            scanf("%d",&a[i][j]);
        } 
    }
     for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Enter b%d%d: ",i+1,j+1);
            scanf("%d",&b[i][j]);
        } 
    }
     printf("Sum of Matrix \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d    ",a[i][j]+b[i][j]); 
        } 
        printf("\n");
    }

    
}
