#include <stdio.h>    // printf function
#include <stdlib.h>   // exit function
#include <errno.h>    // error handling
#include <fcntl.h>    // file control
#include <unistd.h>   // read, write, close
#include <sys/wait.h> // wait function
#include <sys/shm.h>  // shared memory functions
#include <sys/stat.h> // constraints for file permissions
#include <string.h>   // char array manipulation

typedef struct student_marks // structure definition for student marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

typedef struct analize_marks // structure definition for analize_marks
{
    float min;
    float max;
    float average;
    int numofstudent_below;
} analize_marks;



void main()
{
      key_t ky = ftok("file.txt", 78); // create a key for shared memory
    if (ky == -1)
    {
        perror("ftok error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }

    int SMID = shmget(ky, 4096, IPC_CREAT | 0666); // create shared memory
    if (SMID == -1)
    {
        perror("shmget error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }

    pid_t PID1 = fork(); // create child process 1
    if (PID1 == -1)
    {
        perror("fork error: ");
        printf("Error No: %d\n", errno);
        exit(1);
    }
    else if (PID1 == 0)
    { // Child Process C1
      
    }
    else
    {

        pid_t PID2 = fork();    // create child process 2

        if (PID2 == -1)
        {
            perror("fork error: ");
            printf("Error No: %d\n", errno);
            exit(1);
        }
        else if (PID2 == 0)
        { // Child Process C2
           
        }
        else
        {
            pid_t PID3 = fork();    // create child process 3

            if (PID3 == -1)
            {
                perror("fork error: ");
                printf("Error No: %d \n", errno);
                exit(1);
            }
            else if (PID3 == 0)
            { // Child Process C3

               
            }
            else
            {

                pid_t PID4 = fork();    // create child process 4

                if (PID4 == -1)
                {
                    perror("fork error: ");
                    printf("Error No: %d \n", errno);
                    exit(1);
                }
                else if (PID4 == 0)
                { // Child Process C4
                   
                }
                else
                { // Parent Process

                
                }
            }
        }
    }
}
