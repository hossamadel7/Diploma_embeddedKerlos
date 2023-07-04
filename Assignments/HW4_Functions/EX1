#include <stdio.h>
#include <string.h>

int prime(int x,int y)
{

    for(int i=x;i<=y;i++)
    {
        int check=1;
        for(int j=2;j<=i/2;j++)
        {
            if(i%j==0)
            {
                check=0;
                break;
            }
        }
        if(check) printf("%d \n",i);
    }
}

int main()
{
    
    printf("Enter 2 numbers: ");
    int x,y;
    scanf("%d %d",&x,&y);
   printf("Enter between %d and %d: ",x,y);
   prime(x,y);

}
