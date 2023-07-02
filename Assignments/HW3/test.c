#include <stdio.h>
int main()
{
    int n;
    printf("Enter the no. of Data: ");
    scanf("%d",&n);

    int a[10];
    for (int i = 0; i < n; i++)
    {
        printf("Enter number: ");
        scanf("%d",&a[i]);
    
    }
    int inserted;
    printf("Enter inserted element: ");
    scanf("%d",&inserted);
    int location;
    printf("Enter the location: ");
    scanf("%d",&location);
    int temp=a[location-1];
    for (int i = n; i > location-1; i--)
    {
        a[i]=a[i-1];
    }
    a[location-1]=inserted;
    
    

    
}