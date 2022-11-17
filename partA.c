#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling

typedef struct student_marks // structure definition for student marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

void createRecord();
void writeOneRecord();
void readAllRecords();
int getAllDataWithLength();
void updateRecord();
int getAllDataWithLength();
void reWriteList(int length);
void deleteRecord();
void generateData();
char *generateRandomIndex();
float generateRandomMarks();

student_marks *marksPtr;

int main()
{
    int choice;
    printf("----Module Code: ZZ6309----- \n");
    printf("----Module Name: Linux Operating System---- \n\n");

    do
    {
        printf("\n ------Menu------ \n\n");
        printf("1. Create Record \n");
        printf("2. Read all Record \n");
        printf("3. Delete Record \n");
        printf("4. Update Record \n");
        printf("5. Generate 100 Records \n");
        printf("6. Exit \n\n");

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
            deleteRecord();
            break;
        case 4:
            updateRecord();
            break;
        case 5:
            generateData();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
    } while (choice != 5);

    return 0;
}

void createRecord() // function to create a record
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

void writeOneRecord(student_marks data) // function to write a student record to file
{

    FILE *file;
    int wrt;
    int errNo;

    file = fopen("student_marks.dat", "a+"); // open file in append mode
    if (file == NULL)
    {
        errNo = errno;
        printf("Error opening file: %s\n", strerror(errNo));
        exit(1);
    }

    wrt = fwrite(&data, sizeof(struct student_marks), 1, file); // write one record to file

    if (wrt < 0) // check for error in write
    {
        printf("Error No: %d\n", errno);
        perror("fwrite student_marks.dat: ");
        exit(1);
    }

    fclose(file); // close file
}

void readAllRecords() // function to read all record on the student_marks file
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

    while (1) // read each record from file with error handling
    {
      
        fread(&output, sizeof(struct student_marks), 1, file);
        if(feof(file))
        {
            break;
        }
        if ((errNo = ferror(file)) > 0)
        {
            perror("fread dox1.txt: ");
            printf("ferror: %d\n", errNo);
            exit(1);
        }
        else
        {
            printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", output.student_index, output.assignmt01_marks,
                   output.assignmt02_marks, output.project_marks, output.finalExam_marks);              // print record
        }
    }
    printf("\n\n");
    fclose(file); // close file
}


int getAllDataWithLength()   // function to get the number of records in the file
{
    student_marks output;
    FILE *file;
    int wrt;
    int errNo;
    int count = 0;

    marksPtr = (student_marks *)malloc(count * sizeof(struct student_marks));   // allocate memory for the structure

    file = fopen("student_marks.dat", "r"); // open file for writing and reading
    if (file == NULL)   // error handling 
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    printf("\n");
    while (fread(&output, sizeof(struct student_marks), 1, file))  // read each record from file with error handling
    {
        count++;
        marksPtr = (student_marks *)realloc(marksPtr, count * sizeof(struct student_marks)); // reallocate memory for the structure
        strcpy((marksPtr + count - 1)->student_index, output.student_index);    // copy data to the structure
        (marksPtr + count - 1)->assignmt01_marks = output.assignmt01_marks;
        (marksPtr + count - 1)->assignmt02_marks = output.assignmt02_marks;
        (marksPtr + count - 1)->project_marks = output.project_marks;
        (marksPtr + count - 1)->finalExam_marks = output.finalExam_marks;
    }
    fclose(file);   //  close file
    return count;
}

