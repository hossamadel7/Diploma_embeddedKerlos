#include <stdio.h>
#include <string.h>


int main()
{
    int *ptr;
    

    int arr[15];
    int i;
    ptr=arr;
    for ( i = 0; i < 5; i++)
    {
        printf("Element%d:",i+1);
        scanf("%d",ptr);
        ptr++;
        /* code */
    }
    ptr--;
    printf("\n \n");
    for ( i = 0; i < 5; i++)
    {
        printf("Element %d:%d\n",i+1,*ptr);
        ptr--;
        /* code */
    }
    return 0;
}
