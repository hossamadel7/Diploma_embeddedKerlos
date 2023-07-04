#include <stdio.h>
#include <string.h>

int fact(int x)
{
    if(x==1 || x==0) return 1;
    else return x*fact(x-1);
}
int main()
{
    
    printf("Enter a Postive number: ");
    int x,y;
    scanf("%d",&x);

   printf("Factorial of %d ",fact(x));
   

}
