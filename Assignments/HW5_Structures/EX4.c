#include <stdio.h>
#include <string.h>

struct student
{
    char name[50];
    int roll_n,marks;
};

int main()
{
    struct student x[10];
    int i;
    printf("Enter information of students:\n");
    for ( i = 0; i < 10; i++)
    {
        printf("for roll number %d \n",i+1);
        x[i].roll_n=i+1;
        printf("Enter name:");
        scanf("%s",&x[i].name);
        printf("Enter marks:");
        scanf("%d",&x[i].marks);

    }
    printf("/nDisplaying info of students:");
    for ( i = 0; i < 10; i++)
    {
        printf("info. for roll no.%d",i+1);
        printf("name:%s \n Marks:%d",x[i].name,x[i].marks);
    }

    
    return 0;
}
