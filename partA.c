#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling



void createRecord();
void writeOneRecord();
void readAllRecords();

typedef struct student_marks    // structure definition for student marks
{ 
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
            createRecord();
            break;
        case 2:
            readAllRecords();
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


void createRecord()
{
    student_marks input;

    printf("Enter student index number: ");
    scanf("%s", input.student_index);
    printf("Enter assignment 01 marks : ");
    scanf("%f", &input.assignmt01_marks);
    printf("Enter assignment 02 marks : ");
    scanf("%f", &input.assignmt02_marks);
    printf("Enter project marks : ");
    scanf("%f", &input.project_marks);
    printf("Enter finals marks : ");
    scanf("%f", &input.finalExam_marks);

    writeOneRecord(input);
}

void writeOneRecord(student_marks data)
{

    FILE *file;
    int wrt;
    int errNo;

    file = fopen("student_marks.dat", "a+");

    wrt = fwrite(&data, sizeof(struct student_marks), 1, file);

    if (wrt < 0)
    {
        perror("fprintf doc1.txt: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }

    fclose(file);
}

void readAllRecords()
{
    student_marks output;
    FILE *file;
    int wrt;
    int errNo;
    char *row1[] = {"Student Index", "Assignment 01 Marks", "Assignment 02 Marks", "Project Marks", "Final Exam Marks"};

    file = fopen("student_marks.dat", "r"); // open file for writing and reading
    if (file == NULL)
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    printf("\n");

    printf("| %*s | %*s | %*s | %*s | %*s | \n\n", -20, row1[0], -20, row1[1], -20, row1[2], -20, row1[3], -20, row1[4]);

    while (fread(&output, sizeof(struct student_marks), 1, file))
    {
           printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", output.student_index, output.assignmt01_marks,
               output.assignmt02_marks, output.project_marks, output.finalExam_marks);
    }
    printf("\n\n");
    fclose(file);
}