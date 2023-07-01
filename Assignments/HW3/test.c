#include <stdio.h>

int main()
{
    int n;
    printf("Enter the no. of Data: ");
    scanf("%d",&n);
    float sum=0;
    float a[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter number: ");
        scanf("%f",&a[i]);
        sum+=a[i];
    }
    printf("the average=%.2f",sum/n);
    
    
}