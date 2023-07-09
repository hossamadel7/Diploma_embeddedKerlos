#include <stdio.h>
#include <string.h>

struct student
{
    char name[50];
    int roll_n;
    int marks;
};

int main()
{
    printf("Enter info of student:\n\n");
    struct student s1;
    printf("Enter name:");
    scanf("%s",&s1.name);
    printf("Enter roll number:");
    scanf("%d",&s1.roll_n);
    printf("Enter Marks:");
    scanf("%d",&s1.marks);

    printf("\nDisplaying Information:");
    printf("name:%s \n Roll:%d \n Marks:%d \n",s1.name,s1.roll_n,s1.marks);
    return 0;
}
