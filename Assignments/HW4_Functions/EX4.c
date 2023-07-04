#include <stdio.h>
#include <string.h>

int p(int base,int power)
{
    if(power==0) return 1;
    else return base*p(base,power-1);
    
}

int main()
{
    
    printf("Enter base number: ");
    int x,y;
    scanf("%d",&x);
    printf("Enter power number: ");
    scanf("%d",&y);
   printf("The result =%d ",p(x,y));


}