void updateRecord() // function to update a record 
{
    int length = getAllDataWithLength(); // get the number of records in the file
    char student_index[20]; 
    printf("Enter student index number: ");
    scanf("%s", student_index); // get the student index number to update
    student_marks output;
    student_marks updatedRecord;
    int found = 0;
    int count = 0;
    while (count < length)  // loop through the list of data to find the matching record
    {
        if (strcmp(marksPtr[count].student_index, student_index) == 0)  // check if the stduent numbers match
        {
            found = 1;
            printf("Enter assignment 01 marks : ");
            scanf("%f", &(marksPtr + count)->assignmt01_marks);
            printf("Enter assignment 02 marks : ");
            scanf("%f", &(marksPtr + count)->assignmt02_marks);
            printf("Enter project marks : ");
            scanf("%f", &(marksPtr + count)->project_marks);
            printf("Enter finals marks : ");
            scanf("%f", &(marksPtr + count)->finalExam_marks);
        }
        count++;
    }

    if (found == 0) // check if the record was found 
    {
        printf("Record not found \n\n");
    }
    reWriteList(length);
}


void reWriteList(int length)    // function to rewrite the list of data to the file 
{
    FILE *file;
    int wrt;
    int errNo;
    int count = 0;
    file = fopen("student_marks.dat", "w+"); // open file for writing and reading
    while (count < length)
    {
        wrt = fwrite(marksPtr + count, sizeof(struct student_marks), 1, file); // write one record to file
        if (wrt < 0)
        {
            perror("fprintf doc1.txt: ");
            printf("Error No: %d\n", errno);
            exit(1);
        }
        count++;
    }

    printf("Successfully Updated\n\n"); // print success message

    fclose(file);
}

void deleteRecord() // function to delete a student record 
{
    int length = getAllDataWithLength();    // get the number of records in the file
    char student_index[20];
    printf("Enter student index number: "); 
    scanf("%s", student_index); // get the student index number to delete
    student_marks output;
    student_marks updatedRecord;
    int found = 0;
    int count = 0;
    while (count < length)  // find the matching record by looping
    {
        if (strcmp(marksPtr[count].student_index, student_index) == 0)  // chack for matching student index number
        {
            found = 1;
            for (int i = count; i < length - 1; i++)    // remove the record by shifting the list 
            {
                strcpy((marksPtr + i)->student_index, (marksPtr + i + 1)->student_index);
                (marksPtr + i)->assignmt01_marks = (marksPtr + i + 1)->assignmt01_marks;
                (marksPtr + i)->assignmt02_marks = (marksPtr + i + 1)->assignmt02_marks;
                (marksPtr + i)->project_marks = (marksPtr + i + 1)->project_marks;
                (marksPtr + i)->finalExam_marks = (marksPtr + i + 1)->finalExam_marks;
            }
            length--;   // reduce the length of the list
        }
        count++;
    }

    if (found == 0)     // handle record not found 
    {
        printf("Record not found \n\n");
    }
    reWriteList(length);    // rewrite the list to the file
}

void generateData() // function to generate hundred records 
{
    student_marks dataList[100];    // create a list of 100 records
    int count = 0;
    while (count < 100)
    {
        // generate random data for each record
        strcpy(dataList[count].student_index, generateRandomIndex());   
        dataList[count].assignmt01_marks = generateRandomMarks();
        dataList[count].assignmt02_marks = generateRandomMarks();   
        dataList[count].project_marks = generateRandomMarks();
        dataList[count].finalExam_marks = generateRandomMarks();
        writeOneRecord(dataList[count]);
        count++;
    }

    printf("Successfully generated 100 records\n\n");
}

char *generateRandomIndex() // generate random index number 
{
    const char charset[] = "1234567890"; // set of characters to use
    char str1[] = "EG/2018/";   // add the prefix to the index number
    char str2[4];
    int num = 12;
    for (int i = 0; i < num; i++)  
    {
        if (i < 8)
        {
            str2[i] = str1[i];  // add the prefix to the index number
        }
        else
        {
            int key = rand() % (int)(sizeof charset - 1);   // generate random number
            str2[i] = charset[key];
        }
    }
    char *returnStr = str2; // return the generated string
    str2[num] = '\0';   // add null character to the end of the string
    return returnStr;
}

float generateRandomMarks() // generate random marks
{
    return rand() % 100 + 1;    // generate random number between 1 and 100
}
