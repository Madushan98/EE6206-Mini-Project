#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling



typedef struct student_marks
{                                 // structure definition for student marks
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

int main()
{
    int choice;
    printf("Module Code: ZZ6309 \n");
    printf("Module Name: Linux Operating System \n\n");

    do
    {

        printf("1. Create Record \n");
        printf("2. Read all Record \n");
        printf("3. Delete Record \n");
        printf("4. Update Record \n");
        printf("5. Exit \n\n");

        printf("Enter Your Chice \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        
            break;
        case 2:
        
            break;
        case 3:
       
            break;
        case 4:
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
    } while (choice != 5);

    return 0;
}